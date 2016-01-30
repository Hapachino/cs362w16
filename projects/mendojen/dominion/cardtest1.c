/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 *	testVillage: cardtest1.c dominion.o rngs.o
 *	gcc -o card1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1


int main() {
	int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[0] = 5;                 // set the number of cards on hand to 5 for player 0
	G.numActions=1;
	G.discardCount[0]=0;
	G.playedCardCount=0;
	printf ("TESTING playVillage():\n");
#if (NOISY_TEST == 1)
	printf("Set starting values:\n handcount=0\n numActions=1\n discardCount=0\n playedCardCount=0\n\n");
	
	printf("****Testing 1 Village play****\n");
#endif
	playVillage(&G,0);
#if (NOISY_TEST == 1)
	printf("Actions = %d, expected = 3", G.numActions);
	if (G.numActions==3)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Number of Cards Played = %d, expected = 1", G.playedCardCount);
	if (G.playedCardCount==1)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Hand Count = %d, expected = 5", G.handCount[0]);
	if (G.handCount[0]==5)
	{
		printf("....PASS\n\n");
	}
	else{
		printf("....FAIL\n\n");
	}
	
	printf("****Testing another Village play****\n");
#endif
	playVillage(&G,0);
#if (NOISY_TEST == 1)
	printf("Actions = %d, expected = 5", G.numActions);
	if (G.numActions==5)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Number of Cards Played = %d, expected = 2", G.playedCardCount);
	if (G.playedCardCount==2)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Hand Count = %d, expected = 5", G.handCount[0]);
	if (G.handCount[0]==5)
	{
		printf("....PASS\n\n");
	}
	else{
		printf("....FAIL\n\n");
	}
	printf("****Testing another Village play****\n");
#endif
	playVillage(&G,0);
#if (NOISY_TEST == 1)
	printf("Actions = %d, expected = 7", G.numActions);
	if (G.numActions==7)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Number of Cards Played = %d, expected = 3", G.playedCardCount);
	if (G.playedCardCount==3)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Hand Count = %d, expected = 5", G.handCount[0]);
	if (G.handCount[0]==5)
	{
		printf("....PASS\n\n");
	}
	else{
		printf("....FAIL\n\n");
	}	
	printf("****Testing another Village play****\n");
#endif
	playVillage(&G,0);
#if (NOISY_TEST == 1)
	printf("Actions = %d, expected = 9", G.numActions);
	if (G.numActions==9)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Number of Cards Played = %d, expected = 4", G.playedCardCount);
	if (G.playedCardCount==4)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Hand Count = %d, expected = 5", G.handCount[0]);
	if (G.handCount[0]==5)
	{
		printf("....PASS\n\n");
	}
	else{
		printf("....FAIL\n\n");
	}	
#endif
	printf("Testing completed\n");
    return 0;
}
