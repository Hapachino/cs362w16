/*********************************************************************
** Program Filename: unittest3.c
** Author: Kyle Johnson
** Date: 2/2/2016
** Description: implementation file for isGameOver() testing
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testIsGameOver(struct gameState *G)
{
	int noSupply;
	int card;
	int result = isGameOver(G);
	
	if(G->supplyCount[province] == 0)
	{
		if(result != 1)
			printf("FAILED - function call failed\n");
	}
	else
	{
		printf("PASSED - function call did not fail\n");
		return 0;
	}
	
	noSupply = 0;
	for(card = 0; card <= treasure_map; card++)
	{
		if(G->supplyCount[card] == 0)
			noSupply++;
	}
	
	if(noSupply >= 3 && result !=1)
		printf("FAILED - 3 supply piles are empty and game should be over\n");
	else
		printf("PASSED - game is over with 3 empty supply piles\n");
	
	return 0;
}

int main()
{
	struct gameState G;
	int provinces;
	int i, j, k, l;
	
	SelectStream(2);
	PutSeed(3);
	printf("----------------- Testing isGameOver(): ----------------\n");
	//test that game ends when province pile is empty
	for(provinces = 0; provinces < 3; provinces++)
	{
		for (i = 0; i < sizeof(struct gameState); i++)
			((char*)&G)[i] = floor(Random() * 256);
		
		G.supplyCount[province] = provinces;
		testIsGameOver(&G);
	}
	//reset deck supply
	for(j = 0; j <= treasure_map; j++)
		G.supplyCount[j] = 5;
	
	//50 random tests for 0-3 empty piles
	for (l = 0; l < 50; l++)
	{
		k = floor(Random() * 3 + 1);
		
		if (k == 1)
			G.supplyCount[copper] = 0;
		else if (k == 2)
		{
			G.supplyCount[copper] = 0;
			G.supplyCount[silver] = 0;
		}
		else
		{
			G.supplyCount[copper] = 0;
			G.supplyCount[silver] = 0;
			G.supplyCount[gold] = 0;
		}

		testIsGameOver(&G);
	}
	
	
	printf ("testing completed for isGameOver\n");
	
	return 0;
}