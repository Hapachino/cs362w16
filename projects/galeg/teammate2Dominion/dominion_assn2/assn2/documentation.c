smithy:
	Smithy is a fairly simple card.  It lets you draw 3 cards.
	The code is very simple.
	It uses a for loop to call the drawCard method three times.  

adventurer:
	The adventurer card behavior is to keep drawing cards until two of them are treasure cards.
	Then it will put the treasure cards into the hand and discard the rest.
	The code sets a drawnTreasure count and sets a while loop to continue as long as the 
		drawnTreasure count is less than 2.
		It first checks if the deck count is less than 1 and calls the shuffle function in that case.
			That stops any unnecessary calls to an empty stack.
		Then is draws  a card and checks if the card matches to the copper, silver, or gold card types.
		If it does it increments drawntreasure.  Else it adds the drawn card to a temphand array.
		the contents of the temp hand array is discarded via another while loop at the end of 
		the adventurer function.