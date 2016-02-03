/*
*	Author: 	Martin Stryffeler
*	Filename:	unittest3.c
*	Date:		2/2/2016
*
*	isGameOver() function unit testing
*	Initializes a gamestate, then tests isGameOver with varying game states
*	with varying numbers and types of empty and near empty piles.
*
*	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Puts one card into each card's supply
int fillSupply(struct gameState *state)
{
	int i;

	for(i = 0; i < 25; i++)
	{
		state->supplyCount[i] = 1;
	}

	return 0;
}

int main()
{
	int i, j, m;
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState state;
	memset(&state, 23, sizeof(struct gameState));
	initializeGame(numPlayer, k, seed, &state);

	printf("\nTESTING isGameOver():");
	//Test province 0/1 edge case
	printf("\nTesting 1 province remaining.\n");
	state.supplyCount[province] = 1;
	assert(isGameOver(&state) == 0);
	printf("PASS: Game not over.\n");

	printf("\nTesting 0 provinces remaining.\n");
	state.supplyCount[province] = 0;
	assert(isGameOver(&state) == 1);
	printf("PASS: Game over.\n");

	//Test no empty piles
	printf("\nTesting no empty piles.\n");
	fillSupply(&state);
	assert(isGameOver(&state) == 0);
	printf("PASS: Game not over.\n");

	//Test one empty pile
	printf("\nTesting one empty pile. (Skipping provinces)\n");
	for(i = 0; i < 25; i++)
	{
		if(i != 3)	//Skip provinces - only looking at non province piles
		{
			fillSupply(&state);
			state.supplyCount[i] = 0;
			assert(isGameOver(&state) == 0);
			
		}
	}
	printf("PASS: No single non-province empty pile ends the game.\n");

	//Test two empty piles
	printf("\nTesting two empty piles. (Skipping provinces)\n");
	for(i = 0; i < 25; i++)
	{
		for(j = 0; j < 25; j++)
		{
			if(i != 3 && j != 3 && i != j)
			{
				fillSupply(&state);
				state.supplyCount[i] = 0;
				state.supplyCount[j] = 0;
				assert(isGameOver(&state) == 0);
				
			}
		}
	}
	printf("PASS: No two empty non-province piles ends the game.\n");

	//Test three empty piles
	printf("\nTesting three empty piles. (Including provinces)\n");
	for(i = 0; i < 25; i++)
	{
		for(j = 0; j < 25; j++)
		{
			for(m = 0; m < 25; m++)
			{
				if(i != j && i != m && j != m)
				{
					fillSupply(&state);
					state.supplyCount[i] = 0;
					state.supplyCount[j] = 0;
					state.supplyCount[m] = 0;
					assert(isGameOver(&state) == 1);
				}
			}
		}
	}
	printf("PASS: Any combination of three empty piles ends the game.\n");

	return 0;
}