Janel Buckingham
CS 362
Assignment 3 bugs1.c

testGainCard() found no bugs
testDiscardCard() found no bugs
testIsGameOver() found no bugs
testBuyCard() found no bugs


testSmithy(): FAIL number in hand is 8 instead of 7.
    This could have been triggered by the bug I introduced that draws an extra card in an off-by-one error.
testSmithy(): FAIL number in discards is 0, was previously 0. Should have incremented.
    This would be caused by my bug that trashed a discard instead of adding it to discards.
testSmithy(): FAIL number in deckCount is 1, was previously 5. Should have decremented by 2.
    This was probably caused by the bug that draws an extra card.
testSmithy(): FAIL playedCardCount is 0, was previously 0. Should have incremented by 1.
    This would be caused by my bug that trashed a discard instead of adding it to discards.
testSmithy(): FAIL number in hand is 1 instead of 3.
    Uncertain cause, but it appears that playSmithy isn't drawing any cards in this case.
testSmithy(): FAIL number in discards is 0, was previously 0. Should have incremented.
testSmithy(): FAIL playedCardCount is 0, was previously 0. Should have incremented by 1.
    Both of these have already been shown to not be working.
testSmithy(): FAIL playedCardCount is 7, was previously 7. Should have incremented by 1.
    Uncertain cause, but it appears that playSmithy didn't do anything for this set of tests.
    
testAdventurer(): FAIL expected number of cards were not discarded to correct player's discard.  Expected 3, actual value: 2