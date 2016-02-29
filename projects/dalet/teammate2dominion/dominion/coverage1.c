/*
Rishi Bhandarkar
CS 362 - coverage1.c
*/

Statement coverage: 30.95%
Branch coverage: 32.37%

In my testing, I am calling on functions in the Dominion code directly instead of executing an entire game. For instance,
none of the end game functions involved in summing victory points and determining a winner and are ever called from my tests.
Therefore, this is a reasonable amount of statement and branch coverage to expect from my test suite. 

When we look specifically at the card function we invoke in the testing suite, we see that the coverage is much better. The
council_room, village, and smithy functions all achieve 100% coverage, while the adventurer function has 67% coverage. For the
adventurer card, my test case never calls on the function when the game state has an empty deck, so the lines of code reponsible
for shuffling the discard pile and refilling the deck are never executed.

For the unit tests, scoreFor has 31% coverage. The is partly due to a bug in the code, and partly due to the gamestate we used to test. 
That section is broken up into 3 for loops to sum victory points in the players hand, deck, and discard pile. The hand loop executes fine,
but the deck loop has a bug that loops for every card in the discard, not the deck. There are no cards in the discard when we call this
function, which is why we skip 2 of the 3 loops and have only 31% coverage.

drawCard has 36% coverage. This is becasue 2/3 of the code here involves shuffing the discard pile and creating a deck in the case that the deck
is currently empty. In our test cases, the deck always had at least 1 card in it, so we never had to execute this code.

discardCard achieved 88% coverage, and gainCard achieved 100% coverage. Both of those numbers are good numbers for our tests.
