My unit tests (1 - 4) for updateCoins, gainCard, discardCard, and isGameOver didn't catch any bugs
I got 100% line coverage in those functions and they all returned the correct game state. I did however
begin to find my own bugs while testing the cards.
  The smithy card was the first card to be tested and I immediately caught my own bug I introduced by
asserting correct values after the function call.It was very helpful to have written the unit test before
I tested the cards so I had a much better understanding of what the smithy card did considering it called
two outside functions before returning.
  The adventurer card was the second card I tested. I had to stub out the adventurer function where I
removed all of the bugs I introduced to be able to call a clean version. This card was tough to test.
There are several different things that could happen in the function and the while loop particularly
makes it hard to assert that certain values will be present after the function call. The best I could
think of to do is to assert that the discard pile and the hand count have changed under appropriate
circumstances. The tests for the adventurer card pass when run against the original dominion code and
fail when run against the adventurer function I wrote when I introduced bugs. This is a great sign
the tests are in fact testing at least part of the function appropriately. 
