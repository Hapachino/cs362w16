Shaun Stapleton
CS 362
Assignment 5
BugsInTeammates.c

Report any bugs you found in your teammates/ code. You need to report 2 bugs to your teammate in total. 
In case you cannot find out any bugs in your teammates' code, mention in in your report. Name your report 
BugsInTeammates.c (40 points for running your test against teammates' code with intention of finding few 
bugs and 10 points to find at least a bug. So, if you cannot find out any bug, you will loose only 10 points). 
Please note that you may need to change your tests in order to match the refactored code. Based on how your 
teammates refactored the code, what are the method names, what are the parameter passed, you have to change 
your tests. This will also indicate how maintainable your tests are.

linr Unit Tests

Remodel Card:
Bug 1: Calling the cardEffect function fails.
Description: The function returns all of the cards instead of discarding or trashing any.
Steps to reproduce: See the cardtest1 unit test and it will provide you with details. 

Council Room Card:
Bug 1: No cards appear to be discarded after cardEffect function call.
Description: Test the discard pile count before and after calling cardEffect. The count is one less than expected.
Steps to reproduce: See the cardtest4 unit test.
Note: I'm not positive if this is a bug but the discardCount is not incremented in the discardCard function as I think it
should. I may be wrong. Probably don't need to fix this bug.

Adventurer Card:
Bug 1: Gold Treasure Cards not added to hand.
Description: The gold treasure card is discarded each time a player pulls an adventurer card.
The gold card is not added to the players hand as expected.
Steps to reproduce: See the randomtestadventurer test.
Note: This is a bug you introduced.

Smithy Card:
Bug 1: Hand counts aren't incremented properly.
Description: Test the handcount and deck count before and after calling cardEffect.
The handcount is one more than expected and the deck count is one less than expected.
Steps to reproduce: See the cardtest2 unit test.
Note: This is a bug you introduced.  

isGameOver Function:
No bugs found during test.

getCost Function:
No bugs found during test.

fullDeckCount Function:
No bugs found during test.

update_coins Function:
No bugs found during test.


yaof Unit Tests

Remodel Card:
Bug 1: Calling the cardEffect function fails.
Description: The function returns all of the cards instead of discarding or trashing any.
Steps to reproduce: See the cardtest1 unit test. 

Council Room Card:
Bug 1: Hand counts aren't incremented properly.
Description: Test the handcount before and after calling cardEffect.
The handcount is one more than expected.
Steps to reproduce: Run cardtest4 unit test and view the hand count before and after.
Note: This is a bug you introduced.  

Bug 2: No cards appear to be discarded after cardEffect function call.
Description: Test the discard pile count before and after calling cardEffect. The count is one less than expected.
Steps to reproduce: See the cardtest4 unit test.
Note: I'm not positive if this is a bug but the discardCount is not incremented in the discardCard function as I think it
should. I may be wrong. Probably don't need to fix this bug.

Adventurer Card:
No bugs found during test with my unit test or random adventurer test.

Smithy Card:
Bug 1: Hand counts aren't incremented properly.
Description: Test the handcount and deck count before and after calling cardEffect.
The handcount is one more than expected and the deck count is one less than expected.
Steps to reproduce: See the cardtest2 unit test.
Note: This is a bug you introduced.  

isGameOver Function:
No bugs found during test.

getCost Function:
No bugs found during test.

fullDeckCount Function:
No bugs found during test.

update_coins Function:
No bugs found during test.

dominion.c:
Bug 1: Compile throws warning "unused variable 'z', 'cardDrawn', 'drawntreasure', 'temphand', and 'x'"
Description: These variables are defined in dominion.c but are never used.
Steps to reproduce: Compile the test using 'make unittest1'