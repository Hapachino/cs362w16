My coverage of dominionc is as follows;
File 'dominion.c'
Lines executed:34.30% of 653
Branches executed:36.04% of 419
Taken at least once:28.64% of 419
No calls
dominion.c:creating 'dominion.c.gcov'

Based on 34% coverage the following bugs have been exposed:

Unit Tests

fullDeckCount: All tests passed.  No bugs to report based on my test.  Better 
coverage may reveal additional bugs.

isGameOver: The test to see if there are any provice cards still in play failed so 
there may be a bug here. The three empty piles test should verify that the game is 
over this didn't happen, further investigation is warranted here.

playCard: All tests passed. No bugs to report based on my test.  Better 
coverage may reveal additional bugs.

UpdateCoins: All tests passed.  No bugs to report based on my test.  Better 
coverage may reveal additional bugs.

Card Tests

steward: This card has three tests, test1 and test2 fail, test three suceeds.  
test one ( adding 2 cards) exposes and issue where the Hand counts don't increment 
properly.  This was only observed for player 0. This suggests a state issue for the 
current player.
The test two failure is based on test one, the coin counts are correct.  This is 
a false positive.

smithy: Test one of three failed. This bug miscounts the number of cards drawn, causing
only two cards to be drawn rather than the required three.  This was a bug I introduced 
I changed the i++ to ==i, this will cause an increment before the loop is executed 
resulting in one less card.

cut purse: Two out of three tests fail.  The first test failure is due to a discard.  
The results are correct my test didn't account for the discard.  For player 2, there 
seems to be an issue where the player is set up incorrectly and thus I get a copper 
count error.  My error is symptomatic, there is a root cause issue here that needs 
to be explored.

adventurer: Test one out of seven fails.  There seems to be an issue where the Hand 
count should have been incremented by one where it wasn't. Again this could be because 
I don't account for the discard.  Further tests are needed to verify this bug.