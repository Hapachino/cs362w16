/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

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
    
    
    // arrays of all coppers, silvers, and golds
    // int coppers[MAX_HAND];
    // int silvers[MAX_HAND];
    // int golds[MAX_HAND];
    // for (i = 0; i < MAX_HAND; i++)
    // {
        // coppers[i] = copper;
        // silvers[i] = silver;
        // golds[i] = gold;
    // }
   
   
   
   
   
   
   
   
    //SelectStream(1);
    //PutSeed((long)randomSeed);
    //PlantSeeds(1);
    //SelectStream(2);
    //PutSeed(3);
    //Testing Random
    // t = floor(Random()*100000);
    // for(i=0; i < 10; i++) {
      // t = floor(Random()*10);
      // printf("\nRandom Test %d\n", t);
    // }
    
    printf("Card %d", adventurer);
    printf ("TESTING fullDeckCount( ):\n");    
    p=0;
    
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
                      //memcpy(G.discard[p], adventurers, sizeof(int) * discardCards); // set all the cards to current test card
                      
                      
                      
                      count = fullDeckCount(p, allCards, &G);
                      printf("Count = %d, expected = %d\n", count, deckCards + handCards + discardCards);
                      assert(count == (deckCards + handCards + discardCards)); // check if the number of coins is correct
                 
             } //END discardCards
          } //END handCards
       } //END deckCards
       } //END allCards
    } // END player
     printf("All tests passed!\n");
    
    
    
    
    // for (p = 0; p < numPlayer; p++)
    // {
        // for (handCount = 1; handCount <= maxHandCount; handCount++)
        // {
            // for (bonus = 0; bonus <= maxBonus; bonus++)
            // {
// #if (NOISY_TEST == 1)
                // printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
// #endif
                // memset(&G, 23, sizeof(struct gameState));   // clear the game state
                // r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                // G.handCount[p] = handCount;                 // set the number of cards on hand
                // memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                // updateCoins(p, &G, bonus);
// #if (NOISY_TEST == 1)
                // printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
// #endif
                // assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

                // memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                // updateCoins(p, &G, bonus);
// #if (NOISY_TEST == 1)
                // printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
// #endif
                // assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct

                // memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                // updateCoins(p, &G, bonus);
// #if (NOISY_TEST == 1)
                // printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
// #endif
                // assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
            // }
        // }
    // }

    // printf("All tests passed!\n");

    return 0;
}