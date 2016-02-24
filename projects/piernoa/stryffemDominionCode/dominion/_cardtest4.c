/*
*	Author: 	Martin Stryffeler
*	Filename:	cardtest4.c
*	Date:		2/2/2016
*
*	Steward card effect testing
*	
*	Action Sequence:
*	Do one of: draw two cards, get two coins, or trash two cards from your hand.
*
*	Expected Results:
*	Choice: Draw Cards:
*		player's hand is incremented by one
*		player's deck is decremented by two
*		player's coins remain unchanged
*	Choice: Coins
*		player's hand decremented by one
*		player's coins are incremented by two
*		player's deck remains unchanged
*	Choice: Trash
*		player's hand is decremented by three
*		chosen cards are removed from play
*		player's coins, deck remain unchanged
*	
*	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
	int i, j, m;
	int handPos, choice1, choice2, choice3, bonus, player;
	handPos = choice1 = choice2 = choice3 = bonus = player = 0;
	int trash1, trash2;
	int seed = 1000;
	int numPlayers = 2;
	int k[10] = {adventurer, council_room, steward, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState state, controlState;

	initializeGame(numPlayers, k, seed, &state);

	printf("\nTESTING Steward cardEffect\n");

	//************** Test choice1 = 1: +2 cards **************
	printf("\nTesting Choice: Draw Two Cards\n");

	//Set gameState, choice, and call cardEffect
	memcpy(&controlState, &state, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(steward, choice1, choice2, choice3, &state, handPos, &bonus);

	//Test handCount incremented by one
	printf("Testing Hand Count\n");
	if(state.handCount[player] == controlState.handCount[player] + 1)
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player] + 1, state.handCount[player]);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player] + 1, state.handCount[player]);
	}

	//Test deckCount decremented by two
	printf("Testing Deck Count\n");
	if(state.deckCount[player] == controlState.deckCount[player] - 2)
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.deckCount[player] - 2, state.deckCount[player]);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.deckCount[player] - 2, state.deckCount[player]);
	}

	//Test coins unchanged
	printf("Testing Coin Count\n");
	if(state.coins == controlState.coins)
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.coins, state.coins);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.coins, state.coins);
	}


	//************** Test choice1 = 2: +2 coins **************
	printf("\nTesting Choice: Two Coins\n");

	//Reset game state, set choice, and call cardEffect
	memcpy(&state, &controlState, sizeof(struct gameState));
	choice1 = 2;
	cardEffect(steward, choice1, choice2, choice3, &state, handPos, &bonus);

	//Test handCount decremented by one
	printf("Testing Hand Count\n");
	if(state.handCount[player] == controlState.handCount[player] - 1)
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player] - 1, state.handCount[player]);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player] - 1, state.handCount[player]);
	}

	//Test deckCount unchanged
	printf("Testing Deck Count\n");
	if(state.deckCount[player] == controlState.deckCount[player])
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.deckCount[player], state.deckCount[player]);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.deckCount[player], state.deckCount[player]);
	}

	//Test coins incremented by two
	printf("Testing Coin Count\n");
	if(state.coins == controlState.coins + 2)
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.coins + 2, state.coins);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.coins + 2, state.coins);
	}


	//************** Test choice1 = 3: trash two cards **************
	printf("\nTesting Choice: Trash Two Cards\n");
	choice1 = 3;

	//Reset gameState
	memcpy(&state, &controlState, sizeof(struct gameState));

	//Trash each possible combination
	for(i = 1; i < state.handCount[player]; i++)
	{
		for(j = i + 1; j < state.handCount[player]; j++)
		{
			state.hand[player][0] = steward;
			state.hand[player][1] = estate;
			state.hand[player][2] = smithy;
			state.hand[player][3] = silver;
			state.hand[player][4] = copper;

			printf("Starting hand:\n");
			for(m = 0; m < state.handCount[player]; m++)
			{
				printf("%d: %d\n", m, state.hand[player][m]);
			}

			choice2 = j;
			choice3 = i;
			trash1 = state.hand[player][i];
			trash2 = state.hand[player][j];
			cardEffect(steward, choice1, choice2, choice3, &state, handPos, &bonus);

			printf("Removing: %d, %d\n", trash1, trash2);
			printf("Cards remaining:\n");

			for(m = 0; m < state.handCount[player]; m++)
			{
				printf("%d: %d\n", m, state.hand[player][m]);
				assert(state.hand[player][m] != trash1);
				assert(state.hand[player][m] != trash2);
			}

			printf("PASS: Trashed cards removed from hand\n");

			//Reset gameState
			memcpy(&state, &controlState, sizeof(struct gameState));
		}
	}

	//Test handcount, deckcount, and coins after trashing

	//Reset game state, set choice, and call cardEffect
	memcpy(&state, &controlState, sizeof(struct gameState));
	choice1 = 3;
	choice2 = 1;
	choice3 = 2;
	cardEffect(steward, choice1, choice2, choice3, &state, handPos, &bonus);

	//Test handCount decremented by three
	printf("\nTesting Hand Count\n");
	if(state.handCount[player] == controlState.handCount[player] - 3)
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player] - 3, state.handCount[player]);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.handCount[player] - 3, state.handCount[player]);
	}

	//Test deckCount unchanged
	printf("Testing Deck Count\n");
	if(state.deckCount[player] == controlState.deckCount[player])
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.deckCount[player], state.deckCount[player]);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.deckCount[player], state.deckCount[player]);
	}

	//Test coins unchanged
	printf("Testing Coin Count\n");
	if(state.coins == controlState.coins)
	{
		printf("PASS: Expected Value: %d  Actual Value: %d\n", controlState.coins, state.coins);
	}
	else
	{
		printf("FAIL: Expected Value: %d  Actual Value: %d\n", controlState.coins, state.coins);
	}
	return 0;
}