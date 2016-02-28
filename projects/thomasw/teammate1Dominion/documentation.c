/****************************************************************************
* Author: Isaiah Perrotte-Fentress
* Class: CS362w16
* Assignment: Assignment2
* File: Documentation for smithy, adventurer, discardCard() and updateCoins()
*****************************************************************************

/*
Card: Smithy
Type: Action card that costs 4 coins. 
When played the player draws 3 cards from their deck. Card placed in discard 
pile after playing.

Card: Adventurer
Type: Action card that costs 6 coins. 
When played, draw cards until two treasures are draw. If the deck is empty, 
the discard pile should be shuffled. Non-treasure cards are stored in a 
temporary hand. Once two treasures are found, the temp hand is discarded.

Function: discardCard()
Inputs: index of discard card, player, game struct, and card trash flag
Output: int (for error reporting potentially)
If the card was not trashed (removed from the game) it is added to the played 
pile which is incremented to represent the new card. The card is then removed 
from the players hand (regardless of flag). If this was the last card in array, 
or the player only had 1 card, then decrement the count of cards in his hand. 
Otherwise, place the last card in the hand array to this location, remove the 
last card from its previous position, and decrement the count of cards in hand.

Function: updateCoins()
Inputs: player, game struct, bonus from action cards
Output: int (for error reporting potentially)
This function totals up all coins in a users hand. Reset players coins to zero.
Loop through hand looking for treasure, add respective treasure amounts. Add 
any bonus gold to the coins total, and store in the state struct. 