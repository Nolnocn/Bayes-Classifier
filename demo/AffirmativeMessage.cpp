
#include "GolfDemo.hpp"

#include <iostream>

/*
 * Function definition for GolfDemo::printAffirmativeMessage,
 * plus some static variables to help out.
 *
 * Kind of unneccessary, but totally worth it.
 */

static const int NUM_MESSAGES = 5;

static const std::string MESSAGES[ NUM_MESSAGES ] =
{
	"Okay.",
	"Gotcha.",
	"Interesting.",
	"Hmm...",
	"Good to know."
};

void GolfDemo::printAffirmativeMessage() const
{
	int random = rand() % NUM_MESSAGES;
	std::cout << "\n" << MESSAGES[ random ] << "\n\n";
}
