/* Author: Kim McLeod
 * Date: 2.28.16
 * Assignment 5
 * BugFixes.c

These are the bugs that were found by my teammates and fixed by me.

Adventurer - Adventurer is only adding 2 treasure cards when 3 are available. I changed (while < 2) to (while < 3).

Smithy - Smithy incorrectly increments the number of cards the player receives. Player only gets 2 cards when they should get 3. I changed for(i = 0; i < 2; i++) to for(i = 0; i < 3; i++).

Village - village was incorrectly giving the player only one extra action, when it should be giving the player 2 extra actions. I changed state->numActions + 1 to state->numActions + 2.


*/