/*************************************************
 * 
 * Todd Waddell
 * CS362W16
 * Assignment #2
 *
 * 3- (60 points) Pick five cards implemented in dominion.c. Choose 3 cards
 * of your choice and smithy and adventurer cards are mandatory. Refactor
 * the code so that these cards are implemented in their own functions,
 * rather than as part of the switch statement in cardEffect. You should
 * call the functions for these cards in the appropriate place in
 * cardEffect. Check in your changes, with appropriate git commit messages.
 * Document your changes in a text file in your dominion source directory,
 * called “refactor.c.” Your implementation of at least 4 of these 5 cards
 * should be incorrect in some way, i.e., you should introduce subtle bugs
 * that are hard to catch in your changes. Introducing bugs in smithy and
 * adventurer is mandatory.  Write information of your bugs also in
 * refactor.c  Later in this class, other students will test your code, so
 * try to keep your bugs not superficial. Refactored program should compile
 * without any error.
 * **********************************************/
//car effect takes the following elements
//int cardeffect(int card, int choice1, int choice2, int choice3, struct gamestate *state, int handpos, int *bonus)
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*******************************
 * Refactored:
 *  1) Combined while loop [for card discard] into else branch
 *  2) In first while loop, added check to ensure not an endless loop 
 *  in cases where the player has less than 2 coins in their deck.
 *
 *  *****************************/
int adventureEffect(struct gameState *state)
{

    int currentPlayer = whoseTurn(state);
    int drawntreasure = 0;
    int cardDrawn =  0;
    int z = 0;
    int temphand[MAX_HAND];
    while(drawntreasure<=2){
	    if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	        shuffle(currentPlayer, state);
	    }
	    drawCard(currentPlayer, state);
	    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	        drawntreasure++;
	    else{
            state->discard[currentPlayer][state->discardCount[currentPlayer]++] = cardDrawn;
	        state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	    }
      }
      
    return 0;
}	


int smithyEffect(struct gameState *state, int handPos)
{  
    int currentPlayer = whoseTurn(state);
    //+3 Cards

      for (int i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
      //discard card from hand
      discardCard(handPos, currentPlayer, state, 1);
      return 0;
}		
	
int feastEffect(int choice1, struct gameState *state)
{
    int temphand[MAX_HAND];
    int currentPlayer = whoseTurn(state);
    int x = 0;
      //gain card with cost up to 5
      //Backup hand
      for (int i = 0; i <= state->handCount[currentPlayer]; i++){
    	temphand[i] = state->hand[currentPlayer][i];//Backup card
	    state->hand[currentPlayer][i] = -1;//Set to nothing
      }
      //Backup hand

      //Update Coins for Buy
      updateCoins(currentPlayer, state, 4);
      x = 1;//Condition to loop on
      while( x == 1) 
      {//Buy one card
    	if (supplyCount(choice1, state) <= 0){
	      if (DEBUG)
	        printf("None of that card left, sorry!\n");

	      if (DEBUG){
	        printf("Cards Left: %d\n", supplyCount(choice1, state));
	        }
        }
        else if (state->coins < getCost(choice1)){
          printf("That card is too expensive!\n");

          if (DEBUG){
            printf("Coins: %d < %d\n", state->coins, getCost(choice1));
            }
            }
          else{

            if (DEBUG){
                printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
            }

            gainCard(choice1, state, 0, currentPlayer);//Gain the card
            x = 0;//No more buying cards

            if (DEBUG){
                printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
            }

        }
      }     

      //Reset Hand
      for (int i = 0; i <= state->handCount[currentPlayer]; i++)
      {
	    state->hand[currentPlayer][i] = temphand[i];
	    temphand[i] = -1;
      }
      //Reset Hand
      			
      return 0;
}
int mineEffect(int choice1, int choice2, struct gameState *state, int handPos)
{
    int j = 0;
    int currentPlayer = whoseTurn(state);
     j = state->hand[currentPlayer][choice1];  //store card we will trash

      if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
	{
	  return -1;
	}
		
      if (choice2 > treasure_map || choice2 < curse)
	{
	  return -1;
	}

      if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
	{
	  return -1;
	}

      gainCard(choice2, state, 2, currentPlayer);

      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);

      //discard trashed card
      for (int i = 0; i < state->handCount[currentPlayer]; i++)
	{
	  if (state->hand[currentPlayer][i] == j)
	    {
	      discardCard(i, currentPlayer, state, 0);			
	      break;
	    }
	}
	
    return 0;
}
int cutpurseEffect(struct gameState *state, int handPos)
{

    int currentPlayer = whoseTurn(state);
    int i = 0;
    int j = 0;
    int k = 0;

      updateCoins(currentPlayer, state, 2);
      for (i = 0; i < state->numPlayers; i++)
	{
	  if (i != currentPlayer)
	    {
	      for (j = 0; j < state->handCount[i]; j++)
		{
		  if (state->hand[i][j] == gold)
		    {
		      discardCard(j, i, state, 0);
		      break;
		    }
		  if (j == state->handCount[i])
		    {
		      for (k = 0; k < state->handCount[i]; k++)
			{
			  if (DEBUG)
			    printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
			}	
		      break;
		    }		
		}
					
	    }
				
	}				

      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);			

      return 0;




}


