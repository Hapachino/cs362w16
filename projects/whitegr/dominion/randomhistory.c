Summary: I liked this project much more than assignment 3. I wasn't as overwelmed with getting ALL the coding
done. For this assignment I reworked my test code from assignment 3 removing bugs in the test code
and enhanced the randomness by running the tests 2000+ times. Both card tests use randomized cards and game states. The unit tests themselves check the
basic functioning of the card such as bounding conditions; the functioning of the card piles; and the state of of the game itself.
Each function also has a fairly detailed print out of the game state to help possibly identify any issues that come up during random testing
Also the make file has an improved way of producing the gcov outputs than previously. Now everything is in one file!:

randomtestadventurer.out: randomtestadventurer.c interface.o dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c interface.o dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov randomtestadventurer >> randomtestadventurer.out
	gcov -a -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard.out: randomtestcard.c interface.o dominion.o rngs.o
	gcc -o randomtestcard -g  randomtestcard.c interface.o dominion.o rngs.o $(CFLAGS)
	./randomtestcard >> randomtestcard.out
	gcov randomtestcard >> randomtestcard.out
	gcov -a -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

Adventurer Card:
function adventurerCard called 2000 times and returned 100% blocks and executed 94%
The non executed block is for the shuffle function when the players deck runs out. Below is a second version of my unit test with extra code to test status with a deck that needs to be shuffled
function adventurerCard called 2000 returned 100% blocks executed 100% it achieves a 100% code coverage. However I don't do any special test for shuffling since that really should be its own unit test.

Smithy Card:
function smithyCard called 4000 returned 100% blocks executed 100%
This function is fairly easy to completely test. I could have gone further to test functions that smithy relies on but I thought that would be best for specific function tests.
