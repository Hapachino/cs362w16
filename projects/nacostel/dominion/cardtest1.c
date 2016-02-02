/* 
   Filename: cardtest1.c 
   Author: Lorena Nacoste
   Description: Unit test for adventurer card
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

    printf ("TESTING Adventurer card:\n");
    //set the other player's player number 
    int otherP = 1;
    int p = 0;

        
#if (NOISY_TEST == 1)
                printf("Test player %d playing an adventurer card\n", p);
#endif
                  
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                
                //store expected hand and deck counts for comparison after function execution
                expecHand = G.handCount[p] + 2;
                expecDeck = G.deckCount[p] - 2;

                 //save gamestate
                memcpy(&test, &G, sizeof(struct gameState));
                //call function to be tested 
                cardEffect(adventurer, choice1, choice2, choice3, &G, 0, &bonus);

#if (NOISY_TEST == 1)
                //print results of hand and deck count check
                printf("hand count = %d, expected = %d\n", G.handCount[p], expecHand);
                printf("deck count = %d, expected = %d\n", G.deckCount[p], expecDeck);

                //check if adventurere card was successfully discarded
                if(G.hand[p][0] != adventurer)
                	discardCheck = 0;

                else
                	discardCheck = 1;

                //print result of discard test
                printf("Card discarded? %d\n", discardCheck);

        
#endif
                //check if hand count updated correctly
                if(G.handCount[p] != expecHand){
                    printf("Tests FAILED: Wrong number of cards added to hand!\n");
                }

                else{
                    assert(G.handCount[p] == expecHand); 

                    printf("Tests PASSED: Exactly 2 cards added to hand!\n");
                }

                //check if correct card discarded 
                if(discardCheck != 0){
                    printf("Tests FAILED: Wrong card discarded!\n");
                }

                else{
                    assert(discardCheck == 0);
                    printf("Tests PASSED: Right card discarded!\n");
                }

                //check if deck updated correctly
                if(G.deckCount[p] != expecDeck){
                    printf("Tests FAILED: Wrong number of cards removed from deck\n");
                }

                else{
                    assert(G.deckCount[p] == expecDeck);
                    printf("Tests PASSED: 2 cards removed from player's deck!\n");

                }

                //check if other player's deck stayed the same
                if(G.deckCount[otherP] != test.deckCount[otherP]){
                    printf("Tests FAILED: Deck of other player changed!\n");
                }

                else{
                    assert(G.deckCount[otherP] == test.deckCount[otherP]);
                    printf("Tests PASSED: Deck of other player not changed!\n");
                }

                //check if other player's hand stayed the same
                if(G.handCount[otherP] != test.handCount[otherP]){
                    printf("Tests FAILED: Hand of other player changed!\n");
                }

                else{
                    assert(G.handCount[otherP] == test.handCount[otherP]);
                    printf("Tests PASSED: Hand of other player not changed!\n");
                }

                //check if last two cards drawn were treasure cards
                int card1 = G.hand[p][G.handCount[p] - 1];
                int card2 = G.hand[p][G.handCount[p] - 2];
                int card3 = G.hand[p][G.handCount[p] - 3];

                int treasureCounter = 0;

                if (card1 == copper || card1 == silver || card1 == gold){
                    treasureCounter++;
                }


                if (card2 == copper || card2 == silver || card2 == gold){
                    treasureCounter++;
                }


                if (card3 == copper || card3 == silver || card3 == gold){
                    treasureCounter++;
                }

                if(treasureCounter != 3){
                    printf("Tests FAILED:  Last three cards added to current player's hand not treasure cards!\n");
                }

                else{
                    assert(treasureCounter == 3);
                    printf("Tests PASSED:  Last three cards added to current player's hand are treasure cards!\n");
                }
                printf("\n");
             
  




    return 0;
}
