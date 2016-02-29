/*
*	Author: 	Martin Stryffeler
*	Filename:	randomtestcard.c
*	Date:		2/14/2016
*
*	Village card random testing
*	Action Sequence: Draw one card, get two additional actions.
*	
*	Expected Results:
*	Player handcount unchanged
*	Player Deckcount decremented by one
*	Player actions incremented by one (+2 from card, -1 in using the card)
*	Other players' handcount unchanged
*	Supply piles unchanged
*
*	Call: cardEffect(village, choice1, choice2, choice3, &state, handPos, &bonus);
*
*	Randomized Inputs:
*	
*	struct gameState {
*		int numPlayers; 								//Range: 1 to 4
*		int supplyCount[treasure_map+1];				
*		int embargoTokens[treasure_map+1];				
* 		int outpostPlayed;
* 		int outpostTurn;
* 		int whoseTurn;									//Range: 0 to numPlayers - 1
* 		int phase;
* 		int numActions;									//Range: 0 to 10
* 		int coins;
* 		int numBuys; 									
* 		int hand[MAX_PLAYERS][MAX_HAND];				
* 		int handCount[MAX_PLAYERS];						//Range: 1 to MAX_HAND
* 		int deck[MAX_PLAYERS][MAX_DECK];				
* 		int deckCount[MAX_PLAYERS];						//Range: 0 to MAX_DECK
* 		int discard[MAX_PLAYERS][MAX_DECK];
* 		int discardCount[MAX_PLAYERS];					//Range: 0 to MAX_DECK
* 		int playedCards[MAX_DECK];						
* 		int playedCardCount;
*	};
*
*	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define NUM_TESTS 50	//High values generate lots of output, as a bug causes a failure in most tests

int generateState(struct gameState *state)
{
	int i, j;
	int handPos, currentPlayer, handCount, deckCount, discardCount;
	int seed = 1000;
	int numPlayers = (rand() % 3) + 2;								//Randomize number of players
	int k[10] = {adventurer, council_room, steward, gardens, mine, remodel, smithy, village, baron, great_hall};
	int possibleCards[16] = {copper, silver, gold, estate, duchy, province, 
		adventurer, council_room, steward, gardens, mine, remodel, smithy, village, baron, great_hall};

	//Clear memory space and initialize game
	memset(state, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, state);

	state->whoseTurn = (rand() % numPlayers);							//Randomize current player
	state->numActions = (rand() % 10 + 1);								//Randomize number of actions available
	state->handCount[state->whoseTurn] = (rand() % MAX_HAND) + 1;		//Randomize number of cards in hand
	state->deckCount[state->whoseTurn] = (rand() % (MAX_DECK - 4)) + 5;	//Randomize deck count
	state->discardCount[state->whoseTurn] = 
		(rand() % (state->deckCount[state->whoseTurn] - 3) + 1);		//Randomize discard count

	currentPlayer = state->whoseTurn;									//For readability and convenience
	handCount = state->handCount[currentPlayer];
	deckCount = state->deckCount[currentPlayer];
	discardCount = state->discardCount[currentPlayer];

	//For each card in the current player's hand, set it to a random possible card
	for(i = 0; i < handCount; i++)
	{
		state->hand[currentPlayer][i] = possibleCards[rand() % 16];
	}

	//Plant a village card in the player's hand
	handPos = rand() % handCount;
	state->hand[currentPlayer][handPos] = village;

	//For each card in the current player's deck, set it to a random card
	for(i = 0; i < deckCount; i++)
	{
		state->deck[currentPlayer][i] = possibleCards[rand() % 16];
	}

	//Move a random number of cards from the deck to the discard pile
	for(i = 0; i < discardCount; i++)
	{	
		if(deckCount > 2)
		{
			state->discard[currentPlayer][i] = state->deck[currentPlayer][deckCount - 1];
			state->deckCount[currentPlayer]--;
			deckCount--;
		}
	}

	//Return the position of the adventurer to be played
	return handPos;
}

int main()
{
	int i, j, currentPlayer;
	int handPos, choice1, choice2, choice3, bonus;
	int failFlag;
	choice1 = choice2 = choice3 = bonus = 0;
	struct gameState state, controlState;

	srand(time(NULL));

	printf("Beginning Village Random Testing\n\n");

	//Test Expected Results
	for(i = 0; i < NUM_TESTS; i++)
	{
		//Generate randomized game state, copy to a control, and call cardEffect
		handPos = generateState(&state);
		memcpy(&controlState, &state, sizeof(struct gameState));
		cardEffect(village, choice1, choice2, choice3, &state, handPos, &bonus);
		currentPlayer = state.whoseTurn;
		
		failFlag = 0;
		
		printf("------------ %d ------------\n", i);

		//Test hand count
		
		//Expected: unchanged
		if(state.handCount[currentPlayer] != controlState.handCount[currentPlayer])
		{
			failFlag = 1;
			printf("FAIL: Hand Count | Expected: %d | Actual: %d\n", controlState.handCount[currentPlayer], state.handCount[currentPlayer]);
		}

		//Test deck count
		//Expected: decrement by one
		if(controlState.deckCount[currentPlayer] - 1 < state.deckCount[currentPlayer])
		{
			failFlag = 1;
			printf("FAIL: Deck Count | Expected: %d or less | Actual: %d\n", controlState.handCount[currentPlayer] - 1, state.deckCount[currentPlayer]);
		}

		//Test action count
		//Expected: increment by one
		if(controlState.numActions + 1 != state.numActions)
		{
			failFlag = 1;
			printf("FAIL: Action count | Expected: %d | Actual: %d\n", controlState.numActions + 1, state.numActions);
		}


		//Test other players' hand count and deck count
		//Expected: unchanged
		for(j = 0; j < state.numPlayers; j++)
		{
			if(j != currentPlayer)
			{
				if(state.handCount[j] != controlState.handCount[j])
				{
					failFlag = 1;
					printf("FAIL: Player %d's Hand Count | Expected: %d | Actual: %d\n", j, controlState.handCount[j], state.handCount[j]);
				}
				if(state.deckCount[j] != controlState.deckCount[j])
				{
					failFlag = 1;
					printf("FAIL: Player %d's Deck Count | Expected: %d | Actual: %d\n", j, controlState.deckCount[j], state.deckCount[j]);
				}

			}
		}

		//Test supply piles
		//Expected: unchanged
		for(j = 0; j < 25; j++)
		{
			if(state.supplyCount[j] != controlState.supplyCount[j])
			{
				failFlag = 1;
				printf("FAIL: Supply Count %d | Expected: %d | Actual: %d\n", j, controlState.supplyCount[j], state.supplyCount[j]);
			}
		}

		//Print out the inputs that lead to a failure
		if(failFlag == 1)
		{
			printf("Inputs: \n numPlayers %d\n current player %d\n numActions %d\n handCount %d\n deckCount %d\n discardCount %d\n", 
				state.numPlayers, currentPlayer, state.numActions, state.handCount[currentPlayer], state.deckCount[currentPlayer], state.discardCount[currentPlayer]);
		}
		else
		{
			printf("All tests passed!\n");
		}

		printf("\n");
	}
	printf("Village tests complete.\n");

	return 0;
}