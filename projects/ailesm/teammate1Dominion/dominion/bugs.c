/*/
Michael Byrne
byrnemi@onid
CS 362 SE2
02-02-2016


Bug Report

unittest1 (getCost), unittest2 (updateCoins), unittest3 (handCard), unittest4 (isGameOver): All functions
passed randomized testing with near complete coverage. Of the four functions, *getCost* is the only
one to have a failure mode, which was tested successfully with bad input.

As expected in testing the *smithy* card playSmithy() failed to fail correctly when provided with bad input.
This was an artificial bug  added during refactoring. The function returns 1 on every outcome.

During testing, I discovered an unanticipated bug in the *salvager* card. When the player chooses the first
card in their hand, with an index 0, the program interprets that as a non-choice, rather than the card
with index 0. This occurs on average one or two times per 20 game run. This is a significant failure rate.

The bug I introduced into playAdventurer turned out to be not a bug at all. I had removed the check for a
size 0 deck, which would have shuffled the deck, anticipating that it would break, but the shuffled and
check turned out to be redundant because it's done in the drawCard function. Unexpected but interesting.




