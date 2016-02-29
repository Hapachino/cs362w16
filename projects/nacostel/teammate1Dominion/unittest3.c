/* 
   Filename: unittest3.c 
   Author: Lorena Nacoste
   Description: Unit test for drawCard()
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

    int p, r, handCount, expec;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    p = 0;

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }


    handCount = 10;
    printf ("TESTING drawCard():\n");           
        

#if (NOISY_TEST == 1)
                printf("Test player %d with initially empty deck\n", p);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand

                 //empty the deck
                 for(i = 0; i < G.deckCount[p]; i++){
                    G.deck[p][i] = -1;
        
                 }
               
                 G.deckCount[p] = 0;
                //set the expected hand count and deck count after the execution of the function
                expec = G.handCount[p] + 1;
                int expecDeck = G.deckCount[p] - 1;
                int expecDisc = G.discardCount[p];
                //call the function to be tested
                drawCard(p, &G);


#if (NOISY_TEST == 1)
                //print test results
                if(G.handCount[p] == expec)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");

                printf("Cards in hand = %d, Expected = %d\n", G.handCount[p], expec);

                if(G.deckCount[p] == expecDeck)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");

                printf("Cards in deck = %d, Expected = %d\n", G.deckCount[p], expecDeck);

                if(G.discardCount[p] == expecDisc)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");

                printf("Cards in discard = %d, Expected = %d\n", G.discardCount[p], expecDisc);
            
                printf("\n");
#endif
                //assert(G.handCount[p] == expec); // check if the number of cards in hand is correct
                //assert(G.deckCount[p] == expecDeck); // check if the number of cards in deck in hand is correct
                assert(G.discardCount[p] == expecDisc); //check if the number of cards in discard in correct

#if (NOISY_TEST == 1)
                printf("Test player %d with initially filled deck\n", p);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand

                //set the expected hand count after the execution of the function
                expec = G.handCount[p] + 1;
                expecDeck = G.deckCount[p] - 1;
                expecDisc = G.discardCount[p];
                //call the function to be tested
                drawCard(p, &G);


#if (NOISY_TEST == 1)
                //print results
               if(G.handCount[p] == expec)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");

                printf("Cards in hand = %d, Expected = %d\n", G.handCount[p], expec);

                if(G.deckCount[p] == expecDeck)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");

                printf("Cards in deck = %d, Expected = %d\n", G.deckCount[p], expecDeck);

                if(G.discardCount[p] == expecDisc)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");

                printf("Cards in discard = %d, Expected = %d\n", G.discardCount[p], expecDisc);
                printf("\n");
#endif
                assert(G.handCount[p] == expec); // check if the number of coins is correct
                assert(G.deckCount[p] == expecDeck); // check if the number of cards in deck in hand is correct
                assert(G.discardCount[p] == expecDisc); //check if the number of cards in discard in correct
 
  
    

    printf("All tests passed!\n");

    return 0;
}
