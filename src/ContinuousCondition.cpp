
#include "ContinuousCondition.hpp"

#include <math.h>

#include "BayesAction.hpp"

Bayes::ContinuousCondition::ContinuousCondition( const std::string& conditionName )
: m_name( conditionName )
, m_sums( NUM_OUTCOMES, 0.0f )
, m_sumsSquared( NUM_OUTCOMES, 0.0f )
, m_means( NUM_OUTCOMES, 0.0 )
, m_standardDeviations( NUM_OUTCOMES, 0.0 )
{
	// Not much here
}

double Bayes::ContinuousCondition::getMeanForOutcome( OutcomeType outcome ) const
{
	return m_means[ outcome ];
}

double Bayes::ContinuousCondition::getStdDevForOutcome( OutcomeType outcome ) const
{
	return m_standardDeviations[ outcome ];
}

void Bayes::ContinuousCondition::addToSumForOutcome( OutcomeType outcome, float amount )
{
	m_sums[ outcome ] += amount;
	m_sumsSquared[ outcome ] += amount * amount;
}

void Bayes::ContinuousCondition::buildStats( int totalOutcomeCount )
{
	calculateMeans( totalOutcomeCount );
	calculateStdDevs( totalOutcomeCount );
}

void Bayes::ContinuousCondition::calculateMeans( int total )
{
	for( int i = 0; i < NUM_OUTCOMES; ++i )
	{
		m_means[ i ] = (double)m_sums[ i ] / total;
	}
}

void Bayes::ContinuousCondition::calculateStdDevs( int total )
{
	// Credit to Prof. Al Biles for this sampled standand dev calculation impl
	// Keeping track of the squared sums is a very nice trick to simplify it
	for ( int i = 0; i < NUM_OUTCOMES; ++i )
	{
		float sumSq = m_sumsSquared[ i ];
		float sum = m_sums[ i ];
		m_standardDeviations[ i ] = sqrt( ( sumSq - ( sum * sum ) / (double)total ) / ( total - 1 ) );
		
		if( m_standardDeviations[ i ] == 0.0 )
		{
			// Can't have a standard dev of 0, so default to a small number
			m_standardDeviations[ i ] = 0.0001;
		}
	}
}

void Bayes::ContinuousCondition::printData() const
{
	printf( "[Continuous Condition]\n" );
	printf( "Name: %s\n", m_name.c_str() );
	
	printf( "Sums\t | Success: %f\t | Failure: %f\n", m_sums[ OUTCOME_SUCCESS ], m_sums[ OUTCOME_FAILURE ] );
	printf( "Sq Sums\t | Success: %f | Failure: %f\n", m_sumsSquared[ OUTCOME_SUCCESS ], m_sumsSquared[ OUTCOME_FAILURE ] );
	printf( "Means\t | Success: %f\t | Failure: %f\n", m_means[ OUTCOME_SUCCESS ], m_means[ OUTCOME_FAILURE ] );
	printf( "Std Devs | Success: %f\t | Failure: %f\n", m_standardDeviations[ OUTCOME_SUCCESS ], m_standardDeviations[ OUTCOME_FAILURE ] );
	
	printf( "\n==============\n\n" );
}
