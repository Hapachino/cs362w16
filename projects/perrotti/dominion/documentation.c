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
Output: int
If the card was not trashed (removed from the game) it is added to the played 
pile which is incremented, and removed from the players hand. If the trash 
flag was set, the card is removed from the users hand, 



Function: updateCoins()
Inputs:
Output: