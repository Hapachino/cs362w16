/*Chris Loomis
CS362 W16
Assignment 2
documentation.c

Both Smithy and Adventurer are Action cards and I will start from when the card is played using function playCard().  If this is not necessary for this assignment, please disregard and scroll down to the specifics of these cards.  playCard() takes the handposition, up to 3 choices, and the game itself as arguments.  It makes sure the game is in the correct phase, and that the player has an action to spend.  It then gets the card played using the first argument, and checks if it is an Action card.  It then calls function cardEffect(), which I will expand upon in a moment.  After returning from cardEffect() it decrements the number of Actions left and calls updateCoins(), which will be expounded on later.

cardEffect() is where the card's text is actually resolved.  It takes the arguments of the card played, up to 3 choices, the game, the handposition of the card, and a pointer to bonus.  First it sets up some variables to be used, though not all cards need all variables, before hitting the switch statement.  The switch has a case for each card.

Smithy:
The Smithy case enteres a for loop that will loop 3 times.  Each iteration of the loop calls drawCard().  After this is calls discardCard() on itself, discarding Smithy from the player's hand.

Adventurer:
The Adventurer case enters a while loop which continues until it gets the 2 treasures the care ensures.  Within the loop, first it checks if there are cards left in that player's deck, and if not it shuffles the deck.  Then it draws a card and places it in the hand, and assigns it to variable cardDrawn.  cardDrawn is used to check if it is treasure, and if so drawntreasure is incremented.  If it is not treasure it is added to a temphand, an array to hold the cards that will be discarded that utilizes variable z as it's counter.  The card is also removed from the player's hand, as they do not get to keep it.  This completes the while loop, which runs until both treasure cards are found.  At this point another while loop is entered, which goes through temphand adding those cards to the player's discard pile.  Of note, I have not found where the Adventurer card played is discarded.  I do not see it being moved to a position where it could be overwritten, or moved to temphand to be discarded.  I do not see anything to ensure it is properly discarded in playCard().  Most of the time this shouldn't be an issue, as each player gets 1 action, but if a player played Village prior to Adventurer I believe they could play the same Adventurer card twice.

discardCard():
discardCard takes hand position [of card to discard], currentPlayer, the game, and a trash flag as argument.  If the trash flag is not set, the card is added to the current player's discard pile and increment the count of the discard pile.  The played card in the player's hand is set to -1, thus removing it.  This would trash it if the trash flag had been set, as it would not of been added to the discard pile.  Then it tests if the discarded card came from the end of the hand array, if so it just needs to decrement the handCount.  Else, if the hand count is 1, it was the only card in the player's hand and the hand count is simple decremented.  Else, it takes the card from the end of that player's hand array and moves it to the position of the discarded card, writing over it.  The card at the end of the array, the one we just moved, is then set to -1.  Finally the hand count is decremented.

updateCoins():
updateCoins() takes the player, game, and an int bonus.  It starts be [re]setting the game coins to 0, so no one is getting extra coins left in memory from a previous player.  Then it enters a for loop that will loop through the player's hand adding up the treasure in the hand (1 for copper, 2 for silver, and 3 for gold).  It then adds the bonus (this is where Action cards like Woodcutter can add their bonus).

/*