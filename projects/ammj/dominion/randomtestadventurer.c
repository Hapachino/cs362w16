/**
 * Random test for function:
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
 *	Random inputs:
 *	discardCount
 *	deckCount
 *	handCount
 *	cards in discard
 *	cards in deck
 *	cards in hand
 *	coin distribution?
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

struct cardResults
{
	int testsPassed;
	int testsFailed;
	int testNum;
	int numTests;
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
	int zeroCards;
};

/**
 * Function: initCardResults
 * Inputs: struct cardResults
 * Outputs: None
 * Description:  Initialization of elements in struct cardResults
 */
void initCardResults(struct cardResults* results)
{
  results->testsPassed = 0;
  results->testsFailed = 0;
  results->testNum = 0;
  results->numTests = 0;
  results->seed = 0;
  results->counter = 0;
  results->noCoinsInDeck = 0;
  results->players = 0;
  results->curPlayer = 0;
  results->deckCount = 0;
  results->discardCount = 0;
  results->handCount = 0;
  results->advPos = 0;
  results->coinFlag = 0;
  results->initFlag = 0;
  results->cardsToAdd = 0;
  results->buysToAdd = 0;
  results->zeroCards = 0;
}

/**
 * Function: resetResults
 * Inputs: struct cardResults
 * Outputs: None
 * Description:  resets elements in card results for next test
 */
void resetResult(struct cardResults* results){
	  results->noCoinsInDeck = 0;
	  results->deckCount = 0;
	  results->discardCount = 0;
	  results->handCount = 0;
	  results->advPos = 0;
	  results->coinFlag = 0;
	  results->initFlag = 0;
}

/**
 * Function: declCardResults
 * Inputs: None
 * Outputs: pointer to initialized cardResults object
 * Description:  declaration and initialization of cardResults Object
 */
struct cardResults* declCardResults() {
  struct cardResults* results = malloc(sizeof(struct cardResults));
  initCardResults(results);
  return results;
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

int verifyGameState(struct gameState* activeGame, struct gameState* controlGame, struct cardResults* results){

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

	// check coins hasn't changed
	if(!(activeGame->coins == controlGame->coins))
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
	if(!(activeGame->numActions == controlGame->numActions))
	{
		printf("Test %d: FAIL: gameState->numActions Reported: %d, Expected: %d\n", results->testNum,
				activeGame->numActions, controlGame->numActions);
	}

	// check numBuys hasn't changed
	if(!(activeGame->numBuys == controlGame->numBuys))
	{
		printf("Test %d: FAIL: gameState->numBuys Reported: %d, Expected: %d\n", results->testNum,
				activeGame->numBuys, controlGame->numBuys);
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

	// check supplyCounts haven't changed
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
 * 	after playAdventurer() function run in dominion.c
 */
int verifyResults(struct gameState* activeGame, struct gameState* controlGame, struct cardResults* results){

	int curPlayer = results->curPlayer;
	int i = 0;
	int nonCoinCards = 0;
	int discardCheck = 0;
	int preCoinDeck = 0;
	int start = 0;
	int end = 0;
	int addedCards = 0;

	// if there were at least two coins between the deck and discard
	// verify the handCount went up by 1 (2 added - 1 played)
	int countDeckCoins = calcCoins(controlGame->deck[curPlayer],
			controlGame->deckCount[curPlayer]);
	int countDiscardCoins = calcCoins(controlGame->discard[curPlayer],
			controlGame->discardCount[curPlayer]);

	if(countDeckCoins + countDiscardCoins >= results->cardsToAdd)
		addedCards = 2;
	else
		addedCards = countDeckCoins + countDiscardCoins;

	// adventurer should be removed after play and coin cards found added
	if(activeGame->handCount[curPlayer] != controlGame->handCount[curPlayer] + addedCards - 1)
	{
		printf("Test %d: FAIL: HandCount: %d, Expected: %d\n",
				results->testNum, activeGame->handCount[curPlayer],
				controlGame->handCount[curPlayer] + addedCards - 1);
		results->testsFailed++;
	}
	else
	{
		assert(activeGame->handCount[curPlayer] ==
				controlGame->handCount[curPlayer] + addedCards - 1);
		results->testsPassed++;
	}

	// adventurer should be added to the top of the played pile
	if(activeGame->playedCardCount < 1)
	{
		printf("Test %d: FAIL: playedCardCount: %d, Expected: %d\n", results->testNum,
				activeGame->playedCardCount, controlGame->playedCardCount + 1);
		results->testsFailed++;
	}
	else
	{
		assert(activeGame->playedCardCount >= 1);
		results->testsPassed++;
	}

	if(activeGame->playedCards[activeGame->playedCardCount - 1] != adventurer)
	{
		printf("Test %d: FAIL: playedCard: %d, Expected: %d\n",
				results->testNum,
				activeGame->playedCards[activeGame->playedCardCount - 1],
				adventurer);
		results->testsFailed++;
	}
	else
	{
		assert(activeGame->playedCards[activeGame->playedCardCount - 1] == adventurer);
		results->testsPassed++;
	}

	// if the deck was shuffled all discard cards should not contain coins
	// if the deck was not shuffled all newly discarded cards should not contain coins

	// if deck had to be shuffled start verification at discard[0]
	if(countDeckCoins < results->cardsToAdd)
		nonCoinCards = 0;
	else
	{
		// start at the end of the original discard pile index
		nonCoinCards = controlGame->discardCount[curPlayer] - 1;
	}

	if(DEBUGA)
	{
		printf("NonCoinCards: %d, countDeckCoins: %d\n", nonCoinCards, countDeckCoins);
		printDecks(curPlayer, activeGame, controlGame, ALL);
	}

	int discardCopper = 0;
	int discardSilver = 0;
	int discardGold = 0;
	char discardResult[] = "PASS";

	for(i = nonCoinCards + 1; i < activeGame->discardCount[curPlayer]; i++)
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
			results->testsPassed++;

	}

	printf("Test %d: %s: Coins discarded: Gold: %d, Silver: %d, Copper: %d\n", results->testNum, discardResult,
			discardGold, discardSilver, discardCopper);

	// all added cards added to the hand should only be coins
	if(addedCards > 0){

		start = activeGame->handCount[curPlayer] - addedCards;
		end = start + addedCards - 1;

		for(i = start; i < end; i++)
		{
			if(activeGame->hand[curPlayer][i] != copper &&
					activeGame->hand[curPlayer][i] != silver &&
					activeGame->hand[curPlayer][i] != gold)
			{
				printf("Test %d: FAIL: Non-treasure Card added to hand: %d, Expected: %d, %d or %d\n", results->testNum, activeGame->hand[curPlayer][i], copper, silver, gold);
				results->testsFailed++;
			}
			else
			{
				assert(activeGame->hand[curPlayer][i] == copper ||
						activeGame->hand[curPlayer][i] == silver ||
						activeGame->hand[curPlayer][i] == gold);
				results->testsPassed++;
			}
		}
	}

	// verify all cards discarded that were not added to hand
	if(preCoinDeck >= results->cardsToAdd)
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
				"PostHandCount: %d, ControlDeckCount: %d, PostDeckCount: %d\n", results->testNum,
				activeGame->discardCount[curPlayer], discardCheck, controlGame->handCount[curPlayer],
				activeGame->handCount[curPlayer], controlGame->deckCount[curPlayer],
				activeGame->deckCount[curPlayer] );

		results->testsFailed++;
	}
	else
	{
		assert(activeGame->discardCount[curPlayer] == discardCheck);
		results->testsPassed++;
	}

	// nothing else should have changed in the game
	verifyGameState(activeGame, controlGame, results);

	// nothing else should have changed in the game
	//assert(memcmp(controlGame, activeGame, sizeof(struct gameState)) == 0);
	results->testsPassed++;

	return 0;
}

/**
 * Function: randomtestadventurer
 * Inputs: printVal, seed, struct cardResults
 * Outputs: None
 * Description:  setup, running and verification of results obtained from
 * 	running playAdventurer() in dominion.c
 */
void randomtestadventurer(int printVal, int seed, struct cardResults *result){

	int r=0;
	int bias;

	// need a random number of players and to set current player
	// should be at least 2 to max players
	result->players = random_number(2, MAX_PLAYERS);
	result->curPlayer = random_number(0, result->players - 1);

	// need a random number in hand, discard and deck
	// hand needs to be at least 1 for the adventurer card
	//result->handCount = random_number(1, MAX_DECK);
	result->handCount = random_number(1, 10);
	//result->discardCount = random_number(0, MAX_DECK - result->handCount);
	result->discardCount = random_number(0, 10);
	//result->deckCount = random_number(0, MAX_DECK - result->handCount - result->discardCount);
	bias = random_number(0, 1);
	result->deckCount = random_number(0, 10) * bias;

	if(result->deckCount + result->discardCount == 0)
		result->zeroCards++;

	struct gameState *controlGame = newGame();
	struct gameState *activeGame = newGame();

	// Setup Test1
	// need some kingdom cards for initialization of game:
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};

	// initialize the hand
	initializeGame(result->players, k, result->seed, controlGame);

	// update the hand, deck and discard to our random values
	updatePile(result->curPlayer, result->deckCount, DECK, controlGame);
	updatePile(result->curPlayer, result->discardCount, DISCARD, controlGame);
	updatePile(result->curPlayer, result->handCount, HAND, controlGame);

	// insert the adventurer card into the hand at a random position
	result->advPos = random_number(0, result->handCount - 1);
	controlGame->hand[result->curPlayer][result->advPos] = adventurer;

	// copy the data into the controlGame before running the function
	memcpy(activeGame, controlGame, sizeof(struct gameState));

	// play the card
	printf("Configuration: DeckCount: %d, DiscardCount: %d, handCount: %d\n", result->deckCount, result->discardCount, result->handCount);
	r = playAdventurer(activeGame);

	assert(r == 0);

	result->deckCount = random_number(0, 50);
	result->testsPassed++;

	// verify the results
	r = verifyResults(activeGame, controlGame, result);

	// clean up memory
	free(controlGame);
	free(activeGame);
}

int main(int argc, char *argv[]){

	int seed = 9987;
	int printVal = 1;
	int i = 0;

	srand(seed);

	// containers for results
	struct cardResults *result = declCardResults();
	result->seed = seed;
	result->cardsToAdd = 2;
	result->numTests = 100000;

	printf("\nSTARTING: Adventurer (randomtestadventurer)\n");

	for(i = 0; i < result->numTests; i++)
	{
		printf("\nITERATION %d: STARTING\n", result->testNum);
		randomtestadventurer(printVal, seed, result);
		result->testNum++;
	}


	free(result);

	printf("Passed Tests: %d, Failed Tests: %d\n", result->testsPassed, result->testsFailed);
	printf("Tests with 0 cards to draw from: %d\n", result->zeroCards);
	printf("FINISHED: Adventurer (randomtestadventurer)\n");

	return 0;
}

