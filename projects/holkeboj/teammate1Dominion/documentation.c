Smithy: 
The Smithy card allows the user to draw three cards, after which the Smithy carded is discarded from the player's hand and sent back to their discard pile. 
According to the getCost function, it costs four coins to purchase. According to the draw card function, if there are no cards remaining in a player's deck when this card
is played, the player's discard pile will be shuffled and act as their new deck. This occurs BEFORE the smithy card is actually discarded, thus ensuring that the smithy card
will not be in the players "new" deck.

Adventurer:
The adventurer card continously reveals cards in a player's deck until two treasure cards are drawn, at which point the treasure cards are taken into the player's hand
and all other revealed cards are discarded. This card costs 6 coins. According to the code, if the deck is empty the deck will be shuffled before the card draw function is
called, although this seems redundant as card draw checks to see if the deck is empty before doing anything else. The card is discarded after it is played, although
unlike Smithy, it is guranteed to be in the deck if a shuffle occurs during the drawing for the treasure cards.

discardCard:
As its name implies it discards a card based on handPos (position in hand), current player, game state, andtrash state.
In the event the card is not trashed, the discarded card will be added to the played pile.
In all cases the handpos of the player will be set to -1 for that card.
The total number of cards in the player's hand will be decremented.

updateCoins:
Each call of coins begins with the state at 0. Then the treasure cards in the player's hand are examined.
A summation of coins, based on copper (1), silver (2), gold (3) is then calculated.
Finally, a bonus is calculated. 

