Adventurer- When this card is played it is first checked to see if currentPlayer’s handCount 
is less than 1. If the deck is empty then shuffle() is called. Next drawCard is called, and 
checked to see if it is a treasure card. If it is a treasure it stays in the players hand, if 
it is not a treasure card it is added to a temp array. This continues until 2 treasure cards 
are drawn, at which time all drawn non-treasure cards are discarded.

Smithy- When this card is played a loop is simply used to call the drawcard function 3 times, 
which adds 3 cards to the deck, then the Smithy is discarded from the players hand.

discardCard()- If the trashFlag is less than 1, indicating that the card was not trashed, then 
it is added to the played card pile and the played card count increased. The card is then set 
to -1. The card is then removed from the players hand.

updateCoins()- Coin count is set to 0. All the cards in the players hand are then looped through, 
checked if the card is a treasure card, and coins is updated appropriately. Lastly the function 
adds the value of bonus to the coins.
