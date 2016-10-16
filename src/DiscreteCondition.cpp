
#include "DiscreteCondition.hpp"

#include "BayesAction.hpp"

Bayes::DiscreteCondition::DiscreteCondition( const std::string& name, uint32_t numDiscreteValues /*= 2*/ )
: m_numDiscreteValues( numDiscreteValues )
, m_name( name )
, m_counts( numDiscreteValues, std::vector<int>( NUM_OUTCOMES, 0 ) )
, m_proportions( numDiscreteValues, std::vector<double>( NUM_OUTCOMES ) )
{
	// Some stuff here!
	
	// Initialize proportions (100% success by default)
	for( int i = 0; i < m_numDiscreteValues; ++i )
	{
		m_proportions[ i ][ OUTCOME_FAILURE ] = 0.0;
		m_proportions[ i ][ OUTCOME_SUCCESS ] = 1.0;
	}
}

int Bayes::DiscreteCondition::getOutcomeCountForValue( int discreteValue, Bayes::OutcomeType outcome ) const
{
	if( !validateDiscreteValue( discreteValue ) )
	{
		printf( "Invalid value %d provided! [Range: 0 to %d]", discreteValue, m_numDiscreteValues );
		printf( "Returning 0" );
		return 0;
	}
	
	return m_counts[ discreteValue ][ outcome ];
}

double Bayes::DiscreteCondition::getOutcomeProportionForValue( int discreteValue, OutcomeType outcome ) const
{
	if( !validateDiscreteValue( discreteValue ) )
	{
		printf( "Invalid value %d provided! [Range: 0 to %d]", discreteValue, m_numDiscreteValues );
		printf( "Returning 0" );
		return 0.0;
	}
	
	return m_proportions[ discreteValue ][ outcome ];
}

void Bayes::DiscreteCondition::incrementOutcomeForValue( int discreteValue, OutcomeType outcome )
{
	if( !validateDiscreteValue( discreteValue ) )
	{
		printf( "Invalid value %d provided! [Range: 0 to %d]", discreteValue, m_numDiscreteValues );
		printf( "Bailing increment!" );
		return;
	}
	
	++m_counts[ discreteValue ][ outcome ];
}

void Bayes::DiscreteCondition::calculateProportions( const Bayes::BayesAction& action )
{
	// For each discrete value...
	for (int iValue = 0; iValue < m_numDiscreteValues; ++iValue )
	{
		// For each outcome...
		for( int iOutcome = 0; iOutcome < NUM_OUTCOMES; ++iOutcome )
		{
			// Calculate the proportion
			int actionOutcomeCount = action.getCountForOutcome( (OutcomeType)iOutcome );
			
			if( actionOutcomeCount == 0 )
			{
				// Can't divide by zero, so just use a small number instead
				m_proportions[ iValue ][ iOutcome ] = 0.0001;
				break;
			}
			else if ( m_counts[ iValue ][ iOutcome ] == 0 )
			{
				// Shouldn't have a proportion of zero,
				// use 1/10 the size of a proportion for a count of 1
				m_proportions[ iValue ][ iOutcome ] = 0.1 / actionOutcomeCount;
			}
			else
			{
				// Calculate % that this value succeeds/fails out of the total # of successes/failures
				m_proportions[ iValue ][ iOutcome ] = (double)m_counts[ iValue ][ iOutcome ] / actionOutcomeCount;
			}
		}
	}
}

bool Bayes::DiscreteCondition::validateDiscreteValue( int value ) const
{
	return ( ( value >= 0 ) && ( value < m_numDiscreteValues ) );
}

void Bayes::DiscreteCondition::printData() const
{
	printf( "[Discrete Condition]\n" );
	printf( "Name: %s\n", m_name.c_str() );
	
	printf( "Counts (%d)\n", m_numDiscreteValues );
	for ( int i = 0; i < m_numDiscreteValues; ++i)
	{
		printf( "Value %d | Success: %d | Failure: %d\n", i, m_counts[ i ][ OUTCOME_SUCCESS ], m_counts[ i ][ OUTCOME_FAILURE ] );
	}
	
	printf( "Proportions (%d)\n", m_numDiscreteValues );
	for ( int i = 0; i < m_numDiscreteValues; ++i)
	{
		printf( "Value %d | Success: %f | Failure: %f\n", i, m_proportions[ i ][ OUTCOME_SUCCESS ], m_proportions[ i ][ OUTCOME_FAILURE ] );
	}
	
	printf( "\n==============\n\n" );
}
