#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

int main() {
	printf("this is the unittest1\n");
	struct gameState G;
	struct gameState G2;
	int i, j;
	int numPlayers = 2;
	// Initialize G.
	  //set number of Kingdom cards
	for(i = 0; i < 25; i++) {
		G.supplyCount[i] = 1;
	}
	
	G.supplyCount[province] = 10;

	int ret = isGameOver(&G);
	if(ret == 0) 
	{
		printf("PASS when all supply count is 1\n");
	}
	else
	{
		printf("FAIL when all supply count is 1\n");
	}
	assert(ret == 0);


	for(i = 0; i < 25; i++) {
		G.supplyCount[i] = 0;
		ret = isGameOver(&G);
		assert(ret == 0);
		G.supplyCount[i] = 1;
		printf("hello\n");
	}

	printf("PASS when 1 supply count is 0\n");

	SelectStream(1);
	PutSeed((long)time(NULL));
	
	for(i = 0; i < 25; i++) {
		int r1, r2;
		r1 = floor(Random()*25);
		do
			r2 = floor(Random()*25);
		while(r2 == r1);

		G.supplyCount[r1] = 0;
		G.supplyCount[r2] = 0;
		ret = isGameOver(&G);
		assert(ret == 0);
		G.supplyCount[r1] = 1;
		G.supplyCount[r2] = 1;
	}

	return 0;
}
