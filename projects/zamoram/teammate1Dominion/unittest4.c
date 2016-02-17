/* -----------------------------------------------------------------------
 * Testing isGameOver()
 Basic requirements of isGameOver()
   1)Does game end when provience cards are empty?
   2)Game shouldn't end with a provience card.
   3)Does game end when only 2 or less supply piles are empty?
   4)Does game end when a certain type of card 
      is included when the 3 piles are gone?
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>


int main() {
    int i;
    //Used to print out correct name of card being tested in printf statement.
    const char* cardNames[] =
    {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
      "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
     "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map" };
    
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int a, b, c;//Used for testing every combination of 3 cards being zero
    int gameOverRetValue;
     int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    
    
    printf ("\nTESTING isGameOver( ):\n");
    
    
    
    
    
    printf("\nTest 1 - Zero provience cards in supply end game\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    
    //Making sure supply count for other cards is > 0 so they don't end.
    for(i=0; i < 27;i++) {
      G.supplyCount[i] = 10;
    }
    G.supplyCount[province] = 0; //Setting province to 0
    
    gameOverRetValue = isGameOver(&G);
    printf("Return value = %d, expected = 1\n", gameOverRetValue);
    assert(gameOverRetValue == 1);
    
    
    
    
    
    
    printf("\nTest 2 - 1 provience card in supply shouldn't end game\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    
    //Making sure supply count for other cards is > 0 so they don't end.
    for(i=0; i < 27;i++) {
      G.supplyCount[i] = 10;
    }
    
    gameOverRetValue = isGameOver(&G);
    printf("Return value = %d, expected = 0\n", gameOverRetValue);
    assert(gameOverRetValue == 0);
    
    
    
    
    
    
    printf("\nTest 3 - Does game end when 2 or less supply piles are empty\n");
    //printf("(Province card set to 1 - to prevent that from stopping test)\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    
    //All supply piles set to ten
    for(i=0; i < 27;i++) {
      G.supplyCount[i] = 10;
    }

    G.supplyCount[great_hall] = 0; //Setting great_hall to 0
    
    
    printf("           Testing 1 card empty\n");
    gameOverRetValue = isGameOver(&G);
    printf("Return value = %d, expected = 0\n", gameOverRetValue);
    assert(gameOverRetValue == 0);
    
    G.supplyCount[baron] = 0; //Setting baron to 1

    printf("           Testing 2 cards empty\n");
    gameOverRetValue = isGameOver(&G);
    printf("Return value = %d, expected = 0\n", gameOverRetValue);
    assert(gameOverRetValue == 0);
    
    
    
    
    
    
    printf("\nTest 4 - Test all card combinations of empty\n");

    for(a=0;a < 27;a++){
        for(b=0;b < 27;b++){
            for(c=0;c < 27;c++){
                //Don't do test if cards == each other and skip province
                if(a!=b && b!=c && c!=a && a != 3 && b != 3 && c != 3) {
                   //All supply piles set to ten
                   for(i=0; i < 27;i++) {
                     G.supplyCount[i] = 10;
                    }
                    
                    G.supplyCount[a] = 0;
                    G.supplyCount[b] = 0;
                    G.supplyCount[c] = 0;
                    
                    gameOverRetValue = isGameOver(&G);
                    printf("     Testing %s, %s, and %s\n", cardNames[a],cardNames[b],cardNames[c]);
                    printf("     Return value = %d, expected = 1\n", gameOverRetValue);
                    //assert(gameOverRetValue == 1);
                    if(gameOverRetValue == 1) {
                       printf("       TEST PASS\n\n");
                    } else { printf("       TEST FAIL******\n\n"); }
                }
            }
         }
    }


    
    /* printf ("TESTING isGameOver( ):\n");    
    //Test both players
    for (p = 0; p < numPlayer; p++){
       //Used to cycle thru the 6 cards that actually have point values
       for (testAllCards = 0; testAllCards < 6; testAllCards++){
          //Next 3 for() statements used to check various sizes of decks
          //from 0 cards in all decks to 5 cards in each deck.
         for (deckCards = 0; deckCards <= totalCards; deckCards++){
          
          for (handCards = 0; handCards <= totalCards; handCards++){
             
             for (discardCards = 0; discardCards <= totalCards; discardCards++){
                  
                  
                
                      printf("\nTesting player %d with %d %s card(s).\nAmount in location: Deckcards: %d  HandCards: %d DiscardCards: %d. Point Value: %d\n", p, deckCards + handCards + discardCards, cardNames[pointCards[testAllCards]], deckCards, handCards, discardCards,pointValue[testAllCards]);
                      memset(&G, 23, sizeof(struct gameState));   // clear the game state
                      r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                      
                      
                      
                      G.deckCount[p] = deckCards;                 // set the number of cards deckCard
                      memcpy(G.deck[p], nameCards[pointCards[testAllCards]], (sizeof(int) * deckCards)); // set all the cards to current test card "nameCards"      
                      G.handCount[p] = handCards;                 // set the number of cards on handCount
                      memcpy(G.hand[p], nameCards[pointCards[testAllCards]], (sizeof(int) * handCards)); // set all the cards to current test card "nameCards"
                      G.discardCount[p] =discardCards;                 // set the number of cards on discardCount
                      memcpy(G.discard[p], nameCards[pointCards[testAllCards]], (sizeof(int) * discardCards)); // set all the cards to current test card "nameCards"
                      
                      
                      
                      score = scoreFor(p,&G);
                      //Gardens card has a different oracle test so it's included in the else when tested. 
                      if(testAllCards != 5) {
                        printf("Score = %d, expected = %d ", score,(deckCards + handCards + discardCards)*(pointValue[testAllCards]));
                        if(score != ((deckCards + handCards + discardCards)*(pointValue[testAllCards]))){
                           printf("TEST FAILED\n");
                        }
                      } else {
                         printf("Score = %d, expected = %d ", score,(deckCards + handCards + discardCards)/10);
                         if(score != ((deckCards + handCards + discardCards)/(10))){
                           printf("TEST FAILED\n");
                        }
                      }
                      
                 
             } //END discardCards
          } //END handCards
         } //END deckCards
       } //END testAllCards
    } // END player */
    
    
    

    return 0;
}