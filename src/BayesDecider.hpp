
#ifndef BayesDecider_hpp
#define BayesDecider_hpp

#include <string>

#include "BayesOutcomeDefs.h"

namespace Bayes
{
	// Forward dec
	struct BayesObservation;
	
	/*
	 * Class used to store conditions and decide on observations
	 *
	 * Only this class and BayesObservation should be used
	 * outside the Bayes namespace
	 */
	class BayesDecider
	{
	public:
		BayesDecider( const std::string& actionName );
		~BayesDecider();
		
		// Public interface to add conditions to the decider
		// TODO: "Lock" decider before use so new conditions cannot be added
		void addContinuousCondition( const std::string& conditionName );
		void addDiscreteCondition( const std::string& conditionName, uint32_t numValues = 2 );
		
		// Adds an observation to the saved observations
		void addObservation( const BayesObservation& obs );
		
		// Builds data for conditions from observations
		void buildStats();
		
		// Does some Bayesian magic with the given observation
		// and returns whether or not the action should be performed
		bool decide( const BayesObservation& obs ) const;
		
		// Prints data from conditions and action to console
		void printData() const;
		
		// Prints all saved observations to the console
		void printObservations() const;
		
	private:
		struct Impl; // Using the PIML idiom to avoid including every other Bayes class
		
		static const double SQRT2PI; // constant cached for convenience
		
		// Internal functions used to perform aforementioned Bayesian magic
		double calculateBayes( const BayesObservation& obs, OutcomeType outcome ) const;
		double calculateGaussianDistribution( double mean, double stdDev, int x ) const;
		
		// Checks that an observation has the same number of values as there are conditions
		bool validateObservation( const BayesObservation& obs ) const;
		
		Impl* pImpl;
	};
}

#endif /* BayesDecider_hpp */
