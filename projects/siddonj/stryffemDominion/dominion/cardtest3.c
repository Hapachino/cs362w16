/*
*	Author: 	Martin Stryffeler
*	Filename:	cardtest3.c
*	Date:		2/2/2016
*
*	Village card effect testing
*	Action Sequence: Draw one card, get two additional actions.
*	
*	Expected Results:
*	Player handcount unchanged
*	Player deck count + discard count decremented by one
*	Player actions incremented by one (+2 from card, -1 in using the card)
*	Other players' actions unchanged
*	Other players' handcount unchanged
*	Supply piles unchanged
*
*	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	int i;
	int handPos, choice1, choice2, choice3, bonus, player;
	handPos = choice1 = choice2 = choice3 = bonus = player = 0;
	int seed = 1000;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, steward, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	struct gameState state, controlState;
	initializeGame(numPlayers, k, seed, &state);

	//Set control state for comparison, call cardEffect
	memcpy(&controlState, &state, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &state, handPos, &bonus);

	printf("\nTESTING Village cardEffect\n");

	//************** Test hand count **************
	printf("Testing Hand Count\n");
	if(state.handCount[player] == controlState.handCount[player])
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player], state.handCount[player]);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player], state.handCount[player]);
	}

	//************** Test deck + discard count **************
	printf("Testing Discard and Deck Counts\n");
	if((state.deckCount[player] + state.discardCount[player]) == 
		(controlState.deckCount[player] + controlState.discardCount[player] - 1))
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", state.deckCount[player] + state.discardCount[player], 
			controlState.deckCount[player] + controlState.discardCount[player] - 1);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", state.deckCount[player] + state.discardCount[player], 
			controlState.deckCount[player] + controlState.discardCount[player] - 1);
	}


	//************** Test actions count **************
	printf("Testing Actions Count\n");
	if(state.numActions == controlState.numActions + 1)
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.numActions + 1, state.numActions);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.numActions + 1, state.numActions);
	}

	//************** Test other players' deck / discard / hand **************
	printf("Testing other players' deck / discard / hand counts\n");
	for(i = 1; i < numPlayers; i++)
	{
		assert(state.deckCount[i] == controlState.deckCount[i]);
		assert(state.discardCount[i] == controlState.discardCount[i]);
		assert(state.handCount[i] == controlState.handCount[i]);
	}
	printf("PASS: Other players' states unchanged\n");

	//************** Test supply piles **************
	printf("Test Supply Counts\n");
	for(i = 0; i < 25; i++)
	{
		assert(state.supplyCount[i] == controlState.supplyCount[i]);
	}
	printf("PASS: All supply counts unchanged.\n");

	return 0;
}