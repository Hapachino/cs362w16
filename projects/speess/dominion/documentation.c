# Smithy
Using the Smithy card means the player draws three new cards from the deck 
and then discards the Smithy card from the hand.

# Adventurer
Using the Adventurer card means the player draws cards from the deck
until two Treasure cards are drawn. The rest of the cards are discarded.

# discardCard()
Takes in the position of the card being played, updates whether it has been
played/discarded, removes played card from hand, updates positions of cards 
in hand.

# updateCoins()
The new coin count is taken from the combined value of the treasure cards
currently in the player's hand, plus any coin bonus.
Copper=1, silver=2, gold=3.