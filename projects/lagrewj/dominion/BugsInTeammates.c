Jonathan Lagrew
CS362 Assignment 5
Winter 2016


******************
Teammate1: Nancy Chan
******************	

Pass Tests 1,2, and 3. First bug found on unittest4 with scoreFor().

Test 1: tested updateCoins()
All Tests Passed

Test 2: tested fullDeckCount():
All Tests Passed

Test 3: tested isGameOver():
All Tests Passed

Test 4: tested scoreFor():
Test failed. First bug found. 

======================================================
Bug 1 Nancy Chan - scoreFor() Testing
======================================================

After a slight amount of refactoring test worked with Teammate1's code. 

Scores do not equal the expected values. This test failed for both players. Unittest4 found a bug in 
from what I can tell is the garden calculation. We know that a garden is worth 1 VP for every 10 cards,
rounded down. The scoreFor function looks to be using the fullDeckCount() to only calculate the amount 
of curses and not accounting for the garden VP points. 
	
Starting test for scoreFor():
Test 1
Player 0:
Putting in the discard pile:
    5 duchy
    3 provinces
    1 great halls
    2 gardens
    1 curses
deckCount: 5
discardCount: 8
handCount: 5
Player 0 score: 25, expected: 38
Difference in score and expected score!

Test 2
Player 1:
All cards in deck, no additional card changes:
deckCount: 10
discardCount: 0
handCount: 0
Player 1 score: 0, expected: 3
Difference in score and expected score!

2/2 test failed for player 0 and player 1
	
======================================================
Bug 2 Nancy Chan - Smithy Testing
======================================================
Refactored code to match Teammate1's code by adding in an argument that wasn't in my original test.
playSmithy(p, after, handPos).
The test found that the wrong amount of the player's cards after playing the smithy card. Instead of 
3 cards there should of been 4. This also affected the deckCount and discard pile for the counts. This
was the same result for the hundreds of game instances ran. 

Results:

Starting test for Smithy card:
			
	Checking status before player buy...
ERROR 1: handCount is incorrect. Expected: 3 Actual: 4
ERROR 2: deckCount is incorrect. Expected: 124 Actual: 123
ERROR 3: playedCardCount is incorrect. Expected: 338 Actual: 337
Checking status before player buy...
ERROR 1: handCount is incorrect. Expected: 154 Actual: 155
ERROR 2: deckCount is incorrect. Expected: 66 Actual: 65
ERROR 3: playedCardCount is incorrect. Expected: 450 Actual: 449



======================================================
Bug 3 Nancy Chan - Adventurer Testing
======================================================
Refactored code to match Teammate1's code by adding in an argument that wasn't in my original test.
Changed the arguments in the playAdventurer(after, p) function to match teammate's code. 
The cardtest2.c found a bug in the Adventurer card that non-treasure cards that are drawn after the 
card is played are not properly accounted for. This made my test hang up in a loop and not properly 
count the treasure cards that were revealed. 

Results:
ERROR 1: Total card count difference! Should be 2 less than before total. Before: 527 After: 487
ERROR 3: Not enough treasure cards added to hand. Before: 4229216 After: 2
ERROR 1: Total card count difference! Should be 2 less than before total. Before: 154 After: 144
ERROR 3: Not enough treasure cards added to hand. Before: 4229262 After: 50
ERROR 1: Total card count difference! Should be 2 less than before total. Before: 344 After: 331
ERROR 3: Not enough treasure cards added to hand. Before: 4229273 After: 63


********************
Teammate2: Andrew Calhoun 
*********************

======================================================
Bug 1 Andrew Calhoun - scoreFor() Testing
======================================================

Same results as above in Nancy's code with regards to scoreFor().

TESTING scoreFor():

Test 1 - Player 0:
Putting in the discard pile:
    5 duchy
    3 provinces
    1 great halls
    2 gardens
    1 curses
deckCount: 5
discardCount: 8
handCount: 5
Player 0 score: 25, expected: 38

Test 2 - Player 1:
All cards in deck, no additional card changes:
deckCount: 10
discardCount: 0
handCount: 0
Player 1 score: 0, expected: 3

2/2 test(s) failed!

======================================================
Bug 2 Andrew Calhoun - Smithy Testing
======================================================

Changed my test to match teammate's refactored code with changes to my test to enable my test
to detect the bug. My original tests exited the test function because of the error in the code.
This was a good chance to add tests to my original smithy tests to check for all possible errors.
The bug I found was that when the card was played, it did not add the expected 
amount of cards to the player's hand. It was always 1 card short in every test. All other 
functionality passed except for the expected number of cards that the card is supposed to 
grant. 

Smithy Granted Hand Count: 6
Before Smithy in Hand, Hand Count: 5
Test 4 Failed: Smithy did not add expected number of cards to hand.
Expected Hand Count: 9
Actual Result: 8
Checking expected seed state.
Position 0 Deck Card: 4
Position 1 Deck Card: 4
Position 2 Deck Card: 4
Position 3 Deck Card: 4
Position 4 Deck Card: 4
Test 6 failed. Check code or change seed.
Checking hand and seed state.
Player 1 Test Completed.
------------------------
Smithy Test Summary
------------------------
One or more tests failed. playSmithy function has errors.
Smithy card did not work properly.
Smithy gave: 8
Expected: 9
End of Smithy test



======================================================
Bug 3 Andrew Calhoun - Testing Adventurer
======================================================

For the testcard2.c that tested the adventurer card, I did minimal changes to my test in order to get it
working on Andrew's code by only changing the arguments in the playAdventurer() function to match his code.
After the adventurer card is played, instead of two treasure cards being revealed, Andrew's code stops at one.
As shown below, this gave the error 1 only showing a difference of 1 instead of 2. This was confirmed with
test 3 showing that these were treasure cards not being added. 
	
PlayAdventurer
ERROR 1: Total card count difference! Should be 2 less than before total. Before: 527 After: 528
ERROR 2: Hand count difference! Before: 3 After: 6
ERROR 3: Not enough treasure cards added to hand. Before: 16 After: 1
ERROR 1: Total card count difference! Should be 2 less than before total. Before: 154 After: 155
ERROR 2: Hand count difference! Before: 336 After: 351
ERROR 3: Not enough treasure cards added to hand. Before: 62 After: 48
ERROR 1: Total card count difference! Should be 2 less than before total. Before: 344 After: 345
ERROR 2: Hand count difference! Before: 109 After: 120
ERROR 3: Not enough treasure cards added to hand. Before: 73 After: 60
ERROR 1: Total card count difference! Should be 2 less than before total. Before: 655 After: 656
ERROR 2: Hand count difference! Before: 243 After: 288
ERROR 3: Not enough treasure cards added to hand. Before: 103 After: 93
ERROR 1: Total card count difference! Should be 2 less than before total. Before: 554 After: 555
ERROR 2: Hand count difference! Before: 409 After: 412
ERROR 3: Not enough treasure cards added to hand. Before: 155 After: 146

