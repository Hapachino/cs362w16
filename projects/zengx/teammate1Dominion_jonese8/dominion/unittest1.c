/* -----------------------------------------------------------------------
 * CS362 - Assignment 3 - Emmalee Jones
 * Description of updateCoin() unit test. 
 * Include the following lines in the makefile:
 * $ (CFLAGS = -WALL -fpic -coverage -lm )
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 *      unittest1 >> unittestresult.out
 *      gcov unittest1 >> unittestresult.out
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
	int newCards = 0;
    int discarded = 0;
    int shuffledCards = 0;
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
	
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
	
    printf ("TESTING unittest1 updateCoins():\n");
    for (p = 0; p < numPlayers; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
				
                r = initializeGame(numPlayers, k, seed, &G); // initialize a new game
	
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
				
                // copy the game state to a test case: testG
                memcpy(&testG, &G, sizeof(struct gameState));
				
                r = updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
                if (G.coins == handCount * 1 + bonus)
                    ;//printf("updateCoins(): PASS on copper coin cards addition\n");
                else 
                    printf("updateCoins: FAIL on copper coin cards addition\n");
                if (r == 0)
                    ;//printf("updateCoins(): PASS on return code is zero\n");
                else 
                    printf("updateCoins: FAIL on return code is zero\n");
                if (testG.handCount[p] == G.handCount[p] + newCards - discarded)
                   ;//printf("updateCoins(): PASS on handcount does not change\n");
                else 
                    printf("updateCoins: FAIL on handcount does not change\n");
                if (testG.deckCount[p] == G.deckCount[p] - newCards + shuffledCards)
                    ;//printf("updateCoins(): PASS on deckcount does not change\n");
                else 
                    printf("updateCoins: FAIL on deckcount does not change\n");


                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
										
                // copy the game state to a test case: testG
                memcpy(&testG, &G, sizeof(struct gameState));
								
                r = updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);

#endif
                if (G.coins == handCount * 2 + bonus)
                    ;//printf("updateCoins(): PASS on silver coin cards addition\n");
                else 
                    printf("updateCoins: FAIL on silver coin cards addition\n");
                if (r == 0)
                    ;//printf("updateCoins(): PASS on return code is zero\n");
                else 
                    printf("updateCoins: FAIL on return code is zero\n");

                if (testG.handCount[p] == G.handCount[p] + newCards - discarded)
                    ;//printf("updateCoins(): PASS on handcount does not change\n");
                else 
                    printf("updateCoins: FAIL on handcount does not change\n");
                if (testG.deckCount[p] == G.deckCount[p] - newCards + shuffledCards)
                    ;//printf("updateCoins(): PASS on deckcount does not change\n");
                else 
                    printf("updateCoins: FAIL on deckcount does not change\n");

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
				
                // copy the game state to a test case: testG
                memcpy(&testG, &G, sizeof(struct gameState));
				
                r = updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
#endif
                if (G.coins == handCount * 3 + bonus)
                   ;//printf("updateCoins(): PASS on gold coin cards addition\n");
                else 
                    printf("updateCoins: FAIL on gold coin cards addition\n");
                if (r == 0)
                   ;//printf("updateCoins(): PASS on return code is zero\n");
                else 
                    printf("updateCoins: FAIL on return code is zero\n");
                if (testG.handCount[p] == G.handCount[p] + newCards - discarded)
                    ;//printf("updateCoins(): PASS on handcount does not change\n");
                else 
                    printf("updateCoins: FAIL on handcount does not change\n");
                if (testG.deckCount[p] == G.deckCount[p] - newCards + shuffledCards)
                    ;//printf("updateCoins(): PASS on deckcount does not change\n");
                else 
                    printf("updateCoins: FAIL on deckcount does not change\n");
            }
        }
    }
	
	

    printf("All tests completed!\n");

    return 0;
}
