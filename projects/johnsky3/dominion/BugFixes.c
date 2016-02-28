/*
Kyle Johnson
johnsky3
CS362
Assignment 5
2.28.16

Bug Fixes
*****************************************************************************************
Bugs Found by Teammates
*****************************************************************************************

Bug 1:
Function: smithy
	Description: Two tests revealed an error with smithy function. The test are cardtest1 and 
	randomtestcard. 
	The handcount of the current player is incorrect and another players status is effected
	
	cardtest1: 
		expected: hand to increase by 2 after 3 cards are added and one is discarded.
		actual : the hand count remained the same( 5 before and 5 after)
	randomtestcard:
		expected: current players hand to increase by 2 and other players hand to not be effected
		actual: the players hands not increased by the correct amount the hand count is too low
		          the other players status has been effected.	

I fixed this bug by changing the player who receives the cards from currentPlayer + 1 to currentPlayer:
*/
for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
/*
This also resolved the state change for the next player, who no longer receives cards instead of
the current player:

 Player 2 Errors (state change)
  - handcount mismatch - expected 0 actual 3
  - deckcount mismatch - expected 10 actual 7


Bug 2:
 **Test adventurerCard **
  Player 1 Errors
  - discard count mismatch - Expected 0 (stached deck) - actual 1
  
  I fixed the bug with the stashed deck by initializing the temp hand counter to 0 instead of 1. 
  The temp hand is used to discard the appropriate number of cards, so fixing the loop initializer 
  no longer gave a leftover stashed card in the temp deck:
  */
  int z = 0; //counter for temp hand
   while(z-1>=0){
	state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; 
	// discard all cards in play that have been drawn
	z=z-1;
      }
      return 0;
/*

Bug 3:
Function: village
	Description: an error was discovered with the village function actions were not added
	
	cardtest2:
		expected: 2 actions to be added
		actual: actions not added

I fixed this bug by changing the numActions from + 1 to + 2:
*/
 //+2 Actions
      state->numActions = state->numActions + 2;
/*
This allowed the card to add the expected two actions to the current player instead of just 1.

*****************************************************************************************
Other Bugs I Added
*****************************************************************************************

Bug 4:
Function: greatHallCard
	Description: calling greatHallCard flags the card for the trash pile when discarding

I fixed this bug by changing the trash flag parameter in the call to discardCard from 
1 to 0 so that the card is added to the played cards pile as expected:
*/
	  //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
/*


  