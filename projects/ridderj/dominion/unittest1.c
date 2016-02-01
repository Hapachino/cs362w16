/* -----------------------------------------------------------------------
 * Testing fullDeckCount()
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
    int deckCards;
    int handCards;
    int discardCards;
    int seed = 1000;
    int allCards;
    int numPlayer = 2;
    int p, r;
    int count; //keeps return number for fullDeckCount(p, allCards, &G)
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
    
    printf ("TESTING fullDeckCount( ):\n");    
    
    for (p = 0; p < numPlayer; p++){
       
       for (allCards = 0; allCards <= 26; allCards++){
         for (deckCards = 0; deckCards <= totalCards; deckCards++){
          
          for (handCards = 0; handCards <= totalCards; handCards++){
             
             for (discardCards = 0; discardCards <= totalCards; discardCards++){
                  
                  
                
                      printf("Testing player %d with %d %s card(s).\nAmount in location: Deckcards: %d  HandCards: %d DiscardCards: %d.\n", p, deckCards + handCards + discardCards, cardNames[allCards], deckCards, handCards, discardCards);
                      
                      memset(&G, 40, sizeof(struct gameState));   // clear the game state
                      r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                      
                      
                      
                      G.deckCount[p] = deckCards;                 // set the number of cards deckCard
                      memcpy(G.deck[p], nameCards[allCards], sizeof(int) * deckCards); // set all the cards to current test card "nameCards"      
                      
                      G.handCount[p] = handCards;                 // set the number of cards on handCount
                      memcpy(G.hand[p], nameCards[allCards], sizeof(int) * handCards); // set all the cards to current test card "nameCards"
                      
                      G.discardCount[p] =discardCards;                 // set the number of cards on discardCount
                      memcpy(G.discard[p], nameCards[allCards], sizeof(int) * discardCards); // set all the cards to current test card "nameCards"

                      
                      
                      
                      count = fullDeckCount(p, allCards, &G);
                      printf("Count = %d, expected = %d\n", count, deckCards + handCards + discardCards);
                      assert(count == (deckCards + handCards + discardCards)); // check if the number of coins is correct
                 
             } //END discardCards
          } //END handCards
         } //END deckCards
       } //END allCards
    } // END player
     printf("All tests passed!\n");

    return 0;
}