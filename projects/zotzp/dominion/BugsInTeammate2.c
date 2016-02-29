/*  Paul Zotz
    CS 362 Winter 2016
    Assignment 5 - teammate 2 bug report (Janel Buckingham)


Unit & card tests consisted of a game state initialized with two players and then copied to a test game state before each test.
The modified test game state was then checked against the original game state to check for discrepancies between
expected and actual attributes. Random tests involved a completely randomized game state, with necessary attributes initialized
randomly as needed.

unittest1.c - all tests passed
unittest2.c - all tests passed
unittest3.c - all tests passed
unittest4.c - all tests passed

cardtest1.c:
    playSmithy():
    BUGS:
    playSmithy1: smithy draws one more card than expected

    TEST OUTPUT:
    ----------------- Testing Card: smithy ----------------
    TEST 1: current player receives 3 cards
    TEST 1 failed
    expected: 7 actual 8
    TEST 2: cards come from own pile
    TEST 3: no state change for other players
    TEST 4: no change to kingdom or victory card piles



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
randomtestadventurer.c:
    playAdventurer():
    BUGS:
        see cardtest2.c, playAdventurer1;
    TEST OUTPUT:
    Random testing adventurer:

     >>>>> TEST 1 <<<<<
    Adventurer returned successfully - return value 0, expected 0
    Current player received 2 treasures - received 2, expected 2
    Cards added to discard - discard pile 16, expected 17
    Failure: discard not incremented properly
    No state change to other player:
         Other player deck count - actual 72, expected 72
         Other player hand count - actual 190, expected 190
         Other player discard count - actual 0, expected 0
    Testing for identical game states...
    Failure: game states are not identical.

*/
