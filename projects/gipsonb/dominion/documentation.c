Smithy: 	The smithy code is pretty basic. First there is a for loop that cycles through the drawCard function for the current player three times. 
			This gives the player three cards which is what the Smithy card is supposed to do. Second it discards itself using the discardCard function.
			This is because the card is used up when played.
		
Adventurer: The adventure card exists inside a while loop that runs until two treasures have been drawn. The first if statement checks to see if the
			deck is empty and, in finding that it is, it shuffles the deck. After this a card is drawn and compared to the different types of treasures.
			If the card drawn is a treasure then the treasure is incremented. Following that the code creates a temporary hand to hold all cards drawn
			in this manner and removes the drawn card from the player's actual hand. The last while loop runs clean up. This continues until two treasures
			are drawn.
			
discardCard: The first part of the discardCard function checks to see if the card is trashed or not. If it isn't trashed it is added to the played pile.
			 The next part of the function removes the card from the players hand. It does this by reducing the player hand size if the last card in the
			 player's hand array was played. If this wasn't the case then the function shuffles the card played to the last card in the player's hand array
			 before reducing the hand count.
			 		
updateCoins: Each turn the player starts with zero coins and that is exactly how this function starts. The next part of the code is a for loop that loops
			 through the player's hand size looking for the different types of treasures. If it finds a copper it increases the player's coins by 1; If a silver
			 then 2 and if a gold 3. The function ends with adding any bonus coins earned through action cards to the coin count.

