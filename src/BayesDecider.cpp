
#include "BayesDecider.hpp"

#include <math.h>
#include <vector>

#include "BayesAction.hpp"
#include "BayesObservation.hpp"
#include "ContinuousCondition.hpp"
#include "DiscreteCondition.hpp"

const double Bayes::BayesDecider::SQRT2PI = sqrt( 2.0 * M_PI );

/*
 * BayesDecider Impl Definition
 * Data container for BayesDecider
 */
struct Bayes::BayesDecider::Impl
{
	Impl( const std::string& actionName )
	: action( actionName )
	, continuousConditions()
	, discreteconditions()
	, observations()
	{
		// Not much here
	}
	
	// Data members
	BayesAction action;
	std::vector<ContinuousCondition> continuousConditions;
	std::vector<DiscreteCondition> discreteconditions;
	std::vector<BayesObservation> observations;
};

Bayes::BayesDecider::BayesDecider( const std::string& actionName )
: pImpl( new Impl( actionName ) )
{
	// Not much here either
}

Bayes::BayesDecider::~BayesDecider()
{
	delete pImpl;
}

void Bayes::BayesDecider::addContinuousCondition( const std::string& conditionName )
{
	pImpl->continuousConditions.push_back( ContinuousCondition( conditionName ) );
}

void Bayes::BayesDecider::addDiscreteCondition( const std::string& conditionName, uint32_t numValues /*= 2*/ )
{
	if( numValues < NUM_OUTCOMES )
	{
		// A discrete condition should probably have more than one value
		printf( "Warning: Discrete condition %s has less than %d values.\n", conditionName.c_str(), NUM_OUTCOMES );
	}
	
	pImpl->discreteconditions.push_back( DiscreteCondition( conditionName, numValues ) );
}

void Bayes::BayesDecider::addObservation( const BayesObservation& obs )
{
	if( !validateObservation( obs ) )
	{
		printf( "Warning: Observation not valid!\n" );
		
		// Invalid observation, early return
		return;
	}
	
	pImpl->observations.push_back( obs );
}

void Bayes::BayesDecider::buildStats()
{
	size_t numCont = pImpl->continuousConditions.size();
	size_t numDisc = pImpl->discreteconditions.size();
	
	// Iterate through observations,
	// increase counts/sums for conditions & action
	for( BayesObservation obs : pImpl->observations )
	{
		OutcomeType outcome = obs.getOutcome();
		
		const std::vector<float>& contValues = obs.getContinuousValues();
		const std::vector<int>& discValues = obs.getDiscreteValues();
		
		for( int iContVal = 0; iContVal < numCont; ++iContVal )
		{
			float amt = contValues[ iContVal ];
			pImpl->continuousConditions[ iContVal ].addToSumForOutcome( outcome, amt );
		}
		
		for( int iDiscVal = 0; iDiscVal < numDisc; ++iDiscVal )
		{
			int val = discValues[ iDiscVal ];
			pImpl->discreteconditions[ iDiscVal ].incrementOutcomeForValue( val, outcome );
		}
		
		pImpl->action.incremementOutcomeCount( outcome );
	}
	
	// Calculate means & standard deviations for each continuous conditions
	int totalOutcomeCount = pImpl->action.getTotalOutcomeCount();
	for( int iContVal = 0; iContVal < numCont; ++iContVal )
	{
		pImpl->continuousConditions[ iContVal ].buildStats( totalOutcomeCount );
	}
	
	// Calculate proportions for each discrete conditions
	for( int iDiscVal = 0; iDiscVal < numDisc; ++iDiscVal )
	{
		pImpl->discreteconditions[ iDiscVal ].calculateProportions( pImpl->action );
	}
	
	pImpl->action.calculateProportions();
}

bool Bayes::BayesDecider::decide( const BayesObservation& obs ) const
{
	if( !validateObservation( obs ) )
	{
		printf( "Warning: Observation not valid!\n" );
		printf( "Returning false.\n" );
		
		// Can't decide on invalid observation
		return false;
	}
	
	double outcomeYes = calculateBayes( obs, OUTCOME_SUCCESS );
	double outcomeNo = calculateBayes( obs, OUTCOME_FAILURE );
	
	return ( outcomeYes > outcomeNo );
}

double Bayes::BayesDecider::calculateBayes( const BayesObservation& obs, OutcomeType outcome ) const
{
	double like = 1.0;
	
	size_t numCont = pImpl->continuousConditions.size();
	size_t numDisc = pImpl->discreteconditions.size();
	
	const std::vector<float>& contValues = obs.getContinuousValues();
	const std::vector<int>& discValues = obs.getDiscreteValues();
	
	// Multiply the like percentage by the proportion of the given outcome for each discrete condition
	for( int i = 0; i < numDisc; ++i )
	{
		like *= pImpl->discreteconditions[ i ].getOutcomeProportionForValue( discValues[ i ], outcome );
	}
	
	// Multiply the like percentage by the normal distribution of the given outcome for each continuous condition
	// This is where most of that Bayesian magic is
	for( int i = 0; i < numCont; ++i )
	{
		double mean = pImpl->continuousConditions[ i ].getMeanForOutcome( outcome );
		double stdDev = pImpl->continuousConditions[ i ].getStdDevForOutcome( outcome );
		
		like *= calculateGaussianDistribution( mean, stdDev, contValues[ i ] );
	}
	
	like *= pImpl->action.getProportionForOutcome( outcome );
	return like;
}

double Bayes::BayesDecider::calculateGaussianDistribution( double mean, double stdDev, int x ) const
{
	// Credit to Prof. Al Biles for this normal distribution calculation impl
	double xMinusMean = x - mean;
	double e = exp( -1.0 * xMinusMean * xMinusMean / ( 2.0 * stdDev * stdDev ) ); // e^( -( x - mean )^2 / ( 2 * variance ) )
	
	return ( e / ( stdDev * SQRT2PI ) );
}

bool Bayes::BayesDecider::validateObservation(const Bayes::BayesObservation &obs) const
{
	bool sameContCount = ( obs.getContinuousValues().size() == pImpl->continuousConditions.size() );
	bool sameDiscCount = ( obs.getDiscreteValues().size() == pImpl->discreteconditions.size() );
	bool outcomeInRange = ( obs.getOutcome() < NUM_OUTCOMES );
	
	return ( sameContCount && sameDiscCount && outcomeInRange );
}

void Bayes::BayesDecider::printData() const
{
	for( ContinuousCondition cont : pImpl->continuousConditions )
	{
		cont.printData();
	}
	
	for( DiscreteCondition disc : pImpl->discreteconditions )
	{
		disc.printData();
	}
	
	pImpl->action.printData();
}

void Bayes::BayesDecider::printObservations() const
{
	size_t numObs = pImpl->observations.size();
	printf( "[Observations %zu]\n", numObs );
	for ( int i = 0; i < numObs; ++i )
	{
		printf( "[Observation %d]\n", i );
		pImpl->observations[ i ].printData();
	}
}
