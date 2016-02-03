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

unittest3.c - updateCoins() - CLEAN

I was unable to find a bug in this part of the program.

unittest4.c - scoreFor() - BUGGY

This unit test fails to run after the first scenario, because I was able to find a bug.
The bug is located in a helper function for the scoreFor() function. The helper function
is called fullDeckCount. Full deck count takes the player, game state, and a card as arguments. 
It then searches through that players hand for the specified card, and returns the number of 
times it is found. This function is simply being used incorrectly here. The scoreFor function is
looking for the total count of all cards, not just one specific one. As such, the implementation
within scoreFor() for counting gardens cards should be modified to remove these buggy results,
which result in undercounting the points for a player holding garden cards. 

cardtest1.c - playSmithy - BUGGY

This unit test fails to run after the first scenario, because I was able to find a bug.
The bug is located in the playSmithy function, where it adds 4 cards (not 3), and also does 
this for player 2. This causes the first test, that other player states remain the same, to failing
because the first the second player always receives additional cards. These did seems to be 
distributed correctly, as the player deck was pulled from appropriately. I commented out these 
asserts and also noticed the player drawing was receiving 4 cards as well, introducing another 
bug into the system.

cardtest2.c - adventurer - BUGGY

This unit test fails in scenario 1 and scenario 2, and I'm able to immediately find three bugs as 
a result. The first bug is related to the playAdventurer() function not counting gold treasures,
which can result in the number of treasures possible to be added intot he hand being too low. This 
results in the Oracle returning more treasures to the hand than the formula does. If this passes (gold
treasures not a factor), then the test fails on the final test where the total card sizes of a player
are compared. It appears that playAdventurer() is always one card short. This seems to be a bug with 
the temp hand used in the implementation of that card. The temp hand is forgetting to return one card 
to the discard, resulting in this issue. The final bug is that the playAdventurer can return more than 3
treasures to the players hand. This causes an error because the test case compares the starting treasures
in hand to the ending treasures, to ensure no more than 2 were added. This is a problem with the while loop
in playAdventurer.

cardtest3.c - outpost - WIP

cardtest4.c - village - WIP


