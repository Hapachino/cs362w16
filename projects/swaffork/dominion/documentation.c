adventurer:
The adventurer card allows the player to continue drawing cards until three
treasure cards are drawn. All cards drawn that are not treasure cards are
discarded. This is done by creating a temporary hand to hold all drawn cards
which are not treasure cards, then discarding this whole hand after three 
treasure cards have been drawn.

/*****************************************************************************/

smithy:
The smithy card gives the player three additional cards and is then discarded.
This is done by calling the drawCard() function three times and then calling
the discardCard() function so that the smithy card is moved into the discard
pile, where it will be available for use again once the discard pile has been
shuffled.

/*****************************************************************************/

discardCard():
The discardCard() function takes in the current card in the player's hand
(represented by handPos), the current player, the state of the game, and a
trash flag. The trash flash indicates whether the card in handPos is to be
trashed (meanining it is permanently removed from this game) or only discarded.

The effect of this function is to move the last card in the player's hand into
handPos and to decrement the total number of cards in the player's hand.

/*****************************************************************************/

updateCoins():
The updateCoins() function takes in the state of the game, the current player,
and coin bonuses given by cards like feast and cutpurse. The function tallies
the treasure in the player's hands (where copper = 1 coin, silver = 2 coins,
and gold = 3 coins) and adds in the additional coin bonus if it exists.
