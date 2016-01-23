/* -----------------------------------------------------------------------
 * Modified testUpdateCoins
 * 
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    // set seed for random numbers
    srand(3);

    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    int maxHandCount = 5;
    int changeIndex = 4;
    int copperCount = 5;
    int silverCount = 0;
    int goldCount = 0;

    // bool to set coins of all one type before using changeIndex
    bool first = true;
    bool reset = true;
    // expected value
    int expected;

    // arrays of all coppers, silvers, and golds
    int coppers[maxHandCount];
    int silvers[maxHandCount];
    int golds[maxHandCount];
    for (i = 0; i < maxHandCount; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("\n========TESTING updateCoins() with coppers and silvers:========\n");
    for (p = 0; p < numPlayer; p++)
    {
    	// reset counts and checks for next player
		if (p != 0) {
			if (reset) {
				changeIndex = 4;
				copperCount = 5;
				silverCount = 0;
				first = true;
				reset = false;
			}
		}

        for (handCount = 0; handCount <= maxHandCount; handCount++)
        {
#if (NOISY_TEST == 1)
        		// random numnber for bonus
        		bonus = rand() % maxBonus;

                printf("\nTest player %d with %d copper(s), %d silver(s), and %d bonus.\n", p, copperCount, silverCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = 5;                 // set the number of cards on hand
                if (first) {
                	memcpy(G.hand[p], coppers, sizeof(int) * copperCount); // set all the cards to copper
                	first = false;
                }
                else {
                	memcpy(G.hand[p], coppers, sizeof(int) * copperCount); // set some cards to copper
                	memcpy(G.hand[p]+changeIndex, silvers, sizeof(int) * silverCount); // set some cards to silver
                	// move changeIndex to gradually add more silvers
                	changeIndex--;
                }
                
                // printf("Change index = %d\n", changeIndex);

                expected = copperCount + (2 * silverCount) + bonus;

                // Fewer coppers and more silvers
                copperCount--;        
                silverCount++;

                updateCoins(p, &G, bonus);

#if (NOISY_TEST == 1)
				printf("G.coins = %d, expected = %d\n", G.coins, expected);
#endif
				assert(G.coins == expected); // check if the number of coins is correct
        }
    }

	changeIndex = 4;
	copperCount = 5;
	silverCount = 0;
	goldCount = 0;

	// bool to set coins of all one type before using changeIndex
	first = true;
	reset = true;

	printf ("\n========TESTING updateCoins() with coppers and golds:========\n");
   	for (p = 0; p < numPlayer; p++)
    {
    	// reset counts and checks for next player
		if (p != 0) {
			if (reset) {
				changeIndex = 4;
				copperCount = 5;
				goldCount = 0;
				first = true;
				reset = false;
			}
		}

        for (handCount = 0; handCount <= maxHandCount; handCount++)
        {
#if (NOISY_TEST == 1)
        		// random numnber for bonus
        		bonus = rand() % maxBonus;

                printf("\nTest player %d with %d copper(s), %d gold(s), and %d bonus.\n", p, copperCount, goldCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = 5;                 // set the number of cards on hand
                if (first) {
                	memcpy(G.hand[p], coppers, sizeof(int) * copperCount); // set all the cards to copper
                	first = false;
                }
                else {
                	memcpy(G.hand[p], coppers, sizeof(int) * copperCount); // set some cards to copper
                	memcpy(G.hand[p]+changeIndex, golds, sizeof(int) * goldCount); // set some cards to gold
                	// move changeIndex to gradually add more golds
                	changeIndex--;
                }
                
                // printf("Change index = %d\n", changeIndex);

                expected = copperCount + (3 * goldCount) + bonus;

                // Fewer coppers and more golds
                copperCount--;        
                goldCount++;

                updateCoins(p, &G, bonus);

#if (NOISY_TEST == 1)
				printf("G.coins = %d, expected = %d\n", G.coins, expected);
#endif
				assert(G.coins == expected); // check if the number of coins is correct
        }
    }

    printf("\nAll tests passed!");

    return 0;
}
