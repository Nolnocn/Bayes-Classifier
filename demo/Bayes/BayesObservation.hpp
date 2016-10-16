
#ifndef BayesObservation_hpp
#define BayesObservation_hpp

#include <vector>

#include "BayesOutcomeDefs.h"

namespace Bayes
{
	/*
	 * Data container class for values of each condition of a BayesDecider
	 * Used to keep track of data for a decision and store result in decider
	 */
	class BayesObservation
	{
	public:
		BayesObservation( uint32_t numContinuous, uint32_t numDiscrete );
		
		// Accessors for data members
		const std::vector<float>& getContinuousValues() const { return m_continuousValues; };
		const std::vector<int>& getDiscreteValues() const { return m_discreteValues; };
		OutcomeType getOutcome() const { return m_outcome; };
		
		// Setters for data members
		void setContinuousCondition( uint32_t conditionIndex, float value );
		void setDiscreteCondition( uint32_t conditionIndex, int value );
		void setOutcome( OutcomeType outcome );
		
		// Prints formatted member data to the console
		void printData() const;
		
	private:
		// Data members
		std::vector<float> m_continuousValues;
		std::vector<int> m_discreteValues;
		OutcomeType m_outcome;
	};
}

#endif /* BayesObservation_hpp */
