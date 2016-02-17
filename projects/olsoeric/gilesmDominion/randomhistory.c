CS 362 - Software Engineering II
Assignment 4 - randomhistory.c
Mark Giles
RANDOM TESTING - VILLAGE CARD

TESTING METHODOLOGY

The random tester for the village function utilizes a counting loop to create
automated and randomized tests that call the function numerous times under
varying conditions. The first component of the test allows the user to determine
the number of tests to calculate by changing the value of the variable numTests.
This variable directly controls the number of times the loop iterates. Once the
loop begins, it resets validation values and establishes a series of randomized
control variables. The variables listed as such:
	- Hand Count - The player's hand count is randomized to check for varying
		lengths of hand count.
	- Village Card Position - The position of the village card is randomly
		selected.
	- Deck Count - The available cards in the player's deck are randomized.
	- Player's cards - The player's cards are randomly selected, placing the
		village card in the randomly selected position, and randomly selecting
		cards for the rest of the positions.

Once the randomized control variables, the function is called and a series of 
check conditions are used to determine if the test passes. The tests utilized
are as such:
	- Check to ensure the player's hand count is incremented by 1
	- Check to ensure the deckcount is decremented by 1
	- Check to ensure the new position in the player's hand is a legitimate card
	- Check that the game state has two additional actions
	- Check that the village card is added to the played card deck

As with multiple conditions, a failed state is categorized under three conditions:
	- Valid Draw
	- Valid Actions Added
	- Valid Discard

Once the tests are complete, the results are printed showing information regarding
the test if any of the test conditions failed. The test results are shown for each
failed iteration as:

	TEST [test number]
	Function used: [actual function call syntax]
	Position of village card: [randomly selected hand position]
	Number of Cards in hand: [randomly selected number of cards in hand]
	Starting deck count: [randomly selected number of cards in deck]
	Cards in hand: [list of card numbers, e.g. - 2, 3, 14,]
	Random Seed: [random seed used to produce values]
	Failed Items: [valid condition that failed during the test]

Finally, the total number of tests run followed by the totals for passed tests
and failed tests are displayed.

EVALUATING RESULTS

Multiple runs of the random tests revealed a clear error in the function's
effort to increment the number of game state actions by 2. In addition to the 
obvious finding, there seems to be varying results when the deck count is set
to zero before calling the function. The variance is in the drawCard function
which is used by village. If the deck count is 0, there is an alternace outcome
in draw card which changes the results of the test. It seems that in many cases
the test fails if the deck count is set to 0, but this could be a false negative
and more investigation is required to ensure this aspect of the test is assessing
the card's functionality accurately. A potential variable not originally calculated
could be comparing the state of the discard pile in conjunction with the player's
deck.

RANDOM TESTING - ADVENTURER CARD

TESTING METHODOLOGY

The random tester for the adventurer card creates automated tests by generating
several random conditions and calls the function under those conditions. After
the game state is intiialized, the parameters are created before a backup copy
is created. The randomized conditions are listed as:
	- player's hand count - number of cards in player's hand before the function
		is called.
	- player's hand cards - The cards in the randomized number of hand cards are
		randomly selected.

The tests created by calling the function include several parameters. Before calling
the function, the original game state is used to check the player's deck. By
examining each card in the player's deck from top to bottom, the number of cards
are checked until two treasure cards are identified. Both the position of the second
card as well as the number of non-treasure cards drawn for discard are examined.
The tests performed are:
	- player's hand count - ensure the player's hand count has been incremented
		by 2.
	- player's cards - Ensure that the two additional cards in the player's hand
		are the treasure cards taken from the deck.
	- deck - ensure the deck is decremented by the number of cards drawn during
		the process.
	- discard - ensure the non-treasure cards are discarded.

The data in control vairables is used to check the resulting function call 
against expected results after each check is made:
	- isValidDraw - set to 0 if the draw components of the adventurer card are
		not performed successfully
	- isVliadDiscard - used to determine the cards discarded including their
		valid source and destination piles.

EVALUATING RESULTS

The results of the test show conclusively two things at once. The first component
of the test results that is fairly obvious is that all of the tests failed. 
However, as a result of detailed failed display criteria, it is simple to identify
which components require additional investigation. Because the hand state is shown
before and after the function call, it is easy to identify that the hand
has two additional cards and they are in fact treaure cards. However, through
multiple iterations, the cards are overwhelmingly copper cards, revealing an
opportunity to expand the random test by creating varying starting deck
contents. The player's hand tests pass successfully, despite the need to expand
the test. The component that seems to fail each time is the discard operation.
Further investigation is required, however, it would appear that while the cards
checked in the deck are removed properly, they are not added to the appropriate
discard pile, resulting in an unbalanced set of available cards in the game state.

COVERAGE

Assignment 3 vs Assignment 4:
Coverage from assignment 3 reveals an overall branch coverage of approximately 31.65%,
while assignment 4 reveals two components seperately. For the randomtestcard.out
component, which performs random tests against the village card, the overall branch
coverage is 18.23% for the single function card. In the case of randomtestadventurer.out,
which attempts to check the adventurer card, overall branch coverage is 18.71%. When
comparing branch coverage to running the random tests on both cards, the overall branch
coverage is 22.43%. This gives an overall difference that indicates Assignment 3 has
31.65% branch coverage and assignment 4 has 22.43% branch coverage. While at a glance,
this may appear that random testing is providing less coverage, when considering the
fact that I've only tested 2 cards versus the 8 functions of assignment 3, more
investigation is required to determine the results. Because of this, I visually compared
the adventurer lines of code in the coverage results between the two assignements.
In assignment 3, the lines of adventurerEffect function are called an average of 4
times, with a few branches only being executed 25% or 75%. There are also two branches
that are not executed at all. In the case of assignment 4 and the use of testing
the adventurer card with automation, the average call for each line is around 700 times,
with branches previously skipped being executed 100%. The primary component that draws
my attention is to a branch that is called 0% of the time in both the unit tests as
well as the random tests. To me this indicates there is a flaw in the code that is
creating unreachable code that should be corrected or removed.

Outside of looking at branch and statement coverage, the aspects of random testing
that seem the most valuable to me is the fact that so many varying conditions
are being checked in such a small amount of time. In assignment 3 with unit tests,
I carefully crafted a few conditions for the player's hand and deck cards, but
with random testing, I am able to create thousands of potential possibilities
in even less time. This is particularly useful when looking at the position of
played or drawn cards in a given deck. Knowing that these are controlled by
integer arrays brings to the surface a priority of ensuring the functions will
handle their given purpose regardless of the position of the index in the array.
This is particularly useful in the edge cases where the card is at the 0 index
or at the top of the stack. Because of this availability in random testing,
it is clear that boundary testing is far exceeded the capabilities of unit
testing, as we are able to stretch the possible conditions  more quickly and
efficiently than we could in maual creation of unit tests.
