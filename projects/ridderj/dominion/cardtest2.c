/* -----------------------------------------------------------------------
 * Testing smithy card
 Basic requirements of smithy card
   1)Increase current players hand by 3 cards
   2)Other players shouldn't have any changes to their cards.
   3)Smithy card removed from current players hand after being used.
   4)Supply count of all cards not effected.
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
    int smithyFound = 0;
    int supplyCountCheck = 0;
    int treasure[3] = {4,5,6};
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int pointCards[6] = {0,1,2,3,16,10}; //Used to orginize point cards used
    int pointValue[6] = {-1,1,3,6,1,0}; //Used to orginize the point values that go with pointcards
    int score; //keeps return number for fullDeckCount(p, allCards, &G)
     int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG, sizeS;
    int totalCards = 5;
    //Make Array called nameCards, that holds decks full of same card name
    for (i = 0; i < MAX_HAND; i++) {
       for (j = 0; j < MAX_HAND; j++) {
      nameCards[i][j] = i;
       }
    }
    
    
    printf ("TESTING smithy card:\n\n");
    

    
    
    
    
    
    
    
    printf("TEST 1: Increase current players hand by 3 cards.\n");

       
       memset(&G, 23, sizeof(struct gameState));   // clear the game state
       r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
       
       
       G.whoseTurn = 0; //player 1s turn
       
       //put 5 treasure cards in deck
       for (i = 0; i < 6; i++) {
         G.deck[0][i] = copper; 
       }

       G.deckCount[0] = 5;
       

       //Fill hand with 5 smithy cards
       for (i = 0; i < 6; i++) {
         G.hand[0][i] =smithy; //smithy
       }
       G.handCount[0] = 5;
       
       
       
       //run card
       handpos = 3, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
       cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
       

       
       printf("    Total %d cards in hand,expected 7\n", G.handCount[0]);
       if(G.handCount[0] != 7);
         printf("TEST FAIL\n");
       
       
       
       
       
       
       
       
       
       
       printf("\nTEST 2: Other players shouldn't have any changes to their cards.\n");
    
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
          cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
          
          
          for(l=1;l < numPlayer;l++){
             printf("    Player %d has deck count %d,expected 5\n", l+1, G.deckCount[l]);
             assert(G.deckCount[l]== 5);
             printf("    Player %d has discard deck count %d,expected 5\n", l+1, G.discardCount[l]);
             assert(G.discardCount[l]== 5);
             printf("    Player %d has hand count %d,expected 5\n", l+1, G.handCount[l]);
             assert(G.handCount[l]== 5);
          }
       
    }
    
    
    
    
    
    printf("TEST 3: Smithy card removed from current players hand after being used.\n");

       
       memset(&G, 23, sizeof(struct gameState));   // clear the game state
       r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
       
       
       G.whoseTurn = 0; //player 1s turn
       
       //put 5 curse cards in deck
       for (i = 0; i < 6; i++) {
         G.deck[0][i] = curse; 
       }

       G.deckCount[0] = 5;
       
       
       //Fill hand with 4 curse and 1 smithy cards
       for (i = 0; i < 6; i++) {
         G.hand[0][i] =curse;
       }
       G.hand[0][3] = smithy; //smithy
       G.handCount[0] = 5;
       
       
       //set a played card count or program gets seg fault
       G.playedCardCount = 0;
       
       //run card
       handpos = 3, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
       cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
       
       
       //Count smithy cards in hand
       printf("What is hand count %d\n", G.handCount[0]);
       smithyFound = 0;
       for (i = 0; i < G.handCount[0]; i++) {
         if(G.hand[0][i] == smithy) {
            smithyFound++;
         } 
       }
       
       
       printf("    Total %d smithy cards in hand,expected 0\n", smithyFound);
       assert(smithyFound == 0);
      

    
    
    printf("TEST 4: Supply count of all cards not effected.\n");

       
       memset(&G, 23, sizeof(struct gameState));   // clear the game state
       r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
       
       
       G.whoseTurn = 0; //player 1s turn
       
       //put 5 curse cards in deck
       for (i = 0; i < 6; i++) {
         G.deck[0][i] = curse; 
       }

       G.deckCount[0] = 5;
       
       
       //Fill hand with 4 curse and 1 smithy cards
       for (i = 0; i < 6; i++) {
         G.hand[0][i] =curse;
       }
       G.hand[0][3] = smithy; //smithy
       G.handCount[0] = 5;
       
       
       //set a played card count or program gets seg fault
       G.playedCardCount = 0;
       
       
       //SUPPLY COUNT BEFORE
       memcpy(sizeS.supplyCount, G.supplyCount, sizeof(G.supplyCount));   // clear the game state
       
       
       //run card
       handpos = 3, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
       cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
       
       
       
       supplyCountCheck = memcmp(sizeS.supplyCount, G.supplyCount, sizeof(G.supplyCount));
       printf("    Total memcmp is 0,expected 0\n", supplyCountCheck);
       assert(supplyCountCheck == 0);
    
    
    
    
    
    

    return 0;
}