CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f -R *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer *.dSYM unittestresults.out randomtestcard.out randomtestadventurer.out allMyTests.out

default: unittestresults.out

unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4
	echo "Results for running Assignment 3 unit tests:" > unittestresults.out
	
	echo "cardtest1.c" >> unittestresults.out	
	./cardtest1 >> unittestresults.out
	
	echo "cardtest2.c" >> unittestresults.out	
	./cardtest2 >> unittestresults.out
	
	echo "cardtest3.c" >> unittestresults.out	
	./cardtest3 >> unittestresults.out
	
	echo "cardtest4.c" >> unittestresults.out	
	./cardtest4 >> unittestresults.out
	
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
randomtestcard.out: randomtestcard
	echo "Results for running Assignment 4 random unit test for smithy card:" > randomtestcard.out

	echo "randomtestcard.c" >> randomtestcard.out	
	./randomtestcard >> randomtestcard.out

	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

randomtestadventurer.out: randomtestadventurer
	echo "Results for running Assignment 4 random unit test for adventurer card:" > randomtestadventurer.out

	echo "randomtestadventurer.c" >> randomtestadventurer.out	
	./randomtestadventurer >> randomtestadventurer.out

	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

allMyTests.out: cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer
	echo "Results for running all my tests:" > allMyTests.out

	echo "Results for running Assignment 3 unit tests:" >> allMyTests.out
	
	echo "cardtest1.c" >> allMyTests.out	
	./cardtest1 >> allMyTests.out
	
	echo "cardtest2.c" >> allMyTests.out	
	./cardtest2 >> allMyTests.out
	
	echo "cardtest3.c" >> allMyTests.out	
	./cardtest3 >> allMyTests.out
	
	echo "cardtest4.c" >> allMyTests.out	
	./cardtest4 >> allMyTests.out

	echo "Results for running Assignment 4 random unit test for smithy card:" >> allMyTests.out

	echo "randomtestcard.c" >> allMyTests.out	
	./randomtestcard >> allMyTests.out

	echo "Results for running Assignment 4 random unit test for adventurer card:" >> allMyTests.out

	echo "randomtestadventurer.c" >> allMyTests.out	
	./randomtestadventurer >> allMyTests.out

	gcov -b dominion.c >> allMyTests.out
	cat dominion.c.gcov >> allMyTests.out

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestcard: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)