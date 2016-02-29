Mark Giles
CS 362 - Software Engineering II
Assignment 5
Bugfixes.c

Summary
===============================================================================
For my assignment 5 bug fixes, I started by focusing on the areas that my
team mates pointed out in their bug reports. By using the details of the bug
reports, creating break points in GDB for the functions in question, and 
analyzing specified game state information as the program executed, I was able
to identify the areas of concern explicitly and make the appropriate corrections.

I then performed the same steps on the bugs I introduced in refactor.c. While I
was aware of their details since I was the one that created them, I still went
through the steps of performing the operations in GDB to witness the memory
and data structure modifications in real time. By analyzing the expected results
calculated by the game creators, and comparing them to the actual results
produced by my files, I was able to isolate the cause of the issues and fix
them accordingly.

Bug Fixes
===============================================================================
This section details the steps taken to identify, isolate, and resolve each of
the bug fixes performed during this process.


-------------------------------------------------------------------------------
Bug Fix #1
Title: Adventurer card not removed from hand upon use.
Date: 2/28/2016
Description: 
This bug was identified by Eric Olson and provided as a bug report
for identification and correction. The bug report revealed a basic issue where
the function is called and the adventurer card used to call the function in the
first place was not removed from the hand, allowing for subsequent plays of the
same card in the same turn. This takes place in a refactored function called
adventurerEffect that I created, so I set break points in the function, and
stepped through the program using my own unit tests created for the same
function. After a few iterations, I identified that my own tests did not catch
this bug, creating room for improvement in that area. Furthermore, in using
GDB along with GCOV, I was able to see a segment of code that was not executed.
The issue was that there is a section at the end of the function that which has
a conditional while loop dependant on a local variable z to be greater than 0.
As I stepped through the function, I noticed that the z variable remained
unchanged. The z variable is designed to account for the total number of cards
to be discarded appropriately during the function's operations. This value
should increment each time a card is encountered that is not a treasure card.
In the previous while loop, z should be incremented each time this condition is
true. In order to resolve the issue, I added a z++ incrementor line, which
implements the discard pile counting system, and causes the previously dead
code to be activated accordingly.


-------------------------------------------------------------------------------
Bug Fix #2
Title: smithyEffect function gives the player four cards instead of three.
Date: 2/28/2016
Description:
In examining this bug, I used similar methods described above. This bug is both
fairly straightforward in itself and I created the bug myself so it was simple
to actually fix. However, in going through the process, I abstracted my prior
knowledge from the situation by using debugging tools to check member values
and game state information accordingly. In an attempt to find alternate sources
for the bug, I worked through the smithy function, and found that all 
operations appeared to work successfully without error. The function utilizes
a for loop to iterate multiple times drawing a card through the use of the
game's pre-designed function. On the moment when the game's rules expect the
function to continue to discard and exit, I noticed the loop iterates one
additional time, leading to the errored drawCard operation. In evaluating the
code, I noticed that it is in fact set to iterate 4 times instead of 3. To
correct this issue, I changed the for loop setup information on line 674. The
previous version of the function had the conditional section set to "if i <=
3". I removed the "=" character, forcing it to only evaluate true if i < 3. In
Multiple successive runs of the function, the normal functionality of the
function is restored.


-------------------------------------------------------------------------------
Bug Fix #3
Title: Remodel unable to find trashed card when it is in first position of
	player's hand.
Date: 2/28/2016
Description:
This bug was not reported through external means, and was created as a result
of assignment 2. The specific conditions required to trigger the bug create a
unique opportunity for unit test evaluation. My first run of unit card tests
did not find this bug automatically and I had to make some modifications using
my pre-existing knowledge of the bug to find it. However, my un-modified random
tests did find the bug, as it used random selection for the card's position in
the hand. The bug occurs when the trashed card is in the 0 position of the
index, and is created by setting the initial value of i in the for loop that
checks for the trashed card to 1 instead of 0. This essentially skips the first
card in the player's hand when checking for a match. It also allows the function
to operate normally otherwise, creating a unique challenge for creating and
checking the efficiency of tests. To correct the bug, I set the initial value
of i from 1 to 0.


-------------------------------------------------------------------------------
Bug Fix #4
Title: greatHallEffect function adds two actions instead of one.
Date: 2/28/2016
Description: 
This is another function I introduced in the original setup of the game in 
assignment 2. The basic result is that the number of actions is incremented by
2 when it should only be incremented by 1. This was a result of the
state->numActions++ operation was duplicated on lines 726 and 727 of 
dominion.c. In order to fix this, I removed the duplicate execution of the line
and it restored the function's expected operation. As a result of debugging, 
the item to watch in this case is the game state's number of actions. Knowing
the number of actions at the start, it is simple to watch the number of actions
increase throughout the execution of the function. The line in question clearly
reveals itself when the number if actions increments a second time, making the
value of state->numActions 2 higher than the original value.
