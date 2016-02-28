The smithy card simply draws three cards into the hand of the player that played the card, and then discards itself.
The adventurer card draws until two treasure cards are drawn, then it discards all the non-treasure cards that it drew.
discardCard first checks to see if the card was trashed. If not, it adds it to the list of played cards. Then it sets the
  player's last-played card to -1 and removes the card from the player's hand. If it is the last card in their hand, it
  simply reduces the count of cards in their hand. Otherwise, it moves the last card in the hand into the emptied slot
  and then reduces the count of cards.
updateCoins first zeroes out the player's coin count. Then it goes through their cards and adds the appropriate value
  for every coin in their hand. Finally it adds any bonuses that were passed in as an argument.