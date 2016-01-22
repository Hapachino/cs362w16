Smithy card
It draws three cards for current player using drawCard function.  After drawing cards, it discards cards from current player via discardCard function.

Adventurer card
As long as drawntreasure counter (number of treasure card) is less than 2, the adventurer process is performed.  If the current player’s deck is empty, the deck gets shuffled. Draw cards for the player and check the top card.  If the top card is a treasure card (copper, silver, or gold), then drawntreasure counter increments.  Otherwise, the card gets stored in temporary hand.  Once the drawntreasure counter is equal to or greater than 2, then discard all the cards in the temporary hand.

discardCard() 
It checks the trash flag first.  If the card is not trashed, then the card is added to the played pile while incrementing the played card counter.  Set the played card to -1 to mark it as played card.  If the last card in the hand is played, then the hand count is decremented. Also there is only one card in the hand, then the hand count is decremented.  Otherwise, the function replaces the discarded card with the last card in the hand.  It also marks the discarded card as played card.  The number of cards in the hand gets decremented.

updateCoins() 
It first resets the coin count to be zero.  Check the player’s card.  If it is copper, then the coin counter increments.  If it is silver card, the counter increments by two.  If it is gold, the counter increments by three.  Finally, add bonus to the coin counter.
