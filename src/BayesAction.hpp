
#ifndef BayesAction_hpp
#define BayesAction_hpp

#include <string>

#include "BayesOutcomeDefs.h"

namespace Bayes
{
	/*
	 * Class containing the counts & proportions for the
	 * outcome action (do or do not) of a BayesDecider
	 */
	class BayesAction
	{
	public:
		BayesAction( const std::string& name );
		
		// Accessors for counts/proportions
		int getCountForOutcome( OutcomeType outcome ) const;
		double getProportionForOutcome( OutcomeType outcome ) const;
		int getTotalOutcomeCount() const;
		
		// Increases the count for the given outcome type
		void incremementOutcomeCount( OutcomeType outcome );
		
		// Calculates the proportions of each outcome
		// Used after counts have been incremented
		void calculateProportions();
		
		// Prints formatted member data to the console
		void printData() const;
		
	private:
		std::string m_name; // Primarily for debug convenience
		
		// Data members
		int m_counts[ NUM_OUTCOMES ];
		double m_proportions[ NUM_OUTCOMES ];
	};
}

#endif /* BayesAction_hpp */
