/* Robert Jackson CS 362 Bug fixes

 /*----------------------------------------- Adventurer bug
it was discovered that the second while loop was incorrect
Second while loop should be (z - 1 >= 0) instead of (z - 1 > 0)
Line 681 fixed


 */
/*----------------------------------------- Smithy bug
It was reported that Player is gaining 4 cards instead of 3, error in for loop.
line 723 was fixed
for (i = 0; i < 3; i++)


*/
/*-----------------------------------------Council Room Bug
It was reported that Players 2-4 did not draw a card.
second for loop i was not initialized to 0
Line 703 was fixed to:
for ( i = 0; i < state->numPlayers; i++)
{


*/
 /*-----------------------------------------Village Card Bug
Player did not gain/discard correct # of cards.
A missing drawCard() statement resulted in an inaccurate Handcount
This was added in line 740


*/
/*-----------------------------------------ScoreFor Bug
the Deck summation used the discard count instead of the deck count to loop
for (i = 0; i < state->discardCount[player]; i++)
This bug was not introduced by me but found in my tests.


 */


/** RESULTS OF INITIAL TESTS

 (SEE pre-Test.out)

 //RESULTS AFTER DOMINION FIXES ISSUED

 (SEE post-Test.out)


 //CONCLUSION
    Some of the random tests show failure for a number of tests, but the static tests show passing. This indicates that
 either there is an issue with the random test itself, or possibly there are issues regarding the state, and what can
 be considered a valid state as per the current Global values established by dominion. Because the random test tries to
 use all "possible" values not all "probable" values I would conclude that the failure of the tests in the random tests,
 are the result of imperfect states in the setup. i.e no had no deck = no increase in hand count for the drawCard
 function which would

    Additionally there are still some bugs in the scoreFor function. The one bug that was fixed did improve the test
 case  however, it is still failing for the case where a great_hall card is being used. This could mean that there
 is a problem with the test, or that there is an additional problem in the function. More testing would be required.



