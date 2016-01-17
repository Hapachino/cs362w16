CS 362 - Software Engineering II
Assignment 2 - Documentation
Mark Giles

Smithy Card
	Summmary:
	- The Smithy card is an Action card
	- Allows the player to draw three additional cards for use. 
	- The cost of purchasing Smithy is 4 coins.
	- The effect code for Smithy is activated in the cardEffect function.

	Pseudo Code:
	for loop iterates three times
		 execute drawCard function
	discardCard function is called effectively discarding the Smithy card

Aventurer Card
	Summary: 
	- The Adventurer card is an Action card
	- Allows the player to draw cards from the deck until 2	Treasure cards are revealed.
	- The Treasure cards are placed in the hand.
	- The non-treasure cards drawn during the process are discarded.

	Pseudo Code:
	while drawnTreasure is < 2
		if the current player's deck is empty
			shuffle function which will refill the player's deck
		drawCard function adds a card from the player's deck to the player's hand
		set cardDrawn variable to card on top of hand (most recent card)
		if cardDrawn is Treasure card
			add 1 to drawnTreasure variable
		else
			remove the drawnCard from the player's hand and place it on the temp pile
	while z-1>=0 // while there are still cards on the temp deck
		discard the top card from temp deck

discardCard() Method
	Description: Removes the card from the player's hand. If the card is the only card in the deck,
		the count of the player's hand is decremented by one. If the card is the top card in the
		player's hand, the card count is decremented by one. Otherwise, the top card is assigned
		to the position of the discarded card and the card count is decremented by one.
	Input:
		- int handPos
		- int currentPlayer
		- struct gameState *state
		- int trashFlag
	Return:
		Returns 0 once tasks are completed
		
updateCoins() Method
	Description: Adds coins for the value of each Treasure card in the player's hand as well as
		and coins obtained through a bonus.
	Input:
		- int player
		- struct gameState *state
		- int bonus
	Return:
		Returns 0 once tasks are completed