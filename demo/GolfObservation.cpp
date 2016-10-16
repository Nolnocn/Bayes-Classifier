
#include "GolfObservation.hpp"

#include <string>

GolfObservation::GolfObservation() : Bayes::BayesObservation( NUM_CONTINUOUS, NUM_DISCRETE )
{
	// Not much here
}

void GolfObservation::setOutlook( Outlook outlook )
{
	setDiscreteCondition( OUTLOOK_INDEX, outlook );
}

void GolfObservation::setWindy( bool isWindy )
{
	setDiscreteCondition( WINDY_INDEX, isWindy );
}

void GolfObservation::setTemperature( float temp )
{
	setContinuousCondition( TEMPERATURE_INDEX, temp );
}

void GolfObservation::setHumidity( float humidity )
{
	setContinuousCondition( HUMIDITY_INDEX, humidity );
}

void GolfObservation::printGolfObs() const
{
	const std::vector<int>& discValues = getDiscreteValues();
	
	Outlook outlook = (Outlook)discValues[ OUTLOOK_INDEX ];
	
	// Enum to string
	std::string outlookStr;
	switch( outlook )
	{
	case SUNNY:
		outlookStr = "Sunny";
		break;
	case OVERCAST:
		outlookStr = "Overcast";
		break;
	case RAINY:
		outlookStr = "Rainy";
		break;
	default:
		outlookStr = "ERROR";
		break;
	}
	
	printf( "\tOutlook: %s\n", outlookStr.c_str() );
	
	bool windy = discValues[ WINDY_INDEX ];
	printf( "\tWindy: %s\n", windy ? "Yes" : "No" );
	
	const std::vector<float>& contValues = getContinuousValues();
	
	printf( "\tTemperature: %.1f\n", contValues[ TEMPERATURE_INDEX ] );
	printf( "\tHumidity: %.1f\n", contValues[ HUMIDITY_INDEX ] );
	
	printf( "\tPlay Golf: %s\n", getOutcome() ? "Yes" : "No" );
}
