Teammate 2(durhamch) reported the following bugs to me:
Wrong number of cards added to hand after playing adventurer card
Wrong number of cards added to hand after playing smithy card (results from discard bug explained below)

I intoduced the above bugs in Assignment 2. The fixes for these bugs are explained below.

I fixed all the bugs that I introduced in Assignment 2 (this includes bugs reported to me by my team):
Adventurer Card Implementation: The player should no longer be allowed to draw cards once two treasure cards are drawn, I changed this number to three in Assignment 2.  This caused the wrong number of
cards (three) to be drawn.  I changed this number back to two to fix this bug.
Smithy Card Implementation: In Assignment 2, I decremented the hand position, so the wrong card will be discarded.  I removed the decrementation to fix the bug.
Council Room: The card should allow the current player to draw 4 cards. Instead, in assignment 2, I modified the loop to iterate for the number of players. So, an incorrect number of cards will be drawn.
I changed the number back to 4 to fix the bug.
Feast Card Implementation: In assignment 2, I modified the loop conditional to allow the loop to iterate as long as x is less than or equal to 1. At the end of the loop, x is set to 0. So, the loop became
infinite.  I changed the loop condition back to x is equal to 1 to fix the bug.
