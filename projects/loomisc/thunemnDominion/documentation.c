Nathan Thunem
CS362 Winter 2016 - Assignment 2

Smithy Card:
The Smithy card can be bought by the player for 4 coins, and if 
the player has less than 2 Smithy cards already.  The Smithy card
uses the drawCard function to add 3 cards into the players 
hand, then calls the discardCard function to discard the Smithy Card.

Adventurer Card: 
The Adventurer card can be bought by the player for 6 coins.  This
card allows cards to be drawn until the player gets 2 treasure
cards.  The discardCard function is called for every card that is 
not a treasure card. 

discardCard function:
The discardCard function takes parameters: handPos (hand position),
currentPlayer (current player), state (game state), and an int 
(trash flag).  If the trash flag is set to 0, the card will be played,
otherwise it will be trashed.  It will check if the card was played
or discarded, and will update the hand count and number of cards in the
player's hand.

updateCoins function:

The updateCoins function takes parameters: currentPlayer (current player),
state (game state), and an int (trash flag).  The function will reset the 
coin count and then add up the treasure cards in the hand and update 
the coin count again.