
#ifndef ContinuousCondition_hpp
#define ContinuousCondition_hpp

#include <string>
#include <vector>

#include "BayesOutcomeDefs.h"

namespace Bayes
{
	// Forward dec
	class BayesAction;
	
	/*
	 * Class representing a single continuous condition of a BayesDecider
	 * Stores data for values that fall into a range
	 */
	class ContinuousCondition
	{
	public:
		ContinuousCondition( const std::string& name );
		
		// Accessors for data members needed by BayesDecider
		double getMeanForOutcome( OutcomeType outcome ) const;
		double getStdDevForOutcome( OutcomeType outcome ) const;
		
		// Increases the sum for a given outcome by a given amount
		// (Also increases squared sum by squared amount)
		void addToSumForOutcome( OutcomeType outcome, float amount );
		
		// Calculates mean and standard deviation
		// Used after sums have been set
		void buildStats( int totalOutcomeCount );
		
		// Prints formatted member data to the console
		void printData() const;
		
	private:
		void calculateMeans( int total );
		void calculateStdDevs( int total );
		
		std::string m_name; // Primarily for debug convenience
		
		// Data members
		std::vector<float> m_sums;
		std::vector<float> m_sumsSquared;
		std::vector<double> m_means;
		std::vector<double> m_standardDeviations;
	};
}

#endif /* ContinuousCondition_hpp */
