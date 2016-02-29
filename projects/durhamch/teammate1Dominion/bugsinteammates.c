/*
 *
--------------------------------------
int adventurerCard()
Not updating handcount (discard)
Not updating playedCardCount (discard)
Not updating playedCard (discard)

SAMPLE OUTPUT FROM TEST:
    TEST FOR ADVENTURER FIRST CARD PLAYED
    Test 0: FAIL: HandCount: 10, Expected: 8
    Test 0: FAIL: playedCardCount: 0, Expected: 1
    Test 0: FAIL: playedCard: 0, Expected: 7
    Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0
    Test 0: FAIL: DiscardCount: 2, Expected: 3, ControlHandCount: 7, PostHandCount: 10, ControlDeckCount: 10, PostDeckCount: 5, ControlDiscardCount: 0, PostDiscardCount: 2

    TEST FOR DECKCOUNT 0 DISCARDCOUNT 0 test
    Test 0: FAIL: HandCount: 4, Expected: 3
    Test 0: FAIL: playedCardCount: 0, Expected: 1
    Test 0: FAIL: playedCard: 0, Expected: 7
    Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0

--------------------------------------
int smithyCard()
handPos is passed -- in discard
SAMPLE OUTPUT FROM TEST:
    TEST FOR MIXED DRAW CARDS DECKCOUNT 197 DISCARDCOUNT 73

