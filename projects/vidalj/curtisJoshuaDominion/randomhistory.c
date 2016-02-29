randomhistory.c

Before random testing the results from unit testing on the adventurer card where:

Coverage:
adventurer unit test showed 27.73% of 577 lines executed. 
adventurer unit test showed 36.21% of 417 branches executed.
adventurer unit test showed 18.71% of 417 branches taken at least once.
adventurer unit test showed 20.00% of 95 calls executed.   

64% of the blocks in playAdventurer function were executed.

Several branches in the playAdventurer function were never taken such as the branch that
shuffles the players deck if it has less than 1 card.

Bugs:
Hand count is 9 when it should be 7. 
The other players hand count and deck count are also altered.

The unit test implemented a tests on the current players handCount, the current players
deckCount, the other players handCount, and the other players deck count.

Before inserting random variables, I ran the unit test on a loop 1000 times, just to get a baseline
of what bugs were appearing. Quite expectedly the results were:
- Current player handCount passed: 0
- Current player deckCount passed: 1000
- Other player handCount passed: 0
- Other player deckCount passed: 0

The Random Test:
The first random variable I tested were handCount and deckCount for both the curren and other player.
These variables were randomly set to between 0 and the max for each game which is 500.

I initially ran the test 1000 times just to compare to the unit test. The results were
- Current player handCount passed: 11
- Current player deckCount passed: 994
- Other player handCount passed: 0
- Other player deckCount passed: 0

The overall coverage improved by a few percentage points. 
First adventurer random test showed 31.72% of 577 lines executed. 
First adventurer random test showed 38.13% of 417 branches executed.
First adventurer random test showed 21.34% of 417 branches taken at least once.
First adventurer random test showed 22.11% of 95 calls executed.

This also led to 100% of the blocks in play adventurer being executed.

I then set the handCount and deckCount for the current player to be from between -1 and 501.
When I ran the test three times, but this time it was not able to finish (in each of these
instances it appeared that the dominion.c entered an infinite loop. In each of the tests that
resulted in an infinite loop the handCount variable for the current player had been sent to 501. 

I then ran the test with handCount and deckCount for the current player to be from between -1 and 499.
The results were
- Current player handCount passed: 1048
- Current player deckCount passed: 99181
- Other player handCount passed: 0
- Other player deckCount passed: 0

The handCount variable was negative 202 times. The deckHand was negative 227 times.

The coverage was almost completely the same as when when the handCount and deckCount were set to 0 to 
500, with a few tenths of a percent higher branch and call execution.
Second adventurer random test showed 31.89% of 577 lines executed. 
Second adventurer random test showed 38.13% of 417 branches executed.
Second adventurer random test showed 21.58% of 417 branches taken at least once.
Second adventurer random test showed 22.11% of 95 calls executed.


randomtestcard.c tests the smithy card

Before random testing the results from unit testing on the smithy card where:

Coverage:
smithy unit test showed 23.92% of 577 lines executed. 
smithy unit test showed 25.66% of 417 branches executed.
smithy unit test showed 15.35% of 417 branches taken at least once.
smithy unit test showed 18.95% of 95 calls executed.  

One bug had been found in the smithy card affecting the hand count and deck count.

With the random test

- Current player handCount passed: 185
- Current player deckCount passed: 2029
- Other player handCount passed: 100000
- Other player deckCount passed: 100000

smithy unit test showed 26.17% of 577 lines executed. 
smithy unit test showed 26.62% of 417 branches executed.
smithy unit test showed 16.55% of 417 branches taken at least once.
smithy unit test showed 20.00% of 95 calls executed.  

The random test found the same bug affecting the hand count and deck count.
