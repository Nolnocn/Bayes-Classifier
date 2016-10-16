
#include "GolfDemo.hpp"

/*
 * Function definition for GolfDemo::populateDeciderObservations,
 * plus a util function to help out
 */

// Convenience function for adding observations to a decider
static void addObservation( Bayes::BayesDecider& decider,
						    GolfObservation::Outlook outlook,
						    bool windy, float temp, float humidity,
						    Bayes::OutcomeType outcome  )
{
	GolfObservation obs;
	
	obs.setOutlook( outlook );
	obs.setWindy( windy );
	obs.setTemperature( temp );
	obs.setHumidity( humidity );
	obs.setOutcome( outcome );
	
	decider.addObservation( obs );
}

void GolfDemo::populateDeciderObservations()
{
	// Data from Prof. Biles' original demo
	addObservation( m_decider, GolfObservation::SUNNY,	false, 85, 85, Bayes::OUTCOME_FAILURE );
	addObservation( m_decider, GolfObservation::SUNNY, true, 80, 90, Bayes::OUTCOME_FAILURE );
	addObservation( m_decider, GolfObservation::OVERCAST, false, 83, 86, Bayes::OUTCOME_SUCCESS );
	addObservation( m_decider, GolfObservation::RAINY, false, 70, 96, Bayes::OUTCOME_SUCCESS );
	addObservation( m_decider, GolfObservation::RAINY, false, 68, 80, Bayes::OUTCOME_SUCCESS );
	addObservation( m_decider, GolfObservation::RAINY, true, 65, 70, Bayes::OUTCOME_FAILURE );
	addObservation( m_decider, GolfObservation::OVERCAST, true, 64, 65, Bayes::OUTCOME_SUCCESS );
	addObservation( m_decider, GolfObservation::SUNNY, false, 72, 95, Bayes::OUTCOME_FAILURE );
	addObservation( m_decider, GolfObservation::SUNNY, false, 69, 70, Bayes::OUTCOME_SUCCESS );
	addObservation( m_decider, GolfObservation::SUNNY, false, 75, 80, Bayes::OUTCOME_SUCCESS );
	addObservation( m_decider, GolfObservation::SUNNY, true, 75, 70, Bayes::OUTCOME_SUCCESS );
	addObservation( m_decider, GolfObservation::OVERCAST, true, 72, 90, Bayes::OUTCOME_SUCCESS );
	addObservation( m_decider, GolfObservation::OVERCAST, false, 81, 75, Bayes::OUTCOME_SUCCESS );
	addObservation( m_decider, GolfObservation::RAINY, true, 71, 91, Bayes::OUTCOME_FAILURE );
	
	m_decider.buildStats();
}
