
playSmithy() - Smithy Card.
 The smithy cards gives you 3 more cards.
  :: In code ::
 Loop 3x to draw 3 cards. Then discard card from hand.

playAdventurer() - Adventurer Card.
 The adventurer card will reveal cards from your deck until you have 2
 treasure cards. When that happens you keep the treasure cards and discard 
 the other revealed cards.
  :: in code ::
  Loop untiul the player has drawn two treasure cards. If the deck is empty then shuffle
  the discard pile and add back to the deck. If the drawn card is a treasure card
  then increment drawnTreasure otherwise continue revealing cards. After two treasure
  cards are drawn discard all cards that have been revealed except the treasure.

discardCard() - discard card function
 The discard card function reduces the number of cards in the players hand and adds
 them to the played pile. 
  :: In Code ::
 If the card isn't trashed (set by trash flag) then add that card to the played pile.
 Then set the played card to -1 to decrement. If the last card in hand is played reduce
 the number of cards in hand or if there's only one card in hand reduce the cards by 1 
 otherwise replace the discarded card with the last card in hand. Set the last card to -1 
 then reduce the number of cards in hand.


updateCoins() - update coins function
 The update coin function adds coins to the player by means of treasure cards or bonuses 
 from other cards.
  :: In code ::
 First the coins are set to 0 then loop through each treasure card and add the amount of coins.
 Add one for copper, two for silver, and 3 for gold. 
 Finally if there's a bonus then add the bonus to the coin total.


