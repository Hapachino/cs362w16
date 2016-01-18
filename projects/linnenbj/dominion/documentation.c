/*

CS362 - Winter 2016
Assignment 2:  Documentation.c
James Linnenburger


Smithy Card -
------------------------------------------------------------------------
The Smithy card is an action card that costs 4 coins. It allows the 
player to draw three additional cards into their hand.  Once the player 
plays the Smithy card, it is discarded from their hand to their played 
card pile.

(code explanation)
drawCard() is called 3 times for the current player to add the cards
discardCard() is called 


Adventurer Card -
------------------------------------------------------------------------
The Adventurer card is an action card that costs 6 coins.  It allows the 
player to draw two additional treasure cards into their hand.  When the 
card is played, it is discarded from their hand to their played card 
pile.

(code explanation)
1. Check if there is at least 1 card in the players deck
    -if not shuffle() is called on the player's deck.
2. drawcard() is called
3. check the drawn card for a treasure card
   -if so, add 1 to drawntreasure
   -if not, move the drawn card from player's hand to temp hand.
4. loop back to step 1 until drawntreasure is 2.
5. discard all non-treasure cards that were drawn


int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
---------------------------------------------------------------------------------------
This method will remove a specified card from the player's hand and add
it to their played card stack or puts it into the trash.

Parameters:
 - handPos:  This is an integer value that represents the position the card to be 
             discarded is currently stored in the player's hand.

 - currentPlayer: This is an integer value that represents the index of the player that 
                  is going to be discarding a card.

 - *state: This is a pointer to the current state of the game.
 
 - trashFlag: This is an integer that tells if the discarded card should go back to
	          the player's played card pile (any value < 1) or be trashed (any value >=1). 

Return:
  This method always returns 0.
			  
int updateCoins(int player, struct gameState *state, int bonus)
---------------------------------------------------------------------------------------
This method updates the gameState's coins value to include the value of all of the 
coins in the player's hand as well as any coins a player has earned as a bonus through
the action phase of their turn.

Parameters:
 - player: This is an integer value that represents the index of the player whose turn 
           it currently is.

 - *state: This is a pointer to the current state of the game.
 
 - bonus: This is an integer that represents the amount of bonus coins the player has
          earned during this turn.
		
Return:
  This method always returns 0.

*/
