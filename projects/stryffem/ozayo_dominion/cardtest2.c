/*
*	Author: 	Martin Stryffeler
*	Filename:	cardtest2.c
*	Date:		2/2/2016
*
*	Adventurer card effect testing
*	Action Sequence: Reveal cards until two treasure cards are revealed.
*	Add them to your hand, then discard the other revealed cards.
*	
*	Expected Results: 
*	Hand count increases by one
*	Deck count decremented by at least two
*	The two cards added to the hand are coins
*	Post adventurer discard count + deck count = pre adventurer deck + discard - 2
*	Other players' hand count and deck count unchanged
*	Supply piles unchanged
*
*	Call: Must set first card in hand to adventurer
*	state.hand[currentPlayer][0] = adventurer;
*	playAdventurer(state, currentPlayer);
*	
*	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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

	//Set first card to adventurer
	state.hand[player][0] = adventurer;

	//Set control state for comparison, call cardEffect
	memcpy(&controlState, &state, sizeof(struct gameState));
	//playAdventurer(&state);
	cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, &bonus);

	printf("\nTESTING Adventurer cardEffect\n");

	//************** Test hand count **************

	//Test that handCount is incremented by one
	printf("Testing Hand Count\n");
	if(state.handCount[player] == controlState.handCount[player] + 1)
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player] + 1, state.handCount[player]);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player] + 1, state.handCount[player]);
	}


	//************** Test deck count **************

	//Test that deck count is decremented by at least two
	printf("Testing Deck Count\n");
	if(state.deckCount[player] <= controlState.deckCount[player] - 2)
	{
		printf("PASS: Expected Value: <= %d  Actual Value: %d\n", controlState.deckCount[player] - 2, state.deckCount[player]);
	}
	else
	{
		printf("FAIL: Expected Value: <= %d  Actual Value: %d\n", controlState.deckCount[player] - 2, state.deckCount[player]);
	}

	//************** Test hand - added cards should be coins **************
	printf("Testing Added Cards\n");
	if((state.hand[player][state.handCount[player] - 1] == copper || 
		state.hand[player][state.handCount[player] - 1] == silver || 
		state.hand[player][state.handCount[player] - 1] == gold) &&
		(state.hand[player][state.handCount[player] - 2] == copper || 
		state.hand[player][state.handCount[player] - 2] == silver || 
		state.hand[player][state.handCount[player] - 2] == gold))
	{
		printf("PASS: Cards Added are Coins: %d, %d\n", state.hand[player][state.handCount[player] - 1], 
			state.hand[player][state.handCount[player] - 2]);
	}
	else
	{
		printf("FAIL: Cards Added not Coins: %d, %d\n", state.hand[player][state.handCount[player] - 1], 
			state.hand[player][state.handCount[player] - 2]);
	}

	//************** Test discard + deck count **************

	//test(discard + deck) = control(discard + deck - 2
	printf("Testing Discard and Deck Counts\n");
	if((state.deckCount[player] + state.discardCount[player]) == 
		(controlState.deckCount[player] + controlState.discardCount[player] - 2))
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", state.deckCount[player] + state.discardCount[player], 
			controlState.deckCount[player] + controlState.discardCount[player] - 2);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", state.deckCount[player] + state.discardCount[player], 
			controlState.deckCount[player] + controlState.discardCount[player] - 2);
	}

	//************** Test other players' hand count and deck count **************

	printf("Testing Other Players' Hand Count / Deck Count\n");
	for(i = 1; i < numPlayers; i++)
	{
		assert(state.handCount[i] == controlState.handCount[i]);
		assert(state.deckCount[i] == controlState.deckCount[i]);
	}
	printf("PASS: Other players' counts unchanged.\n");

	//************** Test supply piles **************
	printf("Test Supply Counts\n");
	for(i = 0; i < 25; i++)
	{
		assert(state.supplyCount[i] == controlState.supplyCount[i]);
	}
	printf("PASS: All supply counts unchanged.\n");

	return 0;
}