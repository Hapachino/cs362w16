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


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

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


clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out

.PHONY: unittests

unittests: dominion.o rngs.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults.out: unittests
	./cardtest1 >> unittestresults.out
	gcov -a -b dominion.c >> unittestresults.out
	
	./cardtest2 >> unittestresults.out
	gcov -a -b dominion.c >> unittestresults.out
	
	./cardtest3 >> unittestresults.out
	gcov -a -b dominion.c >> unittestresults.out
	
	./cardtest4 >> unittestresults.out
	gcov -a -b dominion.c >> unittestresults.out
	
	./unittest1 >> unittestresults.out
	gcov -a -b dominion.c >> unittestresults.out
	
	./unittest2 >> unittestresults.out
	gcov -a -b dominion.c >> unittestresults.out
	
	./unittest3 >> unittestresults.out
	gcov -a -b dominion.c >> unittestresults.out
	
	./unittest4 >> unittestresults.out
	gcov -a -b dominion.c >> unittestresults.out