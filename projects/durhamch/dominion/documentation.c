////Smithy Card:
The smithy card is called by a switch statement. It first calls the drawCard method 3 times 
putting 3 additional cards in the current player's hand.

The switch statement then calls discardCard passing the current card which discards the 
smithy card in the played pile.

The switch statement then exits.

////Adventurer Card:
The adventurer card is called by a switch statement. It first uses a while statement that
runs while the number of drawn treasure cards is less than 2. 

Reveals card from deck until 2 treasure cards are revealed.

First is makes sure that the remaining deck has more than 0 cards and shuffles it if it is.
The top card is then drawn. If the card is copper/silver/gold it increases drawntreasure
variable. Otherwise the card is put in the temp card hand and the counter for temp hand
is incremented.

Once 2 treasure cards are drawn a while statement is used and while the temp hand counter is
greater than 0 the cards in the temp hand are discarded and the counter for the temp hand
decremented.

The switch statement then exits.

////discardCard() Method:
Accepts 4 arguments. handPos, currentPlayer, state, trashFlag.

First checks if the card has been set to be trashed using the trashFlag argument. If it has
the card is moved to the played pile and the playedcardcount is incremented.

If the last card in the hand is played the cards in the hand are reduced by one. If there
is only one card in the hand the same is done. Otherwise the discarded card is replaced
by the last card in the hand and the number of cards in the hand are reduced by one.

The method then exits.

////updateCoins() Method:
Accepts 3 arguments: player, state, bonus.

First resets the coins to 0. Then for each coin in the player's hand it checks if the
cards are copper/silver/gold and increases the total number of coins. Afterwords it checks
the bonus amount and adds that to the total amount of coins as well.

THe method then exits.
