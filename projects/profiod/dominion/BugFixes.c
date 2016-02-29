Bug 1: 
	Fixed the for loop for drawing cards in smithyFunc. Previously it was set to draw two cards. It has been fixed to draw three cards by increasing the loop control to be less than 3 instead of less than 2. Found by Chris Loomis

Bug 2: 
	Fixed the bug in adventurerFunc where the user draws three treasure cards instead of 2. This was fixed by changing the while condition to be < 2 instead of < 3. I also added the check to see if the drawn card is gold when checking to see if the drawn treasure count should be increased. Found by Chris Loomis 

Bug 3: 
	Fixed the bug in councilRoomFunc where the number of buys was decremented instead of incremented. It has been fixed to increment the card by changing from a decrement operator to an increment operator. Found by Nathan Thunem. 

Bug 4: 
	Fixed the bug in councilRoomFunc where the current player draws 5 cards instead of four. This bug was fixed by adding a check to see if the player is the current player when the function is passing out cards to all players in the game. Found by Nathan Thunem 

Bug 5: 
	Fixed the bug in remodelFunc where it trashed the wrong card. This bug was fixed by changing the does not equal comparison to an is equal comparison in the check to see if the card is the card that was selected for trash. 