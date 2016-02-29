/**
 * Unit test for function:
 * int shuffle(int player, struct gameState *state)
 *
 * Test For:
 *    if more than one card in the deck:
 *		deck is not the same as it was prior
 *		deckCount has not changed
 *		card distribution has not changed (5 coppers before, 5 coppers now)
 *		check all other values in the struct have not been effected
 *
 * Preconditions:
 * player is a valid player
 * gameState has useable data that has reasonably expected values
 * deck is a mix of cards
 * deckCount represents a valid number of cards in the deck
 *
 * PostConditions:
 *  the current player's deck is shuffled
 *  the current player's deck has all the same cards
 *  no other decks are shuffled and no other values have changed
 *  if there is are no cards in the deck shuffle returns -1 else 0
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

	printf("Number of tests with 0 cards in deck: %d\n", lowBound);
	printf("Number of tests with MAX cards in deck: %d\n", highBound);
	printf("Number of tests with mixed cards: %d\n", mixed);

}

/**
 * Function:  unittest3
 * Inputs:  printVal, seed, results
 * Outputs: none
 * Description: tests shuffle() function in dominion.c
 */
void unitTest3(int printVal, int seed, struct results *result){

  int cardNum;
  int testShuffle = 0;

  int deckCount = random_number(-5, MAX_DECK);
  int numPlayers = random_number(2, MAX_PLAYERS);
  int currentPlayer = random_number(1, numPlayers) - 1;

  int i = 0, r = 0;

  // values to hold pre and post card frequency count
  int preCount[treasure_map];
  int postCount[treasure_map];
	memset(preCount, 0, sizeof(preCount));
	memset(postCount, 0, sizeof(postCount));

	// setup the kingdom cards available
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
					 sea_hag, tribute, smithy};

	// setup the struct for the control and active Games
	struct gameState *controlGame = newGame();
	struct gameState *activeGame = newGame();
	activeGame = newGame();
	initializeGame(numPlayers, k, seed, activeGame);

	activeGame->deckCount[currentPlayer] = deckCount;
	activeGame->whoseTurn = currentPlayer;

	// load the deck with randomly generated valid cards
	for(i=0; i < deckCount; i++)
	{
		cardNum = random_number(0, treasure_map);

		// load the pre test card frequencies
		preCount[cardNum] = preCount[cardNum] + 1;

		// put the card into the activeGame
		activeGame->deck[currentPlayer][i] = cardNum;

	}

	// calculate the boundary metric
	if(deckCount == 0)
		result->lowBound++;
	else if(deckCount == 500)
		result->highBound++;
	else
		result->mixedBound++;

	//copy the values from the activeGame into the controlGame
	controlGame = newGame();
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	/************* RUN THE FUNCTION ***********************/
	r = shuffle(currentPlayer, activeGame);

	// load the card frequency for the postCount of the active Game
	for(i = 0; i < activeGame->deckCount[currentPlayer]; i++){
		cardNum = activeGame->deck[currentPlayer][i];
		postCount[cardNum] = postCount[cardNum] + 1;
	}

	// the cards should not be in the same order unless there is only 1 card
	// if they are the same this could be coincidence so we will call it a
	// soft fail and print it out so we can verify frequency
	testShuffle = memcmp(controlGame->deck[currentPlayer], activeGame->deck[currentPlayer], sizeof(activeGame->deck[currentPlayer]));

	if(deckCount <= 1)
		assert(testShuffle == 0);
	else
	{
		if(testShuffle == 0){
			printf("Test %d: Soft-Fail: DeckCount: %d, ", result->testNum, deckCount);
			printf("Pre Hand: ");
			for(i=0; i < deckCount; i++){
				printf("%d,",controlGame->deck[currentPlayer][i]);
			}
			printf(" Shuffled Hand: ");
			for(i=0; i < deckCount; i++){
				printf("%d,",activeGame->deck[currentPlayer][i]);
			}
			printf("\n");

			result->counter++;
		}

	}

	// assert the frequency of cards in the deck equals
	// the frequency of cards in the shuffled deck
	assert(memcmp(preCount, postCount, sizeof(preCount)) == 0);

	// copy the shuffled deck only to the controlGame
	// compare for changes not expected in other fields
	memcpy(&controlGame->deck[currentPlayer], activeGame->deck[currentPlayer], sizeof(activeGame->deck[currentPlayer]));
	assert(memcmp(controlGame, activeGame, sizeof(struct gameState)) == 0);

	// assert -1 is returned if deckCount was not needed
	// assert 0 if there are cards in the deck
	if(deckCount <= 0)
		assert(r == -1);
	else
		assert(r == 0);

	result->testsPassed++;

	// clean up memory
	free(controlGame);
	free(activeGame);
}

/**
 * Function:  rndUnitTest3
 * Inputs:  testsRun, seed, printVal
 * Outputs: none
 * Description: iterator for randomTests using unittest3
 */
void rndUnitTest2(int testsRun, int seed, int printVal){

	// containers for results
	struct results *results = declResults();
	int i;

	// run the random tests
	for(i = 0; i < testsRun; i++)
	{
		results->testNum++;
		unitTest3(printVal, seed, results);
	}

	// print results if requested
	if(printVal == 1)
	{
		printBoundary(results->lowBound, results->highBound, results->mixedBound);
		printResults(results->testsPassed, results->testsFailed);
		printf("Soft-Fail frequency: %d / %d tests.", results->counter, testsRun);
	}

	free(results);

}

int main(int argc, char *argv[]){

	int seed = 9987;
	int testsRun = 1000;
	int printVal = 1;

	srand(seed);

	printf("\nSTARTING: shuffle() (unittest3)\n");
	rndUnitTest2(testsRun, seed, printVal);
	printf("\nFINISHED: shuffle() (unittest3)\n");

	return 0;
}
