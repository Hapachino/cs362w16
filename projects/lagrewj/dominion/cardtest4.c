/*Jonathan Lagrew
 *cardtest4.c
 *test playCouncil_Room()
 *Notes:
 *Council Room is an Action card from the Base set. It is a terminal card draw, meaning it 
 *provides +Cards but no +Action. It is also an interactive card but not an attack, 
 *the huge benefit to you is counterbalanced by a pretty nice benefit to your opponent,
 *making them draw a card. It is extremely good when paired with a handsize attack such as Militia!
 */
 /*
 * Basic Requirements of Council_Room:
 * 1. Current player should receive a total of 4 cards from the deck. 
 * 2. Current player's buys should increase by 1. 
 * 3. No state change should occur for other players.
 * 4. No state change should occur to the victory drawnCard piles and kingdom card piles.
 * 5. Current player should be the same before and after the test.
 * 6. Number of actions should stay the same before and after the test. 
 * 7. Number of coins should stay the same before and after the test. 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#define MAX_HAND_TEST 200//setting max hand test value to 200
#define MAX_DECK_TEST 200//setting max deck test value to 200
#define TESTCARD "Council_Room"

int testPlayCouncil_Room(struct gameState *after, int handPos)
{
	
	int p = after->whoseTurn;//initialize whoseTurn stored as p 
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));
	
	playCouncil_Room(after, handPos);
	
	//drawing 4 cards and discard council_room. Net gain = 3;
	before.handCount[p] = before.handCount[p] + 3;
	if(before.handCount[p] != after->handCount[p])
	{
		printf("ERROR 1: current player %d should have net gain of 3 cards in hand! before count: %d after count: %d\n", p, before.handCount[p], after->handCount[p]);
	}
	//numBuys is incremented by 1
	before.numBuys++;
	if(before.numBuys != after->numBuys)
	{
		printf("ERROR 2: player did not get another Buy point. before numBuys: %d, after numBuys: %d.\n", before.numBuys, after->numBuys);
	}
	//every other player should have an extra card in their deck
	int i;
	for(i = 0; i < before.numPlayers; i ++)
	{
		if(i != p)
		{
			before.handCount[i]++;
			
			if(before.handCount[i] != after->handCount[i])
			{
				printf("ERROR 3: player %d did not recieve a card! before count: %d after count: %d\n", i, before.handCount[i], after->handCount[i]);
			}
		}
	}

	//still current player?
	if(before.whoseTurn != after->whoseTurn)
		printf("ERROR: Current player has changed from %i to %i", before.whoseTurn, after->whoseTurn);
	
	//check coins
	if(before.coins != after->coins)
		printf("ERROR: Number of coins changed from %i to %i", before.coins, after->coins);
	//check number of actions
	if(before.numActions != after->numActions)
		printf("ERROR: Number of actions has changed from %i to %i", before.numActions, after->numActions);
	
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
	
	//generates random tests
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
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
				
				G.whoseTurn = p;
				G.numPlayers = numPlayers;
				
				//filling in random cards based on lecture 11 and 12 Random Testing 
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
	
	printf("Play Council_Room testing has concluded.\n\n");
	return 0;
}