Bugs Found

Unit test 1 (shuffle):
In this test, I check if the deck count after the shuffle is the same as before the shuffle. I did not run into any problems or bugs during this test.

Unit test 2 (updateCoins):
I tested different combinations of players, and treasure cards, and bonuses. I tried to test combinations such as 3 coppers and 2 silvers, but when I
compiled my test code I got a message saying "warning: assignment makes integer from pointer with a cast". This was because I was trying to assign the
coppers array to another array element. Once I changed the word "coppers" to "copper", this warning message disappeared.

Unit test 3 (scoreFor):
I had a segmentation fault in this unit test as a result of my last assert statement failing in my testScoreFor function. This was partly because
I accidentally did not initialize the "score" variable in the testScoreFor() function to 0. However, even after I fixed my mistake the initial
scoreFor test function in dominion.c kept returning a score of 0, which was incorrect. It appears as if there was already a bug introduced in the
scoreFor function in dominion.c.

Unit test 4 (isGameOver):
I assigned different conditions which would trigger the isGameOver functions, such as assigning the supply count of Provinces to 0. I did not run
into any major problems in testing this function.

Card test 1 (Smithy):
The smithy card did not pass the test as I had introduced a bug in Assignment 2 that gave the player an extra card. Initially it passed because
I erroneously called the discardCard function in my testSmithy function. The cardSmithy function in dominion.c already discarded the Smithy card,
so I was basically discarding it twice. In my testSmithy function, there is an if statement that tests whether the player's deck count before
playing Smithy plus 2 is equal to the deck count after playing Smithy (there should only be a net gain in hand count of 2 cards).

Card test 2 (Adventurer):
This card passed the tests, and did not catch the bug I introduced in the Assignment 2. I tested whether or not 2 additional Treasure cards were drawn,
and whether the hand count after the draw was 1 card greater than the initial hand count (there should only be a net gain in hand count of 1 card).

Card test 3 (Village):
This card passed the unit test despite the bug I introduced previously, as the number of actions after playing Village should only increase by one.
For example, if a player starts out with 1 action and plays Village, the total number of actions becomes 1-1+2=2 (-1 action for playing Village).

Card test 4 (Great Hall):
This card did not pass the test I wrote related to number of actions. Similar to the Village card, the total number of actions after playing Great Hall
should remain the same as the previous turn. For example, if a player has 1 action and plays Great Hall, the total number of actions becomes 1-1+1=1 (-1 action for playing Great Hall).
The number of actions should not change after playing this card. However in this test, the total number of actions increased by 1 from 1 to 2 actions after
playing Great Hall.
