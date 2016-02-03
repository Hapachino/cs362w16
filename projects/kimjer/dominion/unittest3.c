#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#define NUMCARDS 10
#define NUMTRIALS 100000

int* getUniqueCards() 
{
	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
}

void ASSERT2(int testVal, int assVal, char *s) 
{	
	if(assVal != testVal) 
	{
		printf("FAIL - %s\n", s);
		printf("ASSERTED value is %d; got %d", assVal, testVal);
		assert(assVal == testVal);
		exit(1);
	}
}

int cardsAreUnique(int k[]) 
{
	int i, j;
	//check selected kingdom cards are different (from dominion.c)
	for (i = 0; i < NUMCARDS; i++)
	{
		for (j = 0; j < NUMCARDS; j++)
		{
			if (j != i && k[j] == k[i])
			{
				return -1;
			}
		}
	}
	return 0;
}

int cardsAreCorrectVals(int k[]) {
	int i;
	for(i = 0; i < NUMCARDS; i++) 
	{
		if(k[i] > treasure_map || k[i] < adventurer) {
			return -1;
		}
	}
	return 0;
}

int test1(int seed) 
{
	int i, j;
	int *k = (int*)malloc(sizeof(int)*NUMCARDS);

	int numPlayers = (rand()% 3) + 2;
	int ret = -1;

	struct gameState *G = newGame();
//	struct gameState *Gcpy = newGame();
	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique

	printf("TEST #1: Kingdom cards random testing\n");
	printf("\t should return 0 if unique; -1 if non-unique\n");
	for(i = 0; i < NUMTRIALS; i++)
	{
		for(j = 0; j < NUMCARDS; j++) {
			k[j] = (rand()%15);
		}
		ret = initializeGame(numPlayers, k, seed, G);
		int cret = cardsAreUnique(k);
		if(cret == 0) {
			ASSERT2(ret, 0, "FAIL when cards are unique");
		}
		else {
			ASSERT2(ret, -1, "FAIL when cards are non-unique");
		}
	}

	printf("PASS\n");
	printf("------------------\n");
	free(G);
	free(k);
}

int test2(int seed) {
	struct gameState *G = newGame();
	//struct gameState *Gcpy = newGame();
	int i;
	int numPlayers;
	int ret;
	int *k = getUniqueCards();
	printf("TEST #2: Number of players random testing\n");
	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
	//random testing for number of players
	for(i = 0; i < NUMTRIALS; i++) {
		numPlayers = rand();
		ret = initializeGame(numPlayers, k, seed, G);
		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
		{
			ASSERT2(ret, 0, "FAIL");
		}
		else
		{
			ASSERT2(ret, -1, "FAIL");
		}
	}
	printf("PASS\n");
	printf("----------------------\n");
	free(G);
	free(k);
}

int test3a(int seed) {
	int ret;
	int numPlayers;
	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
	struct gameState *G = newGame();
	int *k = getUniqueCards();

	//Test when players are 2
	numPlayers = 2;
	ret = initializeGame(numPlayers, k, seed, G);
	curseCount = G->supplyCount[curse];
	estateCount = G->supplyCount[estate];
	duchyCount = G->supplyCount[duchy];
	provinceCount = G->supplyCount[province];
	copperCount = G->supplyCount[copper];
	silverCount = G->supplyCount[silver];
	goldCount = G->supplyCount[gold];
	ASSERT2(curseCount, 10, "curseCount");
	ASSERT2(estateCount, 8, "estateCount");
	ASSERT2(duchyCount, 8, "duchyCount");
	ASSERT2(provinceCount, 8, "provinceCount");
	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
	ASSERT2(silverCount, 40, "silverCount");
	ASSERT2(goldCount, 30, "goldCount");

	free(G);
	free(k);
}

int test3b(int seed) {
	int ret;
	int numPlayers;
	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
	struct gameState *G = newGame();
	int *k = getUniqueCards();
	//Test when players are 3

	numPlayers = 3;
	ret = initializeGame(numPlayers, k, seed, G);
	curseCount = G->supplyCount[curse];
	estateCount = G->supplyCount[estate];
	duchyCount = G->supplyCount[duchy];
	provinceCount = G->supplyCount[province];
	copperCount = G->supplyCount[copper];
	silverCount = G->supplyCount[silver];
	goldCount = G->supplyCount[gold];
	ASSERT2(curseCount, 20, "curseCount");
	ASSERT2(estateCount, 12, "estateCount");
	ASSERT2(duchyCount, 12, "duchyCount");
	ASSERT2(provinceCount, 12, "provinceCount");
	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
	ASSERT2(silverCount, 40, "silverCount");
	ASSERT2(goldCount, 30, "goldCount");

	free(G);
	free(k);
}

int test3c(int seed) {
	int ret;
	int numPlayers;
	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
	struct gameState *G = newGame();
	int *k = getUniqueCards();

	//Test when players are 4
	numPlayers = 4;
	ret = initializeGame(numPlayers, k, seed, G);
	curseCount = G->supplyCount[curse];
	estateCount = G->supplyCount[estate];
	duchyCount = G->supplyCount[duchy];
	provinceCount = G->supplyCount[province];
	copperCount = G->supplyCount[copper];
	silverCount = G->supplyCount[silver];
	goldCount = G->supplyCount[gold];
	ASSERT2(curseCount, 30, "curseCount");
	ASSERT2(estateCount, 12, "estateCount");
	ASSERT2(duchyCount, 12, "duchyCount");
	ASSERT2(provinceCount, 12, "provinceCount");
	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
	ASSERT2(silverCount, 40, "silverCount");
	ASSERT2(goldCount, 30, "goldCount");
	free(G);
	free(k);
}

int test4(int seed) 
{
	int i, j, t, x;
	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
	int trialCount = 100;
	int numPlayers = (rand()% 3) + 2;
	int ret = -1;
	int rand1;
	struct gameState *G = newGame();

	//initialize supplyCount 
	for(i = 0; i < NUMCARDS; i++) 
	{
		supplyCount[i] = -1;
	}
	while(t < trialCount)
	{
		for(j = 0; j < NUMCARDS; j++) {
			rand1 = (rand()%15);
			k[j] = rand1;
		}

		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
		{
			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
			{
				if (k[j] == i)
				{
					//check if card is a 'Victory' Kingdom card
					if (k[j] == great_hall || k[j] == gardens)
					{
						if (numPlayers == 2)
						{ 
							supplyCount[i] = 8; 
						}
						else
						{
							supplyCount[i] = 12;
						}
					}
					else
					{
						supplyCount[i] = 10;
					}
					break;
				}
			}
		}
		ret = initializeGame(numPlayers, k, seed, G);
		int cret = cardsAreUnique(k);
		if(cret == 0) 
		{
			t++;
			for(x = 0; x < NUMCARDS; x++) 
			{
				if(supplyCount[x] == -1) 
				{
					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
				}
				else 
				{
					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
				}
			}
		}
	}


	printf("PASS\n");
	printf("------------------\n");
	free(G);
	free(k);
	return 0;
}

int test5(int seed) {
	int i,j;
	int *k = getUniqueCards();
	int numPlayers ;
	struct gameState *G;
	struct gameState *Gcpy;
	G = newGame();
	Gcpy = newGame();
	numPlayers = 2;
	initializeGame(numPlayers, k, seed, Gcpy);
	//set player decks
	for (i = 0; i < numPlayers; i++)
	{
		G->deckCount[i] = 0;
		for (j = 0; j < 3; j++)
		{
		  G->deck[i][j] = estate;
		  G->deckCount[i]++;
		}
		for (j = 3; j < 10; j++)
		{
		  G->deck[i][j] = copper;
		  G->deckCount[i]++;		
		}
	}

	for (i = 0; i < numPlayers; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);

			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
		}
	}
	return 0;
}

int main() {
	srand(time(NULL));
	int seed = rand() + 1;
		//declaring the reusable variables
	int *k = (int*)malloc(sizeof(int)*NUMCARDS);

	printf("-------------------------------------------------------\n");
	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");

	//testing for unique kingdom cards
	test1(seed);

	//testing for number of players
	test2(seed);

	//testing for supply count
	//when 2 players
	printf("TEST #3a: Supply cards: 3 players\n");
	printf("\t curse = 10, estate|province|duchy = 8\n");
	test3a(seed);
	printf("PASS\n");
	printf("------------------\n");

	//when 3 players
	printf("TEST #3b: Supply cards: 3 players\n");
	printf("\t curse = 20, estate|province|duchy = 12\n");
	test3b(seed);
	printf("PASS\n");
	printf("------------------\n");

	//when 4 players
	printf("TEST #3c: Supply cards: 4 players\n");
	printf("\t curse = 30, estate|province|duchy = 12\n");
	test3c(seed);
	printf("PASS\n");
	printf("------------------\n");

	//testing for correct kingdom card values
	printf("TEST #4: Kingdom cards correct values\n");
	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
	test4(seed);


	test5(seed);

	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
	printf("---------------------------------------------------\n");
	return 0;
}
