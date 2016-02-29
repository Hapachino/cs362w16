/*Kim McLeod
documentation.c
Assignment 2
CS 362




Smithy: The Smithy card is an "action" card. When a player chooses to play the Smithy card, they get three cards from their deck.
The Smithy card moves to be discarded and the player continues her turn (depending on # of actions available).

Smithy card is implemented with cardEffect()
	
	loops 3 times with drawCard()
	calls discardCard() on the Smithy card







Adventurer: The Adventurer card is an "action" card. This card allows the player to draw cards from her deck until two Treasure cards (Copper, Silver, or Gold) are revealed. The player gets to add the Treasure cards to her hand, and discards any other cards drawn with the Adventurer card.

Adventurer card is implemented with cardEffect()
	
	if deck is > 0, shuffle and enter loop
		loops with drawCard() until 2 treasure cards are found
		exits loop when 2 treasure cards are found or end of deck is reached
	
	calls discardCard() on the Adventurer card
	






discardCard(): This method makes sure the card can be played and calls cardEffect on the card.

Takes four inputs: a pointer to the gameState variable to make sure the game hasn't ended.
		   an int to indicate the position of the hand of the card to return
		   an int indicating which player's turn it is
		   an int indicating whether or not the card should be sent to the trash pile

At the end of the turn, discardCard() checks the trashFlag and determines which pile to send the used card to.







updateCoins(): This method adds number of coins in players hand. 1 coin for copper, 2 for silver, and 3 for gold, plus any bonus coins earned from non-Treasure cards.
This number is used when the player buys other cards.

Takes 3 inputs: a pointer to the gameState variable to make sure the game hasn't ended.
		an int to indicate which player's turn it is
		an int to indicate how many bonus coins are to be added

*/
