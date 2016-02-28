/********************************************************************
Assignment 5 - Part 1
Author: Lynn Herrick
Date: 2/25/16
Description:  Submit everything in your git  directory as before.
Grab your teammates code and put it in a seperate folder within your
 folder. Copy paste your tests into their directory and run your 
 tests. You can use your makefile to run the tests or you can run 
 them one by one. Report any bugs you found in your teammates/ code. 
 You need to report 2 bugs to your teammate in total. In case you 
 cannot find out any bugs in your teammates' code, mention in in your 
 report. Name your report BugsInTeammates.c (40 points for running 
 your test against teammates' code with intention of finding few bugs
 and 10 points to find at least a bug. So, if you cannot find out 
 any bug, you will loose only 10 points). Please note that you may
 need to change your tests in order to match the refactored code. 
 Based on how your teammates refactored the code, what are the 
 method names, what are the parameter passed, you have to change 
 your tests. This will also indicate how maintainable your tests are. 
********************************************************************

For full tests, please see unittestresults.out, randomtestadventurer.out,
and randomtestcard.out within /teammate1Dominion and /teammate2Dominion.
Below are provided snipetts from the tests along with conclusions about 
where I believe the bug is and why those tests are showing errors.

----Teammate 1, Regina Imhoff-----

*Card 1: Smithy
Three issues were found reaccuring in the Smithy card.

1. Did player 1's hand change:
Failed. Hand count is 5 + 3 = 7

Conclusion: Current player is not getting 1 of the 3 cards they should get as 
part of Smithy.  This card is not otherwise going to other player(s), it is just
not getting assigned to/use by current player.

*Card 2 - Adventurer
NOTE: This one is a bit tricky as just one run with 1 unit test might not detect any
bugs.  When I ran multiple random tests, if the deck count is not randomized to 0, the
test will fail consistantly on whether the deck has changed to account for the deck 
size change.

3. Did player 1's deck change:
Failed. Deck count is 51 - 2 = 50

Conclusion:  since the player's hand is not incorrect, a card is getting lost somwhere
either in the deck, in the discard, or between those two steps.

*Card 3 - Sea Hag
16. Is next player's top card in their deck a curse:
Failed. Top card is not curse.

Conclusion: Correct curse is not being allocated to other player(s).  Further, 
will go into infinite loop if player = 0.

*Card 4 - Council Room
14. Did the number of buys change + 1':
Failed. Number of buys is 1 + 1 = 3

Conclusion: Number of buys is 1 more than it should be.

*function1 - discardCard

Conclusion: passed all tests

*function2 - drawCard

Conclusion: passed all tests

*function3 - updateCoin

Conclusion: passed all tests

*function4 - gainCard

Conclusion: passed all tests
 

----Teammate 2, Kim McLeod-----

*Card 1: Smithy
1. Did player 1's hand change:
Failed. Hand count is 5 + 3 - 1 = 6

3. Did player 1's deck change - 3:
Failed. Deck count is 5 - 3 = 3

5. Did player 1's discard pile change - 1:
Failed. Discard count is 0 - 1 = 0

Conclusion: current player is not recieving the correct amount of cards.  Cards are off by 1.

*Card 2: Adventurer
3. Did player 1's deck change:
Failed. Deck count is 5 -(0 + 2) = 2

15. Did the played card count change + 1':
Failed. Played card count is 0 + 1 = 0

16. Did the played 1 draw 2 treasure cards':
Failed. Played card count is 36 + 2 = 39

Conclusion: Player draws one more treasure card than supposed to.  This makes card counts off in other areas.

*Card 3: Village

12. Did the number of actions change + 2':
Failed. Phase is 1 + 2 = 2

Conclusion: Not enough actions as there are supposed to be assigned.

*Card 4: Outpost

8. Did the outpost played change + 1:
Failed. Outpost played is 0 + 1 = 2

Conclusion: Outpost is adding 1 extra played output than it is supposed to.

*function1 - discardCard

Conclusion: passed all tests

*function2 - drawCard

Conclusion: passed all tests

*function3 - updateCoin

Conclusion: passed all tests

*function4 - gainCard

Conclusion: passed all tests


