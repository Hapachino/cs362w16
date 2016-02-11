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
 * Random inputs:
 *  cards in deck
 *  estate cards in hand
 *  estate cards in supply
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

#define HAND 0
#define DISCARD 1
#define DECK 2
#define ALL 3

#define DEBUGA 0

typedef struct tests{
	int testsPassed;
	int testsFailed;
	int numTests;
	int currentTest;
	int cardUnderTest;
	int zeroCards;
	int seed;
} TESTS;

typedef struct cards{
	int playedCardPos;
	int deckCount;
	int discardCount;
	int handCount;
} CARDS;

typedef struct cardResults
{
	TESTS* tests;
	CARDS* cards;
	int players;
	int curPlayer;
	int testNum;
	int noCoinsInDeck;
	int coinFlag;
	int initFlag;
	int addedCards;
	int addedBuys;
	int addedCoins;
	int addedActions;
	int coinBonus;
	int choiceFlag;
} RESULTS;

typedef struct cardNames
{
	int cardCount;
	char* cardNames;
} CARDNAMES;

/**
 * Function: initTests
 * Inputs: struct tests*
 * Outputs: None
 * Description:  Initialization of elements in struct tests*
 */
void initTests(TESTS* tests){
	tests->cardUnderTest = baron;
	tests->currentTest = 0;
	tests->numTests = 0;
	tests->seed = 0;
	tests->testsFailed = 0;
	tests->testsPassed = 0;
	tests->zeroCards = 0;
}

/**
 * Function: initCards
 * Inputs: struct cards*
 * Outputs: None
 * Description:  Initialization of elements in struct cards*
 */
void initCards(CARDS* cards){
	cards->deckCount = 0;
	cards->discardCount = 0;
	cards->handCount = 0;
	cards->playedCardPos = 0;
}

/**
 * Function: declTests
 * Inputs: None
 * Outputs: pointer to initialized cardResults object
 * Description:  declaration and initialization of cardResults Object
 */
TESTS* declTests() {
  TESTS* tests = malloc(sizeof(TESTS));
  initTests(tests);
  return tests;
}

/**
 * Function: declCards
 * Inputs: None
 * Outputs: pointer to initialized cards struct
 * Description:  declaration and initialization of cards struct
 */
CARDS* declCards() {
  CARDS* cards = malloc(sizeof(CARDS));
  initCards(cards);
  return cards;
}

/**
 * Function: initCardResults
 * Inputs: struct cardResults
 * Outputs: None
 * Description:  Initialization of elements in struct cardResults
 */
void initCardResults(RESULTS* results)
{
  results->tests = declTests();
  results->cards = declCards();
  results->noCoinsInDeck = 0;
  results->players = 0;
  results->curPlayer = 0;
  results->coinFlag = 0;
  results->initFlag = 0;
  results->addedCards = 0;
  results->addedBuys = 0;
  results->coinBonus = 0;
  results->choiceFlag = 0;
}



/**
 * Function: declCardResults
 * Inputs: None
 * Outputs: pointer to initialized cardResults object
 * Description:  declaration and initialization of cardResults Object
 */
RESULTS* declCardResults() {
  RESULTS* results = malloc(sizeof(RESULTS));
  initCardResults(results);
  return results;
}

/**
 * Function: resetResults
 * Inputs: struct cardResults
 * Outputs: None
 * Description:  resets elements in card results for next test
 */
void resetResult(struct cardResults* results){
	  results->noCoinsInDeck = 0;
	  results->cards->deckCount = 0;
	  results->cards->discardCount = 0;
	  results->cards->handCount = 0;
	  results->cards->playedCardPos = 0;
	  results->coinFlag = 0;
	  results->initFlag = 0;
	  results->coinBonus = 0;
	  results->choiceFlag = 0;
}

/**
 * Function: cardCount
 * Inputs: card, pile
 * Outputs: total of card in hand
 * Description:  Calculates the frequency of a card in a hand
 */
int cardCount(int card, int *pile, int pileCount)
{
	assert(card >= 0);
	assert(pileCount >= 0);

	int i;
	int count = 0;

	for(i = 0; i < pileCount; i++)
	{
		if(pile[i] == card)
			count++;
	}

	if(DEBUGA)
		printf("\nCardCount for: %d, Count: %d\n", card, count);

	return count;
}

/**
 * Function: calcCoins
 * Inputs: array of cards, array element count
 * Outputs: coin calculation
 * Description:  Calculates coins in a given hand
 */
int calcCoins(int *hand, int handCount){

	// verify we have a hand or return error
	if(handCount < 0)
		return -1;

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
 * Function: updatePile
 * Inputs: player, count of elements to update, pile type to update, struct gameState
 * Outputs: None
 * Description:  updates a pile of cards to the number of elements requested in count
 */
int updatePile(int player, int count, int pile, struct gameState *state){

	if(player < 0 || player > MAX_PLAYERS)
		return -1;

	if(count < 0)
		return -1;

	int i;
	int *ptr;
	int oldCount;

	if(pile == HAND)
	{
		oldCount = state->handCount[player];
		state->handCount[player] = count;
		ptr = state->hand[player];
	}
	else if(pile == DECK)
	{
		oldCount = state->deckCount[player];
		state->deckCount[player] = count;
		ptr = state->deck[player];
	}
	else if(pile == DISCARD)
	{
		oldCount = state->discardCount[player];
		state->discardCount[player] = count;
		ptr = state->discard[player];
	}

	for(i = 0; i < count; i++){
		ptr[i] = random_number(0, treasure_map);
	}

	//clear values higher than count
	for(i = count; i < oldCount; i++){
		ptr[i] = 0;
	}

	return 0;
}

/**
 * Function: PrintDecks
 * Inputs: player, activeGame, controlGame
 * Outputs: 0 on successful game completion
 * Description:  Prints out the contents of the decks in the controlGame and activeGame
 */
int printDecks(int player, struct gameState* activeGame, struct gameState* controlGame, int hand){

	if(player < 0 || player > MAX_PLAYERS)
		return -1;

	int i;

	if(hand == DECK || hand == ALL)
	{
			printf("\nControl Deck: count: %d [", controlGame->deckCount[player]);
			for(i=0; i < controlGame->deckCount[player]; i++){

				printf("%d", controlGame->deck[player][i]);
				if(i != controlGame->deckCount[player] - 1)
					printf(", ");
			}
			printf("]");

			printf("\nActive Deck: count: %d [", activeGame->deckCount[player]);
			for(i=0; i < activeGame->deckCount[player]; i++){

				printf("%d", activeGame->deck[player][i]);
				if(i != activeGame->deckCount[player] - 1)
					printf(", ");
			}
			printf("]");
	}

	if(hand == DISCARD || hand == ALL)
	{
			printf("\nControl Discard: count: %d [", controlGame->discardCount[player]);
			for(i=0; i < controlGame->discardCount[player]; i++){

				printf("%d", controlGame->discard[player][i]);
				if(i != controlGame->discardCount[player] - 1)
					printf(", ");
			}
			printf("]");

			printf("\nActive Discard: count: %d [", activeGame->discardCount[player]);
			for(i=0; i < activeGame->discardCount[player]; i++){

				printf("%d", activeGame->discard[player][i]);
				if(i != activeGame->discardCount[player] - 1)
					printf(", ");
			}
			printf("]");
	}

	if(hand == HAND || hand == ALL)
	{
		printf("\nControl Hand: count: %d [", controlGame->handCount[player]);
		for(i=0; i < controlGame->handCount[player]; i++){

			printf("%d", controlGame->hand[player][i]);
			if(i != controlGame->handCount[player] - 1)
				printf(", ");
		}
		printf("]");

		printf("\nActive Hand: count: %d [", activeGame->handCount[player]);
		for(i=0; i < activeGame->handCount[player]; i++){

			printf("%d", activeGame->hand[player][i]);
			if(i != activeGame->handCount[player] - 1)
				printf(", ");
		}
		printf("]");
	}

	return 0;
}

/**
 * Function:  verifyGameState
 * Inputs: activeGame, controlGame, results
 * Outputs: 0 on successful completion
 * Description:  verifies the controlGame state with the activeGame state
 */
int verifyGameState(struct gameState* activeGame, struct gameState* controlGame, struct cardResults* results){

	// assert controlGame, activeGame and results are initialized
  if(!controlGame || !activeGame || !results)
  	return -1;

	int i;
	int curPlayer = results->curPlayer;

	// copy over the only items that should have changed
	memcpy(controlGame->hand[curPlayer], activeGame->hand[curPlayer], sizeof(controlGame->hand[curPlayer]));
	memcpy(controlGame->deck[curPlayer], activeGame->deck[curPlayer], sizeof(controlGame->deck[curPlayer]));
	memcpy(controlGame->discard[curPlayer], activeGame->discard[curPlayer], sizeof(controlGame->discard[curPlayer]));
	memcpy(controlGame->playedCards, activeGame->playedCards, sizeof(controlGame->playedCards));
	controlGame->deckCount[curPlayer] = activeGame->deckCount[curPlayer];
	controlGame->handCount[curPlayer] = activeGame->handCount[curPlayer];
	controlGame->discardCount[curPlayer] = activeGame->discardCount[curPlayer];
	controlGame->playedCardCount = activeGame->playedCardCount;
	controlGame->supplyCount[estate] = activeGame->supplyCount[estate];

	// check coins hasn't changed
	if(!(activeGame->coins == controlGame->coins + results->addedCoins))
	{
		printf("Test %d: FAIL: gameState->coins Reported: %d, Expected: %d\n", results->testNum,
				activeGame->coins, controlGame->coins);
	}

	// check embargo tokens hasn't changed
	if(!(memcmp(activeGame->embargoTokens, controlGame->embargoTokens, sizeof(activeGame->embargoTokens)) == 0))
	{

		for(i = 0; i < treasure_map; i++)
		{
			printf("Test %d: FAIL: gameState->embargoTokens[%d] Reported: %d, Expected: %d\n", results->testNum,
					i, activeGame->embargoTokens[i], controlGame->embargoTokens[i]);
		}
	}

	// check numActions hasn't changed
	if(!(activeGame->numActions == controlGame->numActions + results->addedActions))
	{
		printf("Test %d: FAIL: gameState->numActions Reported: %d, Expected: %d\n", results->testNum,
				activeGame->numActions, controlGame->numActions);
	}

	// check numBuys has an added Action
	if(!(activeGame->numBuys == controlGame->numBuys + results->addedBuys))
	{
		printf("Test %d: FAIL: gameState->numBuys Reported: %d, Expected: %d\n", results->testNum,
				activeGame->numBuys, controlGame->numBuys + 1);
	}

	// check numPlayers hasn't changed
	if(!(activeGame->numPlayers == controlGame->numPlayers))
	{
		printf("Test %d: FAIL: gameState->numPlayers Reported: %d, Expected: %d\n", results->testNum,
				activeGame->numPlayers, controlGame->numPlayers);
	}

	// check outpostPlayed hasn't changed
	if(!(activeGame->outpostPlayed == controlGame->outpostPlayed))
	{
		printf("Test %d: FAIL: gameState->outpostPlayed Reported: %d, Expected: %d\n", results->testNum,
				activeGame->outpostPlayed, controlGame->outpostPlayed);
	}

	// check outpostTurn hasn't changed
	if(!(activeGame->outpostTurn == controlGame->outpostTurn))
	{
		printf("Test %d: FAIL: gameState->outpostTurn Reported: %d, Expected: %d\n", results->testNum,
				activeGame->outpostTurn, controlGame->outpostTurn);
	}

	// check phase hasn't changed
	if(!(activeGame->phase == controlGame->phase))
	{
		printf("Test %d: FAIL: gameState->phase Reported: %d, Expected: %d\n", results->testNum,
				activeGame->phase, controlGame->phase);
	}

	// check all other supplyCounts haven't changed
	if(!(memcmp(controlGame->supplyCount, activeGame->supplyCount, sizeof(controlGame->supplyCount)) == 0))
	{

		// if they have cycle through to find the offender
		for(i = 0; i < treasure_map; i++)
		{
			if(!(activeGame->supplyCount[i] == controlGame->supplyCount[i]))
			{
				printf("Test %d: FAIL: gameState->supplyCount[%d] Reported: %d, Expected: %d\n", results->testNum,
						i, activeGame->supplyCount[i], controlGame->supplyCount[i]);
			}
		}
	}

	// check whoseTurn hasn't changed
	if(!(activeGame->whoseTurn == controlGame->whoseTurn))
	{
		printf("Test %d: FAIL: gameState->whoseTurn Reported: %d, Expected: %d\n", results->testNum,
				activeGame->whoseTurn, controlGame->whoseTurn);
	}

	return 0;
}

/**
 * Function: verifyResults
 * Inputs: struct gameState, struct gameState, struct cardResults
 * Outputs: 0 on successful completion
 * Description:  Function to verify the results of a control and active gameState
 * 	after baron cards is played in dominion.c
 */
int verifyResults(struct gameState* activeGame, struct gameState* controlGame, struct cardResults* results){

	TESTS* tests = results->tests;

	int curPlayer = results->curPlayer;
	int preCount = 0;
	int postCount = 0;
	int choice = results->choiceFlag;
	int removedCards = 0;
	int supplyEstate;
	int handEstates = cardCount(estate, controlGame->hand[curPlayer], controlGame->handCount[curPlayer]);

	printf("Test: %d, choice: %d, hand estates: %d, handCount: %d, estate supply: %d\n",
			results->testNum, results->choiceFlag, handEstates,
			controlGame->handCount[curPlayer], controlGame->supplyCount[estate]);


	// check Baron card is no longer in hand.
	// since there could be more than one baron and baron only adds estate
	// we check by baron frequency
	preCount = cardCount(baron, controlGame->hand[curPlayer], controlGame->handCount[curPlayer]);
	postCount = cardCount(baron, activeGame->hand[curPlayer], activeGame->handCount[curPlayer]);

	if(postCount != preCount - 1)
	{
		printf("Test: %d FAIL: Post Hand Baron Count: %d, Expected: %d\n", results->testNum,
				postCount, preCount - 1);
		tests->testsFailed++;

	} else {

		assert(postCount == preCount - 1);
		tests->testsPassed++;
	}

	// check Baron card added to played pile
	if(activeGame->playedCards[activeGame->playedCardCount -1] != baron)
	{
		printf("Test: %d FAIL: Last Card Played: %d, Expected: %d\n", results->testNum,
				activeGame->playedCards[activeGame->playedCardCount -1], baron);
		tests->testsFailed++;
	} else {
		assert(activeGame->playedCards[activeGame->playedCardCount -1] == baron);
		tests->testsPassed++;
	}

	// check playedCardCount increased
	// applies to all tests
	if(activeGame->playedCardCount != controlGame->playedCardCount + 1)
	{
		printf("Test: %d FAIL: playedCardCount: %d, Expected: %d\n", results->testNum,
				activeGame->playedCardCount, controlGame->playedCardCount + 1);
		tests->testsFailed++;
	} else {
		assert(activeGame->playedCardCount == controlGame->playedCardCount);
		tests->testsPassed++;
	}

	// check 1 less estate card in hand and one less card in hand overall
	// applies to estate in preGame Hand and discard chosen only
	preCount = cardCount(estate, controlGame->hand[curPlayer], controlGame->handCount[curPlayer]);
	postCount = cardCount(estate, activeGame->hand[curPlayer], activeGame->handCount[curPlayer]);

	// if 4 cards chosen but prehand contains no estates reset choiceFlag
	// to allow testing for gain estate choice
	if(preCount == 0 && results->choiceFlag == 1)
		choice = 0;

	// check 1 less estate card
	// applies to estate in preGame Hand and discard chosen only
	if(choice == 1)
	{
		if(!(postCount == preCount - 1))
		{
			printf("Test: %d FAIL: Estate not removed from hand.  Estates in hand: %d, Expected: %d,"
					"control estates in hand: %d\n",
						results->testNum, postCount, preCount - 1, preCount);
			tests->testsFailed++;
		}
		else
		{
			assert(postCount == preCount - 1);
			tests->testsPassed++;
		}
	}
	else
	{
		assert(postCount == preCount);
		tests->testsPassed++;
	}

	// check 2 less card overall
	// applies to estate in preGame Hand and discard chosen only
	if(choice == 1)
		removedCards = 2;
	else
		removedCards = 1;

	if(activeGame->handCount[curPlayer] != controlGame->handCount[curPlayer] - removedCards)
	{
		printf("Test: %d FAIL: Hand Count: %d, Expected: %d\n", results->testNum,
				activeGame->handCount[curPlayer], controlGame->handCount[curPlayer] - removedCards);
		tests->testsFailed++;
	} else {
		assert(activeGame->handCount[curPlayer] == controlGame->handCount[curPlayer] - removedCards);
		tests->testsPassed++;
	}

	// check estate card went on the top of the discard pile
	// Either estate comes from the supply or the hand
	// unless supply is 0, or there is no estate in hand
	if(controlGame->supplyCount[estate] > 0 || preCount > 0)
		supplyEstate = 1;
	else
		supplyEstate = 0;

	if(supplyEstate == 1)
	{
		// check the last discard was an estate
		if(!(activeGame->discard[curPlayer][activeGame->discardCount[curPlayer] - 1] == estate))
		{
			printf("Test: %d FAIL: Estate not discarded.  Last discard: %d, Expected: %d, control estate supply: %d, "
					"control estates in hand: %d, active estate supply: %d, active estates in hand: %d\n",
					results->testNum, activeGame->discard[curPlayer][activeGame->discardCount[curPlayer] - 1], estate,
					controlGame->supplyCount[estate], preCount, activeGame->supplyCount[estate], postCount);
			tests->testsFailed++;
		}
		else
		{
			assert(activeGame->discard[curPlayer][activeGame->discardCount[curPlayer] - 1] == estate);
			tests->testsPassed++;
		}

	} else {
		if(!(activeGame->discard[curPlayer][activeGame->discardCount[curPlayer] - 1] ==
				controlGame->discard[curPlayer][controlGame->discardCount[curPlayer] - 1]))
		{
			printf("Test: %d FAIL: Last discard changed.  Last discard: %d, Expected: %d, control estate supply: %d, "
					"control estates in hand: %d, active estate supply: %d, active estates in hand: %d\n",
					results->testNum, activeGame->discard[curPlayer][activeGame->discardCount[curPlayer] - 1], estate,
					controlGame->supplyCount[estate], preCount, activeGame->supplyCount[estate], postCount);
			tests->testsFailed++;

		}
		else
		{
			assert(activeGame->discard[curPlayer][activeGame->discardCount[curPlayer] - 1] ==
					controlGame->discard[curPlayer][controlGame->discardCount[curPlayer] - 1]);
			tests->testsPassed++;
		}
	}

	// check discard count increased
	if(!(controlGame->discardCount[curPlayer] + supplyEstate == activeGame->discardCount[curPlayer]))
	{
		printf("Test: %d FAIL: Estate not added to DiscardCount.  DiscardCount: %d, Expected: %d, control estate supply: %d, "
				"control estates in hand: %d, active estate supply: %d, active estates in hand: %d\n", results->testNum,
				activeGame->discardCount[curPlayer], activeGame->discardCount[curPlayer] + supplyEstate,
				controlGame->supplyCount[estate], preCount, activeGame->supplyCount[estate], postCount);
		tests->testsFailed++;
	}
	else
	{
		assert(controlGame->discardCount[curPlayer] + supplyEstate == activeGame->discardCount[curPlayer]);
		tests->testsPassed++;
	}

	// check 4 coins added to bonus variable as update Coins will wipe out coins
	// in playcard if estate thrown.  Else 0 coins added.
	if(results->coinBonus != (choice * 4))
	{
		printf("Test: %d FAIL: Coin bonus returned: %d, Expected: %d\n", results->testNum, results->coinBonus, 4);
		tests->testsFailed++;
	} else {
		assert(results->coinBonus == (choice * 4));
		tests->testsPassed++;
	}

	// check supply count for estate remained the same
	// applies to estate in preGame Hand and discard chosen only
	if(choice == 1)
	{
		assert(activeGame->supplyCount[estate] == controlGame->supplyCount[estate]);
		tests->testsPassed++;

	} else {

		if(controlGame->supplyCount[estate] == 0)
		{
			assert(activeGame->supplyCount[estate] == 0);
			tests->testsPassed++;
		}
		else
		{
			if(activeGame->supplyCount[estate] != controlGame->supplyCount[estate] - 1)
			{
				printf("Test: %d FAIL: Estate Supply Count: %d, Expected: %d\n", results->testNum,
						activeGame->supplyCount[estate], controlGame->supplyCount[estate]-1);
				tests->testsFailed++;
			} else {
				assert(activeGame->supplyCount[estate] == (controlGame->supplyCount[estate] - 1));
				tests->testsPassed++;
			}

		}

	}

	// check buys increased
	// applies to estate in preGame Hand and discard chosen only
	if(choice == 1)
	{
		assert(activeGame->numBuys == controlGame->numBuys + 1);
		tests->testsPassed++;
	}


	if(choice == 0)
	{
		controlGame->supplyCount[estate] = activeGame->supplyCount[estate];
	}

	verifyGameState(activeGame, controlGame, results);

	return 0;
}

int setupTest(struct gameState *controlGame, struct gameState *activeGame){

	return 0;
}

/**
 * Function: cardtest1
 * Inputs: printVal, seed, struct cardResults
 * Outputs: None
 * Description:  setup, running and verification of results obtained from
 * 	playing baron card in dominion.c
 */
void randomtestcard(int printVal, int seed, struct cardResults *results){

	int p=0;
	int i=0;
	int supplyEstate;
	int handEstate;
	int handEstateUpper = 3;

	// clear the results
	resetResult(results);

	// need a random number of players and to set current player
	// should be at least 2 to max players
	// Baron card played with estate in hand, estate card chosen
	// need a random number of players and to set current player
	results->players = random_number(2, MAX_PLAYERS);
	results->curPlayer = random_number(0, results->players - 1);

	// need a random number in hand, discard and deck
	// hand needs to be at least 1 for the adventurer card
	//results->cards->handCount = random_number(1, MAX_DECK);
	results->cards->handCount = random_number(0, 5);
	results->cards->discardCount = random_number(0, MAX_DECK - results->cards->handCount);
	results->cards->deckCount = random_number(0, MAX_DECK - results->cards->handCount - results->cards->discardCount);

	if(results->cards->deckCount + results->cards->discardCount == 0)
		results->tests->zeroCards++;

	// if there are card places in the hand get a random number of estates to put in hand
	if(results->cards->handCount < 3)
	{
		handEstateUpper = results->cards->handCount - 1;
	}

	struct gameState *controlGame = newGame();
	struct gameState *activeGame = newGame();

	// setup random values choiceFlag, handCount, deckCount, estate supply, estates in hand
	results->choiceFlag = random_number(0, 1);
	//supplyEstate = random_number(0,30);
	supplyEstate = random_number(0,5);
	handEstate = random_number(0, handEstateUpper);

	// Setup Test1
	// need some kingdom cards for initialization of game:
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};

	// initialize the hand
	initializeGame(results->players, k, results->tests->seed, controlGame);

	// update the hand, deck and discard to our random values
	updatePile(results->curPlayer, results->cards->deckCount, DECK, controlGame);
	updatePile(results->curPlayer, results->cards->discardCount, DISCARD, controlGame);
	updatePile(results->curPlayer, results->cards->handCount, HAND, controlGame);

	// fill the hand with the estates if there are any
	for(i = 0; i < handEstate; i++)
	{
		if(handEstate == results->cards->playedCardPos)
			handEstate++;
		else
			controlGame->hand[results->curPlayer][handEstate] = estate;
	}

	controlGame->supplyCount[estate] = supplyEstate;

	if(DEBUGA)
	{
		printDecks(results->curPlayer, activeGame, controlGame, HAND);
		printf("Coins: %d", calcCoins(controlGame->hand[results->curPlayer], controlGame->handCount[results->curPlayer]));
	}

	// insert the baron card into the hand at a random position
	results->cards->playedCardPos = random_number(0, results->cards->handCount - 1);
	controlGame->hand[results->curPlayer][results->cards->playedCardPos] = baron;

	// copy the data into the cG before running the function
	memcpy(activeGame, controlGame, sizeof(struct gameState));

	p = cardEffect(results->tests->cardUnderTest, results->choiceFlag, 0, 0, activeGame, results->cards->playedCardPos, &results->coinBonus);
	assert(p == 0);
	results->tests->testsPassed++;

	p = verifyResults(activeGame, controlGame, results);

	// clean up memory
	free(controlGame);
	free(activeGame);
}

int main(int argc, char *argv[]){

	int seed = 9987;
	int printVal = 1;
	int i;

	srand(seed);

	// containers for results
	RESULTS *r = declCardResults();
	r->tests->seed = seed;
	r->addedBuys = 1;
	r->tests->numTests = 100000;

	printf("\nSTARTING: Baron (randomtestcard)\n");
	for(i = 0; i < r->tests->numTests; i++)
	{
		randomtestcard(printVal, seed, r);
		r->testNum++;
	}
	free(r);
	printf("\nFINISHED: Baron (randomtestcard)\n");

	return 0;
}
