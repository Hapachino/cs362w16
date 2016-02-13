randomtestadventurer.c - Just looking at code coverage metrics this looks to have gained
me about 5-7% increased code coverage over the previous simple unit tests. I also discovered
a bug in the adventurerEffect where it does not always succeed in drawing two treasure cards
and leaves the deck in an inconsistent state.

randomtestcard.c - I choose to test the smithy effect. First I initialized the game state
to a random but valid state and then triggered the smithy effect. The oracle was to check
the count of cards in the deck, hand and discard after the effect was applied. I did discover
a "bug" where the smithy will seem to succeed when the deck is empty but the game state
hasn't updated and no error has been triggered. This is probably because it's not checking
the error status returned from drawCard.
