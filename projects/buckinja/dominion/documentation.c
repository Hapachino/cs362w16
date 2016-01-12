Janel Buckingham
CS 362 Winter 2016
Assignment 2


Within the cardEffect() function, there is a switch statement with a case for each effect card
that will cause certain changes to the state of the game.  The smithy card is the case that is triggered 
when the 'smithy' enum is passed into cardEffect() as the first parameter.  drawCard() is called 
three times with the current player and state as parameters.  This adds three new cards to the current 
player's hand which is stored in an array (with form 'hand[player][player's hand]') in the struct state parameter.

If the 'adventurer' enum is passed into cardEffect() instead, the function will be locating the top two
treasure cards in the player's hand.  Before each look at the top card, the function ensures the deck is not 
empty, and if it is, shuffles the discards and refills the deck.  Then, a card is drawn into the players' hand
and if it is a treasure card (that is, a copper, silver, or gold coin card), the function increments drawtreasure.  
Otherwise, the card is moved from the hand into a temp array.  After drawtreasure equals 2, the cards from the
temp array are copied to the player's discard pile (array).

In gameplay, the above actions happen when the smithy or adventurer card is played during a player's turn.  


The updateCoins() function starts by resetting the state's coin count to zero.  It then searches through the player's
hand iteratively, and adds 1 to the count for each copper coin in the array, 2 for every silver coin in the array, and
3 for every gold coin in the array.  Afterward, it adds the bonus parameter to the count.  The resulting coin count is 
the total of all coins in the player's hand plus any passed in bonus.


The discardCard() function first checks for the trashFlag flag which would signal that a card is being completely
removed from a player's deck, and if it is not raised, the card in question is added to the player's playedCards array
and the playedCards count is incremented. Next, the function checks if the played card was not the last card in the hand
it is swapped to the last card position.  Lastly, the player's hand count is decremented which removes the last card in
the hand from play.
