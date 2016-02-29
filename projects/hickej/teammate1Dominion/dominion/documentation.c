Smithy:  When the Smithy Card is played, the player draws three cards and discards the played Smithy Card from their hand.

Adventurer: When the Adventurer Card is played, the player reveals cards from their deck until 2 Treasure Cards are found. If the deck is empty, the discard pile is reshuffled and added to the draw deck. The 2 Treasure Cards are placed in the hand and the rest of the revealed cards are discarded along with the played Adventurer Card.

discardCard(): This function checks to see if the card is trashed. If it is not trashed, the card is added to the played pile. The card is then removed from the player’s hand.

updateCoins():  This function resets the coin count to 0, then adds coins for each Treasure Card in the player’s hand, according to each Treasure Card’s value (1 coin per Copper Card, 2 coins per Silver Card, and 3 coins per Gold Card). Bonus coins are then added to the total number of coins.
