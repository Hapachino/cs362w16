/*
  Name: Thomas "Adam" Pippert
  Due Date: 14-February-2015
  File: randomtestadventurer.c
  Purpose: Random tester of adventurer card
*/

#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_TESTS 1000 /* max num tests I want to do, can change to increase/decrease as needed */

int main()
{

  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

  int i;
  int r = 0;
  int choice1 = 0, choice2 = 0, choice3 = 0;
  int numPlayers = 0, currentPlayer = 0;
  int handPos = 0, handCount = 0, deckCount = 0;
  int seed;
  
  struct gameState initState;
  
  srand(time(NULL));
  
  printf("** Testing adventurer.\n\n");
  
  for (i = 0; i < MAX_TESTS; i++) 
    {
      /* Give random values to cardEffect arguments */
      numPlayers = rand()%5; /* Gives max of 4 players per game instructions */
      if(numPlayers == 0 || numPlayers == 1)
        {
          numPlayers += 2; /* Need to have 2-4 players */
        }
      currentPlayer = rand()%numPlayers; 
      seed = rand();
      choice1 = rand()%2;
      choice2 = rand()%2;
      choice3 = rand()%2;
      handPos = rand()%4;
      
      initializeinitStateame(numPlayers, k, seed, &initState);	/* Initialize gamestate */
      
      /* Give random values to state variables */
      initState.deckCount[currentPlayer] = rand()%MAX_DECK; 
      initState.discardCount[currentPlayer] = rand()%MAX_DECK;
      initState.handCount[currentPlayer] = rand()%MAX_HAND;
      
      /* Save values to compare later */
      deckCount = initState.deckCount[currentPlayer];
      
      /* 1 in 3 chance of making empty deck, increase coverage as shown in class */
      if (seed%3 == 0)
        {
          initState.deckCount[currentPlayer] = 0;
        }
      
      /* Need to make sure there's at least 2 treasure cards in deck */
      int j;
      for (j = 0; j < initState.handCount[currentPlayer]; j++)
        {
          gainCard(copper, &initState, 2, currentPlayer);
        }
      
      r = cardEffect(adventurer, choice1, choice2, choice3, &initState, handPos, 0);
      
      int x, treasure = 0, zero = 0;
      for(x = 0; x < initState.handCount[currentPlayer]; x++)
        {
          if(initState.hand[currentPlayer][x] == copper || initState.hand[currentPlayer][x] == silver || initState.hand[currentPlayer][x] == gold)
            {
              treasure++;
            }
          else if(initState.hand[currentPlayer][x] == 0)
            {
              zero++;
            }/* to account for new hand */
        }
      
      /* Make sure cardEffect returned correctly */
      assert(r == 0);	
      
      /* If treasure not increased by at least two, adventurer didn't do its job */
      if(treasure < 2 && zero != initState.handCount[currentPlayer] && initState.handCount[currentPlayer] != 0) 
        {
          printf("\tTest failed: treasure count (i = %d)\n", i);
          printf("\t\tinitState.handCount = %d\ttreasure = %d\n", initState.handCount[currentPlayer], treasure);
          for(x = 0; x < initState.handCount[currentPlayer]; x++)
            {
              printf("\tinitState.hand[currentPlayer][x] = %d\n", initState.hand[currentPlayer][x]);
            }
          printf("\n");
          
        }
      /* If handCount is negative, something went wrong */
      if(initState.handCount[currentPlayer] < 0) 
        {
          printf("\tTest failed: hand count (i = %d)\n", i);
          printf("\t\tinitState.handCount = %d\t handCount = %d\n\n", initState.handCount[currentPlayer], handCount);
        }
      
      if(deckCount < initState.deckCount[currentPlayer]+2 && deckCount != initState.deckCount[currentPlayer] && initState.deckCount[currentPlayer] != 0)
        {
          printf("\tTest failed: deck count (i = %d)\n", i);
          printf("\t\tinitState.deckCount = %d\t deckCount = %d\n\n", initState.deckCount[currentPlayer], deckCount);
        }
      
    }
  
  printf("** Test complete.\n");
  
  return 0;
}
