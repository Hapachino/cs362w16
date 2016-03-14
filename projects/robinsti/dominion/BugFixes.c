/******************************************************************************
 ** Author: Tim Robinson
 ** 2/28/2016
 ** Bug Fixes
 ****
	
	Bug in Adventurer function
	--------------------------
	int playAdventurer(int currentPlayer, struct gameState * state, int drawntreasure, int temphand[], int cardDrawn) {
	  int z = 0;
	  while(drawntreasure<2) {
	    if (state->deckCount[currentPlayer] <1) {//if the deck is empty we need to shuffle discard and add to deck
	      shuffle(currentPlayer, state);
	    }
	    drawCard(currentPlayer, state);
	    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	    
	    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
	      drawntreasure++;
	    } else {
	      temphand[z]=cardDrawn;
	      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	      z++;
	    }
	  }

	  z--;
	  while(z-1>=0) {
	    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	    z=z-1;
	  }
	  
	  return 0;
	}


	The counter variable z, within the above adventurer function, is incorrectly 
	decremented. This causes the bug I introduced and reported by Will (thomasw).

	Removing the incorrect decrement line (z--) corrects this bug.

	Bug in in Smithy function
	-------------------------
	int playSmithy(int currentPlayer, struct gameState * state, int handPos) {
	  // +3 Cards
	  int i;
	  int j;

	  if (currentPlayer != 0) {
	    j = 4;
	  } else {
	    j = 3;
	  }

	  for (i = 0; i < j; i++)
	  {
	    drawCard(currentPlayer, state);
	  }
	      
	  //discard card from hand
	  discardCard(handPos, currentPlayer, state, 0);
	  return 0;
	}

	The bug in the Smithy function that I introduced, found by Isaiah (perrotti),
	is a bit more contrived than the other bugs. The obvious bug here is that
	when the currentPlayer variable is equal to 0 (player 1), then that player 
	draws 2 cards instead of 3.

	The counter variable j in the above function is assigned by a conditional
	statement dependent on the player.
	
	Removing the conditional statement governing the assignment of variable j
	fixes this bug.

	Change:

		if (currentPlayer != 0) {
	    j = 4;
	  } else {
	    j = 3;
	  }

	into, simply:

		j = 4;

	
	Bug in the Great Hall function
	------------------------------

	int playGreatHall(int currentPlayer, struct gameState * state, int handPos) {
	  //+1 Card
	  drawCard(currentPlayer, state);
	  
	  //+1 Actions
	  state->numActions++;
	  
	  //discard card from hand
	  currentPlayer = 1 - currentPlayer;
	  discardCard(handPos, currentPlayer, state, 0);
	  return 0;
	}

	The bug in this function can be seen in the line that effectively performs 
	a bit flip on the currentPlayer variable. The player should not be changing
	in this function, so removing that line fixes this bug.

	Bug in the Embargo function
	---------------------------
	int playEmbargo(int currentPlayer, struct gameState * state, int choice1, int handPos) {
	  //+2 Coins
	  int num_coins = 0;

	  int rand_select = handPos;
	  if (rand_select % 2 == 0) {
	    num_coins = 4;
	  } else {
	    num_coins = 2;
	  }

	  state->coins = state->coins + num_coins;
	  
	  //see if selected pile is in play
	  if ( state->supplyCount[choice1] == -1 )
	  {
	    return -1;
	  }
	  
	  //add embargo token to selected supply pile
	  state->embargoTokens[choice1]++;
	  
	  //trash card
	  discardCard(handPos, currentPlayer, state, 1);   

	  return 0;
	}

	The bug in this function causes a player to gain 4 additional coins if the
	hand position the Embargo card was played from was even.

	This bug can be fixed by replacing the num_coins variable assignment.

	Change:

	 	if (rand_select % 2 == 0) {
	    num_coins = 4;
	  } else {
	    num_coins = 2;
	  }

	Into:

		num_coins = 2;

	This fixes the bug.


	Additional Information
	----------------------
	The completed passed test cases can be found in unittestresults.out.

	The previous failed test output can now be found in bugs_unittestresults.out.

 *****************************************************************************/