/* 
  Name: Thomas "Adam" Pippert
  Due Date: 14-February-2015
  File: randomtestcard.c
  Purpose: Randomtester for card of my choice - Great Hall
*/


#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_TESTS 1000

int main()
{

  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

  int i;
  int r = 0;
  int choice1 = 0, choice2 = 0, choice3 = 0;
  int numPlayers = 0, currentPlayer = 0;
  int handPos = 0, discardCount = 0, numActions = 0;
  int counter = 0;
  int seed;

  srand(time(NULL));
  
  printf("*** Testing /* The Great Hall card (great_hall).\n\n");

  for (i = 0; i < MAX_TESTS; i++) 
    {
      struct gameState * initState = newGame();
      
      /* Give random values to cardEffect arguments */
      numPlayers = rand()%5; /* Gives max of 4 players per game instructions */
      if(numPlayers == 0 || numPlayers == 1)
        {
          numPlayers += 2; /* need to have 2-4 players */
        }
      currentPlayer = 0;
      seed = rand();
      choice1 = rand()%2;
      choice2 = rand()%2;
      choice3 = rand()%2;
      handPos = rand()%4;
      
      initializeGame(numPlayers, k, seed, initState);	/* initialize Gamestate */
      
      /* Give random values to state variables */
      initState->deckCount[currentPlayer] = rand()%MAX_DECK; 
      initState->discardCount[currentPlayer] = rand()%MAX_DECK;
      initState->handCount[currentPlayer] = rand()%MAX_HAND;
      
      /* 1 in 2 chance of making empty deck, increase coverage as shown in class */
      if (seed%2 == 0)
        {
          initState->deckCount[currentPlayer] = 0;
        }
      
      /* Save some values for comparing later */
      discardCount = initState->discardCount[currentPlayer]; /* should increase by 1 */
      numActions = initState->numActions; /* should increase by 1 */
      
      r = cardEffect(great_hall, choice1, choice2, choice3, G, handPos, 0);
      
      /* Make sure cardEffect returned correctly */
      assert(r == 0);	
      
      
      if(discardCount != initState->discardCount[currentPlayer]-1 && initState->discardCount[currentPlayer] !=1) 
        {
          counter++;
          printf("discard count = %d\t\tinitState->discardCount = %d\n", discardCount, initState->discardCount[currentPlayer]);
        }
      if(numActions != initState->numActions-1)
        {
          printf("\tTest failed: num actions (i = %d)\n", i);
          printf("\t\tinitState->numActions = %d\t numActions = %d\n\n", initState->numActions, numActions);
        }
      free(initState);
      
    }
  printf("*** Test complete.\n");
  
  return 0;
}
