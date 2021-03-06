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
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -c unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -c unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -c unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -c unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -c cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -c cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -c cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -c cardtest4.c -g dominion.o rngs.o $(CFLAGS)

cardtests: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	gcc -c -g cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o $(CFLAGS)

unittests: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o
	gcc -c -g unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o $(CFLAGS)

alltests: unittests cardtests
	gcc -o alltests -g unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults.out: alltests
	./alltests > unittestresults.out 2>&1
	gcov dominion.c -b >> unittestresults.out
	gcov dominion.c -f >> unittestresults.out

randomtest1.o: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtest1 -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtest2.o: randomtestcard.c dominion.o rngs.o
	gcc -o randomtest2 -g randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtests: randomtest1.o randomtest2.o
	./randomtest1 > randomtestadventurer.out 2>&1
	gcov dominion.c -b >> randomtestadventurer.out
	gcov dominion.c -f >> randomtestadventurer.out
	./randomtest2 > randomtestcard.out 2>&1
	gcov dominion.c -b >> randomtestcard.out
	gcov dominion.c -f >> randomtestcard.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
