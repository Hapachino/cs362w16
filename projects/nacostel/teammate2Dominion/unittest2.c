/* 
   Filename: unittest2.c 
   Author: Lorena Nacoste
   Description: Unit test for gainCard()
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

    int r;
    int handCount = 0;
    int deckCount = 0; 
    int trashCount = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int check = 1;
    int p = 1;
    
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING gainCard():\n");
    
#if (NOISY_TEST == 1)
                printf("Test player %d with one adventurer card added to hand\n", p);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
             
                //save needed game state variables
                int expecHand = G.handCount[p] + 1;
                int expecDeck = G.deckCount[p];
                int expecDisc = G.discardCount[p];
                //call function to be tested
                gainCard(adventurer, &G, 2, p);

              
                //set sentinel (check) to 0 if adventurer card is found in hand
                for(i = 0; i < G.handCount[p]; i++){
                    if(G.hand[p][i] == adventurer){
                        check = 0;
                    }
                }

#if (NOISY_TEST == 1)
                //Check if card found in expected spot and that deck, discard, and hand counts are correct
                if(check == 0)
                    printf("PASSED: Card found as expected in hand.\n");

                else
                    printf("FAILED: Card NOT found as expected in hand.\n");

                if(expecDeck == G.deckCount[p])
                    printf("PASSED: Cards in deck = %d, Expected = %d.\n", G.deckCount[p], expecDeck);

                else
                    printf("FAILED: Cards in deck = %d, Expected = %d.\n", G.deckCount[p], expecDeck);

                if(expecHand == G.handCount[p])
                    printf("PASSED: Cards in hand = %d, Expected = %d.\n", G.handCount[p], expecHand);

                else
                    printf("FAILED: Cards in hand = %d, Expected = %d.\n", G.handCount[p], expecHand);

                if(expecDisc == G.discardCount[p])
                    printf("PASSED: Cards in discard = %d, Expected = %d.\n", G.discardCount[p], expecDisc);

                else
                    printf("FAILED: Cards in discard = %d, Expected = %d.\n", G.discardCount[p], expecDisc);




                printf("\n");

#endif
                assert(check == 0); // check if sentinel set
                assert(expecDeck == G.deckCount[p]);
                assert(expecHand == G.handCount[p]);
                assert(expecDisc == G. discardCount[p]);
                check = 1;


#if (NOISY_TEST == 1)
                printf("Test player %d with one adventurer card added to deck\n", p);
#endif
                G.deckCount[p] = deckCount;                 // set the number of cards on hand
                memcpy(G.deck[p], golds, sizeof(int) * deckCount); // set all the cards to gold
                //save needed game state variables
                expecHand = G.handCount[p];
                expecDeck = G.deckCount[p] + 1;
                expecDisc = G.discardCount[p];
                //call function to be tested
                gainCard(adventurer, &G, 1, p);

                //set sentinel (check) to 0 if adventurer card is found in hand
                for(i = 0; i < G.deckCount[p]; i++){
                    if(G.deck[p][i] == adventurer){
                        check = 0;
                    }
                }


#if (NOISY_TEST == 1)
              //Check if card found in expected spot and that deck, discard, and hand counts are correct
                if(check == 0)
                    printf("PASSED: Card found as expected in hand.\n");

                else
                    printf("FAILED: Card NOT found as expected in hand.\n");

                if(expecDeck == G.deckCount[p])
                    printf("PASSED: Cards in deck = %d, Expected = %d.\n", G.deckCount[p], expecDeck);

                else
                    printf("FAILED: Cards in deck = %d, Expected = %d.\n", G.deckCount[p], expecDeck);

                if(expecHand == G.handCount[p])
                    printf("PASSED: Cards in hand = %d, Expected = %d.\n", G.handCount[p], expecHand);

                else
                    printf("FAILED: Cards in hand = %d, Expected = %d.\n", G.handCount[p], expecHand);

                if(expecDisc == G.discardCount[p])
                    printf("PASSED: Cards in discard = %d, Expected = %d.\n", G.discardCount[p], expecDisc);

                else
                    printf("FAILED: Cards in discard = %d, Expected = %d.\n", G.discardCount[p], expecDisc);

                printf("\n");
#endif
                assert(check == 0); // check if sentinel is set
                assert(expecDeck == G.deckCount[p]);
                assert(expecHand == G.handCount[p]);
                assert(expecDisc == G. discardCount[p]);
                check = 1;


#if (NOISY_TEST == 1)
                printf("Test player %d with one adventurer card added to trash\n", p);
#endif
                G.discardCount[p] = trashCount;                 // set the number of cards on hand
                memcpy(G.discard[p], golds, sizeof(int) * trashCount); // set all the cards to gold
                //save needed game state variables
                expecHand = G.handCount[p];
                expecDeck = G.deckCount[p];
                expecDisc = G.discardCount[p] + 1;
                //call function to be tested
                gainCard(adventurer, &G, 0, p);


                //set sentinel (check) to 0 if adventurer card is found in hand
                for(i = 0; i < G.discardCount[p]; i++){
                    if(G.discard[p][i] == adventurer){
                        check = 0;
                    }
                }

#if (NOISY_TEST == 1)
                //Check if card found in expected spot and that deck, discard, and hand counts are correct
                if(check == 0)
                    printf("PASSED: Card found as expected in hand.\n");

                else
                    printf("FAILED: Card NOT found as expected in hand.\n");

                if(expecDeck == G.deckCount[p])
                    printf("PASSED: Cards in deck = %d, Expected = %d.\n", G.deckCount[p], expecDeck);

                else
                    printf("FAILED: Cards in deck = %d, Expected = %d.\n", G.deckCount[p], expecDeck);

                if(expecHand == G.handCount[p])
                    printf("PASSED: Cards in hand = %d, Expected = %d.\n", G.handCount[p], expecHand);

                else
                    printf("FAILED: Cards in hand = %d, Expected = %d.\n", G.handCount[p], expecHand);

                if(expecDisc == G.discardCount[p])
                    printf("PASSED: Cards in discard = %d, Expected = %d.\n", G.discardCount[p], expecDisc);

                else
                    printf("FAILED: Cards in discard = %d, Expected = %d.\n", G.discardCount[p], expecDisc);

                printf("\n");
#endif
                assert(check == 0); // check if the sentinel is set
                assert(expecDeck == G.deckCount[p]);
                assert(expecHand == G.handCount[p]);
                assert(expecDisc == G. discardCount[p]);
                check = 1;
         

    
    printf("All tests passed!\n");

    return 0;
}
