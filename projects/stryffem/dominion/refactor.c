/* 	File: refactor.c
	Author: Martin Stryffeler

The action cards smithy, adventurer, cutpurse, village, and council room have had their effects moved out of cardEffects. 
The card effects now take place in functions called from the switch statement in cardEffects().

A bug is now present in the adventurer card effect. This bug affects the number of times the while loop executes, causing 
extra cards to be drawn.

A bug was introduced to the smithy function. The for loop is miswritten, causing it to execute twice instead of three
times.

There is a new bug in the village card function. Instead of incrementing the number of available actions by two, it sets
the number of actions to the current number of coins plus two.

Cutpurse also has a new bug. In the for loop, the i is initialized to 1 instead of 0, causing player 0 to be skipped when
determining who is affected by the card.

*/