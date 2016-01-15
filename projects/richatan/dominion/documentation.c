Tanna Richardson
CS362 - Winter 2016
Assignment #2: Dominion Documentation


---- Smithy Card ----
The Smithy is an action card that allows the user to draw three additional cards.

When a user plays the Smithy card, the code calls the drawCard() method three times
to add three cards to the user's current hand. The code then calls the discardCard() 
method to remove the Smithy card from the user's hand and add it to the played 
pile (trashFlag parameter = 0).


---- Adventurer Card ----
The Adventurer is an action card that allows the user to take two treasure cards
from their deck and add the cards to their current hand.

When a user plays the Adventurer card, the code completes the following actions
in a loop until two treasure cards have been found:
1. If user's deck is empty, call shuffle() method.
2. Call drawCard() method to add one card to user's hand.
3. If card is treasure (copper, silver, or gold), increment treasure count (loop control)
4. If card is not treasure, remove card from hand and add to temp hand

When the loop completes and two treasure cards have been added to the user's hand, the 
code then cleans up by adding the temp hand to the discard pile.


---- discardCard() Method ----
The discardCard() method removes a specified card from the player's hand and adds
it to the played pile or trashes it.

Parameters:
handPos (int): index of card to be discarded (position in hand)
currentPlayer (int): index of current player
*state (struct gameState): pointer to current gameState
trashFlag (int): flag indicating where discarded card should be moved
                 0 = played pile
				 1 = trash (no location)

Returns:
int: 0 = success
Changes to gameState:
  playedCards: discarded card added at last index (if trashFlag = 0)
  playedCardCount: incremented by 1 (if trashFlag = 0)
  hand: changes discarded card value to -1 (at [player index][card position index])
        swaps positions of last card in hand with discarded card (if handCount > 1)
  handCount: reduced by 1



---- updateCoins() Method ----
The updateCoins() method updates the coins variable in gameState with
the total coin count for the current player's turn. The count includes
coins from Treasure cards in the player's hand as well as bonus coins
earned during the Action phase.

Parameters:
player (int): index of player
*state (struct gameState): pointer to current gameState
bonus (int): extra coins to be added to player's hand

Returns:
int: 0 = success
Changes to gameState:
  coins: set to value of Treasure cards in player's hand + bonus
