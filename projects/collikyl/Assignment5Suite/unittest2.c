#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Game Over Test


int *_getSupp(struct gameState *g)
{
        int es = g->supplyCount[1];
        int du = g->supplyCount[2];
        int pr = g->supplyCount[province];
        int cu = g->supplyCount[curse];
        int co = g->supplyCount[copper];
        int si = g->supplyCount[silver];
        int go = g->supplyCount[gold];
        int *supply = malloc(sizeof(int*)*7);
        int hold[7] = {cu,es, du, pr, co, si, go};
        memcpy(supply,(int*)hold,sizeof(int)*7);
        return supply;
}

void _resetSupp(struct gameState *g)
{
	g->supplyCount[1] = 8;
 	g->supplyCount[2] = 8;
	g->supplyCount[province] = 8;
	g->supplyCount[curse] = 10; 
	g->supplyCount[copper] = 46;
	g->supplyCount[silver] = 40; 
	g->supplyCount[gold] = 30;
}

void testEndProvince(struct gameState *g)
{
	int i;
	int flag = 0;
	char *names[] = {"curse","estate","duchy","province","copper","silver","gold"};
	printf("\n\nTesting province end criterion\n");
	for(i = 0; i <= 7; i++)
	{
		g->supplyCount[i] = 0;
		if(isGameOver(g) && i != 3)
		{
			printf("Error. Game ended when %s = %d\n",names[i],g->supplyCount[i]);	
		}
		else if(isGameOver(g))
		{
			printf("Game ended when %s = %d\n",names[i],g->supplyCount[i]);
		}
		_resetSupp(g);	
	}	
}

void _setZero(struct gameState *g, int a, int b, int c)
{
	g->supplyCount[a] = 0;
	g->supplyCount[b] = 0;
	g->supplyCount[c] = 0;
}

void testEndSupply(struct gameState *g)
{
	int i,j;
	int flag = 0;
	char *names[] = {"curse","estate","duchy","province","copper","silver","gold"};

	printf("\nTesting supply count end criterion for %s %s %s\n",names[0],names[1],names[2]);
	_setZero(g,0,1,2);
	if(isGameOver(g)) printf("Passed! Game ended when three supply cards reached 0\n");
	else printf("Suppy count end criterion failed\n");
	_resetSupp(g);

	printf("\nTesting supply count end criterion for %s %s %s\n",names[0],names[1],names[5]);
	_setZero(g,0,1,5);
	if(isGameOver(g)) printf("Passed! Game ended when three supply cards reached 0\n");
	else printf("Suppy count end criterion failed\n");
	_resetSupp(g);

	printf("\nTesting supply count end criterion for %s %s %s\n",names[1],names[2],names[5]);
	_setZero(g,1,2,5);	
	if(isGameOver(g)) printf("Passed! Game ended when three supply cards reached 0\n");
	else printf("Suppy count end criterion failed\n");
	_resetSupp(g);

	printf("\nTesting supply count end criterion for %s %s %s\n",names[5],names[6],names[7]);
	_setZero(g,5,6,7);	
	if(isGameOver(g)) printf("Passed! Game ended when three supply cards reached 0\n");
	else printf("Suppy count end criterion failed\n");
	_resetSupp(g);


	printf("\nTesting supply count end criterion for %s %s %s\n",names[0],names[6],names[7]);
	_setZero(g,0,6,7);	
	if(isGameOver(g)) printf("Passed! Game ended when three supply cards reached 0\n");
	else printf("Suppy count end criterion failed\n");
	_resetSupp(g);


	printf("\nTesting supply count end criterion for %s %s %s\n",names[2],names[6],names[7]);
	_setZero(g,2,6,7);	
	if(isGameOver(g)) printf("Passed! Game ended when three supply cards reached 0\n");
	else printf("Suppy count end criterion failed\n");
	_resetSupp(g);


	printf("\nTesting supply count end criterion for %s %s %s\n",names[1],names[6],names[7]);
	_setZero(g,1,6,7);	
	if(isGameOver(g)) printf("Passed! Game ended when three supply cards reached 0\n");
	else printf("Suppy count end criterion failed\n");
	_resetSupp(g);
}


int main()
{
	int i;
        int seed = 1000;
        int numPlayers = 2;
        int player  = 0;
        struct gameState preState, postState;
        int k[10] = {adventurer, council_room, feast, gardens, mine ,remodel, smithy, village, baron, great_hall};
	initializeGame(numPlayers,k,seed,&postState);
	memcpy(&preState,&postState,sizeof(struct gameState));
	printf("\n\n\tConducting gameOver test...\n\n");
	testEndProvince(&postState);
	testEndSupply(&postState);
}
	
