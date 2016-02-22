/* -----------------------------------------------------------------------
	* Testing isGameOver()
	* This function checks if the game over conditions are met
	* -----------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testIsGameOver(struct gameState *G)
{
	int emptySupplies;
	int card;
	int result = isGameOver(G);
	
	if(G->supplyCount[province] == 0)
	{
		if(result != 1)
		{
			printf("ERROR supplyCount was 0 and isGameOver failed.\n\n");
		}
	}
	else
	{
		emptySupplies = 0;
		for(card = 0; card <= treasure_map; card++)
		{
			if(G->supplyCount[card] == 0)
			{
				emptySupplies++;
			}
		}
		
		if(emptySupplies >= 3 && result !=1)
		{
			printf("ERROR 3 supply counts were empty and isGameOver failed.\n\n");
		}
	}
	
	return 0;
}

int main()
{
	struct gameState G;
	int provinceCount;
	int i;
	int j;
	
	SelectStream(2);
	PutSeed(3);
	printf("Testing isGameOver() unittest3.\n");
	
	for(provinceCount = 0; provinceCount < 3; provinceCount++)
	{
		for (i = 0; i < sizeof(struct gameState); i++) { //from the lessons, random gameState
			((char*)&G)[i] = floor(Random() * 256);
		}
		G.supplyCount[province] = provinceCount;
		
		testIsGameOver(&G);
	}
	//testing if supplyCount for other cards is 0
	//first fill up all cards
	for(j = 0; j <= treasure_map; j++)
	{
		G.supplyCount[j] = 5;
	}
	
	G.supplyCount[copper] = 0;
	G.supplyCount[silver] = 0;
	G.supplyCount[gold] = 0;
	
	testIsGameOver(&G);
	
	//fill up all cards
	for(j = 0; j <= treasure_map; j++)
	{
		G.supplyCount[j] = 5;
	}
	//only empty 2
	G.supplyCount[silver] = 0;
	G.supplyCount[gold] = 0;
	
	testIsGameOver(&G);
	
	 printf ("IsGameOver TESTS FINISHED\n\n");
	
	return 0;
}