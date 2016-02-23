Myles Chatman
CS 362
Assignment 4
2/14/2016

Running the tests:
1. make all
2. gcov randomtestadventurer or randomtestcard
3. make clean

The biggest change I made to this assignment was actually generating a random test rather than
a simple test. Each gamestate is truly different for each test so that each execution of the program is different from the previous. 

I chose to use the steward cars as the randomtestcard for variety.

These are the results I received when running tests for the randomtestadventurer and randomtestcard:

File ‘randomtestadventurer.c’
Lines executed:97.37% of 38
randomtestadventurer.c:creating ‘randomtestadventurer.c.gcov’

File ‘randomtestcard.c’
Lines executed:89.36% of 47
randomtestcard.c:creating ‘randomtestcard.c.gcov’

I have ran the tests multiple times and received different coverage results each time. I also increased the number of tests higher
than 2000 and the results weren’t drastically a large difference. 2000 seems to appropriate to check if certain functions work correctly.

randomtestadventurer:
Most tests that I have run were above 95%. I did receive a 100% coverage when I didn’t use the if/else conditional and this conditional 
is only used simply to test the quantity of success and failures. Without the conditional, each line executes on every test but I feel satisfied 
to have a high percentage of coverage for this test.

The interesting thing about this test is that there were runtime errors during the test. The tests are not always 100% successful. 
The bug I introduced in the previous assignment was caught when the assertion failed. Without the randomizer in tests, I always received
an assertion error on the 519th tests due to lack of an update on the preCount of handCount and postCount of handCount.

randomtestcard:
Similar to the randomtestadventurer, theres a switch statement with three different possibilities based on the test. There is also a if/else 
conditional which is why the coverage is a bit lower than testing the adventurer card.

Executing this program many of times didn’t show any runtime errors even with random generated tests.
