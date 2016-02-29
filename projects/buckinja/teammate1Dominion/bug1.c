/*  Paul Zotz
    CS 362 Winter 2016
    Assignment 3 - bugs found

    unittest1.c, unittest2.c, unittest3.c, unittest4.c No bugs found in any unit tests.

    cardtest1.c: (smithyCard)
        smithy1:    Player does not receive 3 cards; testing for an additional 2 cards (3 - discarded smithy)
                    results in failure.

    cardtest2.c: (adventurerCard)
        adventurer1:    Stacking the deck with kingdom cards and checking for two added treasure fails -
                        more than the last two cards are treasure. This is due to the bug I introduced,
                        which causes the function to draw one more treasure card than intended.


    cardtest3.c: (villageCard):
        village1:   Player does not receive 2 actions due to bug introduced in assignment 2.

    cardtest4.c: (greatHallCard):
        greatHall1:     Testing for an incremented action counter fails here due to the bug I introduced in assignment 2.
                        Almost exactly the same bug as village1 - expected number of actions is off by 1. In hindsight,
                        introducing a bug to my refactored mineCard() (or refactoring more interesting cards in general)
                        would have made for a more interesting card to test.
