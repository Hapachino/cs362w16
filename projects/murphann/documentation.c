/*
Smithy card:
  If the smithy card is played, run the drawCard method three times for
   the player who played the card.

Adventurer card:
  First checks to make sure there are cards available to be drawn. If not,
  shuffles discard pile and adds it to deck.
  While number of drawn treasure cards is less than 2, run draw card function
  on player. If treasure card is drawn, update count of treasure cards and add
  card to hand. If not a treasure card sends it to tempHand.
  When 2 treasure cards have been drawn, stop drawing cards and sends tempHand
  to discard pile.

discardCard() method:
  Check for trashed tag on card. If not found, add to "played pile" and set
  position to -1. if last card in hand is played or if there is one more card
  just reduces number of cards in players hand. if there are multiple cards
  left set next card to last in hand, and set position to -1 and reduce count
  of cards in hand.

updateCoins() method:
  First resets coin count to zero. Then goes through each card in the hand.
  If copper, adds one, if silver adds two and if gold adds three to coin
  count. if not a treasure card does nothing. after all cards in hand processed
  adds any bonus coins from round.
*/
