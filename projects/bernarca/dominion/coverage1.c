dominion.c coverage:

Statement coverage: 28.11%
Branch coverage: 24.34%

This is a reasonable amount of coverage since my tests invoke the functions they're testing directly
without the surrounding operations. cardEffect, for instance, is never called, nor are any of the
end-game functions, and more. So ~25% overall coverage is pretty good.

Of the cards tested, Smithy, Village, and Council Room each had 100% coverage, with Adventurer hitting
93%.
For adventurer, the case where it has to shuffle because the deck is empty isn't being triggered.

For the unit tests, updateCoins had 100% coverage, gainCard had 90%, getCost had 100%, and drawCard had 85%.
For gainCard,the case where the supply of the card is already out is never triggered.
For drawCard, the cases where it has to shuffle the discard back into the deck is never triggered, nor is the
branch when the deckCount = 0 triggered.