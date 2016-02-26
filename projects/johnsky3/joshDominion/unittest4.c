/*********************************************************************
** Program Filename: unittest4.c
** Author: Kyle Johnson
** Date: 2/2/2016
** Description: implementation file for shuffle() function testing
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testShuffle(int player, struct gameState *G)
{
	struct gameState testG;
	memcpy(&testG, G, sizeof(struct gameState));
	
	int call = shuffle(player, G);
	
	if(call != 0)
		printf("FAILED - function call failed\n");
	else
		printf("PASSED - function call did not fail\n");
	
	//compare deck counts
	if(testG.deckCount[player] != G->deckCount[player])
		printf("FAILED - deck counts do not match\n");
	else
		printf("PASSED - deck counts match\n");
	//test if deck changed after shuffle
	if(memcmp(&testG.deck[player], G->deck[player], sizeof(int) * testG.deckCount[player]) == 0)
		printf("FAILED - deck is in same order.\n");
	else
		printf("PASSED - deck is not in same order\n");
	
	return 0;
}

int main()
{
	struct gameState G; 
	int numPlayers = 2;
	int p, i, j;
	int deckNum;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	
	SelectStream(2);
	PutSeed(3);
	printf("----------------- Testing shuffle(): ----------------\n");
	
		for(p = 0;  p < numPlayers; p++)
		{
			for(deckNum = 10; deckNum < 100; deckNum+=2) 
			{
				for (i = 0; i < sizeof(struct gameState); i++)
					((char*)&G)[i] = floor(Random() * 256);
				
				for(j = 0; j < deckNum; j++) //fill deck
				{
					int card = floor(Random() * 10);	
					G.deck[p][j] = k[card];
				}
				G.numPlayers = numPlayers;
				G.deckCount[p] = deckNum;
				
				testShuffle(p, &G);
			}
		}
	 printf ("completed shuffle() testing\n");
	
	return 0;
}