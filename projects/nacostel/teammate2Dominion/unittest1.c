/* 
   Filename: unittest1.c 
   Author: Lorena Nacoste
   Description: Unit test for fullDeckCount()
   Note: Format and skeleton of file based on testUpdateCoins.c provided by instructor.
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
    int seed = 1000;
    int numPlayer = 2;

    int p, r;
    int handCount = 5;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, test;
  
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int count;
    p = 0;

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING fullDeckCount():\n");
    
        
#if (NOISY_TEST == 1)
                printf("Test player %d with one adventurer card\n", p);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                G.hand[p][0] = adventurer; // set one card to adventurer
                //save gamestate
                memcpy(&test, &G, sizeof(struct gameState));
                //call function to be tested and store value of deck count
                count = fullDeckCount(p, adventurer, &G);

#if (NOISY_TEST == 1)
                //print results
                printf("Count of adventurer card = %d, expected = 1\n", count);
                //compare previous state to current state
                int stateCheck = memcmp(&test, &G, sizeof(G));
                //print pass messge if applicable
                if(stateCheck == 0){
                    printf("Game state remained unchanged!\n");
                }
                printf("\n");
#endif
                assert(count == 1); // check if the number of cards found is correct
                assert(stateCheck == 0);

#if (NOISY_TEST == 1)
                printf("Test player %d with two adventurer cards\n", p);
#endif
                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                G.hand[p][0] = adventurer; // set one card to adventurer
                G.hand[p][handCount - 1] = adventurer; // set another card to adventurer

                //save gamestate
                memcpy(&test, &G, sizeof(struct gameState));
                //call function to be tested and store value of deck count
                count = fullDeckCount(p, adventurer, &G);
                
#if (NOISY_TEST == 1)
                //print results
                printf("Count of adventurer card = %d, expected = 2\n", count);
                //compare previous state to current state
                stateCheck = memcmp(&test, &G, sizeof(G));
                //print pass message if applicable
                if(stateCheck == 0){
                    printf("Game state remained unchanged!\n");
                }
                printf("\n");
#endif
                assert(count == 2); // check if the number of cards found is correct
                assert(stateCheck == 0);

#if (NOISY_TEST == 1)
                printf("Test player %d with no adventurer cards\n", p);
#endif

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                //save gamestate
                memcpy(&test, &G, sizeof(struct gameState));
                //call function to be tested and store value of deck count
                count = fullDeckCount(p, adventurer, &G);

#if (NOISY_TEST == 1)
               printf("Count of adventurer card = %d, expected = 0\n", count); 
               //compare previous state to current state
                stateCheck = memcmp(&test, &G, sizeof(G));
                //print pass message if applicable
                if(stateCheck == 0){
                    printf("Game state remained unchanged!\n");
                }
               printf("\n");
#endif
                assert(count == 0); // check if the number of cards found is correct
                assert(stateCheck == 0);
           
    

    printf("All tests passed!\n");

    return 0;
}
