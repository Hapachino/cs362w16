 /**
 * Unit test for function:
 *   Baron card using CardEffect
 *   Using PlayCard would be more like the game but introduces an extra layer of checking
 *
 * Card Functions when played:
 * 	Baron Card added to played cards,
 * 		- last card in played Cards is Baron
 * 		- played cards count increases by 1,
 * 		- handCount decreases by 1
 * 		- last card in hand moved into Baron position
 * 	Baron Card adds +1 to buys
 * 	If there is an estate in the hand, it can be chosen
 * 		- estate card removed,
 * 		- handCount goes down by 1
 * 		- 4 added to coins
 * 	If there is no estate card in hand
 * 		- estate card gained
 * 	If there is an estate in the hand but it is not chosen
 * 		- estate card gained
 *
 * 	Not required to be in this part of the code but it is so we will check it:
 * 	If there are no estates left or last estate drawn game should be set to end.
 *
 * Tests:
 * 	Baron card played with estate in hand, estate card chosen
 * 	Baron card played with estate in hand, estate card not chosen
 * 	Baron card played with no estate in hand
 * 	Baron card played with estate in hand, estate card not chosen but no estates left
 *	Baron card played and estate not in hand but throw estate card away selected
 *
 * Preconditions:
 * 	player is a valid player
 * 	gameState has useable data that has reasonably expected values
 * 	deck is a mix of cards
 * 	deckCount represents a valid number of cards in the deck
 * 	handCount represents a valid number of cards in the hand
 * 	Baron exists in the hand to be played (this is tested prior)
 * 	hand contains cards with at least 1 (Baron)
 *
 * PostConditions:
 *  - Baron card is played and put on played pile
 *  	- if the prior card added actions we don't want this one played again
 *  	- buy increased by 1
 *  - if estate card exists in hand and coins are chosen
 *  	- coins are added to bonus
 *  	- estate card discarded
 *  - if estate card does not exist in hand and coins are chosen
 *  	- estate card added to discard pile
 *  - if estate card exists in hand and estate is chosen
 *  	- estate card discarded
 *  - if estate card does not exist in hand and estate is chosen
 *  	- estate card added to discard pile
 *  - if estate is chosen and no supply of estate cards
 *  	- nothing else changes
 * 	- no other decks are shuffled and no other values have changed
 *
 * 	coins are updated after in playCard routine so coins shouldn't change as they
 * 	will be overwritten
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
#include "dominion_cards.h"
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
	int cardUnderTest;
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
	int coinBonus;
	int choiceFlag;
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
  result->cardUnderTest = 0;
  result->coinBonus = 0;
  result->choiceFlag = 0;
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
	  result->coinBonus = 0;
	  result->choiceFlag = 0;
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
 * Function: verifyResults
 * Inputs: struct gameState, struct gameState, struct cardResults
 * Outputs: 0 on successful completion
 * Description:  Function to verify the results of a control and active gameState
 * 	after baron cards is played in dominion.c
 */
int verifyResults(struct gameState* activeGame, struct gameState* controlGame, struct cardResults* result){

	int curPlayer = result->curPlayer;
	int i = 0;
	int preCount = 0;
	int postCount = 0;
	int fourCoins = result->choiceFlag;
	int removedCards = 0;
	int supplyEstate = 0;

	// check Baron card is no longer in hand.
	// applies to all tests
	for(i=0; i < controlGame->handCount[curPlayer]; i++){
		if(controlGame->hand[curPlayer][i] == baron)
			preCount++;
	}
	for(i=0; i < activeGame->handCount[curPlayer]; i++){
		if(activeGame->hand[curPlayer][i] == baron)
			postCount++;
	}
	if(postCount != preCount - 1)
	{
		printf("FAIL: Post Hand Baron Count: %d, Expected: %d\n", postCount, preCount - 1);
		result->testsFailed++;
	} else {
		assert(postCount == preCount - 1);
		result->testsPassed++;
	}

	// check Baron card added to played pile
	// applies to all tests
	if(activeGame->playedCards[activeGame->playedCardCount -1] != baron)
	{
		printf("FAIL: Last Card Played: %d, Expected: %d\n",
				activeGame->playedCards[activeGame->playedCardCount -1], baron);
		result->testsFailed++;
	} else {
		assert(activeGame->playedCards[activeGame->playedCardCount -1] == baron);
		result->testsPassed++;
	}

	// check playedCardCount increased
	// applies to all tests
	if(activeGame->playedCardCount != controlGame->playedCardCount + 1)
	{
		printf("FAIL: playedCardCount: %d, Expected: %d\n",
				activeGame->playedCardCount, controlGame->playedCardCount + 1);
		result->testsFailed++;
	} else {
		assert(activeGame->playedCardCount == controlGame->playedCardCount);
		result->testsPassed++;
	}

	preCount = 0;
	postCount = 0;

	// check 1 less estate card in hand and one less card in hand overall
	// applies to estate in preGame Hand and discard chosen only
	for(i=0; i < controlGame->handCount[curPlayer]; i++){
		if(controlGame->hand[curPlayer][i] == estate)
			preCount++;
	}
	for(i=0; i < activeGame->handCount[curPlayer]; i++){
		if(activeGame->hand[curPlayer][i] == estate)
			postCount++;
	}

	// if 4 cards chosen but prehand contains no estates reset choiceFlag
	// to allow testing for gain estate choice
	if(preCount == 0 && result->choiceFlag == 1)
		fourCoins = 0;

	// check 1 less estate card
	// applies to estate in preGame Hand and discard chosen only
	if(fourCoins == 1)
	{
		assert(postCount == preCount - 1);
		result->testsPassed++;
	}
	else
	{
		assert(postCount == preCount);
		result->testsPassed++;
	}

	// check 2 less card overall
	// applies to estate in preGame Hand and discard chosen only
	if(fourCoins == 1)
		removedCards = 2;
	else
		removedCards = 1;

	if(activeGame->handCount[curPlayer] != controlGame->handCount[curPlayer] - removedCards)
	{
		printf("FAIL: Hand Count: %d, Expected: %d\n",
				activeGame->handCount[curPlayer], controlGame->handCount[curPlayer] - removedCards);
		result->testsFailed++;
	} else {
		assert(activeGame->handCount[curPlayer] == controlGame->handCount[curPlayer] - removedCards);
		result->testsPassed++;
	}

	// check estate card went on the top of the discard pile
	// applies to all - either estate comes from hand or supply
	// unless supply is 0
	if(controlGame->supplyCount[estate] > 0)
		supplyEstate = 1;
	else
		supplyEstate = 0;

	if(supplyEstate != 0)
	{
		assert(activeGame->discard[curPlayer][activeGame->discardCount[curPlayer] - 1] == estate);
		result->testsPassed++;

	} else {
		assert(activeGame->discard[curPlayer][activeGame->discardCount[curPlayer] - 1] ==
				controlGame->discard[curPlayer][controlGame->discardCount[curPlayer] - 1]);
		result->testsPassed++;
	}

	assert(controlGame->discardCount[curPlayer] + supplyEstate == activeGame->discardCount[curPlayer]);
	result->testsPassed++;

	// check 4 coins added to bonus variable as update Coins will wipe out coins
	// in playcard if estate thrown.  Else 0 coins added.
	if(result->coinBonus != (fourCoins * 4))
	{
		printf("FAIL: Coin bonus returned: %d, Expected: %d\n", result->coinBonus, 4);
		result->testsFailed++;
	} else {
		assert(result->coinBonus == (fourCoins * 4));
		result->testsPassed++;
	}

	// check supply count for estate remained the same
	// applies to estate in preGame Hand and discard chosen only
	if(fourCoins == 1)
	{
		assert(activeGame->supplyCount[estate] == controlGame->supplyCount[estate]);
		result->testsPassed++;

	} else {

		if(controlGame->supplyCount[estate] == 0)
		{
			assert(activeGame->supplyCount[estate] == 0);
			result->testsPassed++;
		}
		else
		{
			if(activeGame->supplyCount[estate] != controlGame->supplyCount[estate] - 1)
			{
				printf("FAIL: Estate Supply Count: %d, Expected: %d\n", activeGame->supplyCount[estate], controlGame->supplyCount[estate]-1);
				result->testsFailed++;
			} else {
				assert(activeGame->supplyCount[estate] == (controlGame->supplyCount[estate] - 1));
				result->testsPassed++;
			}

		}

	}

	// check buys increased
	// applies to estate in preGame Hand and discard chosen only
	if(fourCoins == 1)
	{
		assert(activeGame->numBuys == controlGame->numBuys + 1);
		result->testsPassed++;
	}

	// nothing else should have changed in the game
	memcpy(controlGame->hand[curPlayer], activeGame->hand[curPlayer], sizeof(activeGame->hand[curPlayer]));
	memcpy(controlGame->discard[curPlayer], activeGame->discard[curPlayer], sizeof(activeGame->discard[curPlayer]));
	memcpy(controlGame->playedCards, activeGame->playedCards, sizeof(activeGame->playedCards));
	controlGame->handCount[curPlayer] = activeGame->handCount[curPlayer];
	controlGame->discardCount[curPlayer] = activeGame->discardCount[curPlayer];
	controlGame->playedCardCount = activeGame->playedCardCount;
	controlGame->numBuys = activeGame->numBuys;
	if(fourCoins == 0)
	{
		controlGame->supplyCount[estate] = activeGame->supplyCount[estate];
	}

	// failed compare due to coins updated instead of bonus
	if(controlGame->coins != activeGame->coins)
	{
		printf("FAIL: Testing Values haven't changed:");
		printf(" Coins updated to: %d, Expected: %d\n", activeGame->coins, controlGame->coins);
		controlGame->coins = activeGame->coins;
		result->testsFailed++;
	}

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
 * 	to run the tests on baron card in dominion.c
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
			cardNum = result->cardUnderTest;

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
 * Function: cardtest1
 * Inputs: printVal, seed, struct cardResults
 * Outputs: None
 * Description:  setup, running and verification of results obtained from
 * 	playing baron card in dominion.c
 */
void cardTest3(int printVal, int seed, struct cardResults *result){

	int r=0;
	int i=0;

	// need a random number of players and to set current player
	// should be at least 2 to max players
	// Baron card played with estate in hand, estate card chosen
	result->players = random_number(2, MAX_PLAYERS);
	result->curPlayer = random_number(0, result->players - 1);

	struct gameState *controlGame = newGame();
	struct gameState *activeGame = newGame();

	// Setup Test1
	setupTest(activeGame, result);
	result->choiceFlag = 1;

	// putting an estate card in hand next to baron card
	if(result->advPos == activeGame->handCount[result->curPlayer])
		activeGame->hand[result->curPlayer][result->advPos - 1] = estate;
	else
		activeGame->hand[result->curPlayer][result->advPos + 1] = estate;

	result->deckCount = activeGame->deckCount[result->curPlayer];
	result->discardCount = activeGame->deckCount[result->curPlayer];

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	// test case where adventurer is the first card played
	printf("\nTEST FOR ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE COINS\n");

	r = cardEffect(result->cardUnderTest, result->choiceFlag, 0, 0, activeGame, result->advPos, &result->coinBonus);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	//Baron card played with estate in hand, estate card not chosen
	printf("\nTEST FOR ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE EXTRA ESTATE\n");

	// Setup Test2
	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	resetResult(result);
	setupTest(activeGame, result);
	result->choiceFlag = 0;

	// putting an estate card in hand next to baron card
	if(result->advPos == activeGame->handCount[result->curPlayer])
		activeGame->hand[result->curPlayer][result->advPos - 1] = estate;
	else
		activeGame->hand[result->curPlayer][result->advPos + 1] = estate;

	result->deckCount = activeGame->deckCount[result->curPlayer];
	result->discardCount = activeGame->deckCount[result->curPlayer];

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));
	controlGame->supplyCount[estate] = activeGame->supplyCount[estate];

	r = cardEffect(result->cardUnderTest, result->choiceFlag, 0, 0, activeGame, result->advPos, &result->coinBonus);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	// Baron card played with no estate in hand choose coins
	printf("\nTEST FOR 0 ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE COINS \n");

	// Setup Test3
	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	resetResult(result);
	setupTest(activeGame, result);
	result->choiceFlag = 1;

	// remove all estate cards from hand
	for(i = 0; i < activeGame->handCount[result->curPlayer]; i++)
	{
		if(activeGame->hand[result->curPlayer][i] != result->cardUnderTest)
			activeGame->hand[result->curPlayer][i] = copper;
	}

	result->deckCount = activeGame->deckCount[result->curPlayer];
	result->discardCount = activeGame->deckCount[result->curPlayer];

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	r = cardEffect(result->cardUnderTest, result->choiceFlag, 0, 0, activeGame, result->advPos, &result->coinBonus);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	// Baron card played with no estate in hand choose coins
	printf("\nTEST FOR 0 ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE ESTATE \n");

	// Setup Test3
	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	resetResult(result);
	setupTest(activeGame, result);
	result->choiceFlag = 0;

	// remove all estate cards from hand
	for(i = 0; i < activeGame->handCount[result->curPlayer]; i++)
	{
		if(activeGame->hand[result->curPlayer][i] != result->cardUnderTest)
			activeGame->hand[result->curPlayer][i] = copper;
	}

	result->deckCount = activeGame->deckCount[result->curPlayer];
	result->discardCount = activeGame->deckCount[result->curPlayer];

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	r = cardEffect(result->cardUnderTest, result->choiceFlag, 0, 0, activeGame, result->advPos, &result->coinBonus);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);


	//Baron card played with estate in hand, estate card not chosen but no estates left
	printf("\nTEST FOR ESTATE CARD IN HAND, ESTATE SUPPLY = 0, CHOOSE TAKE ESTATE \n");

	// Setup Test5
	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	resetResult(result);
	setupTest(activeGame, result);
	result->choiceFlag = 0;

	result->deckCount = activeGame->deckCount[result->curPlayer];
	result->discardCount = activeGame->deckCount[result->curPlayer];

	// set supply of estate cards to 0
	activeGame->supplyCount[estate] = 0;

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	r = cardEffect(result->cardUnderTest, result->choiceFlag, 0, 0, activeGame, result->advPos, &result->coinBonus);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

	//Baron card played with estate in hand, estate card not chosen but no estates left
	printf("\nTEST FOR ESTATE CARD IN HAND, ESTATE SUPPLY = 1, CHOOSE TAKE ESTATE \n");

	// Setup Test6
	free(controlGame);
	free(activeGame);
	controlGame = newGame();
	activeGame = newGame();

	resetResult(result);
	setupTest(activeGame, result);
	result->choiceFlag = 0;

	result->deckCount = activeGame->deckCount[result->curPlayer];
	result->discardCount = activeGame->deckCount[result->curPlayer];

	// set supply of estate cards to 0
	activeGame->supplyCount[estate] = 1;

	// copy the data into the controlGame before running the function
	memcpy(controlGame, activeGame, sizeof(struct gameState));

	r = cardEffect(result->cardUnderTest, result->choiceFlag, 0, 0, activeGame, result->advPos, &result->coinBonus);
	assert(r == 0);
	result->testsPassed++;

	r = verifyResults(activeGame, controlGame, result);

		// Baron card played with no estate in hand choose coins
		printf("\nTEST FOR 0 ESTATE IN HAND, ESTATE SUPPLY = 0, CHOOSE COINS \n");

		// Setup Test3
		free(controlGame);
		free(activeGame);
		controlGame = newGame();
		activeGame = newGame();

		resetResult(result);
		setupTest(activeGame, result);
		result->choiceFlag = 1;

		// remove all estate cards from hand
		for(i = 0; i < activeGame->handCount[result->curPlayer]; i++)
		{
			if(activeGame->hand[result->curPlayer][i] != result->cardUnderTest)
				activeGame->hand[result->curPlayer][i] = copper;
		}

		result->deckCount = activeGame->deckCount[result->curPlayer];
		result->discardCount = activeGame->deckCount[result->curPlayer];

		activeGame->supplyCount[estate] = 0;

		// copy the data into the controlGame before running the function
		memcpy(controlGame, activeGame, sizeof(struct gameState));

		r = cardEffect(result->cardUnderTest, result->choiceFlag, 0, 0, activeGame, result->advPos, &result->coinBonus);
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
	result->cardUnderTest = baron;
	result->buysToAdd = 1;

	printf("\nSTARTING: Baron (cardtest3)\n");
	cardTest3(printVal, seed, result);
	free(result);
	printf("\nFINISHED: Baron (cardtest3)\n");

	return 0;
}
