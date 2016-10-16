
#include "BayesAction.hpp"

Bayes::BayesAction::BayesAction( const std::string& name )
: m_name( name )
, m_counts()
, m_proportions()
{
	// Not much here
}

int Bayes::BayesAction::getCountForOutcome( OutcomeType outcome ) const
{
	return m_counts[ outcome ];
}

double Bayes::BayesAction::getProportionForOutcome( OutcomeType outcome ) const
{
	return m_proportions[ outcome ];
}

int Bayes::BayesAction::getTotalOutcomeCount() const
{
	return ( m_counts[ OUTCOME_FAILURE ] + m_counts[ OUTCOME_SUCCESS ] );
}

void Bayes::BayesAction::incremementOutcomeCount( OutcomeType outcome )
{
	++m_counts[ outcome ];
}

void Bayes::BayesAction::calculateProportions()
{
	int total = getTotalOutcomeCount();
	
	m_proportions[ OUTCOME_FAILURE ] = (double)m_counts[ OUTCOME_FAILURE ] / total;
	
	if( m_proportions[ OUTCOME_FAILURE ] == 0.0 )
	{
		// If the prop is 0, use a small number instead
		m_proportions[ OUTCOME_FAILURE ] = 0.0001;
	}
	
	m_proportions[ OUTCOME_SUCCESS ] = (double)m_counts[ OUTCOME_SUCCESS ] / total;
	
	if( m_proportions[ OUTCOME_SUCCESS ] == 0.0 )
	{
		// If the prop is 0, use a small number instead
		m_proportions[ OUTCOME_SUCCESS ] = 0.0001;
	}
}

void Bayes::BayesAction::printData() const
{
	printf( "[BayesAction]\n" );
	printf( "Name: %s\n", m_name.c_str() );
	printf( "Counts\t | Success: %d | Failure: %d\n", m_counts[ OUTCOME_SUCCESS ], m_counts[ OUTCOME_FAILURE ] );
	printf( "Proportions | Success: %f | Failure: %f\n", m_proportions[ OUTCOME_SUCCESS ], m_proportions[ OUTCOME_FAILURE ] );
	printf( "\n==============\n" );
}
