/*
 Robert Jackson
CS362 2/14/16

To run the tests simply type make random it will autimatically run 500k tests and output the information in three files


Smithy Card:
The majority of the set of for testing smithy comes with setting a random state for the decks.
They were set like this: Each player’s deck  size is randomized and is filled with one of the cards chosen at random.
Then their discards and hands are filled similarly.  This was done also by checking the decks printout in the verbose
mode to make sure that the decks, discard, and hand are filled randomly.

 Additionally there is a 30% probability assigned to the deck being empty.

Smithy’s specification is that it draws two cards from the deck, and discards the current card in the hand pos. I
 randomized the hand position of the adventurer card and established checks to make sure that this hand position was
 turned to -1. Simultaneously I made sure that the hand count increased by the 2 cards, which is chanced against the
 decrease in the deck.

 The test then runs through 500k iterations. Counts the number of tests failed on each run, and returns the maximum
 number of failed tests. It did find the bug introduced. It may have found another,  that sometimes results in a false
 positive test. I would have expected it to fail 100% of the time instead it doesn’t.

 Adventurer Card:

 The majority of the set of for testing adventurer comes with setting a random state for the decks.

 They were set like this: Each player’s deck is filled with one of the cards chosen at random that was not a treasure
 card. Then their discards and hands are filled similarly.  This was done also by checking the decks printout in the
 verbose mode to make sure that the decks, discard, and hand are filled randomly.

 In the actual test function, the decks are again randomly selected to either put two coins (minimum needed for the
 function to do something other than return -1. )  and either then top of the deck or the bottom. This way it can
 later be counted.

Depending on which side they are on, the discard is either affected or not.
Additionally there is a 20% probability assigned to the deck being empty, or the discard being set to empty.

 Adventurer’s specification is that it draws cards from the deck, until two coin/treasure cards are obtained. The
 test is primarily designed to check in the discard depending on whether or not the coins are at the bottom or at
 the top, or distributed somewhere in the deck.


 It runs checks for the following:

 If deck count is 0:
It checks to make sure the shuffle functions fires by making sure the discard is added to the deck as per the
 instructions in the adventurer card.

If deck count has cards:
It checks that the hand counts increase by two regardless of where the two coins are in the deck. It checks then also
to make sure the cards drawn that are not cards, are subsequently discarded
The test runs through 500k iterations. It counts the number of tests failed on each run, and returns the maximum
number of failed tests. It did find the bug introduced.

 I’m a little suspicious of the  gcov for the following:
10234574:  671:    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 99% (fallthrough)
branch  1 taken 1%
branch  2 taken 99% (fallthrough)
branch  3 taken 1%
branch  4 taken 1% (fallthrough)
branch  5 taken 99%

It would seem to suggest that it’s fell through 99% of the time until gold, but I know that the random functions are
capable of placing copper, and silver. I have verified it visually in the deck compositions.

 * */