randomhistory.c

These were the previous results for the 4 unit and 4 card tests:
File 'dominion.c'
Lines executed:28.10% of 580
Branches executed:32.05% of 415
Taken at least once:21.45% of 415
Calls executed:21.00% of 100


*I ran all 8 tests from Assignment 3 and then ran 10 tests (Assignment 3+4)
Updated results after testing smithy card:
File 'dominion.c'
Lines executed:30.86% of 580
Branches executed:33.01% of 415
Taken at least once:22.65% of 415
Calls executed:22.00% of 100

randomtestcard.c (Smithy)
I reused some code from my card test in Assignment 3 to test if the number of cards in hand after playing
Smithy was correct. I ran 1000 tests and each time I filled the gamestate
with random bytes. I then called the Random() function to randomize the number of players, the deck
count, discard count, hand count, and played card count. At first my program kept continuously
segfaulting becuase I accidentally set the limit for number of players to greater than 4. 
All of the random tests failed, which is expected since I introduced a bug in Assignment 2 which causes
Smithy to draw an extra card. Regarding coverage, I was able to improve lines executed by almost 3%,
while lines executed, branches executed, branches taken at least once, and calls executed improved by a
slight margin. I improved this test by going further and testing if the deck count prior to playing Smithy was 3 cards more
than after playing Smithy. However, I could have improved coverage for this random test by using more functions 
such as playedCard() instead of cardEffect(). 

Updated results after testing adventurer card:
File 'dominion.c'
Lines executed:32.24% of 580
Branches executed:33.49% of 415
Taken at least once:24.34% of 415
Calls executed:23.00% of 100

randomtestadventurer.c
Once again, I reused some code from my card test in Assignment 3 to test if the handcount is correct
after playing Adventurer, to see if the number of Treasure cards increased by 2. Again, I ran 1000
tests and each time I filled the gamestate with random bytes. I then called the Random() function
to randomize the number of players, the deck count, discard count, hand count, and played card count.
All of the random tests passed, and did not catch the bug I introduced in Assignment 2. Regarding coverage,
almost all of the categories (lines executed, branches executed, etc) increased by a few percent which is
a promising sign. This means I executed more lines and branches, and more branches were taken at least once.
I randomized variables used by the cardAdventurer() function, which probably helped improve my coverage.
