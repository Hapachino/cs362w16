Smithy :
  The smithy card allows a player to draw three more cards from the deck. It does this
  by calling drawCard() three times and adds these cards to the player's hand. Once the
  cards have been drawn, the smithy card is then discarded. The smithy card has a cost
  of 4 coins.

Adventurer :
  The adventurer card play will try to draw two treasure cards. First, there is a check to make sure the
  deck is not empty. If the deck is empty, there is a call to `shuffle` so the deck is guaranteed to
  contain cards. Then, there is a drawCard function which draws a random card from the deck and puts it
  on top of the players deck. The top card in the players hand is the most recently drawn. Then, if the
  card is a treasure card, drawntreasure is incremented , otherwise the card is put into a temp array to
  be discarded after the player has drawn exactly two treasure cards. After the player has drawn two
  treasure cards, there is another loop to discard the cards that were drawn but were not treasure cards.
  This removes them from the deck.

discardCard() :
  First, the trash Flag is checked to see if the card should be added to the played pile or removed
  from the player's deck. If the flag is not set, the card is added to the `played` pile and the played
  card count is incremented. The card is then removed from the players hand and the number of cards
  in the players hand is decremented.

updateCoins() :
  The updateCoins function starts by resetting the coin count to zero. It then iterates through the players
  hand and increments the coin count based on the type of card. If the card is a copper, the count is incremented
  by one. If it is a silver, by two, and three for gold cards. If there are any bonuses passed to the function
  then the bonus coins are added to the total count. 
