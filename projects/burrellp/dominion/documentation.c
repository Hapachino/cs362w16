Documentation.c
Patrick Burrell
CS 362 - W2016
Assignment 2

The Cards:
Smithy - allows the player who played the card to draw three more cards
Adventurer - allows the player to add the next two treasure cards from his/her
deck to the current hand. The cards in the plyer's deck are revealed as the
deck is searched through for two coins.

The Code:
Smithy - the code associated with drawing a Smithy calls drawCard() three times
and then discardCard().

Adventurer - the code associated with drawing an Adventurer creates a while loop
that runs until two treasure cards have been reached in the deck. Within this loop,
the code checks that the player has cards remaining in the deck (the discard pile
is shuffled and added to deck if not), then the player draws a card using drawCard().
If the drawn card is a treasure card, the treasure card count is incremented.
Otherwise, the drawn card is revealed as part of the tempHand and the next card is
drawn. The tempHand is discarded at the end of the turn.

drawCard() - this function first checks that the players deck is empty. If it is,
all of the cards in the discard pile are added back to the deck and shuffled.
The top card from the resulting deck is then drawn. If the original deck is nonempty,
the top card from this deck is added to the player's hand.

discardCard() - this function first checks a card's trashFlag. If the trashFlag < 1,
the card is added to the player's discard pile (i.e. the card has been played) and
the player's playerCardCount is incremented for the turn. If the player has played
his/her last card or only has one card left in his/her hand, the palyer's handCount
is decremented and the discard ends. Otehrwise, the next card in the player's hand
replaces the discared card, the last card is set to -1, and the player's handCount
is decremented before the discard end.

