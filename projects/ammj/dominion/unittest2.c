/**
 * Unit test for function:
 * int updateCoins(int player, struct gameState *state, int bonus)
 *
 * Test For:
 *
 * Preconditions:
 * player is a valid player
 * gameState has useable data that has reasonably expected values
 * bonus is an integer
 * player hand is a mix of coins, coins and other cards, or just other cards
 * handCount for the player correctly identifies the number of cards in the hand
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion_cards.h"
#include "unittest.h"
#include "rngs.h"

/**
 * Function:  printBoundary
 * Inputs:  lowBound, highBound, mixed
 * Outputs: none
 * Description: prints boundary results provided in inputs
 */
void printBoundary(int lowBound, int highBound, int mixed){

	printf("Number of tests with no coin cards: %d\n", lowBound);
	printf("Number of tests with all coin cards: %d\n", highBound);
	printf("Number of tests with mixed cards: %d\n", mixed);

}

/**
 * Function:  unittest2
 * Inputs:  printVal, seed, results
 * Outputs: none
 * Description: tests updateCoins() function in dominion.c
 */
void unitTest2(int printVal, int seed, struct results *results)
{
	int handVal = 0;
	int i, r, cardNum;

	int handCount = random_number(0, MAX_HAND);;
	int numPlayers = random_number(2, MAX_PLAYERS);
	int currentPlayer = random_number(1, numPlayers) - 1;
	int bonus = random_number(-5, 20);
	int copperCards = 0, silverCards = 0, goldCards = 0;

	// setup the kingdom cards available
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
					 sea_hag, tribute, smithy};

	// setup the struct for the control and active Games
	struct gameState *controlGame = newGame();
	struct gameState *activeGame = newGame();

	// initialize the activeGame
	initializeGame(numPlayers, k, seed, activeGame);

	// set the hand to equal something we want and set an active player
	activeGame->handCount[currentPlayer] = handCount;
	activeGame->whoseTurn = currentPlayer;

	// load the hand with randomly generated valid cards
	for(i=0; i < handCount; i++)
	{
		cardNum = random_number(0, treasure_map);

		if(cardNum == copper)
		{
			handVal++;
			copperCards++;
		}
		if(cardNum == silver)
		{
			handVal = handVal + 2;
			silverCards++;
		}
		if(cardNum == gold)
		{
			handVal = handVal + 3;
			goldCards++;
		}

		// put the card into the activeGame
		activeGame->hand[currentPlayer][i] = cardNum;

	}

	//copy the values from the activeGame into the controlGame
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	// set the controlGame coin value
	controlGame->coins = handVal + bonus;

	// run updateCoins on activeGame
	r = updateCoins(currentPlayer, activeGame, bonus);
	assert(r == 0);

	// check if the active and control game have the same values
	// if first assert passes but second doesn't
	// another value has been changed that shouldn't have
	assert(memcmp(&controlGame->coins, &activeGame->coins, sizeof(int)) == 0);
	assert(memcmp(controlGame, activeGame, sizeof(struct gameState)) == 0);

	// update the values for the metrics
	results->testsPassed++;

	if(copperCards + silverCards + goldCards == 0)
		results->lowBound++;
	else if(copperCards + silverCards + goldCards == handCount)
		results->highBound++;
	else
		results->mixedBound++;

	// clean up memory
	free(controlGame);
	free(activeGame);

}

/**
 * Function:  rndUnitTest2
 * Inputs:  testsRun, seed, printVal
 * Outputs: none
 * Description: iterator for randomTests using unittest2
 */
void rndUnitTest2(int testsRun, int seed, int printVal){

	// containers for results
	struct results *results = declResults();
	int i;

	// run the random tests
	for(i = 0; i < testsRun; i++)
	{
		results->testNum++;
		unitTest2(printVal, seed, results);
	}

	// print results if requested
	if(printVal == 1)
	{
		printBoundary(results->lowBound, results->highBound, results->mixedBound);
		printResults(results->testsPassed, results->testsFailed);
	}

	free(results);

}

int main(int argc, char *argv[]){

	int seed = 9987;
	int testsRun = 1000;
	int printVal = 1;

	srand(seed);

	printf("\nSTARTING: updateCoins() (unittest2)\n");
	rndUnitTest2(testsRun, seed, printVal);
	printf("\nFINISHED: updateCoins() (unittest2)\n");

	return 0;
}

