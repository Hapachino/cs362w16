/* -----------------------------------------------------------------------
 *  Business requirements
 *  1) Correctly sums up the treasure cards
 *
 * updateCoins: unittest2.c dominion.o rngs.o
 *      gcc -o unit2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
    int i;
    int numPlayer = 2;
    int maxBonus = 5;
    int p,handCount;
    int bonus;
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[5];
    int silvers[5];
    int golds[5];
	int mixCards1[5]={copper, copper, copper, copper, gold};
	int mixCards2[5]={copper, copper, copper, silver, gold};
	int mixCards3[5]={copper, silver, silver, gold, gold};
	int mixCards4[5]={silver, silver, silver, gold, gold};
	int mixCards5[5]={copper, silver, gold, gold, gold};
	int mixCards6[5]={copper, copper, silver, gold, gold};
	int mixCards7[5]={silver, silver, gold, gold, gold};
	int mixCards8[5]={copper, gold, gold, gold, gold};
	
    for (i = 0; i < 5; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING updateCoins():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
                assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
#endif
                assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
#endif
                assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
            
				
			}
        }
    }

	p=1;
#if (NOISY_TEST == 1)
	printf("\n");
	printf("The following tests the updateCoins with a mix of treasure cards and no bonus.\n");
	printf("Testing updateCoins with 4 copper and 1 gold treasure cards.\n");
#endif
	memcpy(G.hand[p], mixCards1,sizeof(int) * handCount );
	updateCoins(p, &G, 0);
#if (NOISY_TEST == 1)
	printf("G.coins= %d, expected= 7", G.coins);
	if (G.coins==7)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	
	printf("Testing updateCoins with 3 copper, 1 silver, and 1 gold treasure cards.\n");
#endif
	memcpy(G.hand[p], mixCards2,sizeof(int) * handCount );
	updateCoins(p, &G, 0);
#if (NOISY_TEST == 1)
	printf("G.coins= %d, expected= 8", G.coins);
	if (G.coins==8)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	printf("Testing updateCoins with 1 copper, 2 silver, and 2 gold treasure cards.\n");
#endif
	memcpy(G.hand[p], mixCards3,sizeof(int) * handCount );
	updateCoins(p, &G, 0);
#if (NOISY_TEST == 1)
	printf("G.coins= %d, expected= 11", G.coins);
 	if (G.coins==11)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	
	printf("Testing updateCoins with 3 silver and 2 gold treasure cards.\n");
#endif
	memcpy(G.hand[p], mixCards4,sizeof(int) * handCount );
	updateCoins(p, &G, 0);
#if (NOISY_TEST == 1)
	printf("G.coins= %d, expected= 12", G.coins);
 	if (G.coins==12)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}  

	printf("Testing updateCoins with 1 copper, 1 silver, and 3 gold treasure cards.\n");
#endif
	memcpy(G.hand[p], mixCards5,sizeof(int) * handCount );
	updateCoins(p, &G, 0);
#if (NOISY_TEST == 1)
	printf("G.coins= %d, expected= 12", G.coins);
 	if (G.coins==12)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	
	printf("Testing updateCoins with 2 copper, 1 silver, and 2 gold treasure cards.\n");
#endif
	memcpy(G.hand[p], mixCards6,sizeof(int) * handCount );
	updateCoins(p, &G, 0);
#if (NOISY_TEST == 1)
	printf("G.coins= %d, expected= 10", G.coins);
 	if (G.coins==10)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	
	printf("Testing updateCoins with 2 silver and 3 gold treasure cards.\n");
#endif
	memcpy(G.hand[p], mixCards7,sizeof(int) * handCount );
	updateCoins(p, &G, 0);
#if (NOISY_TEST == 1)
	printf("G.coins= %d, expected= 13", G.coins);
 	if (G.coins==13)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
	
	printf("Testing updateCoins with 1 copper and 4 gold treasure cards.\n");
#endif
	memcpy(G.hand[p], mixCards8,sizeof(int) * handCount );
	updateCoins(p, &G, 0);
#if (NOISY_TEST == 1)
	printf("G.coins= %d, expected= 13", G.coins);
 	if (G.coins==13)
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
