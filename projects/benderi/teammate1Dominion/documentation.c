/*****************************************************************************
*	David Vogel
*	CS362 Assignment 2: documentation.c
*	Due: 1/17/16
*	Assignment Requirements:
*		Submit a file called documentation.c that contains documentation of smithy, 
*		adventurer cards. 
*			- Documentation should contain your understanding of smithy and 
*				adventurer cards (code). 
*			- It should also contain documentation of your understanding of 
*				discardCard() and updateCoins() method.
*****************************************************************************/

Smithy Card:
	Smithy is an action card that is called in the switch statement of the cardEffect() method.
	This card gives	the player 3 cards by calling the drawCard() method 3 times in a for loop. 
	The Smithy card is then discarded using the discardCard() method.

Adventurer Card:
	The Adventurer card is also an action card that is called in the switch statement 
	of the cardEffect() method. 
	The effect of the card is to keep drawing cards until 2 treasure cards are obtained. 
	If the deck becomes empty before 2 treasure cards are found, the discard pile is 
	shuffled and added to the deck. The cards that are not treasure cards are added to
	the discard pile.

discardCard() method:
	This method is used to remove a card from the player's hand.
	It first checks to see if the card is flagged to be trashed. 
	If it is not flagged, it is added to the played pile and playedCardCount is incremented.
	If it is flagged, it is not added.
	If the card is not the last in the hand, it will replace it with the last in the hand.
	
updateCoins() method:
	This method calculates the number of coins the player will be able to use in the buy phase.
	First, the number is reset to 0. The method then enters a for loop to check if any of the
	cards in the player's hand are Treasure cards and increments the coins value accordingly.
	Finally, if a bonus value is present, it is added to the amount of coins.