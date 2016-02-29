I hooked my test code up to my two partners code and this 
below is what I found in regards to bugs. Within each directory are my tests applied to 
my teammates code. I had to make minor cosmetic changes to the tests and I added my tests to the make code.

konopaz- (Reverted dominion.c to assignment 2 submittal)

Adventurer Card:
Identified bug when shuffling. The test does identify what the bug is but indicates an error occurd when shuffling.

Smithy Card:
The introduced bug was caught by checking the hand count value.

tannerbe- (Reverted dominion.c to assignment 2 submittal)

Smithy Card:
My Unit Test identifies a bug in the hand count after playing the smithy card.

Adventurer Card:
My unit tests identifies a bug in the amount of cards discarded. 

Changes to teammates make file:
gw_randomtestadventurer.out: gw_randomtestadventurer.c interface.o dominion.o rngs.o
	gcc -o gw_randomtestadventurer -g  gw_randomtestadventurer.c interface.o dominion.o rngs.o $(CFLAGS)
	./gw_randomtestadventurer >> gw_randomtestadventurer.out
	gcov gw_randomtestadventurer >> gw_randomtestadventurer.out
	gcov -a -b dominion.c >> gw_randomtestadventurer.out
	cat dominion.c.gcov >> gw_randomtestadventurer.out

gw_randomtestcardsmithy.out: gw_randomtestcardsmithy.c interface.o dominion.o rngs.o
	gcc -o gw_randomtestcardsmithy -g  gw_randomtestcardsmithy.c interface.o dominion.o rngs.o $(CFLAGS)
	./gw_randomtestcardsmithy >> gw_randomtestcardsmithy.out
	gcov gw_randomtestcardsmithy >> gw_randomtestcardsmithy.out
	gcov -a -b dominion.c >> gw_randomtestcardsmithy.out
	cat dominion.c.gcov >> gw_randomtestcardsmithy.out
