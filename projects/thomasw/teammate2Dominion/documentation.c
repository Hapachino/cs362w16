/******************************************************************************
 ** Author: Tim Robinson
 ** 1/17/2016
 ****
	
	Understanding of the smithy card

	The smithy card causes the current player to draw three cards from their
	deck. The smithy card is played from the cardEffect() function, which is 
	used to process a current player's turn.


	Understanding of the adventurer card

	The adventurer card causes the player to continually draw cards until that
	player has drawn two treasure cards. The adventurer card may cause a deck to
	be shuffled if the current player runs out of cards in their deck, at which
	point they continue to draw until the two treasure cards are drawn.

	The adventurer card causes a temporary hand to be drawn, which is built from
	the drawn cards until two treasure cards have been drawn. If the temporary 
	hand has more than two treasure cards, then all of the cards that have been
	drawn that are not treasure cards are discarded back into the current 
	player's deck.


	Understanding of discardCard()
	
	Description: This function removes the card from the player's hand at the
		position provided by "handPos". This card is put back into the deck if the
		provided flag is set to zero. If the flag is set to any other integer, the
		card is taken out of play and put into the trash. This function is called 
		in the cardEffect() function, meaning that this function is called when a 
		card is played or if a card requires that a card
	is discarded.
	Parameters: int handPos, int currentPlayer, struct gameState * state, 
		int trashFlag
	Preconditions: A valid hand position must be provided. A valid gameState must
		be initialized.
	Postconditions: When this function terminates, the card at hand position
		handPos is taken out of the provided currentPlayer's hand and put into
		their deck. If the trashFlag is set, the card is removed from play and is
		in the trash.


	Understanding of updateCoins()

	Description: This function updates the gameState object that is passed in as 
		a pointer to reflect the number of coins the current player has available
		to play based on their current hand's treasure cards and any card effect
		bonus that has effected the current player. This function is called to 
		initialize gameplay, when an action card is played, and at the end of a 
		turn. An action card (through the cardEffect() function) may trigger a draw
		of cards (which may include additional treasure cards) or may trigger a 
		number of bonus coins to be added to the gameState's number of coins.
			This function counts all of the treasure cards in the current player's 
		hand by matching the card to either copper, silver, or gold. The gameState 
		is updated with the number of available coins available, where copper 
		increases the number of coins by 1, silver by 2, and gold by 3.
	copper increases the number of coins by 1, silver by 2, and gold by 3.

	Parameters: int player, struct gameState *, int bonus
	Preconditions: A valid player must be defined by an integer (0 indexed), and 
		a valid gameState must be defined.
	Postconditions: The gameState object is reset and updated to reflect the
		number of treasure cards in the current player's hand plus any cardEffect
		causing a bonus number of coins.


 *****************************************************************************/