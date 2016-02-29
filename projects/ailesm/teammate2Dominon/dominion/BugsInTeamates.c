/********************************************************************
Assignment 5 - Part 2
Author: Eric Anderson
Date: 2/27/16
Description: Fix all the bugs that are found in your code. First 
fix the bugs that your teammate found then fix the bugs that you 
introduced. Use GDB to debug your code and fix it. Provide a 
documentation file to discuss which bugs you fix and mention your 
code changes. Provide a documentation file BugFixes.c. In case your 
teamates already fixed the bugs and you cannot find out any bugs, 
find out the version they just submitted for assignment 2 and use 
that version. It will give you better practice with git repository 
and repository history.    
********************************************************************/

Ailes
-----------------------------------------------------------------------
FullDeckCount function works correctly

isGameOver function reports 2 bugs:
Bug 1: Test to see if there are any province cards still in play
Description: Place 1 card in the supplycount and then call isGameOver.  The expected result is that the function will return a 0, instead it returns 1.
Steps to duplicate: Set the supply count to either 0 or 1 and test to see that isGameOver returns a 1 or 0 respectively.

Bug 2: Three empty piles should end game
Description: Set all the supply counts to 0 and call isGameOver.  The game should end and the function return 1 to indicate teh game is over.
Steps to reproduce: See unit test 2 test 5

playCard function works correctly

updateCoins function works correctly

Steward Card
Bug 1: Hand counts didn't increment properly
Description: Test the handcount before and after calling cardeffect.  The handcount will be off by 1 card.
Steps to reproduce: See cardtest1 test 1

Smithy Card
Bug 1: Hand counts didn't increment properly
Description: Test the handcount before and after calling cardeffect.  The handcount will be off by 1 card.
Steps to reproduce: See cardtest2 test 1
Note: This is the bug you introduced

Cut Purse Card
Bug 1: Discard a copper card
Description: This test checks to see that single coin (copper card) is discarded.
Steps to reproduce: Check the cards in each players hand to determine how many copper cards they have, then run cardeffect, then count the number of copper cards again.  The result will be a miscount of cards.

Adventurer Card
Bug 1: Hand counts didn't increment properly
Description: Test the handcount before and after calling cardeffect.  The handcount will be off by 1 card.
Steps to reproduce: See cardtest4 test 1
Note: This is the bug you introduced

Dominion.c
Bug 1: warning: unused variable 'drawntreasure'
Description: This variable is defined in dominon.c but is never used at line 660
Steps to reproduce: Compile the test using "make randomtestresults.out"

Bug 2: warning: unused variable 'z'
Description: This variable is defined in dominon.c but is never used at line 662. This is the counter for the temp hand!
Steps to reproduce: Compile the test using "make randomtestresults.out"

Bug 3: warning: unused variable 'cardDrawn'
Description: This variable is defined in dominon.c but is never used at line 661
Steps to reproduce: Compile the test using "make randomtestresults.out"

Byrne
-----------------------------------------------------------------------
FullDeckCount function works correctly

isGameOver function reports 2 bugs:
Bug 1: Test to see if there are any province cards still in play
Description: Place 1 card in the supplycount and then call isGameOver.  The expected result is that the function will return a 0, instead it returns 1.
Steps to duplicate: Set the supply count to either 0 or 1 and test to see that isGameOver returns a 1 or 0 respectively.

Bug 2: Three empty piles should end game
Description: Set all the supply counts to 0 and call isGameOver.  The game should end and the function return 1 to indicate teh game is over.
Steps to reproduce: See unit test 2 test 5

playCard function works correctly

updateCoins function works correctly

Steward Card
Bug 1: Hand counts didn't increment properly
Description: Test the handcount before and after calling cardeffect.  The handcount will be off by 1 card.
Steps to reproduce: See cardtest1 test 1
Note: This is the bug you introduced

Smithy Card
Bug 1: Hand counts didn't increment properly
Description: Test the handcount before and after calling cardeffect.  The handcount will be off by 1 card.
Steps to reproduce: See cardtest2 test 1
Note: This is the bug you introduced

Cut Purse Card
Bug 1: Discard a copper card
Description: This test checks to see that single coin (copper card) is discarded.
Steps to reproduce: Check the cards in each players hand to determine how many copper cards they have, then run cardeffect, then count the number of copper cards again.  The result will be a miscount of cards.

Adventurer Card
Bug 1: Hand counts didn't increment properly
Description: Test the handcount before and after calling cardeffect.  The handcount will be off by 1 card.
Steps to reproduce: See cardtest4 test 1
Note: I did not catch your shuffle bug! I tested shuffle but not with the empty card pile Nice!

Dominion.c:
Bug 1: Compile throws a warning "unused variable cardDrawn"
Description: This variable is defined in dominion.c but is never used.
Steps to reproduce: Compile the test using "make randomtestresults.out"