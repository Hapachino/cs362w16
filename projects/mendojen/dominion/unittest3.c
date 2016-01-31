/* -----------------------------------------------------------------------
 *  Business requirements
 *  1) Correctly ends the game 
 *
 * isGameOver: unittest3.c dominion.o rngs.o
 *      gcc -o unit3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int a,i, result, index, counter;
    struct gameState G;
    

    printf ("TESTING isGameOver():\n");
  
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    
	for (a=0;a<=27;a++) //sets supply count for the kingdom cards to be 5 each
	{
		G.supplyCount[a]=5;
	}
#if (NOISY_TEST == 1)
	printf("Set supply count for all 26 supply cards to 5\n");
	printf("Set province card count to 0\n");
#endif
	G.supplyCount[province]=0;
	result= isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Game over");
	if (result==1)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Setting random piles of 3 to 0 of the supply pile\n");
#endif
	for (i=0;i<100;i++)
	{

		while (counter!=4)
		{
			index=1+rand() % 27;
			
			if (G.supplyCount[index]==0)
			{
				counter--;
			}
			else{
				G.supplyCount[index]=0;
			}
			counter++;
		}
		result=isGameOver(&G);
	#if (NOISY_TEST == 1)
		printf("Game over");
		if (result==1)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
	#endif
		counter=1;
		for (a=0;a<=27;a++) //resets supply count for the kingdom cards to be 5 each
		{
		G.supplyCount[a]=5;
		}
	}
#if (NOISY_TEST == 1)
	printf("Testing random piles of 2 of the supply pile\n");
#endif
	for (i=0;i<100;i++)
	{

		while (counter!=3)
		{
			index=1+rand() % 27;
			
			if (G.supplyCount[index]==0)
			{
				counter--;
			}
			else{
				G.supplyCount[index]=0;
			}
			counter++;
		}
		result=isGameOver(&G);
	#if (NOISY_TEST == 1)
		printf("Game not over");
		if (result==0)
		{
			printf("....PASS\n");
		}
		else{
			printf("....FAIL\n");
		}
	#endif
		counter=1;
		for (a=0;a<=26;a++) //resets supply count for the kingdom cards to be 5 each
		{
		G.supplyCount[a]=5;
		}
	}
#if (NOISY_TEST == 1)
	printf("Set adventurer, feast, gardens pile count to 0\n");
#endif
	G.supplyCount[province]=2;
	G.supplyCount[adventurer]=0;
	G.supplyCount[feast]=0;
	G.supplyCount[gardens]=0;
	result= isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Game over");
	if (result==1)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
#endif
	for (a=0;a<=26;a++) //sets supply count for the kingdom cards to be 5 each
	{
		G.supplyCount[a]=5;
	}	
#if (NOISY_TEST == 1)
	printf("Reset pile count and set feast and gardens pile count to 0\n");
#endif
	G.supplyCount[feast]=0;
	G.supplyCount[gardens]=0;
	result= isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Game not over");
	if (result==0)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
#endif
	G.supplyCount[gardens]=5;
	
#if (NOISY_TEST == 1)
	printf("Set treasure map to 0 to have a total of 3 empty piles\n");
#endif
	G.supplyCount[treasure_map]=0;
	result= isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Game over");
	if (result==1)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	
	printf("Set sea hag to 0 to have a total of 3 empty piles\n");
#endif
	G.supplyCount[sea_hag]=0;
	result= isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Game over");
	if (result==1)
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
