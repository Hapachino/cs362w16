/*
Kyle Johnson
johnsky3
CS 362 W 16
2/14/16

Assignment 4 randomhistory.c writeup:

I began development by taking my unit test for the Village card (cardtest3.c) and worked on converting
it to a random test, as this card was easier to work with compared to the adventurer. To do this, I added a
randomized game state using the methodology shown in the lectures. Then I reviewed the tests I conducted for
the unit tests (players hand count, deck count, played card count) and randomized these where possible.  I 
did this by using a random amount for each players hand count, deck count, and discard count to ensure a wide
variety of game scenarios would be covered. Then I randomized the actual cards in each of these structures by
choosing a random number from the array of available cards and assigning it to the players decks, hands, and
discard piles.  I then made a copy of the random game state and then ran the rest of the test the same way I did
for the unit test assignment, except repeated 10,000 times in a loop to ensure sufficient coverage.  The first issue
I ran into was that the deck counts were running out of bounds after removing the discarded card from the total.
I fixed this by forcing the decks to have a minimum of 2 cards instead of 0.  The other problem was that the
output file was massive since it included all of my printf statements from the unit testing.  To solve this,
I rewrote my if statements to only print the test that caused an error instead of printing all PASSED and FAILED
lines.  I also added counter variables for each type of error so that the results could be summarized after all
10,000 tests had been run. 

Results summary from randomtestcard.out:  

-------------------------------------------
Results Summary (10,000 runs):
-------------------------------------------
Player hand count failures: 0
Player deck count failures: 0
Next player hand count failures: 0
Next player deck count failures: 0
Played card count failures: 0
Action point count failures: 10000
Victory card supply failures: 10000

File 'dominion.c'
Lines executed:22.78% of 575
Branches executed:25.18% of 417
Taken at least once:15.11% of 417
Calls executed:15.79% of 95
dominion.c:creating 'dominion.c.gcov'

The Action point count failures is expected since the bug I introduced reduces the amount of action
points by 1, so the test did work to find the bug.  The random testing also discovered the same bug
as in the unit test, where the number of estate cards changed when they should have remained the same 
for the smithy and village cards:
estate = 6, expected = 8
FAILED - supply count does not match

Overall, this was an improvement over assignment 3 unit test results, which had:

Results from gcov:
File 'dominion.c'
Lines executed:32.87% of 575
Branches executed:32.37% of 417
Taken at least once:23.74% of 417
Calls executed:25.26% of 95

Even though the unit test percentage was higher, that covered 8 distinct unit tests compared
to the results from a single random testing program for the village card.

I then moved on to the adventurer card and tried to take the same approach.  I kept the printf 
statements at first to allow me to see the actual values in the tests to make sure they were still working.
This revealed a problem right away where the player deck counts and hand counts were showing up as negative values.
To fix this I had play around with several options and eventually switched the way I was randomly selecting
cards. Instead of selecting from the available array, I had to use a random selection from floor(Random() * (treasure_map + 1)).

Another issue that remained was that the deck counts were not matching.  I tried to fix this by subtracting
the discarded amount from the expected deck amount since I did not have a good method of replicating the 
discarding of non-treasure cards from the deck used in the adventurer() function.  I was unable to get 
the deck count to work at the time of writing.  The other issue was that the played card count was always
equal to 0 instead of the expected 1.  I was unable to resolve this issue. Testing was done on the normal
dominion.c and dominion.h.

Results summary from randomtestadventurer.out:

-------------------------------------------
Results Summary (10,000 runs):
-------------------------------------------
Player hand count failures: 1485
Player deck count failures: 9723
Next player hand count failures: 0
Next player deck count failures: 0
Played card count failures: 10000
Victory card supply failures: 0

File 'dominion.c'
Lines executed:22.78% of 575
Branches executed:25.18% of 417
Taken at least once:15.11% of 417
Calls executed:15.79% of 95
dominion.c:creating 'dominion.c.gcov'

Coverage-wise, this was an improvement over the unit test results for the same reason as randomtestcard.c,
but the test oracle I wrote was not very useful otherwise.  Because I couldn't resolve the count
discrepancies, it means that I can't tell whether or not the 1,486 player hand count function errors were
due to a bug or my bad testing method. The mistake I made was relying too heavily on my unit test
to create the random tester.  Instead of piggybacking off of the unit test, I should have written a 
totally new function using a different testing method and better replicating the adventurer card results.

I had moved from my re factored versions of dominion.c and dominion.h to help debug my testing of
the adventurer card and fix the hand count error, but when I went back to my buggy versions, I got
a core dump error when there had not been one previously, even using the bugged versions.  I couldn't 
determine which change I made to my code led to this error, and assumed it was related to the buggy version 
of adventurer I had written. I continued to test on the unchanged versions of dominion.c and dominion.h to try 
and resolve the more pressing issues with the deck count discrepancies, whcih ended up taking the rest of my time.
The lesson I learned was not to try and save time by forcing an inferior testing method to work as it takes 
more time to debug than to just write a new program.  

*/

