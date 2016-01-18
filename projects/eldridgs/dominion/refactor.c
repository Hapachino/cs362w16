Smithy:
Added 5 buys.

Adventurer:
Changed "if (state->deckCount[currentPlayer] <1)" to "if (state->deckCount[currentPlayer] <2)" to
cause the deck to reshuffle too soon.

Village:
Discarded handPos + 1 instead of handPos.

Great Hall:
Added "drawCard(currentPlayer + 1, state);" so that next player would get to draw a card as well.


