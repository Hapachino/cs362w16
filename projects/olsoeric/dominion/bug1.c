/*******************************
 * Eric Olson
 * CS362_400 Assignment 3
 * Explanation of testing/bugs found
 *******************************/

For this assignment my test strategy was developed as each test was written, resulting in a
function 'evaluate' that I could use to compare the before and after state of nearly
every gameState value.  This left me to identify interesting scenarios to test, and program
those scenarios.  The results of this testing identified the bugs listed below.  Note that while
not always the responsibility of the tester, I also tried to identify the actual error in code
as well.  Results follow:

/////cardtest1 - smithy_play()/////
This test evaluted the Smithy card and identified that the smithy card itself
functioned properly but was not moved to 'playedCards' as expected at the end of the
turn.  This is due to the smithy_play()'s call to discardCard() passing a 4th paramater
of 1 instead of the expected 0. discardCard() with this flag set actually trashes the card
preventing it from going to playedCard and eventually to discard as expected.

/////cardtest2 - adventurer_play()/////
This test evaluated the adventurer card and identified three bugs.  The first is that there
is no call to discardCard(), leaving the adventurer card in the players hand at the end of 
the turn.  The second bug is in the evaluation of the drawn card, instead of looking for the
3 treasure types it only looks for copper and silver.  This means gold cards are not added to 
hand but rather returned ot the discard pile unused and uncounted.  

The third is more subtle.  If < 2 treasure cards exist in the players deck/discard pile the 
adventurer function actually continues to cycle past the point where all available cards are
considered.  In this scenario handCount continues to decrement into negative values and can cause
seg faults.  While the scenario of fewer then 2 treasure cards in deck/discard is unlikey it is
possible when all treasure cards are already 'in hand', or excesive trashing of treasure cards
occurs.  Since the scneario is viable if unlikey it should be considered and an exit criteria
added to the function to prevent seg faults.  In my testing this scenario is reached in scenario 3,
and the random testing since gold cards are not included in the treasure set per bug #2 are ignored.

/////cardtest3 - council_room_play()/////
This test evaluated the Council Room card and identified one bug.  The addition of 4 cards worked
well, however the numBuys++ has been incorrectly coded as numActions++.  This leaves the player with
an additional Action in error, as well as not providing the expected additional Buy.

/////cardtest4 - village_play()/////
This test evaluated the Village card and identified one bug.  The draw card worked, but numActions
was not increased by 2 as expected.  This is due to the use of the equality '==' instead of the
assignment '=' operator.  Essentially numActions and numActions + 2 are compared returning an ignored
false.

/////unittest1 - updateCoins()/////
Despite random testing and full state validation no bugs were found.

/////unittest2 - gainCard()/////
Despite random testing and full state validation no bugs were found.

/////unittest - shuffle()/////
Despite random testing and full state validation no bugs were found.  This function was also
called via a number of the other functions under test as well.

/////unittest- discardCard()/////
Despite random testing and full state validation no bugs were found.  This function was also
called via a number of the other functions under test as well.
