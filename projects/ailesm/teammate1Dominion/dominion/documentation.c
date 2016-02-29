Michael Byrne
Assignment 2 Part 2 
CS 362 

Card documentation: 

Smithy: 
	Draws 3 cards from top of player deck (drawCard())
	Removes itself from player hand to discard pile (discardCard())
	Returns 0 on success

Adventurer:
	Draws cards from player deck in a loop (drawCard()) until two treasure cards have been revealed
	Shuffle cards with shuffle() if required, excepting currently revealed cards
	If there are no more cards, player receives only 1 or 0 treasures
	Discard all non-treasure cards (discardCard())
	Return 0 on success

Function documentation:

discardCard():
	Tests variable trashFlag to see if card is to be returned to deck or if it is to be removed from game. 
	Then, if the last card in a the player's hand has been played, then the number of cards in the hand is decremented. 
	Then, otherwise, the discarded card is replaced by the last card in the player's hand. 
	The last card in the player's hand is set to -1.
	The gameState's hand count is decremented.
	Returns 0

updateCoins()
	First, resets coin count to zero.
	Then, loops through player's hand, incrementing the coin counter by the appropriate amount when a treasure card is hit.
	Then, adds bonus coin value if needed. 
	Returns 0