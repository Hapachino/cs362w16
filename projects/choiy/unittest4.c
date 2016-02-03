/* -----------------------------------------------------------------------
 * test GainCard()
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 unittest4.c dominion.o rngs.o
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove prints from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int p;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    
	int flagcnt;
	int supplypos;
	int deckcnt, handcnt, discardcnt, supplycnt;

    printf ("TESTING gainCard():\n");
    for (p = 0; p < numPlayer; p++) {
        for (supplypos = 0; supplypos < treasure_map+1; supplypos++)  {
			#if (NOISY_TEST == 1)
				printf("Test player %d with %d supply pos.\n", p, supplypos);
			#endif

            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            initializeGame(numPlayer, k, seed, &G); // initialize a new game
				
			deckcnt = 50, handcnt = 5, discardcnt = 0, supplycnt = 100;

            G.deckCount[p] = deckcnt;
			G.handCount[p] = handcnt;
			G.discardCount[p] = discardcnt;
			G.supplyCount[supplypos] = supplycnt;

			// toFlag = 0 : add to discard
			flagcnt = 0;
			discardcnt++;
			supplycnt--;

			gainCard(supplypos, &G, flagcnt, p);

			#if (NOISY_TEST == 1)
				printf("G.discard count = %d, expected = %d\n", G.discardCount[p], discardcnt);
				printf("G.supply count = %d, expected = %d\n", G.supplyCount[supplypos], supplycnt);
			#endif
			assert(G.discardCount[p] == discardcnt);
			assert(G.supplyCount[supplypos] == supplycnt);


			// toFlag = 1 : add to deck
			flagcnt = 1;
			deckcnt++;
			supplycnt--;

			gainCard(supplypos, &G, flagcnt, p);

			#if (NOISY_TEST == 1)
				printf("G.deck count = %d, expected = %d\n", G.deckCount[p], deckcnt);
				printf("G.supply count = %d, expected = %d\n", G.supplyCount[supplypos], supplycnt);
			#endif
			assert(G.deckCount[p] == deckcnt);
			assert(G.supplyCount[supplypos] == supplycnt);


			// toFlag = 2 : add to hand
			flagcnt = 2;
			handcnt++;
			supplycnt--;

			gainCard(supplypos, &G, flagcnt, p);

			#if (NOISY_TEST == 1)
				printf("G.hand count = %d, expected = %d\n", G.handCount[p], handcnt);
				printf("G.supply count = %d, expected = %d\n", G.supplyCount[supplypos], supplycnt);
			#endif
			assert(G.handCount[p] == handcnt);
			assert(G.supplyCount[supplypos] == supplycnt);
               
			puts("");
        }
    }

    printf("All tests passed!\n");

    return 0;
}
