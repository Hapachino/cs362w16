unittest1.c - isGameOver() - BUGGY

This unit test fails to run after my second scenario, because I was able to find a bug. 
The bug I found in the code is that it doesn't loop through all of the possible supply 
stacks. This means that if one of the last cards (say treasure_map), is the third stack 
to 0, it will not trigger the end game state. Since my unit test randomizes numbers and 
ends up using one of these cards as set to zero to hit the three stacks empty requirement,
the program ends up failing. I was unable to complete the rest of the unit tests because
the assertion on this portion of the code causes it to break. 

unittest2.c - getCost() - CLEAN

I was unable to find a bug in this part of the program.

unittest3.c - updateCoins() - WIP

unittest4.c - scoreFor() - WIP

cardtest1.c - smithy - WIP

cardtest2.c - adventurer - WIP

cardtest3.c - outpost - WIP

cardtest4.c - village - WIP


