/*
*	Author: 	Martin Stryffeler
*	Filename:	cardtest1.c
*	Date:		2/2/2016
*
*	Smithy card effect testing
*	Action Sequence: Discard Smithy and draw three cards.
*	
*	Expected Results: 
*	HandCount increases by two
*	DeckCount decreases by three
*	Other players' states unchanged
*	Supply piles unchanged
*
*	Call: playSmithy(state, currentPlayer, handPos);
*	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//Initialize a game with a smithy in the first player's hand
int smithyInit(struct gameState *state)
{
	int player = 0;
	int numPlayers = 4;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	memset(state, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, state);
	state->hand[player][state->handCount[player] - 1] = smithy;

	return 0;
}

//Compare hand count to a control
int compareHandCount(int player, struct gameState *state, struct gameState *controlState)
{
	if(state->handCount[player] == controlState->handCount[player] + 2)
	{
		printf("PASS: Expected Handcount: %d  Actual: %d\n", controlState->handCount[player] + 2, state->handCount[player]);
	}
	else
	{
		printf("FAIL: Expected Handcount: %d  Actual: %d\n", controlState->handCount[player] + 2, state->handCount[player]);
	}

	return 0;
}

//Compare deck count to a control
int compareDeckCount(int player, struct gameState *state, struct gameState *controlState)
{
	if(state->deckCount[player] == controlState->deckCount[player] - 3)
	{
		printf("PASS: Expected Deckcount: %d  Actual: %d\n", controlState->deckCount[player] - 3, state->deckCount[player]);
	}
	else
	{
		printf("FAIL: Expected Deckcount: %d  Actual: %d\n", controlState->deckCount[player] - 3, state->deckCount[player]);
	}

	return 0;
}

//Check that smithy is removed from the player's hand
int smithyInHand(int player, struct gameState *state)
{
	int i;							//Index
	int smithyCardFlag = 0;			//Smithy card in hand boolean

	//Smithy no longer in hand
	//There are no smithy cards in the deck, so we can be sure that the top card should not be a smithy.
	for(i = 0; i < state->handCount[player]; i++)
	{
		if(state->hand[player][i] == smithy)
		{
			smithyCardFlag = 1;
		}
	}
	
	if(!smithyCardFlag)
	{
		printf("PASS: Smithy no longer in player's hand.\n");
	}
	else
	{
		printf("FAIL: Smithy still in player's hand.\n");
	}

	return 0;
}

//Check that other players' states are unchanged
int comparePlayerState(int player, struct gameState *state, struct gameState *controlState)
{
	int i;	//Index
	for(i = 0; i < state->numPlayers; i++)
	{
		if(i != player)
		{
			if(state->deckCount[i] == controlState->deckCount[i] && state->handCount[i] == controlState->handCount[i])
			{
				printf("PASS: Player %d's deck and hand unchanged.\n", i);
			}
			else
			{
				printf("FAIL: Player %d's deck and hand changed by Smithy cardEffect.\n", i);
			}
		}
	}
	return 0;
}

//Check that every card's supply count is unchanged
int compareSupplyCount(int player, struct gameState *state, struct gameState *controlState)
{
	int i;							//Index
	int supplyCountFlag = 0;		//Disrupted supply count boolean

	//Supply piles
	for(i = 0; i < 25; i++)
	{
		if(state->supplyCount[i] != controlState->supplyCount[i])
		{
			supplyCountFlag = 1;
		}
	}

	if(!supplyCountFlag)
	{
		printf("PASS: All supply counts unchanged.\n");
	}
	else
	{
		printf("FAIL: Supply counts changed by Smithy cardEffect.\n");
	}

	return 0;
}

int main()
{
	int i, j;
	int choice1, choice2, choice3, handPos, bonus, player;
	choice1 = choice2 = choice3 = handPos = bonus = player = 0;

	struct gameState state, controlState;

	printf("\nTESTING Smithy cardEffect\n");
	printf("Testing Deck Count\n");
	for(i = 3; i < 12; i++)
	{
		smithyInit(&state);
		smithyInit(&controlState);
		state.deckCount[player] = i;
		printf("Starting Deck Count %d ", i);
		for(j = 0; j < i; j++)
		{
			state.deck[player][i] = copper;
		}
		handPos = state.handCount[player] - 1;
		memcpy(&controlState, &state, sizeof(struct gameState));
		//cardEffect(smithy, choice1, choice2, choice3, &state, handPos, &bonus);
		playSmithy(&state, state.whoseTurn, handPos);
		compareDeckCount(player, &state, &controlState);
	}

	printf("Testing Hand Count\n");
	for(i = 1; i < 5; i++)
	{
		smithyInit(&state);
		smithyInit(&controlState);
		state.handCount[player] = i;
		printf("Starting Hand Count %d ", i);
		for(j = 0; j < i; j++)
		{
			state.hand[player][j] = copper;
		}
		state.hand[player][i - 1] = smithy;
		handPos = state.handCount[player] - 1;
		memcpy(&controlState, &state, sizeof(struct gameState));
		//cardEffect(smithy, choice1, choice2, choice3, &state, handPos, &bonus);
		playSmithy(&state, state.whoseTurn, handPos);
		compareHandCount(player, &state, &controlState);
	}
	
	printf("Testing Smithy Discard\n");
	for(i = 0; i < 5; i++)
	{
		smithyInit(&state);
		smithyInit(&controlState);
		for(j = 0; j < 5; j++)
		{
			state.hand[player][j] = copper;
		}
		state.hand[player][i] = smithy;
		handPos = i;
		memcpy(&controlState, &state, sizeof(struct gameState));
		//cardEffect(smithy, choice1, choice2, choice3, &state, handPos, &bonus);
		playSmithy(&state, state.whoseTurn, handPos);
		smithyInHand(player, &state);
	}

	printf("Testing Other Players' State\n");
	for(i = 0; i < 4; i++)
	{
		smithyInit(&state);
		smithyInit(&controlState);
		handPos = state.handCount[player] - 1;
		//cardEffect(smithy, choice1, choice2, choice3, &state, handPos, &bonus);
		playSmithy(&state, state.whoseTurn, handPos);
		comparePlayerState(player, &state, &controlState);
	}

	printf("Testing Supply Counts\n");
	smithyInit(&state);
	smithyInit(&controlState);
	handPos = state.handCount[player] - 1;
	//cardEffect(smithy, choice1, choice2, choice3, &state, handPos, &bonus);
	playSmithy(&state, state.whoseTurn, handPos);
	compareSupplyCount(player, &state, &controlState);

	return 0;
}