/**
 * Unit test for function:
 * int getCost(int card)
 *
 * Test For:
 * a valid card number between 0 and 26 is passed to the function.
 * a valid card number between 0 and 26 results in the corresponding
 * 	cost being returned
 * a non-valid card number results in -1 being returned.
 *
 * Preconditions:
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest.h"
#include "rngs.h"

/**
 * Function: unitTest1
 * Inputs: printvalue to determine printing level
 * Outputs: None
 * Description:  tests getCost() function
 */
void unitTest1(int printVal, int testIteration){

	int randomNum = 0;
	int expectedCost = 0;
	int k[] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};

	// get a random number in the range specified
	randomNum = random_number(-2, 40);

	// if the random number is a valid card set expectedCost to card value
	// else set the expected cost to -1
	if((randomNum < sizeof(k)/sizeof(int)) && randomNum >= 0)
	{
		expectedCost = k[randomNum];
	}
	else
	{
		expectedCost = -1;
	}

	// assert the generated number is equal to calculated
	assert(getCost(randomNum) == expectedCost);

	// if printing is on print out the data
	if(printVal == 1)
	{
		printf("Test: %d PASS:  Card Entered: %d, Returned Cost: %d, Expected Cost: %d\n",
				testIteration, randomNum, getCost(randomNum), expectedCost);
	}
}

void rndUnitTest1(int printVal, int testsRun){

	// loop counter, random number var and expected Cost var
	int i=0;

	if(printVal == 1)
  		printf("Testing of int getCost(int card):\n");
	/**
	 * randomly draw a card in the range and check the value against the
	 * expected value.
	 */
	for(i = 0; i <= testsRun; i++)
	{
		 unitTest1(printVal, i);
	}

	if(printVal == 1)
		printf("\n\nAll tests Completed.\n\n");

}

int main(int argc, char *argv[]){

	unsigned int seed = 9987;
	srand(seed);

	printf("\nSTARTING: getCost() (unittest1)\n");
	rndUnitTest1(1, 1000);
	printf("\nFINISHED: getCost() (unittest1)\n");
	return 0;
}
