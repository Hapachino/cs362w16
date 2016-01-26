/* -----------------------------------------------------------------------
 * Testing scoreFor()
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
    int j;
    //Used to print out correct name of card being tested in printf statement.
    const char* cardNames[] =
    {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
      "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
     "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map" };
    
    int nameCards[MAX_HAND][MAX_HAND];
    int testAllCards;
    int deckCards;
    int handCards;
    int discardCards;
    int seed = 1000;
    int numPlayer = 2;
    int p, r;
    int pointCards[6] = {0,1,2,3,16,10}; //Used to orginize point cards used
    int pointValue[6] = {-1,1,3,6,1,0}; //Used to orginize the point values that go with pointcards
    int score; //keeps return number for fullDeckCount(p, allCards, &G)
     int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int totalCards = 5;
    //Make Array called nameCards, that holds decks full of same card name
    for (i = 0; i < MAX_HAND; i++) {
       for (j = 0; j < MAX_HAND; j++) {
      nameCards[i][j] = i;
       }
    }
    
    
    
    
    
    printf ("TESTING scoreFor( ):\n");    
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
    } // END player
    
    
    

    return 0;
}