/*
*	Author: 	Martin Stryffeler
*	Filename:	randomtestadventurer.c
*	Date:		2/14/2016
*
*	Adventurer card random testing
*	Action Sequence: Reveal cards until two treasure cards are revealed.
*	Add them to your hand, then discard the other revealed cards.
*	
*	Expected Results: 
*	Hand count increases by two
*	Deck count decremented by at least two
*	The two cards added to the hand are coins
*	Post adventurer discard count + deck count = pre adventurer deck + discard - 2
*	Other players' hand count and deck count unchanged
*	Supply piles unchanged
*
*	Call: cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, &bonus);
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
*	Call: Must set first card in hand to adventurer
*	state.hand[currentPlayer][0] = adventurer;
*	playAdventurer(state, currentPlayer);
*
*	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define NUM_TESTS 50	//High values generate lots of output, as a bug causes a failure in every test

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

	//Plant an adventurer card in the player's hand
	handPos = 0;
	state->hand[currentPlayer][handPos] = adventurer;

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

	//Ensure that there are at least two coins in the deck
	do
	{
		i = rand() % deckCount;
		j = rand() % deckCount;
	} while(i == j);
	state->deck[currentPlayer][i] = copper;
	state->deck[currentPlayer][j] = silver;

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

	printf("Beginning Adventurer Random Testing\n\n");

	//Test Expected Results
	for(i = 0; i < NUM_TESTS; i++)
	{
		//Generate randomized game state, copy to a control, and call cardEffect
		handPos = generateState(&state);
		memcpy(&controlState, &state, sizeof(struct gameState));
		playAdventurer(&state, state.whoseTurn);
		//cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, &bonus);
		currentPlayer = state.whoseTurn;
		
		failFlag = 0;
		
		printf("------------ %d ------------\n", i);

		//Test hand count
		
		//Expected: increment by two
		if(state.handCount[currentPlayer] != controlState.handCount[currentPlayer] + 2)
		{
			failFlag = 1;
			printf("FAIL: Hand Count | Expected: %d | Actual: %d\n", controlState.handCount[currentPlayer] + 2, state.handCount[currentPlayer]);
		}

		//Test deck count
		//Expected: decrement by at least two
		if(controlState.deckCount[currentPlayer] - 2 < state.deckCount[currentPlayer])
		{
			failFlag = 1;
			printf("FAIL: Deck Count | Expected: %d or less | Actual: %d\n", controlState.handCount[currentPlayer] - 2, state.deckCount[currentPlayer]);
		}

		//Test hand
		//Expected: The two added cards are coins
		if((state.hand[currentPlayer][state.handCount[currentPlayer] - 1] != copper && 
			state.hand[currentPlayer][state.handCount[currentPlayer] - 1] != silver && 
			state.hand[currentPlayer][state.handCount[currentPlayer] - 1] != gold) ||
			(state.hand[currentPlayer][state.handCount[currentPlayer] - 2] != copper && 
			state.hand[currentPlayer][state.handCount[currentPlayer] - 2] != silver && 
			state.hand[currentPlayer][state.handCount[currentPlayer] - 2] != gold))
		{
			failFlag = 1;
			printf("FAIL: Added Cards | Expected: Copper (4), Silver (5), or Gold (6) | Actual: %d, %d\n", 
				state.hand[currentPlayer][state.handCount[currentPlayer] - 1], state.hand[currentPlayer][state.handCount[currentPlayer] - 2]);
		}

		//Test discard + deck count
		//Expected: decremented by two
		if(state.discardCount[currentPlayer] + state.deckCount[currentPlayer] != controlState.discardCount[currentPlayer] + controlState.deckCount[currentPlayer] - 2)
		{
			failFlag = 1;
			printf("FAIL: Deck + Discard Count | Expected: %d | Actual: %d\n", 
				controlState.discardCount[currentPlayer] + controlState.deckCount[currentPlayer] - 2, state.discardCount[currentPlayer] + state.deckCount[currentPlayer]);
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
	printf("Adventurer tests complete.\n");

	return 0;
}