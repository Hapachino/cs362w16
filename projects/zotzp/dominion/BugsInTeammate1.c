/*  Paul Zotz
    CS 362 Winter 2016
    Assignment 5 - teammate 1 bug report (Jeannine Amm)


Tests consisted of a game state initialized with two players and then copied to a test game state before each test.
The modified test game state was then checked against the original game state to check for discrepancies between
expected and actual attributes.

unittest1.c - all tests passed
unittest2.c - all tests passed
unittest3.c - all tests passed
unittest4.c - all tests passed
cardtest1.c - all tests passed

cardtest2.c:
    playAdventurer():
    BUGS:
    playAdventurer1:    Cards not discarded as expected. Stacking the deck to ensure a predictable discard amount
                        results in one less card discarded than expected.
    TEST OUTPUT:
    ----------------- Testing Card: adventurer ----------------
    TEST 1: current player receives 2 treasure cards
    TEST 2: deck is empty - discard must be shuffled and added
    TEST 3: non-treasure cards drawn added to discard
    TEST 3 failed
    expected: 2 actual: 1
    TEST 5: cards came from own deck
    TEST 5: no state change for other players
    TEST 6: no change to kingdom or victory card piles


cardtest3.c - all tests passed
cardtest4.c - all tests passed

*/
