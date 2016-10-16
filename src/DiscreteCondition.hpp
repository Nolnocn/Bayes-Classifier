
#ifndef BayesDiscreteCondition_hpp
#define BayesDiscreteCondition_hpp

#include <string>
#include <vector>

#include "BayesOutcomeDefs.h"

namespace Bayes
{
	// Forward dec
	class BayesAction;
	
	/*
	 * Class representing a single discrete condition of a BayesDecider
	 * Stores data for values that are... discrete
	 */
	class DiscreteCondition
	{
	public:
		DiscreteCondition( const std::string& conditionName, uint32_t numDiscreteValues = 2 );
		
		// Accessors for data members
		int getNumValues() const { return m_numDiscreteValues; };
		int getOutcomeCountForValue( int discreteValue, OutcomeType outcome ) const;
		double getOutcomeProportionForValue( int discreteValue, OutcomeType outcome ) const;
		
		void incrementOutcomeForValue( int discreteValue, OutcomeType outcome );
		
		// Calculates the proportions of each value for each outcome
		// Used after counts have been incremented
		// Passed a BayesAction ref to get the total count for each outcome
		void calculateProportions( const BayesAction& action );
		
		// Prints formatted member data to the console
		void printData() const;
		
	private:
		// Typedefs to simplify 2d vectors
		typedef std::vector<std::vector<int>> OutcomeCounts;
		typedef std::vector<std::vector<double>> OutcomeProportions;
		
		bool validateDiscreteValue( int value ) const;
		
		int m_numDiscreteValues;
		
		std::string m_name; // Primarily for debug convenience
		
		// Data members
		OutcomeCounts m_counts;
		OutcomeProportions m_proportions;
	};
}

#endif /* BayesDiscreteCondition_hpp */
