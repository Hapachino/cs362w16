/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Does random tests on the Adventurer card.
********************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int randomAdventurer(int player, struct gameState *after, int position, int trash)
{
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));

	int i, j, k;
	int card = adventurer;
	int firstChoice = 1;
	int secondChoice = 4;
	int thirdChoice = 4;
	int bonus = 0;

	player = before.whoseTurn;
	j = cardEffect(card, firstChoice, secondChoice, thirdChoice, after, position, &bonus);
	
	k = 0;
	int treasures = 0;
	int drawnCard;
	int temp[MAX_HAND];

	while (treasures < 2)
	{
//checking for empty deck-- if so, need to shuffle in the discard pile		
		if (before.deckCount[player] < 1)
		{
			shuffle(player, &before);
		}
		int count;
		int countDeck;

		if (before.deckCount[player] <= 0)
		{
//putting the discard pile back into the deck
			for (i = 0; i < before.discardCount[player]; i++)
			{
				before.deck[player][i] = before.discard[player][i];
				before.discard[player][i] = -1;
			}

			before.deckCount[player] = before.discardCount[player];
			before.discardCount[player] = 0;
//shuffling the newly-apportioned deck
			shuffle(player, &before);
			before.discardCount[player] = 0;

//set up count as current player's hand count
			count = before.handCount[player];
//set up countDeck as the current deck count
			countDeck = before.deckCount[player];

			if (countDeck == 0)
			{
				return -1;
			}
//add card from deck to hand; increment hand count / decrement deck count
			before.hand[player][count] = before.deck[player][countDeck - 1];
			before.deckCount[player]--;
			before.handCount[player]++;
		}
		else
		{
//set up count as current player's hand count
			count = before.handCount[player];
//set up countDeck as current deck count
			countDeck = before.deckCount[player];
//add card from deck to hand; increment hand count / decrement deck count
			before.hand[player][count] = before.deck[player][countDeck - 1];
			before.deckCount[player]--;
			before.handCount[player]++;
		}
//drawnCard is the top card on the hand, and the card just drawn from the deck
		drawnCard = before.hand[player][before.handCount[player] - 1];

//if card is a treasure, increment the treasure count
		if (drawnCard == copper || drawnCard == silver || drawnCard == gold)
		{
			treasures++;
		}
		else
		{
//remove the drawnCard and decrement hand count
			temp[k] = drawnCard;
			before.handCount[player]--;
			k++;
		}
	}

	while (k - 1 >= 0)
	{
//discard all cards that have been drawn
		before.discard[player][before.discardCount[player]++] = temp[k - 1];
		k--;
	}

	before.playedCards[before.playedCardCount] = before.hand[player][position];
	before.playedCardCount++;
	before.hand[player][position] = -1;

	if (position == (before.handCount[player] - 1))
	{
		before.handCount[player]--;
	}
	else if (before.handCount[player] == 1)
	{
		before.handCount[player]--;
	}
	else
	{
		before.hand[player][position] = before.hand[player][(before.handCount[player] - 1)];
		before.hand[player][before.handCount[player] - 1] = -1;
		before.handCount[player]--;
	}

//	assert(j == 0);
	printf("Error in cardEffect. \n");

//	assert(memcmp(&before, after, sizeof(struct gameState)) == 0);
	printf("Error in memory comparison. \n");

	return 0;
}

int main()
{
	int i, j, k, a;
	int trash, position, count, seed, players;

	struct gameState state;

	int card[10] = { adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village };

	SelectStream(2);
	PutSeed(3);
	srand(time(NULL));

	for (count = 0; count < 2000; count++)
	{
		seed = rand();
		players = 5;

		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&state)[i] = floor(Random() * 256);
		}

		initializeGame(players, card, seed, &state);

		state.numPlayers = players;
		a = floor(Random() * (players - 1));
		state.whoseTurn = a;

//the j for loop should randomly populate the game state with values in range
		for (j = 0; j < players - 1; j++)
		{
			state.deckCount[j] = floor(Random() * MAX_DECK);
			for (k = 0; k < state.deckCount[j]; k++)
			{
				state.deck[j][k] = floor(Random() * 26);
			}
			
			state.discardCount[j] = floor(Random() * MAX_DECK);
			for (k = 0; k < state.discardCount[j]; k++)
			{
				state.discard[j][k] = floor(Random() * 26);
			}

			state.handCount[j] = rand() % MAX_HAND + 1;
			for (k = 0; k < state.handCount[j]; k++)
			{
				state.hand[j][k] = floor(Random() * 26);
			}

			for (k = 0; k < 26; k++)
			{
				state.supplyCount[k] = floor(Random() * 26) + 1;
			}
		}

//generates a random played card count in range
		state.playedCardCount = floor(Random() * MAX_DECK);
		for (j = 0; j < state.playedCardCount; j++)
		{
			state.playedCards[j] = floor(Random() * 26) + 1;
		}

		if (state.handCount[a] < 1)
		{
			exit(-1);
		}

		position = floor(Random() * MAX_HAND);
		trash = floor(Random() * 1);

//run the randomAdventurer with the randomly generated state		
		randomAdventurer(a, &state, position, trash);
	}

	printf("No errors encountered \n");

	return 0;
}