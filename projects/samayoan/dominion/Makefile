CFLAGS = -Wall -w -fpic -coverage -lm

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "Result for running tests" > tests.out

	echo "unittest1.c:" >> tests.out
	gcc -o unittest1 rngs.c dominion.c unittest1.c $(CFLAGS)
	./unittest1 >> tests.out
	gcov dominion.c >> tests.out

	echo "unittest2.c:" >> tests.out
	gcc -o unittest2 rngs.c dominion.c unittest2.c $(CFLAGS)
	./unittest2 >> tests.out
	gcov dominion.c >> tests.out

	echo "unittest3.c:" >> tests.out
	gcc -o unittest3 rngs.c dominion.c unittest3.c $(CFLAGS)
	./unittest3 >> tests.out
	gcov dominion.c >> tests.out

	echo "unittest4.c:" >> tests.out
	gcc -o unittest4 rngs.c dominion.c unittest4.c $(CFLAGS)
	./unittest4 >> tests.out
	gcov dominion.c >> tests.out

	echo "cardtest1.c:" >> tests.out
	gcc -o cardtest1 rngs.c dominion.c cardtest1.c $(CFLAGS)
	./cardtest1 >> tests.out
	gcov dominion.c >> tests.out

	echo "cardtest2.c:" >> tests.out
	gcc -o cardtest2 rngs.c dominion.c cardtest2.c $(CFLAGS)
	./cardtest2 >> tests.out
	gcov dominion.c >> tests.out

	echo "cardtest3.c:" >> tests.out
	gcc -o cardtest3 rngs.c dominion.c cardtest3.c $(CFLAGS)
	echo "NOTE: These tests take a while to run because I try to randomize the cards in the hand."
	./cardtest3 >> tests.out
	gcov dominion.c >> tests.out

	echo "cardtest4.c:" >> tests.out
	gcc -o cardtest4 rngs.c dominion.c cardtest4.c $(CFLAGS)
	./cardtest4 >> tests.out
	gcov dominion.c >> tests.out

	echo "-- See tests.out for test pass/fail status --"

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

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
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *~ *.out
