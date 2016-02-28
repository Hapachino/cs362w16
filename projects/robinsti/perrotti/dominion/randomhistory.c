**** If you are having trouble compiling, run "make clean", then run "make randomtestitems.out" ****
**** You will get two outputs... randomtestrobust.out & randomtestresults.out. *********************
**** The first includes all test case returns from the test runs... it is very long ****************
**** I also combined results from original tests (assignment 3) and assignment 4 tests in one file *
**** You can view the results by running make allnewtests.out and  looking at allnewtests.out file *

Previous code coverage tests:
File 'dominion.c'
Lines executed: 41.84% of 588
Branches executed: 48.92% of 415
Taken at least once: 42.17% of 415
Calls executed: 22.77% of 101
dominion.c:creating 'dominion.c.gcov'

New random generator tests (inclusive of previous tests and new tests):
File 'dominion.c'
Lines executed:42.18% of 588
Branches executed:48.92% of 415
Taken at least once:42.89% of 415
Calls executed:22.77% of 101
dominion.c:creating 'dominion.c.gcov'

Improvements in Coverage:
I didn't add any additional cards to the testing, but simply incremented on previous tests,
as such the changes in coverage didn't surprise me. To gain additional coverage at this point,
the game initializer or other major functions would have to be tested in depth for all of their
fail states. The small gain created by my tests was a result of forcing the game to error out
by passing an incorrect number of players. This resulted in an additional line being called. 

Correctness of Specification Changes - Adventurer Card:
In particular, the adventurer card increased its coverage to focus on helper functions that
need to be working for the card to be working. In this way, the adventurer card now ensures
that if it fails, it can be traced back to other functions that might have issues. I did this
by checking the whose turn function and the number of players assignment in game initializer.
If these two things fail it has a large impact on the ability of the adventurer card to assign
new cards to the correct player. Since my original test focused on all the major elements of the 
adventurer test, this seemed like the logical place to go. Now, this test will not only ensure
the basics of the adventurer are correct, but that modifications elsewhere in the code that directly
influence this card will be watched. 

Correctness of Specification Changes - Outpost Card:
In particular, the outpost card increased its coverage to focus on the initialization of the game,
because that is the most important part to the success of this card. In particular, I focused on
the fact that the status was set correctly to begin with (outpostPlayed == 0), because otherwise
the rest of my tests could produce false positives, or other failures. By checking to make sure
this is correct, I ensure that other changes to the code won't impact these tests, and that the 
ultimate problem can be root caused.

General Comments:

This exercise demonstrated the importance of creating tests that not only focus on your individual function, but on the functions 
sorrounding it. Doing this will allow you to trace back errors to other functions that migth be outside of your current function 
in question, which will help expose gaps in your code coverage and focus. 

Bugs:

No additional bugs were discovered by my code that were not already detected by previous tests. The tests I implemented here were
additional checks to make sure that possible failure points in the rest of the program didn't impact my cards without me knowing
about it. This appears to be a very useful exercise for programmers in the real world. That way when Jimbo two cubes down
decides to leave a typo in his production code and not write proper unit tests, you will catch it in yours. 