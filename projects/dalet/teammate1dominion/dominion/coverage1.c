/*
Matt Walz
CS 362 Assignment 3
coverage1.c

_____________________________________________________________________________________________________
Unit Tests:

1) discardCard() method

File 'unittest1.c'
Lines executed:73.47% of 196
Branches executed:100.00% of 92
Taken at least once:58.70% of 92
Calls executed:68.29% of 82
Creating 'unittest1.c.gcov'


2) gainCard() method

File 'unittest2.c'
Lines executed:79.63% of 108
Branches executed:100.00% of 44
Taken at least once:56.82% of 44
Calls executed:77.08% of 48
Creating 'unittest2.c.gcov'


3) drawCard() method

File 'unittest3.c'
Lines executed:70.11% of 87
Branches executed:100.00% of 44
Taken at least once:56.82% of 44
Calls executed:65.79% of 38
Creating 'unittest3.c.gcov'


4) isGameOver() method

File 'unittest4.c'
Lines executed:82.91% of 117
Branches executed:100.00% of 44
Taken at least once:54.55% of 44
Calls executed:83.33% of 66
Creating 'unittest4.c.gcov'


As you can see from the gcov results, the unit tests all had 100% branch coverage and greater than 70% line coverage. The missing lines in the line coverage were almost exclusively from printf() calls used in lieu of asserts.


_____________________________________________________________________________________________________
Card Tests:

1) Smithy

File 'cardtest1.c'
Lines executed:70.90% of 134
Branches executed:100.00% of 70
Taken at least once:57.14% of 70
Calls executed:60.66% of 61
Creating 'cardtest1.c.gcov'


2) Village

File 'cardtest2.c'
Lines executed:64.24% of 151
Branches executed:100.00% of 78
Taken at least once:56.41% of 78
Calls executed:59.70% of 67
Creating 'cardtest2.c.gcov'


3) Adventurer

File 'cardtest3.c'
Lines executed:74.73% of 91
Branches executed:80.00% of 60
Taken at least once:45.00% of 60
Calls executed:62.22% of 45
Creating 'cardtest3.c.gcov'


4) Remodel

File 'cardtest4.c'
Lines executed:68.53% of 197
Branches executed:98.21% of 112
Taken at least once:52.68% of 112
Calls executed:55.21% of 96
Creating 'cardtest4.c.gcov'


Again, we see very high branch coverage. In fact, branch coverage was greater than 98% for 3 of the card tests. The lone test with less than 98% branch coverage was Adventurer and looking at the .gcov file for the test one can see that the reason for this low branch coverage is that this test had a couple of (if - else if - else) loops in place of asserts, so a test would miss 2 out of 3 branches. Doing this a few times on a small program significantly hurts the coverage statistics.



_____________________________________________________________________________________________________
Dominion.c Coverage:

File 'dominion.c'
Lines executed:34.38% of 573
Branches executed:38.69% of 411
Taken at least once:25.30% of 411
Calls executed:23.40% of 94
Creating 'dominion.c.gcov'

You can see through the 8 unit tests we managed to get branch coverage of almost 40% and line coverage of close to 35%. When you consider that we only tested 4 action cards out of a possible 20 actions cards (20% of the action cards) it is actually fairly remarkable that we reached 35% line coverage. The additional coverage came from the game initialization function which was necessary to establish game situations on which to test the functions and card effects.

The area of the code which received the least amount of coverage was the end of turn and end of game functions. Because the unit tests all tested functions and/or card effects which took place during one player's turn, the functions and methods invoked when player turns end and pass to the next player (e.g. clean-up of played cards piles, revising game states, etc.) were not covered by the tests. Additionally, the functions and methods invoked by an end of game scenario, such as scoring and determining the winning player, were never tested. Again, this was due to the fact that the functions and methods tested all impacted only a single player's turn.

In later iterations of the test suite it is imperative that these sections of the code are tested.