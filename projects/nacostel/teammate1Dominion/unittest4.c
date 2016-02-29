/* 
   Filename: unittest4.c 
   Author: Lorena Nacoste
   Description: Unit test for discardCard()
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
 

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING discardCard():\n");
    
        
           

    handCount = 10;
    p = 1;

#if (NOISY_TEST == 1)
                printf("Test player %d with first card discarded, trash flag set\n", p);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand

                //calculate the expected played card and hand count after execution of discardCard()
                expec = G.playedCardCount + 1;
                int expecHand = G.handCount[p] - 1;
                int expecDeck = G.deckCount[p];
                int expecDisc = G.discardCount[p];
                //call function to be tested
                discardCard(0, p, &G, 0);

#if (NOISY_TEST == 1)
                //print results
                if(G.handCount[p] == expecHand)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");
                printf("Cards in hand = %d, Expected = %d\n", G.handCount[p], expecHand);
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
                if(expec == G.playedCardCount)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");
                printf("Cards in played pile = %d, Expected = %d\n", G.playedCardCount, expec);
               
               printf("\n");
#endif
                assert(G.playedCardCount == expec); // check if the number of played cards is correct
                assert(G.handCount[p] == expecHand); //check if number of cards in hand is correct
                 assert(G.deckCount[p] == expecDeck); // check if the number of cards in deck in hand is correct
                assert(G.discardCount[p] == expecDisc); //check if the number of cards in discard in correct


#if (NOISY_TEST == 1)
                printf("Test player %d with last card in hand discarded, trash flag not set\n", p);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand

                
                //calculate the expected hand count after execution of discardCard()
                expecHand = G.handCount[p] - 1;
                expecDeck = G.deckCount[p];
                expecDisc = G.discardCount[p];
                expec = G.playedCardCount;
                
                //call function to be tested
                discardCard(G.handCount[p], p, &G, 1);

#if (NOISY_TEST == 1)
                //print results
               if(G.handCount[p] == expecHand)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");
                printf("Cards in hand = %d, Expected = %d\n", G.handCount[p], expecHand);
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
                if(expec == G.playedCardCount)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");
                printf("Cards in played pile = %d, Expected = %d\n", G.playedCardCount, expec);
               
               printf("\n");
#endif
              assert(G.playedCardCount == expec); // check if the number of played cards is correct
              assert(G.handCount[p] == expecHand); //check if number of cards in hand is correct
              assert(G.deckCount[p] == expecDeck); // check if the number of cards in deck in hand is correct
              assert(G.discardCount[p] == expecDisc); //check if the number of cards in discard in correct
                
    

#if (NOISY_TEST == 1)
                printf("Test player %d with only card in hand discarded, trash flag not set\n", p);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = 1;                 // set the number of cards on hand

                //calculate the expected hand count after execution of discardCard()
                expecHand = G.handCount[p] - 1;
                expecDeck = G.deckCount[p];
                expecDisc = G.discardCount[p];
                expec = G.playedCardCount;

                //call function to be tested
                discardCard(0, p, &G, 1);

#if (NOISY_TEST == 1)
                //print results
                //print results
               if(G.handCount[p] == expecHand)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");
                printf("Cards in hand = %d, Expected = %d\n", G.handCount[p], expecHand);
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
                if(expec == G.playedCardCount)
                    printf("Tests PASSED: ");

                else 
                    printf("Tests FAILED: ");
                printf("Cards in played pile = %d, Expected = %d\n", G.playedCardCount, expec);
               
#endif
              assert(G.playedCardCount == expec); // check if the number of played cards is correct
              assert(G.handCount[p] == expecHand); //check if number of cards in hand is correct
              assert(G.deckCount[p] == expecDeck); // check if the number of cards in deck in hand is correct
              assert(G.discardCount[p] == expecDisc); //check if the number of cards in discard in correct
                

    
    printf("All tests passed!\n");

    return 0;
}
