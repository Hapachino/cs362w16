CFLAGS = -Wall -fpic -coverage -lm
TFLAGS = -fprofile-arcs -ftest-coverage

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc $(TFLAGS) -c dominion.c -g  $(CFLAGS)

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

unittest1: _unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g _unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: _unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g _unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: _unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g _unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: _unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g _unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: _cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g _cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: _cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g _cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest4: _cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g _cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestcard: _randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g _randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: _randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g _randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest4
	./unittest1 > unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestcard.out: randomtestcard
	./randomtestcard > randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer > randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest4 randomtestcard randomtestadventurer

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest4 randomtestcard randomtestadventurer *.gcov *.gcda *.gcno *.so *.out badTestDrawCard testDrawCard
