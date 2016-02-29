/**
 * Unit test for function:
 * int smithyCard(int handPos, struct gameState *state);
 *
 * Card Functions when played:
 * 	3 cards are drawn from the deck
 * 	card is added to played pile
 * 	if deck is empty and there are cards in the discard pile
 * 		deck is shuffled before draw
 * 	if deck is empty and discard pile is empty no cards should be drawn
 * 	if deck is empty and less than 3 card in deck, less than 3 cards drawn
 *
 * Assumptions:
 * Preconditions:
 * 	player is a valid player
 * 	gameState has useable data that has reasonably expected values
 * 	deck is a mix of cards
 * 	deckCount represents a valid number of cards in the deck
 * 	handCount represents a valid number of cards in the hand
 * 	Smithy exists in the hand to be played (this is checked prior to function call)
 * 	hand contains cards valid cards with at least Smithy
 * 	coins are updated through playCard function so card function is not required to update coins
 *
 * PostConditions:
 *  - Smithy card is played and put on played pile
 *  - coins are updated
 *  the current player's deck has all the same original cards still
 *  	with the exception of Smithy
 * 	-  no other decks are shuffled and no other values have changed
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest.h"
#include "rngs.h"

#define GOLD_VALUE 3
#define SILVER_VALUE 2
#define COPPER_VALUE 1

struct cardResults
{
	int testsPassed;
	int testsFailed;
	int testNum;
	int counter;
	int noCoinsInDeck;
	int seed;
	int players;
	int curPlayer;
	int deckCount;
	int discardCount;
	int handCount;
	int advPos;
	int coinFlag;
	int initFlag;
	int cardsToAdd;
	int buysToAdd;
};

/**
 * Function: initCardResults
 * Inputs: struct cardResults
 * Outputs: None
 * Description:  Initialization of elements in struct cardResults
 */
void initCardResults(struct cardResults* result)
{
  result->testsPassed = 0;
  result->testsFailed = 0;
  result->testNum = 0;
  result->seed = 0;
  result->counter = 0;
  result->noCoinsInDeck = 0;
  result->players = 0;
  result->curPlayer = 0;
  result->deckCount = 0;
  result->discardCount = 0;
  result->handCount = 0;
  result->advPos = 0;
  result->coinFlag = 0;
  result->initFlag = 0;
  result->cardsToAdd = 0;
  result->buysToAdd = 0;
}

/**
 * Function: resetResults
 * Inputs: struct cardResults
 * Outputs: None
 * Description:  resets elements in card results for next test
 */
void resetResult(struct cardResults* result){
	  result->noCoinsInDeck = 0;
	  result->deckCount = 0;
	  result->discardCount = 0;
	  result->handCount = 0;
	  result->advPos = 0;
	  result->coinFlag = 0;
	  result->initFlag = 0;
}

/**
 * Function: declCardResults
 * Inputs: None
 * Outputs: pointer to initialized cardResults object
 * Description:  declaration and initialization of cardResults Object
 */
struct cardResults* declCardResults() {
  struct cardResults* result = malloc(sizeof(struct cardResults));
  initCardResults(result);
  return result;
}

/**
 * Function: calcCoins
 * Inputs: array of cards, array element count
 * Outputs: coin calculation
 * Description:  Calculates coins in a given hand
 */
int calcCoins(int *hand, int handCount){

	int i;
	int coinCount = 0;

	for(i=0; i < handCount; i++)
	{
		if(hand[i] == gold)
		{
			coinCount = coinCount + GOLD_VALUE;
		}
		else if(hand[i] == silver)
		{
			coinCount = coinCount + SILVER_VALUE;
		}
		else if(hand[i] == copper)
		{
			coinCount = coinCount + COPPER_VALUE;
		}
	}

	return coinCount;
}

/**
 * Function: verifyResults
 * Inputs: struct gameState, struct gameState, struct cardResults
 * Outputs: 0 on successful completion
 * Description:  Function to verify the results of a control and active gameState
 * 	after smithyCard() function run in dominion.c
 */
int verifyResults(struct gameState* activeGame, struct gameState* controlGame, struct cardResults* result){

	int curPlayer = result->curPlayer;

	// if there were at least three cards between the deck and discard
	// verify the handCount went up by 2 (3 added - 1 played)
	int countAvailCards = controlGame->deckCount[curPlayer] + controlGame->discardCount[curPlayer];
	int addedCards = 0;
	int deckCheck = 0;
	int discardCheck = 0;

	if(countAvailCards >= result->cardsToAdd)
		addedCards = result->cardsToAdd;
	else
		addedCards = countAvailCards;

	// smithy should be removed after play and 3 or less cards added
	// TODO:  refactored
	if(!(activeGame->handCount[curPlayer] == controlGame->handCount[curPlayer] + addedCards - 1))
	{
		printf("FAIL:  Post HandCount Result: %d, Expected: %d\n", activeGame->handCount[curPlayer],controlGame->handCount[curPlayer] + addedCards - 1);
		result->testsFailed++;
	} else {
		assert(activeGame->handCount[curPlayer] == controlGame->handCount[curPlayer] + addedCards - 1);
		result->testsPassed++;
	}


	// smithy should be added to the top of the played pile
	if(!(activeGame->playedCardCount == controlGame->playedCardCount + 1))
	{
		printf("FAIL:  Post PlayedCardCount Result: %d, Expected: %d\n", activeGame->playedCardCount,controlGame->playedCardCount + 1);
		result->testsFailed++;
	} else {
		assert(activeGame->playedCardCount == controlGame->playedCardCount + 1);
		result->testsPassed++;
	}

	if(!(activeGame->playedCards[activeGame->playedCardCount - 1] == smithy))
	{
		printf("FAIL:  Post Last PlayedCard Result: %d, Expected: %d\n", activeGame->playedCards[activeGame->playedCardCount - 1], smithy);
		result->testsFailed++;
	} else {
		assert(activeGame->playedCards[activeGame->playedCardCount - 1] == smithy);
		result->testsPassed++;
	}

	// verify all cards from discard were not added to hand
	if(controlGame->deckCount[curPlayer] >= result->cardsToAdd)
	{
		// the post deck - the predeck = cards pulled
		deckCheck = controlGame->deckCount[curPlayer] - addedCards;
		discardCheck = controlGame->discardCount[curPlayer];
	}
	else
	{
		// if the deck was shuffled we have all cards - addedCards - postdeckCount
		// should equal post discard
		deckCheck = controlGame->deckCount[curPlayer] +
				controlGame->discardCount[curPlayer] - addedCards;
		discardCheck = 0;
	}

	// refactored into two seperate values - original version was calculating remaining cards
	// incorrectly
	if(!(activeGame->discardCount[curPlayer] == discardCheck))
	{
		printf("FAIL:  Post Deck Count: %d, Expected: %d\n", activeGame->discardCount[curPlayer], discardCheck);
		result->testsFailed++;
	} else {
		assert(activeGame->discardCount[curPlayer] == discardCheck);
		result->testsPassed++;
	}

	if(!(activeGame->deckCount[curPlayer] == deckCheck))
	{
		printf("FAIL:  Post Deck Count: %d, Expected: %d\n", activeGame->deckCount[curPlayer], deckCheck);
		result->testsFailed++;
	} else {
		assert(activeGame->deckCount[curPlayer] == deckCheck);
		result->testsPassed++;
	}

	// control actions updated to match activeGame to verify nothing else changed
	memcpy(controlGame->hand[curPlayer], activeGame->hand[curPlayer], sizeof(controlGame->hand[curPlayer]));
	memcpy(controlGame->deck[curPlayer], activeGame->deck[curPlayer], sizeof(controlGame->deck[curPlayer]));
	memcpy(controlGame->discard[curPlayer], activeGame->discard[curPlayer], sizeof(controlGame->discard[curPlayer]));
	memcpy(controlGame->playedCards, activeGame->playedCards, sizeof(controlGame->playedCards));
	controlGame->deckCount[curPlayer] = activeGame->deckCount[curPlayer];
	controlGame->handCount[curPlayer] = activeGame->handCount[curPlayer];
	controlGame->discardCount[curPlayer] = activeGame->discardCount[curPlayer];
	controlGame->coins = activeGame->coins;
	controlGame->playedCardCount = activeGame->playedCardCount;

	// nothing else should have changed in the game
	assert(memcmp(controlGame, activeGame, sizeof(struct gameState)) == 0);
	result->testsPassed++;

	return 0;
}

/**
 * Function: setupTest
 * Inputs: struct activeGame, struct cardResults
 * Outputs: None
 * Description:  setup of elements in the activeGame and results in preparation
 * 	to run the tests on smithyCard() function in dominion.c
 */
void setupTest(struct gameState *activeGame, struct cardResults *result){

	int i;
	int cardNum = 0;

	// need some kingdom cards for initialization of game:
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};

	// need a random hand size and position for smithy
	// hand size is at least 1 as smithyCard assumes the card
	// is in the hand when the function called (playCard checks card)
	result->handCount = random_number(4, 10);
	result->advPos = random_number(0, result->handCount - 1);

	// declare the structs to hold the activeGame and control Game
	// assumption:  initializeGame initializes game properly
	initializeGame(result->players, k, result->seed, activeGame);

	// set the player to our random current player
	activeGame->whoseTurn = result->curPlayer;

	// generate a random hand for the current player
	// insert smithy into a random position
	activeGame->handCount[result->curPlayer] = result->handCount;

	for(i=0; i < result->handCount; i++)
	{
		if(i != result->advPos)
			cardNum = random_number(0, treasure_map);
		else
			cardNum = smithy;

		activeGame->hand[result->curPlayer][i] = cardNum;
	}

	activeGame->coins = calcCoins(activeGame->hand[result->curPlayer], activeGame->handCount[result->curPlayer]);

	if(result->initFlag == 1){

		activeGame->deckCount[result->curPlayer] = result->deckCount;
		for(i=0; i < result->deckCount; i++)
		{
			if(result->coinFlag == 1)
				cardNum = silver;
			else
				cardNum = random_number(0, treasure_map);
			activeGame->deck[result->curPlayer][i] = cardNum;
		}

		activeGame->discardCount[result->curPlayer] = result->discardCount;
		for(i=0; i < result->discardCount; i++)
		{
			if(result->coinFlag == 1)
				cardNum = gold;
			else
				cardNum = random_number(0, treasure_map);
			activeGame->discard[result->curPlayer][i] = cardNum;
		}

	}

}

/**
 * Function: cardtest1
 * Inputs: printVal, seed, struct cardResults
 * Outputs: None
 * Description:  setup, running and verification of results obtained from
 * 	running smithyCard() in dominion.c
 */
void cardtest1(int printVal, int seed, struct cardResults *result){

	int r=0;
    int i = 0;
	// need a random number of players and to set current player
	// should be at least 2 to max players
	result->players = random_number(2, MAX_PLAYERS);
	result->curPlayer = random_number(0, result->players - 1);

	struct gameState *controlGame = newGame();
	struct gameState *activeGame = newGame();

	// Setup Test1
	setupTest(activeGame, result);
	result->deckCount = activeGame->deckCount[result->curPlayer];
	result->discardCount = activeGame->deckCount[result->curPlayer];

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	// test case where smithy is the first card played
	printf("\nTEST FOR SMITHY FIRST CARD PLAYED\n");

	// refactored for Lorena code
	r = smithyCard(result->curPlayer, activeGame, result->advPos,i);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	// testing for Smithy being first card played
	printf("\nTEST FOR DECKCOUNT 0 DISCARDCOUNT 0 test\n");

	// Setup Test1
	resetResult(result);

	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	result->deckCount = 0;
	result->discardCount = 0;
	result->initFlag = 1;

	setupTest(activeGame, result);

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	// refactored for Lorena code
  r = smithyCard(result->curPlayer, activeGame, result->advPos, i);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	// add random cards to the discard pile to simulate middle of the game
	resetResult(result);
	result->deckCount = random_number(1, 200);
	result->discardCount = random_number(1, 200);
	result->initFlag = 1;

	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	printf("\nTEST FOR MIXED DRAW CARDS DECKCOUNT %d DISCARDCOUNT %d\n", result->deckCount, result->discardCount);

	setupTest(activeGame, result);

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	r = smithyCard(result->curPlayer, activeGame, result->advPos, i);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	// Setup Test4
	resetResult(result);

	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	result->deckCount = random_number(1, 2);
	result->discardCount = random_number(1, 5);
	result->initFlag = 1;
	result->coinFlag = 1;

	printf("\nTEST FOR ALL COINS IN DECK AND DISCARD\n");

	setupTest(activeGame, result);

	// Ensure last card in hand is a treasure card to get around program crashing
	if(result->advPos == activeGame->handCount[result->curPlayer] - 1)
	{
		activeGame->hand[result->curPlayer][result->advPos - 1] = activeGame->hand[result->curPlayer][result->advPos];
		activeGame->hand[result->curPlayer][activeGame->handCount[result->curPlayer] - 1] = 5;
		result->advPos--;
	}
	else
	{
		activeGame->hand[result->curPlayer][activeGame->handCount[result->curPlayer] - 1] = 5;
	}

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));
	r = smithyCard(result->curPlayer, activeGame, result->advPos, i);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	// clean up memory
	free(controlGame);
	free(activeGame);
}

int main(int argc, char *argv[]){

	int seed = 9987;
	int printVal = 1;

	srand(seed);

	// containers for results
	struct cardResults *result = declCardResults();
	result->seed = seed;
	result->cardsToAdd = 3;

	printf("\nSTARTING: Smithy (cardtest1)\n");
	cardtest1(printVal, seed, result);

	free(result);
	printf("\nFINISHED: Smithy (cardtest1)\n");

	return 0;
}
