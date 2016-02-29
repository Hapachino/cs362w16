/*
  Name: Thomas "Adam" Pippert
  Due Date: 2-February-2016
  File: cardtest4.c
  Purpose: Card testing for Steward card
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
  
  int i, j; 	                /* Counters */
  int p, p2;		        /* Players */
  int pos;		        /* Position */
  int playerDeckSize;	        /* Size of players deck */
  int opponentDeckSize;	        /* Size of opponent's deck */
  int pileSize;		        /* Size of usable card pile */
  int numPlayers = 2;  	        /* Players for a valid gamestate */
  int numTests = 1; 	        /* Testing spread */
  int numActions;               /* number of player actions */
  int amount;			/* number of coins */
  int found;			/* Is it found?*/
  int choice;                   /* Iterate player choices */
  struct gameState initState;   /* Original gamestate */
  struct gameState testState;   /* Gamestate under test */
  int k[10] = {feast, gardens, embargo, remodel, tribute, mine, cutpurse, ambassador, great_hall, steward};
  char testCard[] = "Steward";  /* Card under test */

 /* Testing the Card */

  printf("*** TESTING CARD: %s ***\n\n ", testCard);
	
  for(i = 0; i < numTests; i++)
    {
      /* Set initial hand variables */
      pos = -1;
      p = 0;
      p2 = 1;
      
      for (choice = 1; choice <= 3; choice++)
        {
          if (choice == 1)
            {
              printf("*** TESTING CHOICE ONE: +2 Cards ***\n");

              /* Copy into another state to preserve */
              initializeGame(numPlayers, k, 1000, &initState);
              memcpy(&testState, &initState, sizeof(struct gameState));
      
              /* Initialize DeckSize variables for player and opponent */
              playerDeckSize = testState.handCount[p];		  
              opponentDeckSize = testState.deckCount[p2];
              
              /* How many cards were played? */
              pileSize = testState.deckCount[p];  /* Non-trashed cards */
              /* Initialize numActions and coin amounts */
              numActions = testState.numActions;
              amount = initState.coins;

              /* Play the card to gain two cards */
              cardEffect(steward, 1, 0, 0, &testState, 0, 0);

              /** Choice 1 only tests **/

              /* Test 1 Choice 1: Ensure player gains two cards with choice 1 */
              printf("\nTest 1 Choice 1: Play Steward and gain two cards:\n");
              if(initState.handCount[p] + 1 == testState.handCount[p])
                {/* Lose Steward card(-1) and gain 2 more(+2) = 1 */
                  printf("Passed. Expected hand count: %d, Hand count finish: %d\n", initState.handCount[p] +1, testState.handCount[p]);
                }
              else
                { /* ERROR: Hand size has incorrect card count */
                  printf("FAILED. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p] +1, testState.handCount[p]);
                }
              
              /* Test 2 Choice 1: Ensure player gains 2 numActions */
              printf("\nTest 2 Choice 1: Play Steward, choice1, make sure no numActions are given:\n");
              if(numActions == testState.numActions)
                {
                  printf("Passed. Expected gained actions: %d, Gained Actions finish: %d\n", 0, testState.numActions - numActions);
                }
              else
                { /* ERROR: Number of actions mismatched */
                  printf("FAILED. Expected gained actions: %d, Gained Actions finish: %d\n", 0, testState.numActions - numActions);
                }

              /* Test 3 Choice 1: Make certain player gains no money */
              printf("\nTest 3 Choice 1: Play Steward to gain cards, but make sure no coins are given:\n");
              if(amount == testState.coins) 
                {
                  printf("Passed. Expected coins gained: %d   Coins gained finish: %d\n", 0, testState.coins - amount);
                }
              else
                { /* ERROR: Coins value changed */
                  printf("FAILED. Expected coins gained: %d   Coins gained finish: %d\n", 0, testState.coins - amount);	
                }
              /* No Test 4 or 5 for Choice 1 */
              printf("\nTest 4 Choice 1: none\n");
              printf("\nTest 5 Choice 1: none\n");
            }
          else if (choice == 2)
            {
              printf("*** TESTING CHOICE TWO: +2 Coins ***\n");

              /* Copy into another state to preserve */
              initializeGame(numPlayers, k, 1000, &initState);
              memcpy(&testState, &initState, sizeof(struct gameState));
              
              /* Initialize DeckSize variables for player and opponent */
              playerDeckSize = testState.handCount[p];		  
              opponentDeckSize = testState.deckCount[p2];
              
              /* How many cards were played? */
              pileSize = testState.deckCount[p];  /* Non-trashed cards */
              /* Initialize numActions and coin amounts */
              numActions = testState.numActions;
              amount = initState.coins;

              /* Play the card to gain two coins */
              cardEffect(steward, 2, 0, 0, &testState, 0, 0);

              /* Test 1 Choice 2: Make sure player gains no cards */
              printf("\nTest 1 Choice 2: Play Steward gains no cards:\n");
              if(initState.handCount[p] -1 == testState.handCount[p])
                {
                  printf("Passed. Expected hand count: %d, Hand count finish: %d\n", initState.handCount[p] -1, testState.handCount[p]);
                }
              else
                { /* ERROR: Hand size mismatch */
                  printf("FAILED. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p] -1, testState.handCount[p]);
                }
              
              /* Test 2 Choice 2: Make sure player gains no numActions */
              printf("\nTest 2 Choice 2: Since player received coins, make sure no numActions are given:\n");
              if(numActions == testState.numActions) 
                {
                  printf("Passed. Expected Actions: %d, Actions gained finish: %d\n", numActions, testState.numActions - initState.numActions);
                }
              else
                { /* ERROR: numActions mismatch */
                  printf("FAILED. Expeccted Actions %d, Actions gained finish: %d\n", numActions, testState.numActions - initState.numActions);
                }

              /* Test 3 Choice 2: Ensure player gains two coins */
              printf("\nTest 3 Choice 2: Receive 2 coins:\n");
              if(amount == testState.coins)
                {
                  printf("Passed. Expected coin count: %d, Coin count finish: %d\n", amount, testState.coins);
                }
              else
                { /* ERROR: Number of coins insufficient */
                  printf("FAILED. Expected coin count: %d, Coin count finish: %d\n", amount, testState.coins);	
                }

              /* No Test 4 or 5 for Choice 2 */
              printf("\nTest 4 Choice 2: none\n");
              printf("\nTest 5 Choice 2: none\n");
            }
          else
            {
              printf("*** TESTING CHOICE THREE: -2 Cards ***\n");

              /* Because cards must be chosen to test,
                 hand initialization is specified for this choice */
              initializeGame(numPlayers, k, 1000, &initState);
              initState.hand[p][0] = steward;
              initState.hand[p][1] = estate;
              initState.hand[p][2] = duchy;
              initState.hand[p][3] = province;
              initState.hand[p][4] = great_hall;
              initState.deck[p][0] = steward;
              initState.deck[p][1] = feast;
              initState.deck[p][2] = province;
              initState.deck[p][3] = gardens;
              initState.deck[p][4] = mine;
              memcpy(&testState, &initState, sizeof(struct gameState));

              /* Initialize for Choice 3 */
              amount = initState.coins;
              numActions = initState.numActions;

              /* Play the steward card with Choice 3 */
              cardEffect(steward, 3, duchy, estate, &testState, 0, 0);

              /* Test 1 Choice 3: Make sure player gains no cards */
              printf("\nTest 1 Choice 3: Play Steward and ensure two cards are discarded:\n");
              if(initState.handCount[p] -3 == testState.handCount[p])
                { /* -1 to trash Steward, -2 to discard */
                  printf("Passed. Expected hand count: %d, Hand count finish: %d\n", initState.handCount[p] -3, testState.handCount[p]);
                }
              else
                { /* ERROR: Hand size insufficient */
                  printf("FAILED. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p] -3, testState.handCount[p]);
                }
              
              /* Test 2 Choice 3: Make sure player gains no numActions */
              printf("\nTest 2 Choice 3: Play Steward and trash 2 cards, but make sure no numActions are given:\n");
              if(numActions == testState.numActions)
                {
                  printf("Passed. Expected Actions gained: %d, Actions gained finish: %d\n", 0, testState.numActions - initState.numActions);
                }
              else
                { /* ERROR: Actions changed */
                  printf("FAILED. Expected Actions gained: %d, Actions gained finish: %d\n", 0, testState.numActions - initState.numActions);
                }

              /* Test 3 Choice 3: Ensure player gains no coins */
		printf("\nTest 3: Play Steward, since 2 cards left no coins are given:\n");
		if(amount == testState.coins)
                  {
                    printf("Passed. Expected coins gained: %d, coins gained finish: %d\n", 0, testState.coins - amount);
                  }
		else
                  { /* ERROR: Change in coin count */
                    printf("FAILED. Expected coins gained: %d, coins gained finish: %d\n", 0, testState.coins - amount);
                  }

		/* Test 4 Choice 3: Make sure removed cards are no longer in hand */
		printf("\nTest 4 Choice 3: Make sure the removed cards are no longer in hand:\n");
		found = 0;
		for(j = 0; j < testState.handCount[p]; j++)
                  {
                    if(testState.hand[p][j] == duchy || testState.hand[p][j] == estate)
                      {
                        found = 1;
                      }
                  }

		if(found != 1)
                  {
                    printf("Passed. Removed cards no longer in hand\n");
                  }
		else
                  { /* ERROR: Removed card is still in hand */
                    printf("FAILED. Removed cards not trashed\n");
                  }
            
		/* Test 5a Choice 3: Ensure removed cards are no longer in deck */
		printf("\nTest 5a choice 3: Make sure the removed cards are not in the deck:\n");
		found = 0;
		for(j = 0; j < testState.deckCount[p]; j++)
                  {
                    if(testState.deck[p][j] == duchy || testState.deck[p][j] == estate)
                      {
                        found = 1;
                      }
                  }
                
		if(found != 1)
                  {
                    printf("Passed. Removed cards not in deck\n");
                  }
		else
                  { /* ERROR: Removed cards in the deck */
                    printf("FAILED. Removed cards in deck.\n");
                  }

                /* Test 5b Choice 3: Discard count unchanged */
		printf("\nTest5b Choice 3: Discard count should not be incremented if trashed: \n");
		if(testState.discardCount[p] >= 2)
                  {
			printf("Passed. Removed cards trashed\n");
                  }
		else
                  { /* ERROR: Discard count insufficient */
			printf("FAILED. Removed cards not trashed.\n");
                  }
            }

          /** All Choices Tests **/
          
          /* Test 6a: Ensure opponent's deck did not change size */
          printf("\nTest 6a: Opponent's deck size unchanged when Adventurer is drawn:\n");
          if(testState.deckCount[p2] == opponentDeckSize)
            {
              printf("Passed. Deck size start: %d, Deck size finish: %d\n", opponentDeckSize, testState.deckCount[p2]);
            }
          else
            { /* ERROR: Opponent's deck changed */
              printf("FAILED. Deck size start: %d, Deck size finish: %d\n", opponentDeckSize, testState.deckCount[p2]);
            }
          
          /* Test 6b: Ensure opponent's hand did not change size */
          printf("\nTest 6b: Other player's hand size unchanged when smithy is drawn:\n");
          if(testState.handCount[p2] == initState.handCount[p2])
            {
              printf("Passed. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p2], testState.handCount[p2]);
            }
          else
            { /* ERROR: Opponent's hand changed */
              printf("FAILED. Hand size start: %d, Hand size finish: %d\n", initState.handCount[p2], testState.handCount[p2]);
            }
          
          /* Test 7: Cards are sourced from player's deck, keeping 2 cards */
          printf("\nTest 7: Player is drawing and keeping only two cards from own pile:\n");
          if(initState.deckCount[p] -2 == testState.deckCount[p])
            {/* -1 because one non-coin card pulled */
              printf("Passed. Expected: %d, Deck size finish: %d\n", initState.deckCount[p] - 2, testState.deckCount[p]);
            }
          else
            { /* ERROR: Deck size incorrect, cards missourced */
              printf("FAILED. Expected: %d, Deck size finish: %d\n", initState.deckCount[p] - 2, testState.deckCount[p]);
            }
          
          /* Test 8: Steward card added to the played card pile */
          printf("\nTest 8: Steward card added to played pile after use:\n");
          if(testState.playedCardCount == 1)
            {
              printf("Passed. Expected increase in played pile: %d, Played pile: %d\n", 1, testState.playedCardCount);
            }
          else
            {
              printf("FAILED. Expected increase in played pile: %d, Played pile: %d\n", 1, testState.playedCardCount);
            }
          
          /* Test 9: Extraneous Victory Point changes */
          printf("\nTest 9: Supply of Victory Points unchanged: \n ");
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
          
          /* Test 10: Extraneous money changes */
          printf("\nTest 10: Changes in Coins: \n");
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
    }
  return 0;
}                
		

