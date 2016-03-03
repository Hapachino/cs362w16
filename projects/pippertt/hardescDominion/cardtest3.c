/*
  Name: Thomas "Adam" Pippert
  Due Date: 2-February-2016
  File: cardtest3.c
  Purpose: Card testing for Village card
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

  int i; 	               /* Counters */
  int p, p2;		       /* Players */
  int pos;		       /* Position */
  int playerDeckSize;	       /* Size of players deck */
  int opponentDeckSize;	       /* Size of opponent's deck */
  int pileSize;		       /* Size of usable card pile */
  int numPlayers = 2;  	       /* Players for a valid gamestate */
  int numTests = 1; 	       /* Testing spread */
  int numActions;              /* number of player actions */ 
  struct gameState initState;  /* Original gamestate */
  struct gameState testState;  /* Gamestate under test */
  int k[10] = {duchy, gardens, province, estate, tribute, mine, cutpurse, ambassador, great_hall, adventurer};
  char testCard[] = "Village"; /* Card under test */

  /* Testing the Card */

  printf("*** TESTING CARD: %s ***\n\n ", testCard);
	
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
      pileSize = testState.deckCount[p];  /* Non-trashed cards */
      numActions = testState.numActions;
		
      /* Play the card! */
      cardEffect(village, 0, 0, 0, &testState, 0, 0);
      
      /* Test 1: Make sure player gains one card. */ 
      printf("\nTest 1: Play Village and gain 1 card:\n");
      if(initState.handCount[p] == testState.handCount[p])
        {/* Lose Village (-1), but gain 1 (+1) */
          printf("Passed. Expected hand count: %d   Hand count finish: %d\n", initState.handCount[p], testState.handCount[p]);
        }
      else
        { /* ERROR: Hand size mismatch */
          printf("FAILED. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p], testState.handCount[p]);
        }

      /* Test 2: Ensure player gains exactly 2 numActions */
      printf("\nTest 2: Play Village and gain 2 numActions:\n");
      if(testState.numActions - initState.numActions == 2)
        {/* start w/action 1, use action to play card (-1), gain 2 */
          printf("Passed. Expected Action count: %d   Action finish: %d\n", 2, testState.numActions - initState.numActions);
	}
      else
        {
          printf("FAILED. Expected Action count: %d   Action finish: %d\n", 2, testState.numActions - initState.numActions);		}

 /* Test 3a: Ensure opponent's deck did not change size */
      printf("\nTest 3a: Opponent's deck size unchanged when Adventurer is drawn:\n");
      if(testState.deckCount[p2] == opponentDeckSize)
        {
        printf("Passed. Deck size start: %d, Deck size finish: %d\n", opponentDeckSize, testState.deckCount[p2]);
        }
      else
        { /* ERROR: Opponent's deck changed */
        printf("FAILED. Deck size start: %d, Deck size finish: %d\n", opponentDeckSize, testState.deckCount[p2]);
        }

       /* Test 3b: Ensure opponent's hand did not change size */
      printf("\nTest 3b: Other player's hand size unchanged when smithy is drawn:\n");
      if(testState.handCount[p2] == initState.handCount[p2])
        {
          printf("Passed. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p2], testState.handCount[p2]);
        }
      else
        { /* ERROR: Opponent's hand changed */
          printf("FAILED. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p2], testState.handCount[p2]);
        }
            
 /* Test 4: Cards are sourced from player's deck*/
      printf("\nTest 4: Player is drawing from own pile:\n");
      if(initState.deckCount[p] -1 == testState.deckCount[p])
        {/* - 1 taken from the deck */
          printf("Passed. Expected: %d, Deck size finish: %d\n", initState.deckCount[p] - 1, testState.deckCount[p]);
	}
      else
        { /* ERROR: Deck size incorrect, cards missourced */
          printf("FAILED. Expected: %d, Deck size finish: %d\n", initState.deckCount[p] - 1, testState.deckCount[p]);
        }

      /* Test 5: Village card added to the played card pile */
      printf("\nTest 5: Village card added to played pile after use:\n");
      if(testState.playedCardCount == 1)
        {
          printf("Passed. Expected increase in played pile: %d, Played pile: %d\n", 1, testState.playedCardCount);
        }
      else
        {
         printf("FAILED. Expected increase in played pile: %d, Played pile: %d\n", 1, testState.playedCardCount);
        }
      
      /* Test 6: Extraneous Victory Point changes */
      printf("\nTest 6: Supply of Victory Points unchanged: \n ");
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
         
      /* Test 7: Extraneous money changes */
         printf("\nTest 7: Changes in Coins: \n");
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

      
