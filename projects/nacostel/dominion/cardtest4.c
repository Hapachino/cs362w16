/* 
   Filename: cardtest4.c 
   Author: Lorena Nacoste
   Description: Unit test for mine card
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

    printf ("TESTING mine card:\n");
    int p = 0;
    int otherP = 1;
        
#if (NOISY_TEST == 1)
                printf("Test player %d playing a mine card with choice1 = copper, choice2 = silver\n", p);
#endif

                memset(&G, 23, sizeof(struct gameState));   // clear the game state

                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                
                //store expected hand count for comparison after function execution
                expecHand = G.handCount[p] - 1;
                expecDeck = G.deckCount[p];
                G.hand[p][1] = copper;
                //save gamestate
                memcpy(&test, &G, sizeof(struct gameState));
                //call function to be tested 
                cardEffect(mine, 1, silver, choice3, &G, 0, &bonus);
                



#if (NOISY_TEST == 1)
                //print results of hand count check
                printf("hand count = %d, expected = %d\n", G.handCount[p], expecHand);
            

                //check if smithy card was successfully discarded
                if(G.hand[p][0] != mine)
                	discardCheck = 0;

                else
                	discardCheck = 1;

                //print result of discard test
                printf("Card discarded? %d\n", discardCheck);

        
#endif
                //check player's hand count 
               if(G.handCount[p] != expecHand){
                    printf("Tests FAILED: Wrong number of cards added to hand!\n");
                }

                else{
                    assert(G.handCount[p] == expecHand); 

                    printf("Tests PASSED: Right number of cards added to hand!\n");
                }

                //check if correct card discarded and print pass message
                if(discardCheck != 0){
                    printf("Tests FAILED: Mine card not discarded!\n");
                }

                else{
                    assert(discardCheck == 0);
                    printf("Tests PASSED: Mine card discarded!\n");
                }

                //check player's deck count
                if(G.deckCount[p] != expecDeck){
                    printf("Tests FAILED: Wrong number of cards removed from deck\n");
                }

                else{
                    assert(G.deckCount[p] == expecDeck);
                    printf("Tests PASSED: Right number of cards removed from deck!\n");

                }

                //check other player's deck count
                if(G.deckCount[otherP] != test.deckCount[otherP]){
                    printf("Tests FAILED: Deck of other player changed!\n");
                }

                else{
                    assert(G.deckCount[otherP] == test.deckCount[otherP]);
                    printf("Tests PASSED: Deck of other player not changed!\n");
                }

                //check other player's hand count
                if(G.handCount[otherP] != test.handCount[otherP]){
                    printf("Tests FAILED: Hand of other player changed!\n");
                }

                else{
                    assert(G.handCount[otherP] == test.handCount[otherP]);
                    printf("Tests PASSED: Hand of other player not changed!\n");
                }


                int cardDrawn = G.hand[p][G.handCount[p] - 1];
               

                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                    assert(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold);
                    printf("Tests PASSED: Card drawn is a treasue card!\n");
                }

                else{
                    printf("Tests FAILED: Card drawn is not a treasure card!\n");

                }

                printf("\n");

#if (NOISY_TEST == 1)
                printf("Test player %d playing a mine card with choice1=gold, choice2=copper\n", p);
#endif

                memset(&G, 23, sizeof(struct gameState));   // clear the game state

                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                
                //store expected hand count for comparison after function execution
                expecHand = G.handCount[p];
                G.hand[p][1] = gold;
                expecDeck = G.deckCount[p];
                //save gamestate
                memcpy(&test, &G, sizeof(struct gameState));
                //call function to be tested 
                cardEffect(mine, 1, copper, choice3, &G, 0, &bonus);

#if (NOISY_TEST == 1)
                //print results of hand count check
                printf("hand count = %d, expected = %d\n", G.handCount[p], expecHand);
            

                //check if smithy card was successfully discarded
                if(G.hand[p][0] != mine)
                    discardCheck = 0;

                else
                    discardCheck = 1;

                //print result of discard test
                printf("Card discarded? %d\n", discardCheck);

        
#endif
                //check player's hand count 
               if(G.handCount[p] != expecHand){
                    printf("Tests FAILED: Wrong number of cards added to hand!\n");
                }

                else{
                    assert(G.handCount[p] == expecHand); 

                    printf("Tests PASSED: Right number of cards added to hand!\n");
                }

                //check if correct card discarded and print pass message
                if(discardCheck != 0){
                    printf("Tests FAILED: Mine card not discarded!\n");
                }

                else{
                    assert(discardCheck == 0);
                    printf("Tests PASSED: Mine card discarded!\n");
                }

                //check player's deck count
                if(G.deckCount[p] != expecDeck){
                    printf("Tests FAILED: Wrong number of cards removed from deck\n");
                }

                else{
                    assert(G.deckCount[p] == expecDeck);
                    printf("Tests PASSED: Right number of cards removed from deck!\n");

                }

                //check other player's deck count
                if(G.deckCount[otherP] != test.deckCount[otherP]){
                    printf("Tests FAILED: Deck of other player changed!\n");
                }

                else{
                    assert(G.deckCount[otherP] == test.deckCount[otherP]);
                    printf("Tests PASSED: Deck of other player not changed!\n");
                }

                //check other player's hand count
                if(G.handCount[otherP] != test.handCount[otherP]){
                    printf("Tests FAILED: Hand of other player changed!\n");
                }

                else{
                    assert(G.handCount[otherP] == test.handCount[otherP]);
                    printf("Tests PASSED: Hand of other player not changed!\n");
                }


                cardDrawn = G.hand[p][G.handCount[p] - 1];
               

                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                    assert(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold);
                    printf("Tests PASSED: Card drawn is a treasue card!\n");
                }

                else{
                    printf("Tests FAILED: Card drawn is not a treasure card!\n");

                }


               
                
                printf("\n");

#if (NOISY_TEST == 1)
                printf("Test player %d playing a mine card with choice1 not a treasure card\n", p);
#endif

                memset(&G, 23, sizeof(struct gameState));   // clear the game state

                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                
                //store expected hand count for comparison after function execution
                expecHand = G.handCount[p];
                expecDeck = G.deckCount[p];
                G.hand[p][1] = estate;
                //save gamestate
                memcpy(&test, &G, sizeof(struct gameState));
                //call function to be tested 
                cardEffect(mine, 1, gold, choice3, &G, 0, &bonus);

#if (NOISY_TEST == 1)
                //print results of hand count check
                printf("hand count = %d, expected = %d\n", G.handCount[p], expecHand);
            

                //check if smithy card was successfully discarded
                if(G.hand[p][0] != mine)
                    discardCheck = 0;

                else
                    discardCheck = 1;

                //print result of discard test
                printf("Card discarded? %d\n", discardCheck);

        
#endif
                //check player's hand count 
               if(G.handCount[p] != expecHand){
                    printf("Tests FAILED: Wrong number of cards added to hand!\n");
                }

                else{
                    assert(G.handCount[p] == expecHand); 

                    printf("Tests PASSED: Right number of cards added to hand!\n");
                }

                //check if correct card discarded and print pass message
                if(discardCheck != 0){
                    printf("Tests FAILED: Mine card not discarded!\n");
                }

                else{
                    assert(discardCheck == 0);
                    printf("Tests PASSED: Mine card discarded!\n");
                }

                //check player's deck count
                if(G.deckCount[p] != expecDeck){
                    printf("Tests FAILED: Wrong number of cards removed from deck\n");
                }

                else{
                    assert(G.deckCount[p] == expecDeck);
                    printf("Tests PASSED: Right number of cards removed from deck!\n");

                }

                //check other player's deck count
                if(G.deckCount[otherP] != test.deckCount[otherP]){
                    printf("Tests FAILED: Deck of other player changed!\n");
                }

                else{
                    assert(G.deckCount[otherP] == test.deckCount[otherP]);
                    printf("Tests PASSED: Deck of other player not changed!\n");
                }

                //check other player's hand count
                if(G.handCount[otherP] != test.handCount[otherP]){
                    printf("Tests FAILED: Hand of other player changed!\n");
                }

                else{
                    assert(G.handCount[otherP] == test.handCount[otherP]);
                    printf("Tests PASSED: Hand of other player not changed!\n");
                }


                cardDrawn = G.hand[p][G.handCount[p] - 1];
               

                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                    assert(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold);
                    printf("Tests PASSED: Card drawn is a treasue card!\n");
                }

                else{
                    printf("Tests FAILED: Card drawn is not a treasure card!\n");

                }


               
                
                printf("\n");





    return 0;
}
