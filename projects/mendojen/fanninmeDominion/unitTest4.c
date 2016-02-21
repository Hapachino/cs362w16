/* -----------------------------------------------------------------------
 *  Business requirements
 *  1) Correctly lets a player buy a card 
 *
 * buyCard: unittest4.c dominion.o rngs.o
 *      gcc -o unit4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
    int a, result, index, i;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    

    printf ("TESTING buyCard():\n");
  
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	G.coins=1000;
	printf("Testing when numBuys=0\n");	
	G.numBuys=0;
	for (i=0;i<50;i++)
	{
		index=rand() % 10;
		result=buyCard(k[index],&G);
#if (NOISY_TEST == 1)
		printf("Player is unable to buy a card");
		if (result==-1)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
#endif
	}

	G.numBuys=100;
#if (NOISY_TEST == 1)
	printf("Testing when there are enough buys. \n");
#endif
	for (i=0;i<10;i++)
	{
		index=rand() % 10;
		result=buyCard(k[index],&G);
#if (NOISY_TEST == 1)
		printf("Player is able to buy a card");
		if (result==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
#endif
	}

	
	G.supplyCount[gardens]=0;
#if (NOISY_TEST == 1)
	printf("Testing when supply count of desired card is 0\n ");
#endif
	result=buyCard(k[3],&G);
#if (NOISY_TEST == 1)
	printf("Player is unable to buy a card");
	if (result==-1)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
#endif

	G.coins=100;
	G.supplyCount[gardens]=5;
	G.supplyCount[adventurer]=5;
	G.supplyCount[council_room]=5;
	G.supplyCount[feast]=5;
	G.supplyCount[mine]=5;
	G.supplyCount[remodel]=5;
	G.supplyCount[smithy]=5;
	G.supplyCount[village]=5;
	G.supplyCount[baron]=5;
	G.supplyCount[great_hall]=5;
#if (NOISY_TEST == 1)	
	printf("Testing when supply count of desired card is not 0\n ");
#endif
	for (a=0;a<10;a++)
	{
		result=buyCard(k[a],&G);
#if (NOISY_TEST == 1)
		printf("Player is able to buy a card");
		if (result==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
	}
	printf("Testing when there is not enough coins to purchase card \n ");
#endif
	for (a=0;a<10;a++)
	{
		G.coins=1;
		result=buyCard(k[a],&G);
#if (NOISY_TEST == 1)
		printf("Player is unable to buy a card");
		if (result==-1)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
#endif
	}
		
	G.coins=5;
#if (NOISY_TEST == 1)
	printf("Testing when player has enough coins\n");
#endif
	result=buyCard(k[3],&G);
#if (NOISY_TEST == 1)
 	printf("Player is able to buy a card");
	if (result==0)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
#endif 
	printf("Tests Completed!\n");
    return 0;
}