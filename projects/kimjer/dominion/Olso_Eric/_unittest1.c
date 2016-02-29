#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

int main() {

	printf("-------------------------------------\n");
	printf("START of the unittest1\n");
	printf("-------------------------------------\n");
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
		//assert(ret == 0);
		if(i == province)
		{
			if(ret == 0)
				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
			assert(ret == 1);
		}
		else
		{
			if(ret == 1)
				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
			assert(ret == 0);
		}
		G.supplyCount[i] = 1;
	}
	printf("PASS when any one supply is set to 0\n");


	//random testing when any two supplies are 0
	SelectStream(1);
	PutSeed((long)time(NULL));
	
	for(i = 0; i < 10000; i++) 
	{
		int r1, r2;
		r1 = floor(Random()*25);
		do
			r2 = floor(Random()*25);
		while(r2 == r1);

		G.supplyCount[r1] = 0;
		G.supplyCount[r2] = 0;
		ret = isGameOver(&G);

		if(r2 == province || r1 == province)
		{
			//if province is 0, game should be over
			if(ret == 0)
				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
			assert(ret == 1);
		}
		else
		{
			if(ret == 1)
				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
			assert(ret == 0);
		}
		G.supplyCount[r1] = 1;
		G.supplyCount[r2] = 1;
	}
	printf("PASS when any two supplies are set to 0\n");

	//random testing when any three supplies are 0

	for(i = 0; i < 10000; i++) 
	{
		int r1, r2, r3;
		r1 = floor(Random()*25);
		do
			r2 = floor(Random()*25);
		while(r2 == r1);

		do
			r3 = floor(Random()*25);
		while(r3 == r1 || r3 == r2 );


		G.supplyCount[r1] = 0;
		G.supplyCount[r2] = 0;
		G.supplyCount[r3] = 0;
		ret = isGameOver(&G);

		//if three supplies are 0 game should be over
		if(ret == 0)
			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
		assert(ret == 1);
		
		G.supplyCount[r1] = 1;
		G.supplyCount[r2] = 1;
		G.supplyCount[r3] = 1;
	}

	printf("PASS when any three supplies are set to 0\n");
	printf("-------------------------------------\n");
	return 0;
}
