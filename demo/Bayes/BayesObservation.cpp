
#include "BayesObservation.hpp"

Bayes::BayesObservation::BayesObservation( uint32_t numContinuous, uint32_t numDiscrete )
: m_continuousValues( numContinuous )
, m_discreteValues( numDiscrete )
, m_outcome( OUTCOME_FAILURE )
{
	// Not much here
}

void Bayes::BayesObservation::setContinuousCondition( uint32_t conditionIndex, float value )
{
	if( conditionIndex > m_continuousValues.size() )
	{
		printf( "Warning: Index %d is out of bounds for continuous conditions (Max size %lu)\n", conditionIndex, m_continuousValues.size() );
		
		// Invalid index, early return
		return;
	}
	
	m_continuousValues[ conditionIndex ] = value;
}

void Bayes::BayesObservation::setDiscreteCondition( uint32_t conditionIndex, int value )
{
	if( conditionIndex > m_discreteValues.size() )
	{
		printf( "Warning: Index %d is out of bounds for discrete conditions (Max size %lu)\n", conditionIndex, m_discreteValues.size() );
		
		// Invalid index, early return
		return;
	}
	
	m_discreteValues[ conditionIndex ] = value;
}

void Bayes::BayesObservation::setOutcome( OutcomeType outcome )
{
	m_outcome = outcome;
}

void Bayes::BayesObservation::printData() const
{
	printf( "Continuous Values (%lu)\n", m_continuousValues.size() );
	for ( int i = 0; i < m_continuousValues.size(); ++i )
	{
		printf( "Value %d: %f\n", i, m_continuousValues[ i ] );
	}
	
	printf( "Discrete Values (%lu)\n", m_discreteValues.size() );
	for ( int i = 0; i < m_discreteValues.size(); ++i )
	{
		printf( "Value %d: %d\n", i, m_discreteValues[ i ] );
	}
	
	printf( "\n==============\n\n" );
}
