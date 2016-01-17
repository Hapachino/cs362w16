/********************************************************************************************************************************************************
*** Filename: documentation.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/15/2015
*** Due date: 1/17/2015
*** Assignment 2 
*** Description:  Documentation should contain your understanding of smithy and adventurer cards (code).
***               It should also contain documentation of your understanding of discardCard() and updateCoins() methods.  
***
********************************************************************************************************************************************************


Smithy:
An action card that is called in the switch function cardEffect() that will add 3 cards from the player's deck to the player's hand. 
This is done by calling drawcard() 3 times then calls the discardCard() to discards the Smithy card from the hand. 
If the player's deck is empty before drawCard() is called, the discarded pile of cards is shuffled into the deck. 


Adventurer:
An action card that will keep drawing cards from the player's deck until two treasure cards have been drawn. 
Untill two treasure cards have been added to the hand, it will perform the following in a loop. 
It will check if the player's deck is empty or not. If it is, it will shuffle in the cards from the discarded pile.
It will then call drawCard(). The two treasure cards are added to the player's hand while all other cards drawn are kept in a temphand array then discarded. 


discardCard():
This method will discard a played card from the player's hand. It will add the card to the played deck array if it has not been flagged to be trashed. It also updates the
playedCardCount variable of the struct gameState *state. It will then reduce the number of cards in the player's hand by 1 and replace it with the last card in hand if it was not the only card left. 


updateCoins():
This method will calculate how many coins the player will have to spend during the buy phase. First, the coin count is reset to 0. The method iterates through every card currently in the player's hand to check if it is a treasure card.
If the card is a copper, silver, or gold treasure card, the coin count is updated. Copper is worth 1, silver is worth 2, and gold is worth 3. Finally, it adds the integer variable bonus to the coin count that is passed to the method
as a parameter. 

*/




