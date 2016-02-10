//Megan Fanning

//Write up and check in the development of your random testers, 
//including improvements in coverage and effort to check the correctness of your specification, as randomhistory.c.

Adventurer
-----------------------------------
Original Coverage
File dominion.c
Lines executed:3.57% of 561
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94

implications:
The segfault which occured made this test virtually unusable, this code needs be corrected to allow better testing.
 The limited coverage within unitTest itself indicates that the test coverage is less than optimal it may require a different method of dealing with failed tests so that the entire program doesn't stop when a error is found.
 Additionally branch coverage is poor inplying that conditional statements maybe incorrect.
Bug:segfault
cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]];
the card drawn is equal to a negative number which causes a segfault.

Current Coverage
File 'dominion.c'
Lines executed:5.18% of 560
Branches executed:4.82% of 415
Taken at least once:3.86% of 415
Calls executed:5.32% of 94

The new coverage increases the number of lines executed but the branch coverage isn't as good.

Baron
------------------------------------------
File 'dominion.c'
Lines executed:5.18% of 560
Branches executed:4.82% of 415
Taken at least once:3.86% of 415
Calls executed:5.32% of 94

Village
---------------------------------------
Orginal Coverage
File dominion.c
Lines executed:3.57% of 561
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94
Creating 'dominion.c.gcov'
bug:segfault.
The segfault is occuring in the discardCard function on line 1259, the current player value is very high (in the hundreds of thousands) and played card count is a negative number, either.
just prior to calling the village card the whoseTurn field is very high (hundreds of thousands) and the played card count is negative. This indicates that it was a failure to initialize these value with "reasonable" values for the purposes for random testing.

Current Coverage
File 'dominion.c'
Lines executed:5.18% of 560
Branches executed:4.82% of 415
Taken at least once:3.86% of 415
Calls executed:5.32% of 94
Creating 'dominion.c.gcov'


