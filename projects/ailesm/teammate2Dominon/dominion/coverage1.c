/*
   Eric Anderson
   CS362 Assignment 3
   01/30/2016
   Note: use 'make unittestresults.out' to create unittestresults.out
*/
/*
OVERALL
File 'dominion.c'
Lines executed:34.30% of 653
Branches executed:36.04% of 419
Taken at least once:28.64% of 419
No calls
dominion.c:creating 'dominion.c.gcov'

Overall coverage is at ~34%, given the number of cards and actions I haven't written 
test cases for, this low coverage is to be expected.  I can increase the coverage by 
adding more tests to each existing test case and by adding more test cases.

UNIT/CARD TESTS
unittest1: FullDeckCount

File 'unittest1.c'
Lines executed:89.66% of 58
Branches executed:100.00% of 28
Taken at least once:89.29% of 28
No calls
unittest1.c:creating 'unittest1.c.gcov'

The coverage % of 89.66% looks good, There are missing lines, but these 
are all either comments or I "quieted" printf statements. In looking at 
the dominion coverage , I find that the fullDeckCount function has been 
completely covered.  My test passed here so this suggests that this function 
works as expected.


unittest2: GameOver

File 'unittest2.c'
Lines executed:76.92% of 117
Branches executed:100.00% of 50
Taken at least once:76.00% of 50
No calls
unittest2.c:creating 'unittest2.c.gcov'

The coverage % is 76.92%. Like the previous test, this really is 100% 
coverage but because of quieting down things, several braches were not taken. 
The dominion coverage also suggests that I have covered the function completely, 
however in this case the test fails.

The issue looks to be a descrepency between the expected supply count and what we got back. 
This could be that the state being passed to the function has an issue (we need 
to test all the functions above this, or I have an error in my test, in which case 
debugging of my test is needed.)


unittest3: playCard

File 'unittest3.c'
Lines executed:81.40% of 43
Branches executed:88.89% of 18
Taken at least once:72.22% of 18
No calls
unittest3.c:creating 'unittest3.c.gcov'


The coverage is almost complete. and the tests passed. The function also appears to 
be well exercsed in dominion.c.  I believe this one is tested well and functions as 
expected.


unittest4: UpdateCoins

File 'unittest4.c'
Lines executed:83.67% of 49
Branches executed:100.00% of 20
Taken at least once:80.00% of 20
No calls
unittest4.c:creating 'unittest4.c.gcov'

The coverage is 83.67% (again because I turned off degug and Noisy_test). All 
nodes and branches are covered, with the highest amount of coverage of any 
test within dominion.c. The oracle behaves as expected.


cardtest1: Steward

File 'cardtest1.c'
Lines executed:73.10% of 197
Branches executed:100.00% of 70
Taken at least once:71.43% of 70
No calls
cardtest1.c:creating 'cardtest1.c.gcov'

The code coverage is high but the test cases failed.  It appears that there 
is something wrong with both the coins addition and the discard.  The 
discard was not well covered (only cover 1 time) and should be an additional test case.


cardtest2: Smithy

File 'cardtest2.c'
Lines executed:73.27% of 101
Branches executed:100.00% of 32
Taken at least once:65.62% of 32
No calls
cardtest2.c:creating 'cardtest2.c.gcov'

This test also failed.  It appears that there is something wrong with the handcount.  
The coverage seems pretty good but I need to write more testing around this to better
determine what is the issue.

cardtest3: Cut Purse

File 'cardtest3.c'
Lines executed:90.00% of 120
Branches executed:100.00% of 38
Taken at least once:84.21% of 38
No calls
cardtest3.c:creating 'cardtest3.c.gcov'

This test failed the handcount test.  THis area  was well covered with 125,000 passes.  
I believe the test coverage is good. But, the discrepancy is in the 
state.hand[][] variable. Somehow the cardEffect() function appears to be 
changing the hand more than the steward switch case does...
This function is a good candidate for further debugging.

cardtest4: Adventurer

File 'cardtest4.c'
Lines executed:68.99% of 129
Branches executed:84.00% of 50
Taken at least once:50.00% of 50
No calls
cardtest4.c:creating 'cardtest4.c.gcov'

This test also fails.  THis function was also well covered and the lines well executed.
There appears to be two issues with this.  The first  error I get is with the 2 
additional cards, the secondissue is with the treasure cards.  Further testing is needed
in both areas to better determine what is happening.

*/