/*
*	scoreFor() function unit testing
*	Initializes a gamestate, then tests scoreFor() with a hand, a deck,
*	and a discard pile full of each score affecting card.
*
*	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//Sets all cards in hand, deck, and discard pile to copper
//They won't affect the score, and we can examine the scoring cards we choose in isolation
int initDeck(int player, struct gameState *state)
{
	int i;

	for(i = 0; i < state->handCount[player]; i++)
		state->hand[player][i] = copper;

	for(i = 0; i < state->discardCount[player]; i++)
		state->discard[player][i] = copper;

	for(i = 0; i < state->deckCount[player]; i++)
		state->deck[player][i] = copper;

	return 0;
}

int computeScore(int player, int card, int count, struct gameState *state)
{
	int value = 0;

	switch(card)	
	{
		case curse:
			value = -1;
			break;

		case estate:
			value = 1;
			break;

		case duchy:
			value = 3;
			break;

		case province:
			value = 6;
			break;

		case gardens:
			value = (fullDeckCount(player, 0, state) / 10);
			break;

		case great_hall:
			value = 1;
			break;

		default:
			value = 0;
			break;
	}

	return value * count;
}

int main()
{
	int i, j;
	int seed = 1000;

	int maxHand = 5;
	int maxDiscard = 11;
	int maxDeck = 11;

	int numPlayer = 2;
	int player, handCount, deckCount, discardCount;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int victoryCards[6] = {curse, estate, duchy, province, gardens, great_hall};
	
	struct gameState state;

	int actualScore;
	int expectedScore;

	printf("\nTESTING scoreFor():");
	//for each player
	for(player = 1; player < numPlayer; player++)
	{
		//for each victory card
		for(i = 0; i < 6; i++)
		{
			printf("\nTest player %d with victory cards of type %d.\n", player, victoryCards[i]);
			//for each possible hand size
			printf("HAND\n");
			for(handCount = 0; handCount < maxHand; handCount++)
			{
				memset(&state, 23, sizeof(struct gameState));
				initializeGame(numPlayer, k, seed, &state);

				initDeck(player, &state);
				state.handCount[player] = handCount;

				//fill player's hand with card
				for(j = 0; j < handCount; j++)
				{
					state.hand[player][j] = victoryCards[i];
				}

				//test score
				expectedScore = computeScore(player, victoryCards[i], handCount, &state);
				actualScore = scoreFor(player, &state);
				if(expectedScore == actualScore)
				{
					printf("PASS: Expected Score: %d  Actual Score: %d\n", expectedScore, actualScore);
				}
				else
				{
					printf("FAIL: Expected Score: %d  Actual Score: %d\n", expectedScore, actualScore);
				}
				
			}
			//for each possible discard size
			printf("DISCARD\n");
			for(discardCount = 0; discardCount < maxDiscard; discardCount++)
			{
				//fill player's discard pile with card and check score
				memset(&state, 23, sizeof(struct gameState));
				initializeGame(numPlayer, k, seed, &state);

				initDeck(player, &state);
				state.discardCount[player] = discardCount;

				for(j = 0; j < discardCount; j++)
				{
					state.discard[player][j] = victoryCards[i];
				}

				expectedScore = computeScore(player, victoryCards[i], discardCount, &state);
				actualScore = scoreFor(player, &state);
				if(expectedScore == actualScore)
				{
					printf("PASS: Expected Score: %d  Actual Score: %d\n", expectedScore, actualScore);
				}
				else
				{
					printf("FAIL: Expected Score: %d  Actual Score: %d\n", expectedScore, actualScore);
				}
			}
			//for each possible deck size
			printf("DECK\n");
			for(deckCount = 0; deckCount < maxDeck; deckCount++)
			{
				//fill player's deck with card and check score
				memset(&state, 23, sizeof(struct gameState));
				initializeGame(numPlayer, k, seed, &state);

				initDeck(player, &state);
				state.deckCount[player] = deckCount;

				for(j = 0; j < deckCount; j++)
				{
					state.deck[player][j] = victoryCards[i];
				}

				expectedScore = computeScore(player, victoryCards[i], deckCount, &state);
				actualScore = scoreFor(player, &state);
				if(expectedScore == actualScore)
				{
					printf("PASS: Expected Score: %d  Actual Score: %d\n", expectedScore, actualScore);
				}
				else
				{
					printf("FAIL: Expected Score: %d  Actual Score: %d\n", expectedScore, actualScore);
				}

			}
		}
	}
	return 0;
}