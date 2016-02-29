/*
 *
 * randomcardtest.c
 *
 *
 *
 * Include the following lines in your makefile:
 *
 * 
 *
 *
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "assert.h"
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define REPS 100 

int main() {

   
   struct gameState G, testG;
   int numPlayers;
   int player;
   int handPos;//position of council_room card in hand
   int bonus;
   int choice1 = 0, choice2 = 0, choice3 = 0;
   int seed = 1000;
   int i, j, k[10];
   int council_roomPos;
   int reps = REPS; 


 while (reps > 0) {

   printf("\n\n\n-------------------------Random Testing council_room-------------------\n\n");


   srand((unsigned int) time(NULL) + reps);

   numPlayers = ((rand() % 3) + 2);
   council_roomPos = rand() % 10;
   player = rand() % numPlayers;//randomize the player who will play the adventurer

   printf("council_room card at k[%d] position.\nnumber of players = %d\nplayer playing council_room = %d\n", council_roomPos, numPlayers, player);

//   printf("line 42\n");   
   //make random kingdom card selections 
   printf("randomizing kingdom cards...\n");
   for (i = 0; i < 10; i++) {
      if (i == council_roomPos) {k[i] = council_room;}
      else {
         k[i] = (rand() % 20) + 7;
      } 
      if (i == 0) {continue;}

      //ensure unique cardds
      for (j = 0; j < i; j++) { 
         if (k[i] == k[j]) {
            k[i] = (rand() % 20) + 7;//reassign k[i] if duplicate
            j = -1;//restart for loop
         } 
      }
   }
 //  printf("line 57\n");

   //printf all kingdom cards
   printf("\nkingdom cards:\n");
   for (i = 0; i < 10; i++) {
      printf("\tk[%d] = %d\n", i, k[i]);
   }

   printf("initializing game...\n");
   initializeGame(numPlayers, k, seed, &G);
  
/*   printf("supply counts:\n");
   for (i = 0; i < treasure_map + 1; i++) {
      printf("\tsupplyCount[%d] = %d\n", i, G.supplyCount[i]);
   }
*/
   //set random supplyCount of decks
   for (i = 0; i < treasure_map + 1; i++) {
      if (G.supplyCount[i] == -1) {continue;}
      G.supplyCount[i] = rand() % G.supplyCount[i];
   }

   //print supply of all decks 
/*   printf("supply counts:\n");
   for (i = 0; i < treasure_map + 1; i++) {
      printf("\tsupplyCount[%d] = %d\n", i, G.supplyCount[i]);
   }
*/
   //randomize state variables
   G.numActions = rand() % 5;
   G.coins = rand() % 5;
   G.numBuys = rand() % 5;
   G.whoseTurn = player;
   


   printf("numactions = %d\ncoins = %d\nnumbuys = %d\nwhoseTurn = %d\nphase = %d\n\n", G.numActions, G.coins, G.numBuys, G.whoseTurn, G.phase); 



   //Set the hand count for each player
   for (i = 0; i < numPlayers; i++) {
      //if not player's turn, then they have 5 cards in hand
/*      if (i != player) {
         handCount[i] = 5;
         continue;
      }
*/
      int handCountOption = rand() % 4;

      switch(handCountOption) {
         case 0: G.handCount[i] = 5;
            break;
         case 1: G.handCount[i] = (rand() % 5) + 1;//player has between 1 and 5 cards in hand
            break;
         case 2: G.handCount[i] = (rand() % 10 ) + 1;//player has between 1 and 10 cards in hand.
            break;
         case 3: G.handCount[i] = (rand() % 25 ) + 1;//player has between 1 and 25 cards in hand
      }
   }

   //fill hand with random cards
   handPos = rand() % G.handCount[player];
   for (i = 0; i < numPlayers; i++) {
      for (j = 0; j < G.handCount[i]; j++) {
         if ((i == player) && (j == handPos)) { 
            G.hand[player][j] = adventurer;//this sets the adventurer card in the player's hand
         }
         else {
            int cardTypeOption = rand() % 3;
            switch (cardTypeOption) {
               case 0: G.hand[i][j] = rand() % 4;//card is a victory card 
                  break;
               case 1: G.hand[i][j] = (rand() % 3) + 4;//card is a treasuer card 
                  break;
               case 2: G.hand[i][j] = k[(rand() % 10)];//card is a kingdom card 
                  break;
            }
         }
      }
   }

   //Set the deck count for each player
   for (i = 0; i < numPlayers; i++) {

      int deckCountOption = rand() % 4;

      switch(deckCountOption) {
         case 0: G.deckCount[i] = 10;
            break;
         case 1: G.deckCount[i] = rand() % 24;//player has between 0 and 25 cards in deck 
            break;
         case 2: G.deckCount[i] = rand() % 49;//player has between 0 and 50 cards in deck.
            break;
         case 3: G.deckCount[i] = rand() % MAX_DECK;//player has between 0 and 500 cards in deck 
      }
   }

   //fill each player deck with random cards
   for (i = 0; i < numPlayers; i++) {
      for (j = 0; j < G.deckCount[i]; j++) {
         int cardTypeOption = rand() % 3;
         switch (cardTypeOption) {
            case 0: G.deck[i][j] = rand() % 4;//card is a victory card 
               break;
            case 1: G.deck[i][j] = (rand() % 3) + 4;//card is a treasuer card 
               break;
            case 2: G.deck[i][j] = k[(rand() % 10)];//card is a kingdom card 
               break;
         }
      }
   }

   //Set the discard count for each player
   for (i = 0; i < numPlayers; i++) {

      int discardCountOption = rand() % 4;

      switch(discardCountOption) {
         case 0: G.discardCount[i] = 10;
            break;
         case 1: G.discardCount[i] = rand() % 24;//player has between 0 and 25 cards discarded 
            break;
         case 2: G.discardCount[i] = rand() % 49;//player has between 0 and 50 cards in discarded
            break;
         case 3: G.discardCount[i] = rand() % MAX_DECK - G.deckCount[i];//player has between 1 and 500 cards discarded 
      }
   }

   //fill each player deck with random cards
   for (i = 0; i < numPlayers; i++) {
      for (j = 0; j < G.discardCount[i]; j++) {
         int cardTypeOption = rand() % 3;
         switch (cardTypeOption) {
            case 0: G.discard[i][j] = rand() % 4;//card is a victory card 
               break;
            case 1: G.discard[i][j] = (rand() % 3) + 4;//card is a treasuer card 
               break;
            case 2: G.discard[i][j] = k[(rand() % 10)];//card is a kingdom card 
               break;
         }
      }
   }

   int playedCardCountOption = rand() % 4; 

   switch(playedCardCountOption) {
      case 0: G.playedCardCount = 0;
         break;
      case 1: G.playedCardCount = (rand() % 3) + 1;//between 1 and 3 cards played 
         break;
      case 2: G.playedCardCount = (rand() % 5) + 1;//player has between 1 and 5 cards played 
         break;
      case 3: G.playedCardCount = (rand() % MAX_DECK) + 1;//player has between 1 and 500 cards played 
   }

   for (i = 0; i < G.playedCardCount; i++) {
      int cardTypeOption = rand() % 3;
      switch (cardTypeOption) {
         case 0: G.playedCards[i] = rand() % 4;//card is a victory card 
            break;
         case 1: G.playedCards[i] = (rand() % 3) + 4;//card is a treasuer card 
            break;
         case 2: G.playedCards[i] = k[(rand() % 10)];//card is a kingdom card 
            break;
      }
   }

/*TESTING THE TESTING!!!!!!!----------------------------------------------*/

   //test random card selection:
   
   printf("numCardsPlayed = %d\n", G.playedCardCount);
   for (i = 0; i < G.playedCardCount; i++) {
//      printf("\tplayedCard[%d] = %d\n", i, G.playedCards[i]);
   }
 
   printf("\nplayer %d playing council_room from handpos %d\n\n", player, handPos);
   for (i = 0; i < numPlayers; i ++) {
      printf("player %d:  handCount = %d\t", i, G.handCount[i] );
      for (j = 0; j < G.handCount[i]; j ++) {
//         printf("\tG.hand[%d][%d] = %d\n", i, j, G.hand[i][j]); 
      } 
      printf("deckCount = %d\t", G.deckCount[i] );
      for (j = 0; j < G.deckCount[i]; j ++) {
//         printf("\tG.deck[%d][%d] = %d\n", i, j, G.deck[i][j]); 
      } 
      printf("discardCount = %d\n", G.discardCount[i] );
      for (j = 0; j < G.discardCount[i]; j ++) {
//         printf("\tG.discard[%d][%d] = %d\n", i, j, G.discard[i][j]); 
      } 
   }

   printf("\ncopying game state G to testG\n");
   memcpy(&testG, &G, sizeof(struct gameState));
  
   printf("calling cardEffect(council_room, 0, 0, &testG, handPos = %d, &bonus = %d)\n", handPos, bonus);
   cardEffect(council_room, choice1, choice2, choice3, &testG, handPos, &bonus);


   printf("\nTEST 1: DRAW 4 CARDS - player has 4 new cards - 1 discard\n");

   printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player] + 3);
   assert(testG.handCount[player] == G.handCount[player] + 3);

   printf("\nTEST 2: BUYS INCREMENTED - buys + 1\n");

   printf("\tnumBuys = %d; expected = %d", testG.numBuys, G.numBuys + 1);
   assert(testG.numBuys == G.numBuys + 1);

   printf("\nTEST 3: CARDS ARE FROM DECK - new cards are the next cards from deck\n");

   printf("\tdiscardCount + deckCount = %d; expected = %d", testG.discardCount[player] + testG.deckCount[player], G.discardCount[player] + G.deckCount[player] - 4);
   assert(testG.discardCount[player] + testG.deckCount[player] == G.discardCount[player] + G.deckCount[player] - 4);

 
   printf("\nTEST 4: PLAYED CARDS - 1 additional played card\n");

   printf("\tplayedCardCount = %d, expected = %d", testG.playedCardCount, G.playedCardCount + 1);
   assert(testG.playedCardCount == G.playedCardCount + 1);

   printf("\nTEST 5: OTHER PLAYERS DRARW CARD - each other player in the game draws a card from their deck\n");
   for (i  = 0; i < numPlayers; i++) {
      if (i == player) {continue;}
      printf("\tPlayer[%d]:\n\t\thandCount = %d; expected = %d\t%s\n\t\tdeckCount + discardCount = %d; expected = %d\t%s\n", i, testG.handCount[i], G.handCount[i] + 1,
        assert2(testG.handCount[i] == G.handCount[i] + 1), testG.discardCount[i] + testG.deckCount[i], G.discardCount[i] + G.deckCount[i] - 1,
        assert2(testG.discardCount[i] + testG.deckCount[i] == G.discardCount[i] + G.deckCount[i] - 1));
   }

   printf("\nTEST 6: NO STATE CHANGE - state remains unchanged in unaffected variables\n");

   //Test supply counts
   printf("\tSupply Counts:\t");
   int fail = 0;
   for (i = 0; i < treasure_map + 1; i++) {
      if (G.supplyCount[i] != testG.supplyCount[i]) {
         printf("testG.supplyCount[%d] = %d, expected = %d\tFAIL\n", i, testG.supplyCount[i], G.supplyCount[i]);
         fail = 1;
      }
   }
   if (!fail) {
      printf("PASS\n");
   }
   else printf("FAIL\n"); 

   //test other player cards
   printf("\n\tOther Player States:\n");     

   for (i = 0; i < numPlayers; i++) {
      if (player == i) {continue;}
      printf("\t\tPlayer[%d]: ", i);
      fail = 0;
      
      for (j = 0; j < testG.discardCount[i]; j++) {
         if (testG.discard[i][j] != G.discard[i][j]) {
            printf("\n\t\ttestG.discard[%d][%d] = %d; expected = %d\tFAIL\n", i, j, testG.discard[i][j], G.discard[i][j]);
            fail = 1;
         }
      }
      for (j = 0; j < testG.deckCount[i]; j++) {
         if (testG.deck[i][j] != G.deck[i][j]) {
            printf("\n\t\ttestG.deck[%d][%d] = %d; expected = %d\tFAIL\n", i, j, testG.deck[i][j], G.deck[i][j]);
            fail = 1;
         }
      }
      if (testG.discardCount[i] != G.discardCount[i]) {
         fail = 1;
         printf("player[%d] state: FAIL\n", i); 
      }
      if (!fail) printf("PASS\n");
   }

   printf("\n\tnumActions = %d; expected = %d", testG.numActions, G.numActions);
   assert(testG.numActions == G.numActions);
   printf("\tcoins = %d; expected = %d\t", testG.coins, G.coins);
   assert(testG.coins == G.coins);
//   printf("\t\nnumActions = %d; expected = %d\n", testG.numActions, G.numActions);
   
   printf("\n\n----------------------council_room test complete------------------------\n\n\n");


   reps--;
 }
   return 0;
}
