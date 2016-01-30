/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * playSalvager: cardtest2.c dominion.o rngs.o
 *      gcc -o card2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
    G.handCount[0] = 10;                 // set the number of cards on hand to 5 for player 0
	G.numBuys=0;
	G.discardCount[0]=0;
	G.coins=0;
	printf ("TESTING playSalvager():\n");
#if (NOISY_TEST == 1)
	printf("Set starting values:\n handcount=0\n numBuys=0\n coins=0\n playedCardCount=0\n\n");
	
	printf("****Testing 1 Salvager play****\n");
#endif
	playSalvager(&G,0,adventurer);
#if (NOISY_TEST == 1)
	printf("Buys = %d, expected = 1", G.numBuys);
	if (G.numBuys==1)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Coins = %d, expected = 6", G.coins);
	if (G.coins==6)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Hand Count = %d, expected = 8", G.handCount[0]);
	if (G.handCount[0]==8)
	{
		printf("....PASS\n\n");
	}
	else{
		printf("....FAIL\n\n");
	}
	printf("****Testing another Salvager play****\n");
#endif
	playSalvager(&G,0,adventurer);
#if (NOISY_TEST == 1)
	printf("Buys = %d, expected = 2", G.numBuys);
	if (G.numBuys==2)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Coins = %d, expected = 6", G.coins);
	if (G.coins==6)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Hand Count = %d, expected = 6", G.handCount[0]);
	if (G.handCount[0]==6)
	{
		printf("....PASS\n\n");
	}
	else{
		printf("....FAIL\n\n");
	}

	printf("****Testing another Salvager play****\n");
#endif
	playSalvager(&G,0,adventurer);
#if (NOISY_TEST == 1)
	printf("Buys = %d, expected = 3", G.numBuys);
	if (G.numBuys==3)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Coins = %d, expected = 6", G.coins);
	if (G.coins==6)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Hand Count = %d, expected = 4", G.handCount[0]);
	if (G.handCount[0]==4)
	{
		printf("....PASS\n\n");
	}
	else{
		printf("....FAIL\n\n");
	}

	printf("****Testing another Salvager play with no discarded card****\n");
#endif
	playSalvager(&G,0,0);
#if (NOISY_TEST == 1)
	printf("Buys = %d, expected = 4", G.numBuys);
	if (G.numBuys==4)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Coins = %d, expected = 0", G.coins);
	if (G.coins==0)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Hand Count = %d, expected = 3", G.handCount[0]);
	if (G.handCount[0]==3)
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
