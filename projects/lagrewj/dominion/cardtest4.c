/*Jonathan Lagrew
 *test playCouncil_Room()
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define MAX_HAND_TEST 200
#define MAX_DECK_TEST 200

int testPlayCouncil_Room(struct gameState *post, int handPos)
{
	int i;
	int p = post->whoseTurn;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	playCouncil_Room(post, handPos);
	
	//drawing 4 cards and discard council_room. Net gain = 3;
	pre.handCount[p] = pre.handCount[p] + 3;
	if(pre.handCount[p] != post->handCount[p])
	{
		printf("ERROR 1: current player %d should have net gain of 3 cards in hand! Pre count: %d Post count: %d\n", p, pre.handCount[p], post->handCount[p]);
	}
	//numBuys is incremented by 1
	pre.numBuys++;
	if(pre.numBuys != post->numBuys)
	{
		printf("ERROR 2: player did not get another Buy point. Pre numBuys: %d, Post numBuys: %d.\n", pre.numBuys, post->numBuys);
	}
	//every other player should have an extra card in their deck
	for(i = 0; i < pre.numPlayers; i ++)
	{
		if(i != p)
		{
			pre.handCount[i]++;
			
			if(pre.handCount[i] != post->handCount[i])
			{
				printf("ERROR 3: player %d did not recieve a card! Pre count: %d Post count: %d\n", i, pre.handCount[i], post->handCount[i]);
			}
		}
	}

	//still current player?
	if(pre.whoseTurn != post->whoseTurn)
		printf("ERROR: Current player has changed from %i to %i", pre.whoseTurn, post->whoseTurn);
	
	//check coins
	if(pre.coins != post->coins)
		printf("ERROR: Number of coins changed from %i to %i", pre.coins, post->coins);
	//check number of actions
	if(pre.numActions != post->numActions)
		printf("ERROR: Number of actions has changed from %i to %i", pre.numActions, post->numActions);
	
	return 0;
}

int main()
{
	int p;
	int numTests = 600;
	struct gameState G;
	int handPos;
	int numPlayers;
	int maxPlayers = 5;
	int i, j, m, n, q, r, s;
/* 	int k[10] = {adventurer, council_room, feast, gardens, mine
		   , remodel, smithy, village, baron, great_hall}; */
	
	SelectStream(2);
	PutSeed(3);
	printf("Testing playCouncil_Room() cardtest4.\n");
	
	for(s = 0; s < numTests; s++)
	{
		for(numPlayers = 2; numPlayers < maxPlayers; numPlayers++)
		{
			for(p = 0; p < numPlayers; p++)
			{
				for (i = 0; i < sizeof(struct gameState); i++) { //from the lessons, random gameState
					((char*)&G)[i] = floor(Random() * 256);
				}
				//initializeGame(numPlayers, k, 1, &G);
				G.whoseTurn = p;
				G.numPlayers = numPlayers;
				
				//give cards to all players
				for(j = 0; j < numPlayers; j++)
				{
					G.handCount[j] = floor(Random() * MAX_HAND_TEST)+1;//need at least one village in our hand
					G.deckCount[j] = floor(Random() * MAX_DECK_TEST);
					G.discardCount[j] = floor(Random() * MAX_DECK_TEST);
					
					for(m = 0; m < G.handCount[j]; m++)
					{
						G.hand[j][m] = floor(Random() * treasure_map) + 1;
					}
					
					for(r = 0; r < G.discardCount[j]; r++)
					{
						G.discard[j][r] = floor(Random() * treasure_map) + 1;
					}

					for(n = 0; n < G.deckCount[j]; n++)
					{
						G.deck[j][n] = floor(Random() * treasure_map) + 1;
					}

				}
				
				//only current player has played cards
				G.playedCardCount = floor(Random() * MAX_DECK_TEST);
				for(q = 0; q < G.playedCardCount; q++)
				{
					G.playedCards[q] = floor(Random() * treasure_map) + 1;
				}	
				G.numBuys = 1; //not buying cards so any number will do
				handPos = floor(Random() * G.handCount[p]);//place council_room in a random pos
				G.hand[p][handPos] = council_room;
				
				testPlayCouncil_Room(&G, handPos);
				
			}
		}
	}
	
	printf("PLAY COUNCIL_ROOM TESTS FINISHED.\n\n");
	return 0;
}