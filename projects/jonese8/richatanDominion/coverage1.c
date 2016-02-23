Tanna Richardson
CS362 - Winter 2016
Assignment 3 part 4
Test Coverage for Assignment 3 Test Suite

-------------------------------------------------------------------------------------------
	Overall Coverage
-------------------------------------------------------------------------------------------
The overall coverage for my test suite is:
	Lines executed:		 42.88% of 562
	Branches executed:	 51.56% of 417
	Taken at least once: 34.05% of 417
	Calls executed:		 31.58% of 95

This is not suprising given that assignment 3 included unit tests for only a subset of the
code. My unit tests directly used or tested 9 out of the 22 total functions (41%) in
dominion.c as shown below. The overall coverage, not surprisingly, is in that same range.

Functions Tested: 5/22
 - shuffle()
 - buyCard()
 - gainCard()
 - getWinners()
 - cardEffect(smithy, adventurer, council_room, baron)

Functions Used in Tests: 4/22
 - initializeGame()
 - whoseTurn()
 - drawCard()
 - getCost()
 
Functions Not Used or Tested: 13/22
 - compare()
 - newGame()
 - kingdomCards()
 - playCard()
 - numHandCards()
 - handCard()
 - supplyCount()
 - fullDeckCount()
 - endTurn()
 - isGameOver()
 - scoreFor()
 - updateCoins()
 - discardCard()
Note: some of these functions were called by functions that I tested or used, but they
were not directly called in my unit tests.


-------------------------------------------------------------------------------------------
	Statement Coverage
-------------------------------------------------------------------------------------------

gcov shows that overall statement coverage for my test suite was 43%. This is expected,
given that I tested (directly or indirectly) roughly 41% of the functions. The following
is a summary of lines that were never executed based on the dominion.c.gcov file.

Lines 20-22: newGame() block
All of my tests manually created and malloced a game so this is expected. In the future, I
could use newGame instead as it does not change the spirit of the test and improves coverage.

Lines 25-28: kingomCards() block
Again, this is expected as I manually created a kingdom cards array for simplicity.

Line 57 & 67: initializeGame() return error for numPlayers or kingdomCards
I was not specifically testing initializeGame for this assignment, so I always created
a game with a valid number of players and kingdom cards. These should be added in a unit 
test specific to the initializeGame function.

Line 143: initializeGame() catch shuffle() error
This line was never executed because a valid game was created and shuffle() always
succeeded. The line is included for error handling, but should never be executed unless
there is a bug. I don't see a reason to explicity force this to fail.

Lines 217-250: playCard() block
I did not specifically test the playCard() function and none of the functions or cards
that I did test use it either. I bypassed playCard() and called cardEffect() directly
to test individual cards. This was an intential choice to distinguish bugs found in the
cards from potential bugs in the playCard() function. A unit test for playCard() should
be added in the future.

Lines 292-293: numHandCards() block
This is a simple function that returns the number of cards in the current player's hand. 
In my tests, I accessed the handCount directly through the gameState struct rather than 
using the function to make it easier to isolate bugs. A very simple unit test could be 
added in the future to test this function directly.

Lines 296-298: handCard() block
This is a simple function that returns the card in the specified position of the current
player's hand. As with numHandCards() above, I accessed this information direclty via
the gameState struct.

Lines 305-321: fullDeckCount() block
I did not have a need for this function in the specific tests that I implemented. It 
should have its own unit test added in the future.

Lines 328-365: endTurn() block
I did not specifically test the endTurn() function and none of the functions or cards
that I did test use it either. A unit test for endTurn() should be added in the future.

Lines 372-392: isGameOver() block
I did not specifically test the isGameOver() function and none of the functions or cards
that I did test use it either. A unit test for isGameOver() should be added in the future.

Lines 411-426: scoreFor() score from discard and deck
I did not test the scoreFor() function direclty, but it is called by getWinners() that I
did test. To simplify the test, I cleared all cards from all player's discards and decks,
and stacked the hands to create the desired test case. Therefore, only the "score from
hand" portion of the scoreFor() code executes. The remaining portions should be covered
in an individual unit test specific to scoreFor().

Line 442: getWinners() set unused players score to -9999
I tested getWinners() so all lines should be executed. I'm not sure why this line is
not exectuing. This is a simple for loop from 0 to MAX_PLAYERS that uses scoreFor() for 
all real players and sets all others to -9999. This requires further investigation.

Line 453 & 470: getWinners() swap highScore if player j is higher than player i
This is a missed case in my unit test that should be added. All of my test cases set
the winners as the first n players. I need to add a case where the first player loses
and one or more later player's win.

Line 462: getWinners() add point to player's who had less turns
This is a missed case in my unit test that should be added. All of my test cases set
whoseTurn to the last player so that the function would not change the results of my
stacked deck. I need to add a case where the extra point changes the outcome.

Lines 500-531: drawCard() shuffle empty deck
I did not test drawCard() directly but I used it in the shuffle() test to get the deck
in the desired state. At most I emptied the deck, and then never called drawCard() again,
so the function was never executed with an empty deck. This case should be tested
when a unit test specific to drawCard() is added.

Lines 552-608: getCost() block (minus line 575)
I only used the getCost() function to retrieve the cost of one test card (mine). The
remaining parts of the function should be added with a unit test specific to getCost.
Although in this case, the usefulness of a unit test seems limited because it would
almost be copy/paste of the actual function code. 

Lines 611-1051: cardEffect() block
Most of the lines in this function were not executed because I did not test those cards.
Of the cards that I did test, there were a few lines not executed:
Line 741: baron - isGameOver call if supplyCount = 0. I did not test this case because
it wasn't an outcome specific to the baron card. I should add this case in the future.

Lines 1069 & 1073: discardCard() discard last or only card
I did not test discardCard() directly but it was used by functions I did test. None of
my test cases must have had the conditions necessary to run these statements. They 
should be covered in a test specific to discardCard().

Lines 1131 & 1134: updateCoins() for silver and gold
I did not test updateCoins() directly but it was used by functions I did test. All of
my test cases used copper only so the silver and gold cases did not run. They should
be covered in a test specific to updateCoins().

Line 1156: runAdventurer() empty deck
I tested the adventurer card but none of my test cases used an empty deck. This test
case should be added.

Lines 1199-1253: runMine() and runRemodel block
I did not test the mine or remodel card. It should be added in future unit tests.


-------------------------------------------------------------------------------------------
	Branch Coverage
-------------------------------------------------------------------------------------------

gcov shows that out of 417 branches, my unit tests executed 51% of them. The taken at least
once is lower, at 34%, because some branch conditions were checked but never followed. Many
of the branches not executed were because the branches occurred in functions that I did not
test. These have already been explained in detail in the statement coverage so I will not
repeat them here.

Of the functions I did test, the following branches had less than 100% coverage:

In getWinners(), the true branch for "if (i >= state->numPlayers)" and the true branch for
"if (players[i] > players[j])" were never taken. This is the same issue described in
statement coverage for lines 453 and 470. It is a missing test case and should be added.
There are also two branches not taken under "//add 1 to players who had less turns". This
is the same issue described above for line 462. Again, this is a missing case that should
be added.

In the baron case of cardEffect(), the false branch for "if (supplyCount(estate, state) > 0)"
never executes. Also the true branch for "if (supplyCount(estate, state) == 0)". I did not
test various supplyCount scenarios as I deemed this outside the scope of the baron card.
For completeness, it should be added to the test cases.

In runAdventurer(), the true branch for "if (state->deckCount[currentPlayer] <1)" is never
executed as explained above for line 1156. This should be added.

Also, in runAdventurer(), the silver and gold branches are not executed for 
"if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)". All of my test
cases use copper only. The other treasure cards should be added for completeness.
Note: this is a case where statement coverage did not show any missed lines, but branch
coverage showed conditions that were not checked. 100% statement coverage does not equate
to 100% branch coverage.


-------------------------------------------------------------------------------------------
	Boundary Coverage
-------------------------------------------------------------------------------------------

gcov does not explicitly provide information to check boundary coverage. It provides 
information on cases (boundaries) that are not tested, but it does not tell how far away
from the boundary the test value is. For example, the if statement below appears in 
initializeGame() to check the number of players requested.

    if (numPlayers > MAX_PLAYERS || numPlayers < 2){
		branch  0 taken 100% (fallthrough)
		branch  1 taken 0%
		branch  2 taken 0% (fallthrough)
		branch  3 taken 100%

gcov shows that numPlayers > MAX_PLAYERS is false and numPlayers < 2 is false in 100% of
my test cases. Based on this I know that I have not tested boundary conditions for above
MAX_PLAYERS and below 2 players. It does not, however, tell me if I have tested the boundary 
conditions equal to or just below MAX_PLAYERS and equal to or just above 2 players. I could
have tested something in the middle every time. To really assess boundary coverage, we must 
compare the branch conditions with our test cases. 


-------------------------------------------------------------------------------------------
	Path Coverage
-------------------------------------------------------------------------------------------

It is difficult to determine path coverage from the gcov results. You can create a rough
calculation based on nested percentages, but this approach assumes equal probably and it 
is difficult to know which branches follow each other on individual executions. Here is an 
example of nested branches from initializeGame() where the code checks to see if the 
selected kingdom cards are different:

	for (i = 0; i < 10; i++){
		for (j = 0; j < 10; j++){
			if (j != i && kingdomCards[j] == kingdomCards[i]){
				
gcov provides branch coverage for each line as follows:
	for (i = 0; i < 10; i++)
		true (i < 10): 91%
		false: 9%
	for (j = 0; j < 10; j++)
		true (j < 10): 91%
		false: 9%
	if (j != i && kingdomCards[j] == kingdomCards[i])
		true (j!=i): 90%
		false (j!=i): 10%
		true (kingdomCards[j] == kingdomCards[i]): 0%
		false (kingdomCards[j] == kingdomCards[i]): 100%

This information can be used to infer the path coverage. For example, the path i < 10,
j < 10, j!=i, and kingdomCards[j] != kingdomCards[i] is taken roughly 74%. This is 
calculated by taking 100% of 90% of 91% of 91% of the total 100. It can be helpful to
get a rough idea of path coverage and check paths never taken, but as mentioned above
it is not a concrete result for path coverage.

