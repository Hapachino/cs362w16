General Information:
I chose to refactor the code for the following cards: Adventurer, Smithy, Council Room, Feast, and Mine. I moved the code from the switch statements to their own individual functions. 
These changes are reflected in dominion.c and dominion.h.

Bugs:
I chose to introduce bugs in the code for the following cards: Adventurer, Smithy, Council Room, and Feast.
Adventurer: The player should no longer be allowed to draw cards once two treasure cards are drawn, I changed this number to three.
Smithy: I decremented the hand position, so the wrong card will be discarded.
Council Room: The card should allow the current player to draw 4 cards. Instead, I modified the loop to iterate for the number of players. So, an incorrect number of cards will be drawn.
Feast: I modified the loop conditional to allow the loop to iterate as long as x is less than or equal to 1. At the end of the loop, x is set to 0. So, the loop is now infinite.
