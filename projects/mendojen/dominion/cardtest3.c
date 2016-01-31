/* -----------------------------------------------------------------------
 *  Business requirements
 *  1) Current player gets 3 cards 
 *  2) 3 cards will only come from current player's pile
 *  3) Other player's state remains unchanged
 *
 * testSmithy: cardtest3.c dominion.o rngs.o
 *      gcc -o card3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
    int r,i;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

	printf ("TESTING playSmithy():\n");
 	for (i=0;i<50;i++)
	{
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.handCount[0] = 0;                 // set the number of cards on hand to 5 for player 0

	#if (NOISY_TEST == 1)
		printf("Set starting values:\n handcount=0\n numBuys=0\n coins=0\n playedCardCount=0\n\n");
		
		printf("****Testing 1 Smithy play****\n");
	#endif
		playSmithy(&G,0);
	#if (NOISY_TEST == 1)
		printf("Hand Count = %d, expected = 3", G.handCount[0]);
		if (G.handCount[0]==3)
		{
			printf("....PASS\n\n");
		}
		else{
			printf("....FAIL\n\n");
		}
		printf("Number of Cards Played = %d, expected = 1", G.playedCardCount);
		if (G.playedCardCount==1)
		{
			printf("....PASS\n\n");
		}
		else{
			printf("....FAIL\n\n");
		}
		printf("****Testing another Smithy play****\n");
	#endif
		playSmithy(&G,2);
	#if (NOISY_TEST == 1)
		printf("Hand Count = %d, expected = 6", G.handCount[0]);
		if (G.handCount[0]==6)
		{
			printf("....PASS\n\n");
		}
		else{
			printf("....FAIL\n\n");
		}
		printf("Number of Cards Played = %d, expected = 2", G.playedCardCount);
		if (G.playedCardCount==2)
		{
			printf("....PASS\n\n");
		}
		else{
			printf("....FAIL\n\n");
		}
		printf("****Testing another Smithy play****\n");
	#endif
		playSmithy(&G,0);
	#if (NOISY_TEST == 1)
		printf("Hand Count = %d, expected = 9", G.handCount[0]);
		if (G.handCount[0]==9)
		{
			printf("....PASS\n\n");
		}
		else{
			printf("....FAIL\n\n");
		}
		printf("Number of Cards Played = %d, expected = 3", G.playedCardCount);	
		if (G.playedCardCount==3)
		{
			printf("....PASS\n\n");
		}
		else{
			printf("....FAIL\n\n");
		}
		printf("****Testing another Smithy play****\n");
	#endif
		playSmithy(&G,0);
	#if (NOISY_TEST == 1)
		printf("Hand Count = %d, expected = 15", G.handCount[0]);
		if (G.handCount[0]==15)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
		printf("Number of Cards Played = %d, expected = 4", G.playedCardCount);	
		if (G.playedCardCount==4)
		{
			printf("....PASS\n\n"); 
		}
		else{
			printf("....FAIL\n\n");
		}
	#endif
		endTurn(&G);
	#if (NOISY_TEST == 1)
		printf("****Testing other player's hand****\n");
		printf("Buys = %d, expected = 1", G.numBuys);
		if (G.numBuys==1)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
		printf("Number of Cards Played = %d, expected = 0", G.playedCardCount);	
		if (G.playedCardCount==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
		printf("Hand Count = %d, expected = 0", G.handCount[0]);
		if (G.handCount[0]==0)
		{
			printf("....PASS\n\n");
		}
		else{
			printf("....FAIL\n\n");
		}
	#endif	
	}
	printf("Testing completed\n");
    return 0;
}
