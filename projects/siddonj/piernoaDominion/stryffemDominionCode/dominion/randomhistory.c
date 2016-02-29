/*	Author: 	Martin Stryffeler
	Filename:	randomhistory.c
	Date:		2/14/2016

Random Tests Development

Adventurer

For the adventurer random test, the first step I took was to examine the inputs that the card takes.
The cardEffect() function takes a few choices, a hand position, a reference to a bonus, and the game state.
Looking through the actual function code, I see that the choices and bonus are not used at all in the adventurer
card effect. The main input that we are concerned with is the game state, which is fairly complex. So I examined
each member variable that makes up the game state to determine which are significant to the adventurer card.

The inputs that I decided to randomize are:
	number of players
	current player
	number of actions remaining
	hand count
	cards in the player's hand
	deck count
	cards in the player's deck
	discard count
	cards in the player's discard pile

This was easy to accomplish with a simple procedural function which starts with a standard initialized game state
and then randomizes the variables within ranges permitted by the game.

For the oracle, I was able to reuse some code from the unit tests of adventurer. The oracle for the adventurer
random test is a copied control state. The adventurer cardEffect is not called on the control state, but the intended
effects of the card are applied. The adventurer cardEffect is called with the test game state, and then it is compared
to the control state.

The same bug that I introduced in assignment 2 and found in assignment 3 triggers a failure in every iteration of 
the random test. The hand count is one too many and the deck + discard count is one too few. This is due to one 
too many coins being drawn.

Once the adventurer random test was complete, the same process was repeated for the village card random test.


Village

First, a randomized game state is generated. Next, the state is copied. Then, the cardEffect function is called. Finally,
the state is compared to the control state. If the state differs from what is expected based on the rules of the card, 
an error report is generated with the expected and actual values, and the inputs that led to the error.

The village card random test also found a bug very quickly. When the card is played, the number of actions is set to
the wrong amount. The test catches this bug in each iteration except when the random inputs produce a correct result
by coincidence. This is caused by the bug that I introduced which causes the number of actions to be set in relation to
the number of coins rather than the previous number of actions.


Coverage

Alone the random village test acheived only 21.65% line coverage and 23.36% branch coverage, with only 15.59% of branches
taken at least once for the overall dominion file. The village function has 100% coverage, however. The adventurer had 24.91% line coverage and 25.66% branch coverage, 
with 19.42% taken at least once. Though the overall dominion coverage is small, the random tests acheived what my unit 
tests did not with adventurer. The adventurer function has 100% line coverage, and 100% branch coverage, with every branch
taken at least 50 times (with 5000 iterations run). This is compared with the 64% execution coverage of the adventurer
unit test. 

My unit tests provided 36.77% line coverage and 43% branch coverage, with 33% of branches taken at least once.
Together with the random tests, they achieve 41.24% line coverage, 44.84% branch coverage with 37.41% taken at least once.
The call coverage is also improved from 25% to 27.37%. The random tests definitely contribute to the total coverage, and 
the adventurer function now has 100% coverage as well.

*/
