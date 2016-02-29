/**
 * Unit test for function:
 * int getWinners(int players[MAX_PLAYERS], struct gameState *state)
 *
 * Test For:
 * 		each player gets a point for every estate in their hand, deck and discard
 * 		each player gets 3 points for every duchy in their hand, deck and discard
 * 		each player gets 6 points for every province in their hand, deck and discard
 * 		each player gets 1 point for every great_hall in their hand, deck and discard
 * 		each player gets 1 point for every 10 cards in their hand, deck and discard combined
 * 		players greater than player but less than MAX_PLAYERS do not get scored
 *
 * 	3 scenarios:
 *    two players
 *    three players
 *    four players
 *
 * Preconditions:
 * player is a valid player
 * gameState has useable data that has reasonably expected values
 * deck is a mix of cards
 * deckCount represents a valid number of cards in the deck
 * discard is a mix of cards
 * discardCount represents a valid number of cards in the deck
 * hand is a mix of cards
 * handCount represents a valid number of cards in the deck
 *
 * PostConditions:
 *  the player with the highest total of the formula:
 *  cards mean cards in hand, deck and discard piles
 *  (-1 * curse cards) + (1 * estate cards) + (3 * duchy cards) + (6 * province cards)
 *  + (1 * great_hall cards) + (total cards / 10 * gardens cards)
 *
 *  // boundary tests:
 *  // when remainder from discard % 10, deck % 10 and hand % 10 = 10
 *  // score when all cards 0
 *  // score when many cards but no victory cards
 *  // score for all victory cards
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

#define PRINTPASS 1

#define HAND 0
#define DECK 1
#define DISCARD 2

#define CURSE_CT 0
#define ESTATE_CT 1
#define DUCHY_CT 2
#define PROVINCE_CT 3
#define GREATHALL_CT 4
#define GARDENS_CT 5

#define DECK_CT 0
#define DISCARD_CT 1
#define HAND_CT 2

// container for the player Value arrays
struct playerValues{
	int deckCounts[HAND_CT+1];
	int cardCounts[GARDENS_CT+1];
	int totalCards;
	int score;
	int winner;
};

// group of playerValue structs
struct playerGroup{
	int numPlayers;
	struct playerValues* playerValues[MAX_PLAYERS];
};

/**
 * Function: initPlayerValues
 * Inputs: playerValues as struct
 * Outputs: none
 * Description:  initializes a playerValues struct
 */
void initPlayerValues(struct playerValues *playerValues){

	int i;
	playerValues->score = 0;
	playerValues->winner = 0;
	playerValues->totalCards = 0;

	for(i=0; i <= HAND_CT; i++)
	{
		playerValues->deckCounts[i] = 0;
	}

	for(i=0; i <= GARDENS_CT; i++)
	{
		playerValues->cardCounts[i] = 0;
	}

}

/**
 * Function: setupPlayValues()
 * Inputs: none
 * Outputs: struct playerValues
 * Description:  declares and initializes a playerValues struct
 */
struct playerValues* newPlayerValues()
{
	struct playerValues* player = (struct playerValues*)malloc(sizeof(struct playerValues));
	initPlayerValues(player);
	return player;
}

/**
 * Function: initPlayerGroup()
 * Inputs: struct PlayerGroup
 * Outputs: None
 * Description:  initializes a group of playerValues
 */
void initPlayerGroup(struct playerGroup* playerGroup){
	int i;

	for(i=0; i < MAX_PLAYERS; i++)
		playerGroup->playerValues[i] = newPlayerValues();
}

/**
 * Function: initPlayerGroup()
 * Inputs: None
 * Outputs: struct PlayerGroup ptr
 * Description:  Declares and initializes a group of playerValues
 */
struct playerGroup* newPlayerGroup() {

  struct playerGroup* playerGroup = (struct playerGroup*) malloc(sizeof(struct playerGroup));
  initPlayerGroup(playerGroup);
  return playerGroup;

}

/**
 * Function: calculate_total()
 * Inputs: player, game
 * Outputs: 0 on successful completion
 * Description:  Calculates a players total victory points
 */
int calculate_total(int player, struct gameState *state)
{
	int total = -999;
	int frequencies[treasure_map] = {0};
	int totalCards = 0;

	if(player < MAX_PLAYERS && player <= state->numPlayers)
	{
		// count the frequency of all the cards
		total = 0;
		totalCards = state->deckCount[player]+state->discardCount[player]+state->handCount[player];
		getDeckFrequencies(state->deck[player], state->deckCount[player], frequencies, treasure_map);
		getDeckFrequencies(state->discard[player], state->discardCount[player], frequencies, treasure_map);
		getDeckFrequencies(state->hand[player], state->handCount[player], frequencies, treasure_map);
		total = frequencies[curse] * (-1);
		total = total + (frequencies[estate]);
		total = total + (frequencies[duchy] * 3);
		total = total + (frequencies[province] * 6);
		total = total + frequencies[great_hall];
		total = total + ((frequencies[gardens] * totalCards)/10);
	}

	return total;
}

/**
 * Function: shuffleCards
 * shuffles cards to be added to hands
 * Inputs: cards as array ptr, numCards as int
 * Outputs: 0 for successful completion
 * based on dominion.c shuffle()
 */
int updateCards(int player, struct playerValues *playValues, struct gameState *state){

	int i;

	initPlayerValues(playValues);


	playValues->deckCounts[HAND_CT] = random_number(1,10);
	playValues->deckCounts[DECK_CT] = random_number(1,200);
	playValues->deckCounts[DISCARD_CT] = random_number(1,200);

	state->handCount[player] = playValues->deckCounts[HAND_CT];
	state->deckCount[player] = playValues->deckCounts[DECK_CT];
	state->discardCount[player] = playValues->deckCounts[DISCARD_CT];

	playValues->totalCards = playValues->deckCounts[HAND_CT] + playValues->deckCounts[DECK_CT] + playValues->deckCounts[DISCARD_CT];

	for(i = 0; i < playValues->deckCounts[HAND_CT]; i++)
	{
		state->hand[player][i] = random_number(0, treasure_map);

		if(state->hand[player][i] == curse)
			playValues->cardCounts[CURSE_CT]++;
		else if(state->hand[player][i] == estate)
			playValues->cardCounts[ESTATE_CT]++;
		else if(state->hand[player][i] == duchy)
			playValues->cardCounts[DUCHY_CT]++;
		else if(state->hand[player][i] == province)
			playValues->cardCounts[PROVINCE_CT]++;
		else if(state->hand[player][i] == great_hall)
			playValues->cardCounts[GREATHALL_CT]++;
		else if(state->hand[player][i] == gardens)
			playValues->cardCounts[GARDENS_CT]++;

	}

	for(i = 0; i < playValues->deckCounts[DECK_CT]; i++)
	{
		state->deck[player][i] = random_number(0, treasure_map);

		if(state->deck[player][i] == curse)
			playValues->cardCounts[CURSE_CT]++;
		else if(state->deck[player][i] == estate)
			playValues->cardCounts[ESTATE_CT]++;
		else if(state->deck[player][i] == duchy)
			playValues->cardCounts[DUCHY_CT]++;
		else if(state->deck[player][i] == province)
			playValues->cardCounts[PROVINCE_CT]++;
		else if(state->deck[player][i] == great_hall)
			playValues->cardCounts[GREATHALL_CT]++;
		else if(state->deck[player][i] == gardens)
			playValues->cardCounts[GARDENS_CT]++;
	}

	for(i = 0; i < playValues->deckCounts[DISCARD_CT]; i++)
	{
		state->discard[player][i] = random_number(0, treasure_map);

		if(state->discard[player][i] == curse)
			playValues->cardCounts[CURSE_CT]++;
		else if(state->discard[player][i] == estate)
			playValues->cardCounts[ESTATE_CT]++;
		else if(state->discard[player][i] == duchy)
			playValues->cardCounts[DUCHY_CT]++;
		else if(state->discard[player][i] == province)
			playValues->cardCounts[PROVINCE_CT]++;
		else if(state->discard[player][i] == great_hall)
			playValues->cardCounts[GREATHALL_CT]++;
		else if(state->discard[player][i] == gardens)
			playValues->cardCounts[GARDENS_CT]++;
	}

	return 0;
}

/**
 * Function:  unittest4
 * Inputs:  printVal, seed, results
 * Outputs: none
 * Description: tests getWinners() function in dominion.c
 */
void unitTest4(int printVal, int seed, struct results *result){

	int i, r=0;
	int players[MAX_PLAYERS] = {0};

	struct playerGroup *playGroup = newPlayerGroup();

	// setup the kingdom cards available
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
					 sea_hag, tribute, smithy};

	// setup the struct for the control and active Games
	struct gameState *controlGame = newGame();
	struct gameState *activeGame = newGame();

	playGroup->numPlayers = random_number(2, MAX_PLAYERS);
	initializeGame(playGroup->numPlayers, k, seed, controlGame);

	playGroup->playerValues[0]->cardCounts[0] = 23;
	playGroup->playerValues[1]->cardCounts[0] = 46;
	playGroup->playerValues[2]->cardCounts[0] = 75;
	playGroup->playerValues[3]->cardCounts[0] = 66;

	for(i = 0; i < playGroup->numPlayers; i++)
	{
		updateCards(i, playGroup->playerValues[i], controlGame);
	}

	//copy the values from the activeGame into the controlGame
	memcpy(activeGame, controlGame, sizeof(struct gameState));

	// calculate the scores for the players
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		playGroup->playerValues[i]->score = calculate_total(i, controlGame);
	}

	// run the getWinners function
	r = getWinners(players, activeGame);
	assert(r == 0);

	int winningScore = playGroup->playerValues[0]->score;
	int curWinner = 0;
	playGroup->playerValues[0]->winner = 1;

	for(i = 0; i < MAX_PLAYERS; i++)
	{

		if(playGroup->playerValues[i]->score >= winningScore)
		{
			winningScore = playGroup->playerValues[i]->score;
			playGroup->playerValues[curWinner]->winner = 0;
			playGroup->playerValues[i]->winner = 1;
			curWinner = i;
		}

	}

	for(i=0; i < MAX_PLAYERS; i++)
	{
		int j;
		int score = scoreFor(i, activeGame);

		if(!(playGroup->playerValues[i]->winner == players[i]) || !(score == playGroup->playerValues[i]->score))
		{
			printf("TEST: %d, FAIL: Player: %d of %d players\nScore: %d, Expected: %d, Winner Val Returned: %d,"
					" Expected: %d\n",
					result->testNum, i, playGroup->numPlayers, score,
					playGroup->playerValues[i]->score, players[i], playGroup->playerValues[i]->winner);
			result->testsFailed++;
		}
		else
		{
			assert(playGroup->playerValues[i]->winner == players[i]);

			if(PRINTPASS){
				printf("TEST: %d, PASS: Player: %d of %d players\nScore: %d, Expected: %d, Winner Val Returned: %d,"
						" Expected: %d\n",
						result->testNum, i, playGroup->numPlayers, score,
						playGroup->playerValues[i]->score, players[i], playGroup->playerValues[i]->winner);
			}
		}

		if(!(scoreFor(i, activeGame) == playGroup->playerValues[i]->score))
		{
			printf("HAND: ");
			for(j = 0; j < activeGame->handCount[i]; j++)
			{
				printf("%d,", activeGame->hand[i][j]);
			}
			printf("\n");
			printf("DECK: ");
			for(j = 0; j < activeGame->deckCount[i]; j++)
			{
				printf("%d,", activeGame->deck[i][j]);
			}
			printf("\n");
			printf("DISCARD: ");
			for(j = 0; j < activeGame->discardCount[i]; j++)
			{
				printf("%d,", activeGame->discard[i][j]);
			}
			printf("\n");
			printf("CURSE: %d, ESTATES: %d, DUCHY: %d, PROVINCE: %d, GREAT_HALL:%d, GARDENS: %d, totalCards: %d\n",
					playGroup->playerValues[i]->cardCounts[CURSE_CT], playGroup->playerValues[i]->cardCounts[ESTATE_CT],
					playGroup->playerValues[i]->cardCounts[DUCHY_CT], playGroup->playerValues[i]->cardCounts[PROVINCE_CT],
					playGroup->playerValues[i]->cardCounts[GREATHALL_CT], playGroup->playerValues[i]->cardCounts[GARDENS_CT],
					playGroup->playerValues[i]->totalCards);
		}
	}


	result->testsPassed++;

	// clean up memory
	for(i = 0; i < MAX_PLAYERS; i++){
		free(playGroup->playerValues[i]);
	}
	free(playGroup);
	free(controlGame);
	free(activeGame);
}

/**
 * Function:  rndUnitTest4
 * Inputs:  testsRun, seed, printVal
 * Outputs: none
 * Description: iterator for randomTests using unittest4
 */
void rndUnitTest4(int testsRun, int seed, int printVal){

	// containers for results
	struct results *results = declResults();
	int i;

	// run the random tests
	for(i = 0; i < testsRun; i++)
	{
		results->testNum++;
		unitTest4(printVal, seed, results);
	}

	// print results if requested
	if(printVal == 1)
	{
		printResults(results->testsPassed, results->testsFailed);
	}

	free(results);

}

int main(int argc, char *argv[]){

	int seed = 9987;
	int testsRun = 100;
	int printVal = 1;

	srand(seed);

	printf("\nSTARTING: getWinners (unittest4)\n");
	rndUnitTest4(testsRun, seed, printVal);
	printf("\nFINISHED: getWinners (unittest4)\n");

	return 0;
}
