/*
  Name: Thomas "Adam" Pippert
  Due Date: 2-February-2016
  File: cardtest2.c
  Purpose: Card testing for Adventurer card
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

  int i, j; 	               /* Counters */
  int p, p2;		       /* Players */
  int pos;		       /* Position */
  int played;		       /* Cards played from deck */
  int playerDeckSize;	       /* Size of players deck */
  int opponentDeckSize;	       /* Size of opponent's deck */
  int pileSize;		       /* Size of usable card pile */
  int numPlayers = 2;  	       /* Players for a valid gamestate */
  int numTests = 1; 	       /* Testing spread */
  int preCount;                /* Initial coin card count */
  int coinAcquire;	       /* count of acquired coins */
  int totalDrawn;	       /* Cards drawn before +2 coins */
  int drawnTreasure;	       /* Treasure card counter */
  struct gameState initState;  /* Original gamestate */
  struct gameState testState;  /* Gamestate under test */
  int k[10] = {duchy, gardens, province, estate, tribute, mine, cutpurse, ambassador, great_hall, adventurer};
  char testCard[] = "adventurer"; /* Current card under test */

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
      played = testState.handCount[p] - testState.discardCount[p];
      pileSize = testState.deckCount[p];  /* Non-trashed cards */

      /* Initialize other state variables */
      totalDrawn = 0;
      drawnTreasure = 0;
      coinAcquire = 0;	  
		
      /* Test 1a: Drawing continues until two coins drawn */
      printf("\nTest 1: Play Adventurer, draw cards until two coins are drawn:\n");
      initializeGame(numPlayers, k, 1000, &initState);
      memcpy(&testState, &initState, sizeof(struct gameState));
      testState.hand[p][0] = adventurer;
      testState.hand[p][1] = duchy;
      testState.hand[p][2] = estate;
      testState.hand[p][3] = province;
      testState.hand[p][4] = gardens;
      testState.deck[p][0] = copper;
      testState.deck[p][1] = silver;
      testState.deck[p][2] = gold;
      testState.deck[p][3] = copper;
      testState.deck[p][4] = silver;
      preCount = testState.handCount[p];
      cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);

      if(testState.handCount[p] - preCount == 2) 
        {
        printf("Passed. Coin card count expected: %d, count finish: %d\n", 2, testState.handCount[p] - preCount);
	}
      else
        { /* ERROR: Coin card count mismatch */
          printf("FAILED. Coin card count expected: %d, count finish: %d\n", 2, testState.handCount[p] - preCount);
        }
      /* List of coin cards found */
      printf("Coin cards found: ");
      for(j = 0; j < testState.handCount[p]; j++)
        {
        if(testState.hand[p][j] == copper)
          {
            printf("copper, ");
            coinAcquire += 1;
          }
        if(testState.hand[p][j] == silver)
          {
            printf("silver, ");
            coinAcquire += 2;
          }
        if(testState.hand[p][j] == gold)
          {
            printf("gold, ");
            coinAcquire += 3;
          }
        }

      /* Test 1b: Correct coin values */
      printf("\nTest 1b: Acquired cards, coin value unchanged before use:\n");
      if(initState.coins == testState.coins)
        {
        printf("Passed. Coin amount is the same.\n");
        }
      else
        { /* ERROR: Coin value changed */
        printf("FAILED. Coin amount is different.\n");
        }

      /* Test 1c: Play card, draw gold */
      printf("\nTest 1c: Test 1 with gold drawn:\n");
      initializeGame(numPlayers, k, 1000, &initState);
      memcpy(&testState, &initState, sizeof(struct gameState));
      testState.hand[p][0] = adventurer;
      testState.hand[p][1] = duchy;
      testState.hand[p][2] = estate;
      testState.hand[p][3] = province;
      testState.hand[p][4] = gardens;
      testState.deck[p][0] = gold;
      testState.deck[p][1] = silver;
      testState.deck[p][2] = gold;
      testState.deck[p][3] = copper;
      testState.deck[p][4] = gold;
      preCount = testState.handCount[p];
      cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);				
      if(testState.handCount[p] - preCount == 2) 
        {
          printf("Passed. Coin card count expected: %d, count finish: %d\n", 2, testState.handCount[p] - preCount);
	}
      else 
        { /* ERROR: Coin count mismatch */
          printf("FAILED. Coin card count expeccted: %d, count finish: %d\n", 2, testState.handCount[p] - preCount);
        }
      printf("Coin cards found: ");
      for(j = 0; j < testState.handCount[p]; j++)
        {
        if(testState.hand[p][j] == copper)
          {
            printf("copper, ");
            coinAcquire += 1;
          }
        if(testState.hand[p][j] == silver)
          {
            printf("silver, ");
            coinAcquire += 2;
          }
        if(testState.hand[p][j] == gold)
          {
            printf("gold, ");
            coinAcquire += 3;
          }
        }
      
      /* Test 2: Ensure drawnTreasure is matching amount of distributed coin cards */
      initializeGame(numPlayers, k, 1000, &initState);
      memcpy(&testState, &initState, sizeof(struct gameState));
      testState.hand[p][0] = adventurer;
      testState.hand[p][1] = duchy;
      testState.hand[p][2] = estate;
      testState.hand[p][3] = province;
      testState.hand[p][4] = gardens;
      testState.deck[p][0] = gardens;
      testState.deck[p][1] = silver;
      testState.deck[p][2] = gold;
      testState.deck[p][3] = copper;
      testState.deck[p][4] = duchy;
      cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);	

      printf("\nTest 2: Make sure all cards were discarded that were not coins:\n");
      if(1 == testState.discardCount[p])
        {/* Gain one non-coincard prior to 2 with this deck */
          printf("Passed. Expected discard amount: %d, Discarded finish: %d\n", 1, testState.discardCount[p]);
        }
      else
        { /* ERROR: Discarded cards incorrectly */
          printf("FAILED. Expected discard amount: %d, Discarded finish: %d\n", 1, testState.discardCount[p]);
	}	

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
      
      /* Test 4: Cards are sourced from player's deck, keeping 2 cards */
      printf("\nTest 4: Player is drawing and keeping only two cards from own pile:\n");
      if(initState.deckCount[p] -3 == testState.deckCount[p])
        {/* -1 because one non-coin card pulled */
          printf("Passed. Expected: %d, Deck size finish: %d\n", initState.deckCount[p] - 3, testState.deckCount[p]);
	}
      else
        { /* ERROR: Deck size incorrect, cards missourced */
          printf("FAILED. Expected: %d, Deck size finish: %d\n", initState.deckCount[p] - 3, testState.deckCount[p]);
        }

      /* Test 5: Adventurer card added to the played card pile */
      printf("\nTest 5: Adventurer card added to played pile after use:\n");
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

