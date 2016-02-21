/**
 * Unit test for function:
 * int playAdventurer(struct gameState *state);
 *
 * Card Functions when played:
 * 	flips through deck and draws two treasure cards and adds to deck
 * 	if end of deck is reached before 2 treasure cards found discard
 * 	deck should be shuffled and discard pile added.
 * 	When finished adventurer is added to the discard pile
 *
 *
 * Tests:
 * 	if adventure card is the first card played with no discard deck
 * 	expected result:
 * 		2 cards added to hand
 * 		adventurer removed from hand and added to played cards
 * 			- handCount decreases, playedCount increases
 * 		coins should be updated to include 2 treasures added
 * 		all coins discarded were not treasures
 * 		all cards added were treasures
 * 		cards not added to hand were discarded
 *
 * 	if adventure card is played when deck and discard pile have already been exhausted
 * 	expected result:
 * 		adventure card removed from hand and added to played cards
 * 			- handCount decreases, playedCount increases
 * 		no other changes
 *
 * 	if adventure card is played in the middle of the game with random discard and deck
 * 	expected result:
 * 		2 cards added to hand
 * 		adventurer removed from hand and added to played cards
 * 			- handCount decreases, playedCount increases
 * 		coins should be updated to include 2 treasures added
 * 		all coins discarded were not treasures
 * 		all cards added were treasures
 * 		cards not added to hand were discarded
 *
 * 	if adventure card is played with no coins left in deck or discard pile
 * 	expected result:
 * 		adventure card removed from hand and added to played cards
 * 			- handCount decreases, playedCount increases
 * 		no other changes
 *
 *
 * Preconditions:
 * 	player is a valid player
 * 	gameState has useable data that has reasonably expected values
 * 	deck is a mix of cards
 * 	deckCount represents a valid number of cards in the deck
 * 	handCount represents a valid number of cards in the hand
 * 	Adventurer exists in the hand to be played (this should be a test)
 * 	hand contains cards (this should be a test)
 * 	available coins updated through playCard so function is not required to update coins
 *
 * PostConditions:
 *  - Adventurer card is played and put on played pile
 *  	- if the prior card added actions we don't want this one played again
 *  - if 2 treasure cards were found hand has 2 extra cards and no longer contains Adventurer
 *  - else hand no longer contains Adventurer and treasure cards found are added
 * 	- no other decks are shuffled and no other values have changed
 * 	- boundary test what if there are no coin cards in deck and discard
 *
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
	int coinsToAdd;
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
 * Function: calcCoinsCards
 * Inputs: array of cards, array element count
 * Outputs: treasure Card summation
 * Description:  Calculates treasureCards in a given hand
 */
int calcCoinCards(int *hand, int handCount){

	int i;
	int cardCount = 0;

	for(i=0; i < handCount; i++)
	{
		if(hand[i] == gold || hand[i] == silver || hand[i] == copper)
		{
			cardCount++;
		}

	}

	return cardCount;
}

/**
 * Function: verifyResults
 * Inputs: struct gameState, struct gameState, struct cardResults
 * Outputs: 0 on successful completion
 * Description:  Function to verify the results of a control and active gameState
 * 	after playAdventurer() function run in dominion.c
 */
int verifyResults(struct gameState* activeGame, struct gameState* controlGame, struct cardResults* result){

	int curPlayer = result->curPlayer;
	int i = 0;
	int nonCoinCards = 0;
	int discardCheck = 0;
	int preCoinDeck = 0;
	int start = 0;
	int end = 0;
	int addedCards = 0; // updated to pull up value

	// if there were at least two coins between the deck and discard
	// verify the handCount went up by 1 (2 added - 1 played)
	int countDeckCoins = calcCoins(controlGame->deck[curPlayer],
			controlGame->deckCount[curPlayer]);
	int countDiscardCoins = calcCoins(controlGame->discard[curPlayer],
			controlGame->discardCount[curPlayer]);

	if(countDeckCoins + countDiscardCoins >= result->cardsToAdd)
		addedCards = 2;
	else
		addedCards = countDeckCoins + countDiscardCoins;

	// adventurer should be removed after play and coin cards found added
	if(activeGame->handCount[curPlayer] != controlGame->handCount[curPlayer] + addedCards - 1)
	{
		printf("Test %d: FAIL: HandCount: %d, Expected: %d\n",
				result->testNum, activeGame->handCount[curPlayer],
				controlGame->handCount[curPlayer] + addedCards - 1);
		result->testsFailed++;
	}
	else
	{
		assert(activeGame->handCount[curPlayer] ==
				controlGame->handCount[curPlayer] + addedCards - 1);
		result->testsPassed++;
	}

	// adventurer should be added to the top of the played pile
	if(activeGame->playedCardCount < 1)
	{
		printf("Test %d: FAIL: playedCardCount: %d, Expected: %d\n", result->testNum,
				activeGame->playedCardCount, controlGame->playedCardCount + 1);
		result->testsFailed++;
	}
	else
	{
		assert(activeGame->playedCardCount >= 1);
		result->testsPassed++;
	}

	if(activeGame->playedCards[activeGame->playedCardCount - 1] != adventurer)
	{
		printf("Test %d: FAIL: playedCard: %d, Expected: %d\n",
				result->testNum,
				activeGame->playedCards[activeGame->playedCardCount - 1],
				adventurer);
		result->testsFailed++;
	}
	else
	{
		assert(activeGame->playedCards[activeGame->playedCardCount - 1] == adventurer);
		result->testsPassed++;
	}

	// all discarded cards should not be coins
	// count the coin card in the control deck if count is less than 2
	// cards would have to be shuffled and all discard cards would be checked
	// else only the last few cards would need to be checked.

	/*preCoinDeck = calcCoinCards(controlGame->deck[curPlayer], controlGame->deckCount[curPlayer]);
	if(preCoinDeck >= result->cardsToAdd)
		nonCoinCards = activeGame->discard[curPlayer] - controlGame->discard[curPlayer];

	for(i = nonCoinCards; i < activeGame->discardCount[curPlayer]; i++)
	{
		assert(activeGame->discard[curPlayer][i] != copper);
		assert(activeGame->discard[curPlayer][i] != silver);
		assert(activeGame->discard[curPlayer][i] != gold);
		result->testsPassed++;
	}*/
	// if the deck was shuffled all discard cards should not contain coins
	// if the deck was not shuffled all newly discarded cards should not contain coins

	// if deck had to be shuffled start verification at discard[0]
	if(countDeckCoins < result->cardsToAdd)
		nonCoinCards = 0;
	else
	{
		// start at the end of the original discard pile index
		nonCoinCards = controlGame->discardCount[curPlayer] - 1;
	}

	int discardCopper = 0;
	int discardSilver = 0;
	int discardGold = 0;
	char discardResult[] = "PASS";

	for(i = nonCoinCards; i < activeGame->discardCount[curPlayer]; i++)
	{

		if(!(activeGame->discard[curPlayer][i] != copper))
		{
			discardCopper++;
			strcpy(discardResult, "FAIL");
		}
		else if(!(activeGame->discard[curPlayer][i] != silver))
		{
			discardSilver++;
			strcpy(discardResult, "FAIL");
		}
		else if(!(activeGame->discard[curPlayer][i] != gold))
		{
			discardGold++;
			strcpy(discardResult, "FAIL");
		}
		else
			result->testsPassed++;

	}
	printf("Test %d: %s: Coins discarded: Gold: %d, Silver: %d, Copper: %d\n", result->testNum, discardResult,
			discardGold, discardSilver, discardCopper);

	// all added cards added should be coins
	if(addedCards > 0){

		start = activeGame->handCount[curPlayer] - addedCards;
		end = start + addedCards - 1;

		for(i = start; i < end; i++)
		{
			if(activeGame->hand[curPlayer][i] != copper &&
					activeGame->hand[curPlayer][i] != silver &&
					activeGame->hand[curPlayer][i] != gold)
			{
				printf("Test %d: FAIL: Non-treasure Card added to hand: %d, Expected: %d, %d or %d\n", result->testNum, activeGame->hand[curPlayer][i], copper, silver, gold);
				result->testsFailed++;
			}
			else
			{
				assert(activeGame->hand[curPlayer][i] == copper ||
						activeGame->hand[curPlayer][i] == silver ||
						activeGame->hand[curPlayer][i] == gold);
				result->testsPassed++;
			}
		}
	}

	// verify all cards discarded that were not added to hand
	if(preCoinDeck >= result->cardsToAdd)
	{
		// the post deck - the predeck = cards pulled
		// cards pulled - 2 should equal the post discard
		discardCheck = controlGame->deckCount[curPlayer] - activeGame->deckCount[curPlayer] - addedCards +
				controlGame->discardCount[curPlayer];
	}
	else
	{
		// if the deck was shuffled we have all cards - 2 - postdeckCount
		// should equal post discard
		discardCheck = controlGame->deckCount[curPlayer] +
				controlGame->discardCount[curPlayer] - addedCards -
				activeGame->deckCount[curPlayer];
	}


	if(activeGame->discardCount[curPlayer] != discardCheck)
	{
		printf("Test %d: FAIL: DiscardCount: %d, Expected: %d, ControlHandCount: %d, "
				"PostHandCount: %d, ControlDeckCount: %d, PostDeckCount: %d, "
				"ControlDiscardCount: %d, PostDiscardCount: %d\n", result->testNum,
				activeGame->discardCount[curPlayer], discardCheck, controlGame->handCount[curPlayer],
				activeGame->handCount[curPlayer], controlGame->deckCount[curPlayer],
				activeGame->deckCount[curPlayer], controlGame->discardCount[curPlayer],
				activeGame->discardCount[curPlayer]);

		result->testsFailed++;
	}
	else
	{
		assert(activeGame->discardCount[curPlayer] == discardCheck);
		result->testsPassed++;
	}

	// nothing else should have changed in the game
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
 * 	to run the tests on playAdventurer() function in dominion.c
 */
void setupTest(struct gameState *activeGame, struct cardResults *result){

	int i;
	int cardNum = 0;

	// need some kingdom cards for initialization of game:
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};

	// need a random hand size and position for adventurer
	// hand size is at least 1 as playAdventurer assumes the card
	// is in the hand when the function called (playCard checks card)
	result->handCount = random_number(4, 10);
	result->advPos = random_number(0, result->handCount - 1);
	result->cardsToAdd = 2;

	// declare the structs to hold the activeGame and control Game
	// assumption:  initializeGame initializes game properly
	initializeGame(result->players, k, result->seed, activeGame);

	// set the player to our random current player
	activeGame->whoseTurn = result->curPlayer;

	// generate a random hand for the current player
	// insert adventurer into a random position
	activeGame->handCount[result->curPlayer] = result->handCount;

	for(i=0; i < result->handCount; i++)
	{
		if(i != result->advPos)
			cardNum = random_number(0, treasure_map);
		else
			cardNum = adventurer;

		activeGame->hand[result->curPlayer][i] = cardNum;
	}

	activeGame->coins = calcCoins(activeGame->hand[result->curPlayer], activeGame->handCount[result->curPlayer]);

	if(result->initFlag == 1){

		activeGame->deckCount[result->curPlayer] = result->deckCount;
		for(i=0; i < result->deckCount; i++)
		{
			if(result->coinFlag == 1)
				cardNum = smithy;
			else
				cardNum = random_number(0, treasure_map);
			activeGame->deck[result->curPlayer][i] = cardNum;
		}

		activeGame->discardCount[result->curPlayer] = result->discardCount;
		for(i=0; i < result->discardCount; i++)
		{
			if(result->coinFlag == 1)
				cardNum = duchy;
			else
				cardNum = random_number(0, treasure_map);
			activeGame->discard[result->curPlayer][i] = cardNum;
		}

	}

}

/**
 * Function: cardtest2
 * Inputs: printVal, seed, struct cardResults
 * Outputs: None
 * Description:  setup, running and verification of results obtained from
 * 	running playAdventurer() in dominion.c
 */
void cardTest2(int printVal, int seed, struct cardResults *result){

	int r=0;

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

	// test case where adventurer is the first card played
	printf("\nTEST FOR ADVENTURER FIRST CARD PLAYED\n");

	// refactored for Janel's code
	r = adventurerCard(activeGame, result->curPlayer);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	/*
	 * This test goes into an infinite loop when the last card in the hand is not a coin
	 * The infinite loop causes the program to crash by continuing to write a value to
	 * an array after incrementing the index for the array
	 */


	printf("\nTEST FOR DECKCOUNT 0 DISCARDCOUNT 0 test\n");

	// Setup Test2
	resetResult(result);

	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	result->deckCount = 0;
	result->discardCount = 0;
	result->initFlag = 1;

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

	// refactored for Janel's code
  r = adventurerCard(activeGame, result->curPlayer);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	// Setup Test 3
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

	// refactored for Janel's code
	r = adventurerCard(activeGame, result->curPlayer);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);


	// test if players deck and players discard piles contains no coins
	// Setup Test4
	resetResult(result);

	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	result->deckCount = random_number(1, 5);
	result->discardCount = random_number(1, 5);
	result->initFlag = 1;
	result->coinFlag = 1;

	printf("\nTEST FOR NO COINS IN DECK OR DISCARD\n");

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

	// refactored for Janel's code
	r = adventurerCard(activeGame, result->curPlayer);
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
	result->cardsToAdd = 2;

	printf("\nSTARTING: Adventurer (cardtest2)\n");
	cardTest2(printVal, seed, result);

	free(result);
	printf("\nFINISHED: Adventurer (cardtest2)\n");

	return 0;
}
