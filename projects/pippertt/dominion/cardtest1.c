/* Name: Thomas "Adam" Pippert
   Due Date: 2-February-2016
   File: cardtest1.c
   Purpose: Card tests for Smithy card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main()
{

  int i; 		       /* Counter */
  int p, p2;		       /* Players */
  int pos;		       /* Current position */
  int played;		       /* Cards played from deck */
  int playerDeckSize;	       /* Size of player's deck */
  int opponentDeckSize;	       /* Size of opponent's deck */
  int pileSize;		       /* Size of usable card pile */
  int numPlayers = 2;  	       /* Players for a valid gamestate */
  int numTests = 1; 	       /* Testing spread */
  struct gameState initState;  /* Original Gamestate */
  struct gameState testState;  /* Gamestate under test */
  int k[10] = {feast, gardens, embargo, remodel, tribute, mine, cutpurse, ambassador, great_hall, smithy};
  char testCard[] = "Smithy";  /* Current card under test */

  /* Testing the Card */

  printf("*** TESTING CARD: %s ***\n\n", testCard);
  
  for(i = 0; i < numTests; i++)
    {      
      /* Set initial hand variables */
      pos = -1;
      p = 0;
      p2 = 1;
      
      /* Copy into another state to preserve */
      initializeGame(numPlayers, k, 1000, &initState);
      memcpy(&testState, &initState, sizeof(struct gameState));
      
      /* Initialize DeckSize variables for player and opponent */
      playerDeckSize = testState.handCount[p];			  
      opponentDeckSize = testState.deckCount[p2];

      /* How many cards were played? */
      played = testState.handCount[p] - testState.discardCount[p];
      pileSize = testState.deckCount[p];  /* Non-trashed cards */
		
      /* Play the card! */
      cardEffect(smithy, 0, 0, 0, &testState, 0, 0);
		
      /* Test 1: Make sure player is at 3 or more cards */
      printf("\nTest 1: Play Smithy and gain 3 cards:\n");
      if(testState.handCount[p] == initState.handCount[p] + 2)
        { /* -1 for losing Smithy, +3 for cards gained */
          printf("Passed. Expected hand count: %d, Hand count finish: %d\n", initState.handCount[p] +2, testState.handCount[p]);
        }
      else
        { /* ERROR: Hand was modified by incorrect number of cards */
          printf("FAILED. Deck size start: %d, Deck size finish: %d\n", initState.handCount[p] +2, testState.handCount[p]);
        }

      /* Test 2a: Ensure opponent's deck did not change size */
      printf("\nTest 2a: Opponent's deck size unchanged when Smithy is drawn:\n");
      if(testState.deckCount[p2] == initState.deckCount[p2])
        {
          printf("Passed. Deck size start: %d, Deck size finish: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
        }
      else
        { /* ERROR: Opponent's deck changed */
          printf("FAILED. Deck size start: %d, Deck size finish: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
        }
         
      /* Test 2b: Ensure opponent's hand did not change size */
      printf("\nTest 2b: Other player's hand size unchanged when smithy is drawn:\n");
      if(testState.handCount[p2] == initState.handCount[p2])
        {
          printf("Passed. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p2], testState.handCount[p2]);
        }
      else
        { /* ERROR: Opponent's hand changed */
          printf("FAILED. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p2], testState.handCount[p2]);
        }

      /* Test 3: Cards are sourced from player's deck */
      printf("\nTest 3: Player is drawing from own deck:\n");
      if(initState.deckCount[p] - 3 == testState.deckCount[p])
        {/* 5 in deck, - 3 taken from it */
      printf("Passed. Expected: %d, Deck size finish: %d\n", initState.deckCount[p] - 3, testState.deckCount[p]);
        }
      else
        { /* ERROR: Deck size changed by incorrect number */
          printf("FAILED. Expected: %d, Deck size finish: %d\n", initState.deckCount[p] - 3, testState.deckCount[p]);
        }
      
      /* Test 4: Smithy card added to the played card pile */
      printf("\nTest 4: Smithy card added to played pile after use:\n");
      if(testState.playedCardCount == 1)
        {
          printf("Passed. Expected increase in played pile: %d, Played pile: %d\n", 1, testState.playedCardCount);
        }
      else
        {
         printf("FAILED. Expected increase in played pile: %d, Played pile: %d\n", 1, testState.playedCardCount);
        }
      
      /* Test 5: Extraneous Victory Point changes */
      printf("\nTest 5: Supply of Victory Points unchanged: \n ");
      if(initState.supplyCount[estate] != testState.supplyCount[estate])
        { /* ERROR: Estate points changed */
          printf("FAILED. Estate Points Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[estate], testState.supplyCount[estate]);
        }
      if(initState.supplyCount[duchy] != testState.supplyCount[duchy])
        { /* ERROR: Duchy points changed */
          printf("FAILED. Duchy Points Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[duchy], testState.supplyCount[duchy]);
        }
      if(initState.supplyCount[province] != testState.supplyCount[province])
        { /* ERROR: Province points changed */
          printf("FAILED. Province Points Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[province], testState.supplyCount[province]);
        }
      if(initState.supplyCount[curse] != testState.supplyCount[curse])
        { /* ERROR: Curse points changed */
          printf("FAILED. Curse Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[curse], testState.supplyCount[curse]);
        }
      else
        { /* Game state preserved! */
         printf("Passed. Land points unchanged.\n");
        }
         
      /* Test 6: Extraneous money changes */
         printf("\nTest 6: Changes in Coins: \n");
         if(initState.supplyCount[copper] != testState.supplyCount[copper])
           { /* ERROR: Copper coin count changed */
             printf("FAILED. Copper Coin Mismatch. Expected: %d  Received: %d\n", initState.supplyCount[copper], testState.supplyCount[copper]);
           }
         if(initState.supplyCount[silver] != testState.supplyCount[silver])
           { /* ERROR: Silver coin count changed */
         printf("FAILED. Silver Coin Mismatch. Expected: %d  Received: %d\n", initState.supplyCount[silver], testState.supplyCount[silver]);
           }
         if(initState.supplyCount[gold] != testState.supplyCount[gold])
           { /* ERROR: Gold coin count changed */
             printf("FAILED. Gold Coin Mismatch. Expected: %d  Received: %d\n", initState.supplyCount[gold], testState.supplyCount[gold]);
           }
         else
           {
             printf("Passed. Coin counts for all treasure card types unchanged.\n");
           }
         
    }
         
  return 0;
}
