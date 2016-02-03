/* -----------------------------------------------------------------------
 *  Business requirements
 *  1) Current player gets 2 cards only 
 *  2) Cards only come from current player's deck
 *  3) Other player's state remains unchanged
 *
 * testAdventurer: cardtest4.c dominion.o rngs.o
 *      gcc -o card4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int r,i;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	
    printf ("TESTING adventurer():\n");
	for (i=0;i<50;i++)
	{
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.handCount[0]=0;
	#if (NOISY_TEST == 1)
		printf ("****Playing adventurer card 1 time****\n");
	#endif	
		playAdventurer(&G); 
	#if (NOISY_TEST == 1)
		printf("Handcount: %d\n", G.handCount[0]);
		printf("Number of Cards Played = %d, expected = 0", G.playedCardCount);	
		if (G.playedCardCount==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
		printf ("****Playing adventurer card another time****\n");
	#endif	 
		playAdventurer(&G); 
	#if (NOISY_TEST == 1)
		printf("Handcount: %d\n", G.handCount[0]);
		printf("Number of Cards Played = %d, expected = 0", G.playedCardCount);	
		if (G.playedCardCount==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
		printf ("****Playing adventurer card another time****\n");
	#endif	
		playAdventurer(&G); 
	#if (NOISY_TEST == 1)
		printf("Handcount: %d\n", G.handCount[0]);
		printf("Number of Cards Played = %d, expected = 0", G.playedCardCount);	
		if (G.playedCardCount==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
		printf ("****Playing adventurer card another time****\n");
	#endif	
		playAdventurer(&G); 
	#if (NOISY_TEST == 1)
		printf("Handcount: %d\n", G.handCount[0]);
		printf("Number of Cards Played = %d, expected = 0", G.playedCardCount);	
		if (G.playedCardCount==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
		printf ("****Playing adventurer card another time****\n");
	#endif	
		playAdventurer(&G); 
	#if (NOISY_TEST == 1)
		printf("Handcount: %d\n", G.handCount[0]);
		printf("Number of Cards Played = %d, expected = 0", G.playedCardCount);	
		if (G.playedCardCount==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
		printf ("****Playing adventurer card another time****\n");
	#endif	 
		playAdventurer(&G); 
	#if (NOISY_TEST == 1)
		printf("Handcount: %d\n", G.handCount[0]);
		printf("Number of Cards Played = %d, expected = 0", G.playedCardCount);	
		if (G.playedCardCount==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
		printf ("****Playing adventurer card another time****\n");
	#endif	
		playAdventurer(&G); 
	#if (NOISY_TEST == 1)
		printf("Handcount: %d\n", G.handCount[0]);
		printf("Number of Cards Played = %d, expected = 0", G.playedCardCount);	
		if (G.playedCardCount==0)
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

