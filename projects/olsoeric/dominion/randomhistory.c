/*************
 * Eric Olson
 * Assignment #4 
 * Examination of random testing of 2 card functions 
 *************/

Random testers were produced for the Adventurer card, and the Great Hall card.  They can be run
using the commands 'make randomtestadventurer.out' & 'make randomtestcard.out' respectively.
Individual results outlined below.  General coverage is appended to the output files, with
21.45%, and 21.11% coverage for Adventurer and Great Hall respectively (24.44% coverage if both
test sets are run before coverage pulled)  This coverage is lessmeaningful as it looks at dominion.c 
as a whole, as only 2 functions were the target of testing.


/////Adventurer/////
  I produced a random tester that initializes a new game, and puts together a random size/content
for hand, deck and discard piles.  It then ensures the player has an adventurer card and plays it.
The before and after state of the gameState objects are compared to ensure correct functionality.
Non affected states are checked for no change, and 2 new treasure cards in hand, as well as 1
played card, and 2 cards pulled from deck/discard are all checked.  Again there are two bugs, the 
first is that the check for treasure cards currently ignores Gold, instead checks for silver twice.  
Secondly the function doesn't handle the situation where there are not two treasure cards present in 
deck/discard to draw.  This is compounded by not considering gold cards as treasure.

  The coverage for my unit tests were 100%, with 1 coverage conditon missed.  This remains the same,
100% of statements tested, with 1 the only branch condition missed being the second check for silver:

if (cardtype == copper || cardtype == silver || cardtype == silver)

  Since the second check for silver will never return true (due to short circuting after the first
check for silver), reaching 100% branch conditional coverage is impossible, however every branch was
executed.

/////Great Hall/////
  Similiar to Adventurer this random tester initializes a game and then adds a random size/content
hand, deck and discard.  It makes sure the player has a Great Hall card, and then plays it.  Here
again every component of the game state is compared pre/post card play, and all results are checked
for correct functionality.  No changes where none expected, 1 additional card drawn, 1 played, 1 new
action, and 1 fewer card in deck/discard.  No errors were found with this testing.

  This card was not previously tested so no prior coverage data is available.  This particular card has 
few statements and no branchs, so 100% statement & branch coverage was trivially met.  That's not to say
that more complex functionality wasn't executed during the imbeded function calls (shuffling, and draw
card for example).
