/* -----------------------------------------------------------------------
 * Testing village card
 Basic requirements of smithy card
   1)Increase current players hand by 1 card
   2)Actions increased by 2
   3)Increase current players hand +1 card and +2 actions with different player sizes.
   4)Play village card when players deck is empty.
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
    
    
    printf ("TESTING village card:\n\n");
    

    
    
    
    
    
    
    
    printf("TEST 1: Increase current players hand by 1 card.\n");

       
       memset(&G, 23, sizeof(struct gameState));   // clear the game state
       r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
       
       
       G.whoseTurn = 0; //player 1s turn
       
       //put 5 treasure cards in deck
       for (i = 0; i < 6; i++) {
         G.deck[0][i] = copper; 
       }

       G.deckCount[0] = 5;
       

       //Fill hand with 5 village cards
       for (i = 0; i < 6; i++) {
         G.hand[0][i] =village; //village
       }
       G.handCount[0] = 5;
       
       
       
       //run card
       handpos = 3, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
       cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
       

       
       printf("    Total %d cards in hand,expected 5\n", G.handCount[0]);
       //assert(G.handCount[0] == 5);
       if(G.handCount[0] != 5)
          printf("TEST FAILED\n");
     
     
     
     
     printf("TEST 2: Actions increased by 2.\n");

       
       memset(&G, 23, sizeof(struct gameState));   // clear the game state
       r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
       
       
       G.whoseTurn = 0; //player 1s turn
       
       //put 5 treasure cards in deck
       for (i = 0; i < 6; i++) {
         G.deck[0][i] = copper; 
       }

       G.deckCount[0] = 5;
       

       //Fill hand with 5 village cards
       for (i = 0; i < 6; i++) {
         G.hand[0][i] =village; //village
       }
       G.handCount[0] = 5;
       
       //Set actions to 1
       G.numActions = 1;
       
       //run card
       handpos = 3, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
       cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
       

       
       printf("     Current Actions %d ,expected 3\n", G.numActions);
       //assert(G.numActions == 3);
       if(G.numActions != 3)
          printf("TEST FAILED\n");
       
     printf("TEST 3: Increase current players hand +1 card and +2 actions with different player sizes.\n");

       
       for(numPlayer = 2; numPlayer < 5;numPlayer++) {
       printf("    Testing with %d players\n",numPlayer);
       
       
          memset(&G, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
          
          
          G.whoseTurn = 0; //player 1s turn
          
          //put 5 treasure cards in deck
          for (i = 0; i < 6; i++) {
            G.deck[0][i] = copper; 
          }

          G.deckCount[0] = 5;
          

          //Fill hand with 5 village cards
          for (i = 0; i < 6; i++) {
            G.hand[0][i] =village; //village
          }
          G.handCount[0] = 5;
          
          //Set actions to 1
          G.numActions = 1;
          
          //run card
          handpos = 3, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
          cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
          

          
          printf("     Current Actions %d ,expected 3\n", G.numActions);
          if(G.numActions != 3) {
            printf("       TEST FAIL\n");
          };
          printf("     Total %d cards in hand,expected 5\n", G.handCount[0]);
          //assert(G.handCount[0] == 5);
          if(G.handCount[0] != 5)
            printf("       TEST FAIL\n");
       }
       
       
       
       
       
       
       printf("TEST 4: Play village card when players deck is empty.\n");

       
       for(numPlayer = 2; numPlayer < 5;numPlayer++) {
       printf("    Testing with %d players\n",numPlayer);
       
       
          memset(&G, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
          
          
          G.whoseTurn = 0; //player 1s turn
          
          //put 5 treasure cards in deck
          // for (i = 0; i < 6; i++) {
            // G.deck[0][i] = copper; 
          // }

          G.deckCount[0] = 0;
          

          //Fill hand with 5 village cards
          for (i = 0; i < 6; i++) {
            G.hand[0][i] =village; //village
          }
          G.handCount[0] = 5;
          
          //Set actions to 1
          G.numActions = 1;
          
          
          
          //Fill discard deck with 5 copper cards
          for (i = 0; i < 6; i++) {
            G.discard[0][i] = copper; //copper
          }
          G.discardCount[0] = 5;
          
          
          
          
          //run card
          handpos = 3, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
          cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);
          

          
          printf("     Current deck count %d, hand count %d, and actions %d;expected 4,5,&3\n", G.deckCount[0], G.handCount[0],G.numActions);
       if(G.deckCount[0] != 4 || G.handCount[0] != 5 || G.numActions != 3 ) {
            printf("       TEST FAIL\n");
          };
     
       
       }
       
       
       
       
 
    
    
    

    return 0;
}