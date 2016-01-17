Samuel Ford
CS362-400, Winter 2016
Assignment 2

Documentation
=============

Adventurer
----------
Playing the adventurer card will allow the player to draw cards from their deck until they reveal two treasure cards.  The two treasure cards go into the player's hand and the other cards that were drawn are discarded.


Smithy
------
When the Smithy card is played, the player draws three cards from their deck and adds them to their hand.  This is accomplished by looping three times and calling the drawCard() function on each iteration.


discardCard()
-------------
Despite its name, the discardCard() function handles both discarding and trashing a card from the player's hand.  Whether a card is discarded or trashed is determined by the trashFlag integer parameter; if trashFlag is less than 1 then the card is simply discarded (i.e. added to the discard pile and removed), otherwise it’s trashed (i.e. not added to the discard pile and removed).

Removal is accomplished by making sure the card-to-be-removed ends up outside of the bounds of the gameState.hand array index (gameState.handCount) so that it cannot be played.  To be extra sure that the card won’t be played (e.g. if there’s an indexing bug) the value of the card is set to -1 (rather than the enum value of that card), changing it from a card into something unplayable.


updateCoins()
-------------
updateCoins() is a rather strange function to me.  It appears to be executed in both the Action and Buy phases but, at least on the surface, the code seems problematic.  Specifically:

1. updateCoins() automatically plays every treasure card in the player’s hand when it’s executed.  This would be problematic if updateCoins() is executed more than once but...

2. updateCoins() sets gameState.coins to zero whenever it’s executed, thusly negating the treasure-playing effects of any previous executions of updateCoins().  The trouble is that updateCoins() is used to handle cards that have coin-related effects (e.g. cutpurse), so zeroing the coins on every execution becomes problematic.  If you were to play more than one card with coin-related effects in the Action phase, then it seems like the coin-related effects of previous cards would be effectively negated (leaving you with only the last coin-related effect).  For example, if you managed to play three cutpurses (+2 coins * 3) then you would only end up with 2 coins (rather than 6).

I haven’t explored the codebase enough to verify if the function ends up working properly (because of the context it’s executed in) or if it's actually buggy.  From some preliminary testing (which could be wrong), it seems to nullify coin-related effects of previously played cards as mentioned above.

At the very least, I believe that updateCoins() could be implemented in a much more predictable fashion (refactoring the treasure-playing code into another function and resetting the coin count at the start of each turn rather than on each execution of updateCoins()).
