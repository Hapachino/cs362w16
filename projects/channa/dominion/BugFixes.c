Nancy Chan
CS 362
Winter 2016
Assignment 5: BugFixes.c

/**********************************
teammate1Dominion - Andrew Calhoun
**********************************/
At first, Andrew's tests were reporting bugs for adventurer and smithy. However, when I examined Andrew's
adventurer test, I discovered that his test was only testing an internal implementation of adventurer and
not my implementation. By setting a breakpoint at my adventurer function in my dominion.c, it confirmed
my suspicions that my code was not actually being executed in his test since there were no calls to my function
either directly with playAdventurer() nor indirectly with the cardEffect function.

Andrew's smithy test was resulting in a segmentation fault. Upon closer inspection, I learned that his call
to my smithy function had not been changed to match my refactored implementation. The parameter order needed
to be corrected. Once corrected, the segmentation fault no longer occurred. There was one last remaining issue
in which a conditional statement in his test needed to be corrected as well. Once corrected, expected values
equaled actual values from my smithy function.

In summary, Andrew's test suite did not find any bugs in my code. Rather than fixing bugs in my code, I instead
assisted in fixing bugs in the tests.

/**********************************
teammate2Dominion - Jonathan Lagrew
**********************************/

Bug 1: scoreFor()
I used GDB to set a breakpoint at the scoreFor() function. Jonathan's bug report mentioned fullDeckCount() using the
number of curses and not accounting for the number of gardens. With this information, I stepped through the scoreFor()
function and printed out "fullDeckCount(player, 0, state)". The number printed was indeed the number of curses and not
the number of gardens.

Bug 2: smithy

Bug 3: adventurer