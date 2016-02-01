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
    This would be caused by the off-by-one error I introduced when discarding the temp hand.
    
    
testCutpurse(): FAIL player 1's hand count is 5 instead of 4.
testCutpurse(): FAIL player 2's hand count is 5 instead of 4.
testCutpurse(): FAIL player 3's hand count is 5 instead of 4.
testCutpurse(): FAIL player 1's discard count did not increment.
testCutpurse(): FAIL player 2's discard count did not increment.
testCutpurse(): FAIL player 3's discard count did not increment.
testCutpurse(): FAIL player 1 has 3 coppers in their hand instead of expected 2.
testCutpurse(): FAIL player 2 has 3 coppers in their hand instead of expected 2.
testCutpurse(): FAIL player 3 has 3 coppers in their hand instead of expected 2.
testCutpurse(): FAIL current player's hand count changed from 5 to 4.
testCutpurse(): FAIL other player's hand count did not decrement.
testCutpurse(): FAIL other player's discard count did not increment.
testCutpurse(): FAIL current player's hand count changed from 5 to 3.
testCutpurse(): FAIL kingdom cards supply has been altered.
testCutpurse(): FAIL victory card supply has been altered.
testCutpurse(): FAIL victory card supply has been altered.
testCutpurse(): FAIL victory card supply has been altered.
    The bug that I introduced in this function was to swap i and j in this line:
    discardCard(j, i, state, 0);
    This change would cause the player number to be swapped with the hand position of the card to be discarded.  This produced wild behavior in the tests, changing values incorrectly where they should have remained the same, and did not change values when they should have.  
    
    
testRemodel(): NOTE--Using cards of EQUAL VALUE, should be a legal move.
testRemodel(): FAIL produced an error.
    I believe this is a bug (not introduced by me) in remodel.  The lines:
          if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
		{
		  return -1;
		}
    are not in keeping with the dominion card for remodel which would allow for the cost of choice2 +2 to be <= cost of choice 1.  As such, the function only works currently if the cost of choice 2 is at least 2 more than the cost of choice one.
    
testRemodel(): FAIL current player's hand count didn't decrement correctly. Was 5, is now 5.
testRemodel(): FAIL current player's discard count was 0, is now 0, but should have incremented by 2.
testRemodel(): FAIL kingdom cards supply has not been altered.
    These test cases were not able to succeed because of the previously mentioned bug.
    
testRemodel(): NOTE--Exchanging for max value choice2.
testRemodel(): FAIL current player's hand count didn't decrement correctly. Was 5, is now 2.
testRemodel(): FAIL current player's discard count was 0, is now 0, but should have incremented by 2.
    In this case, the above bug was NOT triggered, so the tests caught two different bugs... the discarded cards are not discarding correctly and more cards are being removed from the player's hand than should be.  The second bug was introduced by me by deleting a "break" after the first deletion takes place.
    
testRemodel(): NOTE--Exchanging for more than max value choice2 -- shouldn't be a legal move.
testRemodel(): FAIL didn't produce an error.
    The first bug in remodel that I mentioned caused this error as well.  Without the bug, a player should not be able to purchase a card of this cost, but it was allowed.  The following two FAIL tests result because the function was allowed to run instead of producing an error.
    
testRemodel(): FAIL current player's hand count changed.
testRemodel(): FAIL victory card supply has been altered.
testRemodel(): NOTE--Exchanging for value +1 for choice2, should alter victory deck.
testRemodel(): FAIL produced an error.
    Likewise, this case should have been allowed to run, but was prevented by the same bug, causing the following three tests to fail as well.

testRemodel(): FAIL current player's hand count didn't decrement correctly. Was 5, is now 5.
testRemodel(): FAIL current player's discard count was 0, is now 0, but should have incremented by 2.
testRemodel(): FAIL victory card supply has not been altered.
