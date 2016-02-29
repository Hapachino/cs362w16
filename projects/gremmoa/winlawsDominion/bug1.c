******************************************************************************

****  CS 362 - Assignment 3 - Unit Testing For Dominion - Spencer Winlaw  ****

********************  bug1.c - bugs found during testing  ********************

******************************************************************************

A3.1) discardCard()
----------------------------------------------------------------------------
Doesn't place card into player's discard pile. Instead it places cards into 
playedCards pile which is emptied upon next call to endTurn(), without ever
being transferred into the player's discard pile. Therefore no cards that 
have been discarded using this function will ever be able to be recycled 
back into the players hand and each card is effectively just trashed
This bug was first detected in unittest3 which specifically tested the
discardCard() function, but was also picked up in each of the card tests.

A3.2) Smithy Card
----------------------------------------------------------------------------
Draws 4 cards to player's hand when it should only draw 3. This was an 
off-by-one error introduced by the use of an incorrect logical operator 
(<= instead of <).
**Bug from Assignment 2

A3.3) Adventurer Card
----------------------------------------------------------------------------
Doesn't discard adventurer card after it is played. Therefore the card 
remains in the players hand and is not recorded in the player's playedCards.
This is a significant issue as it would allow the player to continually play
the card an infinite number of times. This in itself is a problem for 
gameplay, but in addition, the card functionality has no checks to ensure 
there are two more treasure cards remaining in a player's deck to be drawn, 
and could enter into an infinite loop searching for more when there are none
to be found, breaking the game.

A3.3) Adventurer Card
----------------------------------------------------------------------------
When drawing for treasure cards, silver is falls through the check and 
therefore gets discarded and treated as if it were not a treasure card. 
Instead the silver card should be kept and the number of treasure cards
drawn should be incremented.
**Bug from Assignment 2

A3.5) Great Hall Card
----------------------------------------------------------------------------
Increments numBuys when it shouldn't and fails to increment numActions when 
it should. This incorrect behavior is introduced by the use of the wrong 
attribute name.
**Bug from Assignment 2


