/*
*	gainCard() function unit testing
*	Initializes a gamestate, then tests gainCard with varying game states,
*	chosen cards, and destinations(toFlag).
*
*	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

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
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState state, stateCopy;
	memset(&state, 23, sizeof(struct gameState));
	initializeGame(numPlayer, k, seed, &state);

	printf("\nTESTING gainCard()\n");
	//Check return values for chosen cards with empty / near empty supply
	//Give each supply pile one card
	//Test return value for gaining each kind of card with one available
	//Then test return value for each card with none available
	printf("\nTest one card remaining.\n");
	fillSupply(&state);
	for(i = 0; i < 25; i++)
	{
		assert(gainCard(i, &state, 1, 0) == 0);
	}
	printf("PASS: gainCard successful with one card remaining.\n");

	printf("\nTest no cards remaining.\n");
	for(i = 0; i < 25; i++)
	{
		assert(gainCard(i, &state, 1, 0) == -1);
	}
	printf("PASS: gainCard terminates early with no supply remaining.\n");

	//Check that supply decreases when a card is gained
	printf("\nTest supply decrementing.\n");
	memset(&state, 23, sizeof(struct gameState));
	initializeGame(numPlayer, k, seed, &state);
	
	for(i = 0; i < 25; i++)
	{
		state.supplyCount[i] = 10;
		memcpy(&stateCopy, &state, sizeof(struct gameState));
		gainCard(i, &state, 1, 0);
		assert(state.supplyCount[i] == stateCopy.supplyCount[i] - 1);
	}
	printf("PASS: supply decrements by one when gainCard is called.\n");

	//Check that the chosen card goes to the given destination
	memset(&state, 23, sizeof(struct gameState));
	initializeGame(numPlayer, k, seed, &state);

	printf("\nTest that gained card goes to correct destination.\n");

	//Test hand
	printf("\nTest that chosen card goes to the player's hand.\n");
	for(i = 0; i < 25; i++)
	{
		memset(&state, 23, sizeof(struct gameState));
		initializeGame(numPlayer, k, seed, &state);
		state.supplyCount[i] = 10;
		memcpy(&stateCopy, &state, sizeof(struct gameState));
		gainCard(i, &state, 2, 0);
		assert(state.hand[0][state.handCount[0]-1] == i);
		assert(state.handCount[0] == stateCopy.handCount[0] + 1);
	}
	printf("PASS: chosen card goes to the player's hand and handCount increments in each case.\n");

	//Test deck
	printf("\nTest that chosen card goes to the player's deck.\n");
	for(i = 0; i < 25; i++)
	{
		memset(&state, 23, sizeof(struct gameState));
		initializeGame(numPlayer, k, seed, &state);
		state.supplyCount[i] = 10;
		memcpy(&stateCopy, &state, sizeof(struct gameState));
		gainCard(i, &state, 1, 0);
		assert(state.deck[0][state.deckCount[0]-1] == i);
		assert(state.deckCount[0] == stateCopy.deckCount[0] + 1);
	}
	printf("PASS: chosen card goes to the player's deck and deckCount increments in each case.\n");

	//Test discard
	printf("\nTest that chosen card goes to the player's discard pile.\n");
	for(i = 0; i < 25; i++)
	{
		memset(&state, 23, sizeof(struct gameState));
		initializeGame(numPlayer, k, seed, &state);
		state.supplyCount[i] = 10;
		memcpy (&stateCopy, &state, sizeof(struct gameState));
		gainCard(i, &state, 0, 0);
		assert(state.discard[0][state.discardCount[0]-1] == i);
		assert(state.discardCount[0] == stateCopy.discardCount[0] + 1);
	}
	printf("PASS: chosen card goes to the player's discard pile and discardCount increments in each case.\n");

	return 0;
}