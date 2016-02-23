Smithy

This card allows the player to draw three cards from their deck.  It performs this action by running the drawCard() function 3 times inside a loop.


Adventurer

This card will draw cards from the players deck until 2 treasure cards are found, these are put into the players hand and the remaining revealed cards discarded. This performs its action by creating a while loop that will track the number of drawn treasures performing the drawcard() function until the treasure count has reached 2.  The other cards are placed into a tempHand array that will then all be discarded once the 2 treasures are found.


discardCard()

This is a function that takes 4 arguments: handPos, currentPlayer, gameState, and trashFlag. First if the trash flag is not set ( >1 ), the card is added to the played pile. Next it will removed the card from the players hand, reducing the number of cards in the players hand count by 1.


updateCoins()

This function updates the coin count for the number of availble coins for a player.  It has 3 arguments player, gameState, and bonus.  First it resets the coin count back to 0, then adds coins for each treasure card in the players hand, 1 for copper, 2 for silver, 3 for gold. It will then add any bonus that was passed into the function.
