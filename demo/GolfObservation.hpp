
#ifndef GolfObservation_hpp
#define GolfObservation_hpp

#include "BayesObservation.hpp"

/*
 * Derived class of BayesObservation
 * Provides a specialized Observation interface for GolfDemo
 *
 * More or less just allows conditions to be set by name more conveniently
 */
class GolfObservation : public Bayes::BayesObservation
{
public:
	enum Outlook
	{
		SUNNY,
		OVERCAST,
		RAINY,
		NUM_OUTLOOKS
	};
	
	GolfObservation();
	
	// Calls BayesObservation::setDiscreteCondition for appropriate index
	void setOutlook( Outlook outlook );
	void setWindy( bool isWindy );
	
	// Calls BayesObservation::setContinuousCondition for appropriate index
	void setTemperature( float temp );
	void setHumidity( float humidity );
	
	// Prints out data formatted for GolfDemo
	void printGolfObs() const;
	
private:
	// Enums for constants
	enum DiscreteCondIndices
	{
		OUTLOOK_INDEX,
		WINDY_INDEX,
		NUM_DISCRETE
	};
	
	enum ContinuousCondIndices
	{
		TEMPERATURE_INDEX,
		HUMIDITY_INDEX,
		NUM_CONTINUOUS
	};
};

#endif /* GolfObservation_hpp */
