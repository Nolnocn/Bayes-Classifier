
#ifndef GolfDemo_hpp
#define GolfDemo_hpp

#include <string>

#include "BayesDecider.hpp"
#include "GolfObservation.hpp"

/*
 * Class representing an interactive demo for the BayesDecider
 * Handles deciding based on user input
 * Based on Prof. Al Biles' original Golf Demo 
 */
class GolfDemo
{
public:
	enum State
	{
		INTRO,
		INPUT_OUTLOOK,
		INPUT_WINDY,
		INPUT_TEMP,
		INPUT_HUMIDITY,
		MAKE_DECISION,
		SAVE_OBSERVATION,
		SAVE_NEGA_OBSERVATION,
		TRY_AGAIN,
		NUM_STATES
	};
	
	GolfDemo();
	
	void init();
	
	// State functions
	void enterIntroState();
	void updateIntroState();
	
	void enterOutlookInputState();
	void updateOutlookInputState();
	
	void enterWindyInputState();
	void updateWindyInputState();
	
	void enterTempInputState();
	void updateTempInputState();
	
	void enterHumidityInputState();
	void updateHumidtyInputState();
	
	void enterMakeDecisionState();
	void updateMakeDecisionState();
	
	void enterSaveObsState();
	void updateSaveObsState();
	
	void enterSaveNegaObsState();
	void updateSaveNegaObsState();
	
	void enterTryAgainState();
	void updateTryAgainState();
	
private:
	void initDecider();
	void populateDeciderObservations();
	
	void changeState( State toState );
	void update();
	
	// Util functions
	bool validateBoolInput( bool& output ) const;
	bool validateFloatInput( float& output ) const;
	void printAffirmativeMessage() const;
	
	// Data members
	Bayes::BayesDecider m_decider;
	GolfObservation m_activeObservation;
	State m_currentState = NUM_STATES;
	bool m_exit;
};

#endif /* GolfDemo_hpp */
