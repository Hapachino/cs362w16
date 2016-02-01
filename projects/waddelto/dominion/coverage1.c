Todd Waddell
CS 362 W16 400
Assignment 3

For Assignment 3, my testing executed 38.14% of dominion.c
Branches executed were 46.93%
Branches taken at least once were 32.63%
Calls executed were 32.63%.
Looking at the aggregate statistics, I think this is pretty good coverage
considering that I didn't write a comprehensive test suite for all of
dominion.c  (But, you'll be the judge of that.)

Here are the functions (not cards that I tested) and their coverage results:
1) Shuffle: 
    Called 57504 times, returned 100% blocks executed 100%

2) BuyCard: Called 2000 times returned 100%, blocks executed 76%
    We checked supply count values with equal frequency 50% per branch. 
    We checked phase correctness and sufficient funds.
    We should have checked setting numBuys to 0, but ran out of time.
    We should have checked not enough money, but ran out of time.

3) UpdateCoins:
    Called 26,001 times, 100% blocks executed 100%.  
    As mentioned in the bug1.c report, the problem we uncovered with
    updateCoins was not in the function itself, but in other functions that
    improperly recorded bonus coins as coins in play.  Thus when
    updateCoins was called and sets state->coins = 0 in preparation for
    calculating treasure in hand, then it reset and lost coins granted    through treasure cards.

4) fullDeckCount
    Called 2999 returned 100% blocks executed 100%
    We have fairly light coverage at the borders.  Often, we're at 99% for
    one branch and 1% for the alternate.  Future testing should deepen
    border coverage.

Cards:
1) Smithy:
    Called 2999, returned 100% blocks executed 100%
    We have broader branch coverage here at 75%/25%.
    Looking at the secondary call to discardCard, we have 12499 calls
    returned 100% blocks executed 88%.
    We're missing a nuanced case in discardCard when we only have one card
    in hand.

2) Adventurer:
    3000 calls, returned 100%, blocks executed 92%.
    Since we had tested shuffle in a separate unittest, we did not send any
    cases where a shuffle was necessary.  In a full test suite, we would do
    that to check for unanticipated interactions.  The omission here was
    soley due to time constraints.
    
    Everything else in Adventurer received at least a moderate number of iterations.

3) Minion:
    Because Minion is part of the cardEffect function, we don't have gcov
    breakout aggregate data for this subroutine. Line data tells us that we
    sent 1000 calls and achieved broad coverage, with the following
    exceptions.
    We didn't present any cases where neither choice 1 or 2 were selected.
    Nor did we present any chases where both were selected. Similarly, we
    didn't present any cases where any of the players should have discarded
    but didn't have enough cards in hand to qualify. These should
    be added in future testing

4) Sea Hag
    As with Minion, Sea Hag is not broken out into her own function.  So we
    don't have aggreate coverage information for this subroutine.
    However, from the line data, we can say that we achieved 100% block
    coverage for 2000 subroutine calls.
