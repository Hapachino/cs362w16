/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/14/2016
 * Description: Assignment 4 notes and coverage report
 */

Random testing functions can be compiled with the following command:
    make randomtestresults.out

The randomization of my tests could use significant improvement. At the moment,
the game seed and number of players are the only real randomized portions.
There are bugs in both the Smithy and Adventurer cards that cause 100%
failure results in all test cases, which will make further random testing
less likely to provide useful results.

In the random test for the adventurer card, I achieved 100% branch coverage and
82% line coverage, which is fairly good. Many of the test cases for this card
ended with a failure related to no additional cards being added to the test
hand. This is due to a bug in the playAdventurer function. The other failures
are attributed to initializing games with either 1 or 5 players.

Game initialization errors were also common in random testing for the smithy
card, when player numbers of 1 or 5 were input. The other failures were due to
a player not gaining/discarding the correct number of cards. On this test, my
branch coverage was only 57.14%, and line coverage of 63.27%. The lower numbers
here are due to the branch where the player gains/discards being closer to the
top of the statement chain. If the test does not fail on initialization, then
it always fails at this point and simply never makes it to the branches further
down in the code.
