/* -----------------------------------------------------------------------
 * Testing adventurer card
 Basic requirements of adventurer card
   1)Player should recieve 2 treasure cards in their hand.
   2)Adventurer card should work with all treasure coins.
   3)If deck is empty adventurer should single that cards
      should be shuffled from discard deck and be used.
   4)Other players shouldn't have any changes to their cards.
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
    int l;
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
    int treasureFound = 0;
    int treasure[3] = {4,5,6};
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int pointCards[6] = {0,1,2,3,16,10}; //Used to orginize point cards used
    int pointValue[6] = {-1,1,3,6,1,0}; //Used to orginize the point values that go with pointcards
    int score; //keeps return number for fullDeckCount(p, allCards, &G)
     int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int totalCards = 5;
    //Make Array called nameCards, that holds decks full of same card name
    for (i = 0; i < MAX_HAND; i++) {
       for (j = 0; j < MAX_HAND; j++) {
      nameCards[i][j] = i;
       }
    }
    
    
    printf ("TESTING adventurer card:\n\n");
    

    
    
    
    
    
    
    
    printf("TEST 1&2: Player should recieve 2 treasure cards in their hand.\n");
    printf("Adventurer card should work with all treasure coins.\n");
    for(l=0;l < 3;l++) {
       printf("    Testing with %s\n",cardNames[treasure[l]]);
       
       memset(&G, 23, sizeof(struct gameState));   // clear the game state
       r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
       
       
       G.whoseTurn = 0; //player 1s turn
       
       //put treasure cards in deck
       for (i = 0; i < 6; i++) {
         G.deck[0][i] = treasure[l]; 
       }
       G.deck[0][4] = 20;
       G.deck[0][5] = 20;
       //deck has estate, duchy, treasure, treasure, treasure
       G.deckCount[0] = 5;
       

       //Fill hand with adventurer cards
       for (i = 0; i < 6; i++) {
         G.hand[0][i] = 7; //adventurer
       }
       G.handCount[0] = 5;
       
       
       
       //run card
       handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
       cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
       
       //Count treasure cards in hand
       treasureFound = 0;
       for (i = 0; i < G.handCount[0]; i++) {
         if(G.hand[0][i] == 4 || G.hand[0][i] == 5 || G.hand[0][i] == 6) {
            treasureFound++;
         } 
       }
       
       printf("    Total %d cards in hand & found %d treasure cards,expected 6 & 2 %s\n", G.handCount[0],treasureFound, cardNames[treasure[l]]);
       if(G.handCount[0] != 6 || treasureFound != 2)
          printf("TEST FAIL\n");
    } //END tresure types
    
    
    
    
    
    
    
    
    
    
    
    
    
    printf("\nTEST 3: If deck is empty adventurer should single that cards\n");
    printf("should be shuffled from discard deck and be used.\n");
    
    
    
    
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
       r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
       
       
       G.whoseTurn = 0; //player 1s turn
       
       //deck = to zero cards
       G.deck[0][i] = -1; 
       G.deckCount[0] = 0;
       

       //Fill hand with adventurer cards
       for (i = 0; i < 6; i++) {
         G.hand[0][i] = 7; //adventurer
       }
       G.handCount[0] = 5;
       
       
       //put treasure cards in discard deck
       for (i = 0; i < 6; i++) {
         G.discard[0][i] = 4; 
       }
       //discard deck has estate, duchy, treasure, treasure, treasure
       G.discardCount[0] = 5;
       
       
       
       //run card
       handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
       cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
       
        //Count treasure cards in hand
       treasureFound = 0;
       for (i = 0; i < G.handCount[0]; i++) {
         if(G.hand[0][i] == 4 || G.hand[0][i] == 5 || G.hand[0][i] == 6) {
            treasureFound++;
         } 
       }
       
       printf("    Total %d cards in discard deck\n", G.discardCount[0]);
       if(G.discardCount[0] != 0)
          printf("TEST FAIL\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    printf("\nTEST 4: Other players shouldn't have any changes to their cards.\n");
    
    for(numPlayer = 2; numPlayer < 5;numPlayer++) {
       printf("    Testing with %d players\n",numPlayer);
       
       memset(&G, 23, sizeof(struct gameState));   // clear the game state
       r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
       
       G.whoseTurn = 0; //player 1s turn
       
       //Fill Other players decks
       for(l=1;l < numPlayer;l++){
          for (i = 0; i < 6; i++) {
            G.deck[l][i] = 0;
            G.discard[l][i] = 0;
            G.hand[l][i] = 0; 
          }
            G.deckCount[l] = 5;
            G.discardCount[l] = 5;
            G.handCount[l]= 5;
       }
       
       
       //put treasure cards in deck
       for (i = 0; i < 6; i++) {
         G.deck[0][i] = 4; 
       }
       G.deckCount[0] = 5;

       //Fill hand with adventurer cards
       for (i = 0; i < 6; i++) {
         G.hand[0][i] = 7; //adventurer
       }
       G.handCount[0] = 5;
       
       //run card
       handpos = 1, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
        cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
       for(l=1;l < numPlayer;l++){
          printf("    Player %d has deck count %d,expected 5\n", l+1, G.deckCount[l]);
          assert(G.deckCount[l]== 5);
          printf("    Player %d has discard deck count %d,expected 5\n", l+1, G.discardCount[l]);
          assert(G.discardCount[l]== 5);
          printf("    Player %d has hand count %d,expected 5\n", l+1, G.handCount[l]);
          assert(G.handCount[l]== 5);
       }
       
    }
    
    

    
    
    
    

    return 0;
}