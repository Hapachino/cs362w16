/* 
   Filename: cardtest2.c 
   Author: Lorena Nacoste
   Description: Unit test for smithy card
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

    int r, expecHand, expecDeck;
    

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, test;
  
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int bonus = 0;

    int discardCheck;

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING Smithy card:\n");
    //set the other player's player number 
    int otherP = 1;
    int p = 0;
                
    
        
#if (NOISY_TEST == 1)
                printf("Test player %d playing a smithy card\n", p);
#endif
                
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                
                //store expected hand and deck counts for comparison after function execution
                expecHand = G.handCount[p] + 3;
                expecDeck = G.deckCount[p] - 3;

                //save gamestate
                memcpy(&test, &G, sizeof(struct gameState));

                //call function to be tested 
                G.hand[p][0] = smithy;
                cardEffect(smithy, choice1, choice2, choice3, &G, 0, &bonus);

#if (NOISY_TEST == 1)
                //print results of hand count check
                printf("hand count = %d, expected = %d\n", G.handCount[p], expecHand);
            

                //check if smithy card was successfully discarded
                if(G.hand[p][0] != smithy)
                	discardCheck = 0;

                else
                	discardCheck = 1;

                //print result of discard test
                printf("Card discarded? %d\n", discardCheck);

        
#endif
                //check if the hand count updated correctly
                if(G.handCount[p] != expecHand){
                    printf("Tests FAILED: Wrong number of cards added to hand!\n");
                }

                else{
                    assert(G.handCount[p] == expecHand); 

                    printf("Tests PASSED: Exactly 3 cards added to hand!\n");
                }

                //check if correct card discarded 
                if(discardCheck != 0){
                    printf("Tests FAILED: Wrong card discarded!\n");
                }

                else{
                    assert(discardCheck == 0);
                    printf("Tests PASSED: Right card discarded!\n");
                }

                //check if the deck count updated correctly
                if(G.deckCount[p] != expecDeck){
                    printf("Tests FAILED: Wrong number of cards removed from deck\n");
                }

                else{
                    assert(G.deckCount[p] == expecDeck);
                    printf("Tests PASSED: Three cards removed from deck!\n");

                }

                //check if the other player's deck remains unchanged
                if(G.deckCount[otherP] != test.deckCount[otherP]){
                    printf("Tests FAILED: Deck of other player changed!\n");
                }

                else{
                    assert(G.deckCount[otherP] == test.deckCount[otherP]);
                    printf("Tests PASSED: Deck of other player not changed!\n");
                }


                //check if the other player's hand remains unchanged
                if(G.handCount[otherP] != test.handCount[otherP]){
                    printf("Tests FAILED: Hand of other player changed!\n");
                }

                else{
                    assert(G.handCount[otherP] == test.handCount[otherP]);
                    printf("Tests PASSED: Hand of other player not changed!\n");
                }
                printf("\n");
             
    



    return 0;
}
