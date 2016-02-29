/* 
   Filename: cardtest3.c 
   Author: Lorena Nacoste
   Description: Unit test for council room card
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

    int r, expecHand, expecHand2, expecDeck, expecDeck2;
    

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

    printf ("TESTING Council Room card:\n");
    int p = 0;
    int otherP = 1;
        
#if (NOISY_TEST == 1)
                printf("Test player %d playing a council room card\n", p);
#endif
                 
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                
                //store expected hand count for comparison after function execution
                expecHand = G.handCount[p] + 4;
                expecDeck = G.deckCount[p] - 4;
                expecHand2 = G.handCount[otherP] + 1;
                expecDeck2 = G.deckCount[otherP] - 1;
            
                //save gamestate
                memcpy(&test, &G, sizeof(struct gameState));
                //call function to be tested 
                cardEffect(council_room, choice1, choice2, choice3, &G, 0, &bonus);

#if (NOISY_TEST == 1)
                //print results of hand count check for current player and other player
                printf("hand count = %d, expected = %d\n", G.handCount[p], expecHand);
                printf("deck count = %d, expected = %d\n", G.deckCount[p], expecDeck);
                printf("other player's hand count = %d, expected = %d\n", G.handCount[otherP], expecHand2);
                printf("other player's deck count = %d, expected = %d\n", G.deckCount[otherP], expecDeck2);

                //check if council room card was successfully discarded
                if(G.hand[p][0] != council_room)
                	discardCheck = 0;

                else
                	discardCheck = 1;

                //print result of discard test
                printf("Card discarded? %d\n", discardCheck);

        
#endif
                //check current player's hand count
                if(G.handCount[p] != expecHand){
                    printf("Tests FAILED: Wrong number of cards added to hand!\n");
                }

                else{
                    assert(G.handCount[p] == expecHand); 

                    printf("Tests PASSED: Exactly 4 cards added to hand!\n");
                }

                //check if correct card discarded and print pass message
                if(discardCheck != 0){
                    printf("Tests FAILED: Wrong card discarded!\n");
                }

                else{
                    assert(discardCheck == 0);
                    printf("Tests PASSED: Right card discarded!\n");
                }

                //check current player's deck count
                if(G.deckCount[p] != expecDeck){
                    printf("Tests FAILED: Wrong number of cards removed from deck\n");
                }

                else{
                    assert(G.deckCount[p] == expecDeck);
                    printf("Tests PASSED: Four cards removed from current player's deck!\n");

                }

                //check other player's deck count
                if(G.deckCount[otherP] != expecDeck2){
                    printf("Tests FAILED: Deck of other player not changed correctly!\n");
                }

                else{
                    assert(G.deckCount[otherP] == expecDeck2);
                    printf("Tests PASSED: One card removed from other player's deck!\n");
                }


                //check other player's hand count
                if(G.handCount[otherP] != expecHand2){
                    printf("Tests FAILED: Hand of other player not changed correctly!\n");
                }

                else{
                    assert(G.handCount[otherP] == expecHand2);
                    printf("Tests PASSED: One card added to other player's hand!\n");
                }
                printf("\n");
             
    



    return 0;
}
