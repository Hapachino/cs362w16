/*
Jack Holkeboer
OSU cs362
holkeboj@onid.oregonstate.edu

I discovered the following bugs as a result of my tests:

****  discardCard does not affect discard pile ***
I noticed that all my tests checking for discard after a card is played were failing.
I realized this is because I was checking the discardCount and the discard[]
array, neither of which are affected by the discardCard() function.
So even though the card is removed from the hand, it is not moved into the discard pile.
This is important because discarded cards are later added into the deck.

****  Adventurer doesn't give two treasures
This occurred for player 1 but not for player 2.
This is the result of a bug I introduced which 
draws the incorrect number of cards (see refactor.c)

****  Adventurer doesn't increment played card count
This is because adventurer does not call discardCard,
which usually performs this function.  Instead it adds
cards to the discard pile itself (the ones drawn which are
not treasure).  

****  Adventurer doesn't increment discard count
This is not caused by the same issue from above since
adventurer does not call discardCard().  It's instead
cause because adventurer does not increment the count.

**** Smithy doesn't draw correct number of cards
This only happens when hand position is 2.
This is a bug I introduced (see refactor.c)

*/