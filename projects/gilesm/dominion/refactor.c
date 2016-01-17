CS 362 - Software Engineering II
Assignment 2 - Refactor
Mark Giles

Adventurer Card
In the switch statement under the case adventurer section, I removed all code
except for the return 0, which allow the function to exit upon completion. I
added a new line: "adventurerEff(currentPlayer, drawnTreasure, cardDrawn, 
temphand, state);". This line effectively calls the new function I created. 
The deleted code from cardEffect was added back to the new function and 
executed. The bug I introduced in the function is by removing the z++ section
in the first while loop. The z variable is used to track how many cards that
must be discarded once the primary part of the adventurer card is produced.
This will result in z-1 = -1, which means the second while loop will never run,
and the temphand cards will never be discarded.

Smithy Card
For smithy I created a new function called smithyEffect(int currentPlayer,
struct gameState *state). The change I made was in the for loop. I made the
conditional based on if i <= 3 instead of just i < 3. This will cause an
additional card to be drawn each time smithy is played.

Remodel Card
New function called remodelEffect(int currentPlayer, int choice1, int choice2,
struct gameState *state, int handpos). The initial value of i in the for loop
has been changed from 0 to 1. This will skip the first card while checking
for a match.

Village Card
New function called villageEffect(int currentPlayer, struct gameState *state,
int handpos). In the section where two actions are added, there is only one
action added.

Great Hall Card
New function called greatHallEffect(int currentPlayer, struct gameState 
*state, int handpos). The line that adds one to the number of actions is typed
twice, essentialls adding two actions.
