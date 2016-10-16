
#include "GolfDemo.hpp"

#include <iostream>

#include "StateFunctions.hpp"

// Array of StateFunctions corresponding to the GolfDemo::State enum
static const StateFunctions<GolfDemo> stateTable[ GolfDemo::NUM_STATES ] = {
	//Enter Function						Update Function
	{ &GolfDemo::enterIntroState,			&GolfDemo::updateIntroState },			// Intro
	{ &GolfDemo::enterOutlookInputState,	&GolfDemo::updateOutlookInputState },	// Input Outlook
	{ &GolfDemo::enterWindyInputState,		&GolfDemo::updateWindyInputState },		// Input Windy
	{ &GolfDemo::enterTempInputState,		&GolfDemo::updateTempInputState },		// Input Temperature
	{ &GolfDemo::enterHumidityInputState,	&GolfDemo::updateHumidtyInputState },	// Input Humidity
	{ &GolfDemo::enterMakeDecisionState,	&GolfDemo::updateMakeDecisionState },	// Decide
	{ &GolfDemo::enterSaveObsState,			&GolfDemo::updateSaveObsState },		// Save Observation
	{ &GolfDemo::enterSaveNegaObsState,		&GolfDemo::updateSaveNegaObsState },	// Save Nega-Observation
	{ &GolfDemo::enterTryAgainState,		&GolfDemo::updateTryAgainState }		// Try Again
};

GolfDemo::GolfDemo()
: m_decider( "Play Golf" )
, m_activeObservation()
, m_currentState( INTRO )
, m_exit( false )
{
	// Not much here
}

void GolfDemo::init()
{
	// Get the decider up and running
	initDecider();
	populateDeciderObservations();
	
	// Enter first state and begin updating
	stateTable[ m_currentState ].enter( this );
	update();
}

void GolfDemo::initDecider()
{
	// Add the appropriate conditions to the decider
	m_decider.addDiscreteCondition( "Outlook", GolfObservation::NUM_OUTLOOKS );
	m_decider.addDiscreteCondition( "Windy" );
	
	m_decider.addContinuousCondition( "Temperature" );
	m_decider.addContinuousCondition( "Humidity" );
}

void GolfDemo::changeState( State toState )
{
	m_currentState = toState;
	stateTable[ m_currentState ].enter( this );
}

void GolfDemo::update()
{
	while( !m_exit )
	{
		stateTable[ m_currentState ].update( this );
	}
}

void GolfDemo::enterIntroState()
{
	std::cout << "Welcome to the Bayesian Golf Advising Consultancy.\n";
	std::cout << "We're here to help you determine if today is a good day to tee off.\n\n";
}

void GolfDemo::updateIntroState()
{
	std::cout << "Let's begin.\n\n";
	changeState( INPUT_OUTLOOK );
}

void GolfDemo::enterOutlookInputState()
{
	std::cout << "How's the weather outside (1: Sunny, 2: Overcast, or 3: Rainy)? ";
}

void GolfDemo::updateOutlookInputState()
{
	// Read in input
	std::string inputStr;
	getline( std::cin, inputStr );
	
	// Try to convert input to an int
	int intput = std::atoi( inputStr.c_str() );
	
	// If the int is 0, convert failed
	if( intput > 0 && intput <= GolfObservation::NUM_OUTLOOKS )
	{
		// If the input was valid, save it to the observation
		m_activeObservation.setOutlook( (GolfObservation::Outlook)( intput - 1 ) );
		
		printAffirmativeMessage();
		
		// Move on to the next state
		changeState( INPUT_WINDY );
	}
	else
	{
		// If input was invalid, print and re-enter state
		std::cout << "\nUnrecognized input. Please use one of the following:\n";
		std::cout << "\t1 for Sunny\n" << "\t2 for Overcast\n" << "\t3 for Rainy\n" << "\n";
		enterOutlookInputState();
	}
}

void GolfDemo::enterWindyInputState()
{
	std::cout << "Is it windy (y/n)? ";
}

void GolfDemo::updateWindyInputState()
{
	bool response = false;
	
	if( validateBoolInput( response ) )
	{
		// Save input to the observation
		m_activeObservation.setWindy( response );
		
		printAffirmativeMessage();
		changeState( INPUT_TEMP );
	}
	else
	{
		std::cout << "\nA simple yes or no will suffice.\n\n";
		enterWindyInputState();
	}
}

void GolfDemo::enterTempInputState()
{
	std::cout << "What's the temperature outside (in degrees F)? ";
}

void GolfDemo::updateTempInputState()
{
	float temp;
	
	if( validateFloatInput( temp ) )
	{
		// Save input to the observation
		m_activeObservation.setTemperature( temp );
		
		printAffirmativeMessage();
		changeState( INPUT_HUMIDITY );
	}
	else
	{
		std::cout << "\nUnrecognized input. Try a number.\n\n";
		enterTempInputState();
	}
}

void GolfDemo::enterHumidityInputState()
{
	std::cout << "How about the humdity outside (in percent)? ";
}

void GolfDemo::updateHumidtyInputState()
{
	float humidity;
	
	if( validateFloatInput( humidity ) )
	{
		// Save input to the observation
		m_activeObservation.setHumidity( humidity );
		
		printAffirmativeMessage();
		changeState( MAKE_DECISION );
	}
	else
	{
		std::cout << "\nUnrecognized input. Try a number.\n\n";
		enterHumidityInputState();
	}
}

void GolfDemo::enterMakeDecisionState()
{
	std::cout << "Alright, time to check with Mr. Bayes...\n";
	std::cout << "Is today a good day to play golf?\n\n";
}

void GolfDemo::updateMakeDecisionState()
{
	// Make a decision and update the observation's outcome
	bool playGolf = m_decider.decide( m_activeObservation );
	m_activeObservation.setOutcome( (Bayes::OutcomeType)playGolf );
	
	// Print the decision
	if( playGolf )
	{
		std::cout << "Yeah, let's play a round!\n\n";
	}
	else
	{
		std::cout << "No, it's probably best to stay home.\n\n";
	}
	
	// Wait for input so the user has time to read the decision
	std::cout << "Press Enter to continue... ";
	std::cin.get();
	
	changeState( SAVE_OBSERVATION );
}

void GolfDemo::enterSaveObsState()
{
	// Show the user the data
	std::cout << "\nObservation:\n";
	m_activeObservation.printGolfObs();
}

void GolfDemo::updateSaveObsState()
{
	std::cout << "\nWould you like to save this observation (y/n)?: ";
	
	bool response = false;
	
	if( validateBoolInput( response ) )
	{
		if( response )
		{
			// Add the observation and rebuild the stats
			m_decider.addObservation( m_activeObservation );
			m_decider.buildStats();
			
			std::cout << "Saving observation...\n";
			
			// Move on to the try again state
			changeState( TRY_AGAIN );
		}
		else
		{
			// Maybe the user wants to save the observation
			// with the opposite outcome
			changeState( SAVE_NEGA_OBSERVATION );
		}
	}
	else
	{
		// Not re-entering the state because we don't need the obs printed again
		std::cout << "\nA simple yes or no will suffice.\n";
	}
}

void GolfDemo::enterSaveNegaObsState()
{
	std::string negaOutcome = m_activeObservation.getOutcome() ? "No" : "Yes";
	std::cout << "Would you rather save this observation as a \"" << negaOutcome << "\" to play golf instead (y/n)?: ";
}

void GolfDemo::updateSaveNegaObsState()
{
	bool response = false;
	
	if( validateBoolInput( response ) )
	{
		// If the user wants to save...
		if( response )
		{
			// Invert the observation's outcome
			Bayes::OutcomeType outcome = m_activeObservation.getOutcome() ? Bayes::OUTCOME_FAILURE : Bayes::OUTCOME_SUCCESS;
			m_activeObservation.setOutcome( outcome );
			
			// Add and build
			m_decider.addObservation( m_activeObservation );
			m_decider.buildStats();
			
			std::cout << "Saving observation...\n";
		}
		
		// Either way, move on to try again state
		changeState( TRY_AGAIN );
	}
	else
	{
		std::cout << "\nA simple yes or no will suffice.\n";
		enterSaveNegaObsState();
	}
}

void GolfDemo::enterTryAgainState()
{
	std::cout << "\nWould you like to try another observation (y/n)?: ";
}

void GolfDemo::updateTryAgainState()
{
	bool response = false;
	
	if( validateBoolInput( response ) )
	{
		// Either restart or quit
		if( response )
		{
			changeState( INTRO );
		}
		else
		{
			// Print goodbye message based on observation outcome
			if( m_activeObservation.getOutcome() )
			{
				std::cout << "\nHave a good round!\n";
			}
			else
			{
				std::cout << "\nBetter luck tomorrow.\n";
			}
			
			m_exit = true;
		}
	}
	else
	{
		std::cout << "\nA simple yes or no will suffice.\n";
		enterTryAgainState();
	}
}

bool GolfDemo::validateBoolInput( bool& output ) const
{
	// Get the input
	std::string inputStr;
	getline( std::cin, inputStr );
	
	// Handle case sensitivity
	char first = tolower( inputStr[ 0 ] );
	
	// Check if input was y or n
	if( first == 'y' )
	{
		output = true;
		return true;
	}
	else if( first == 'n' )
	{
		output = false;
		return true;
	}
	else
	{
		// Failed to validate
		return false;
	}
}

bool GolfDemo::validateFloatInput( float& output ) const
{
	// Get the input
	std::string inputStr;
	getline( std::cin, inputStr );
	
	// Convert to float
	output = (float)std::atof( inputStr.c_str() );
	
	// Failed conversion will return 0.0, but 0.0 could also be input...
	return ( output != 0.0 || ( output == 0.0 && inputStr[ 0 ] == '0' ) );
}
