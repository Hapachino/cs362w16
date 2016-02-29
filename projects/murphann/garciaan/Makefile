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

CardTest4: cardTest4.c dominion.o rngs.o
	gcc -o cardTest4 cardTest4.c -g	dominion.o rngs.o	 $(CFLAGS)

CardTest3: cardTest3.c dominion.o rngs.o
	gcc -o cardTest3 cardTest3.c -g	dominion.o rngs.o	 $(CFLAGS)

CardTest2: cardTest2.c dominion.o rngs.o
	gcc -o cardTest2 cardTest2.c -g	dominion.o rngs.o	 $(CFLAGS)

CardTest1: cardTest1.c dominion.o rngs.o
	gcc -o cardTest1 cardTest1.c -g	dominion.o rngs.o	 $(CFLAGS)

unitTest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g	dominion.o rngs.o	 $(CFLAGS)

unitTest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g	dominion.o rngs.o	 $(CFLAGS)

unitTest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g	dominion.o rngs.o	 $(CFLAGS)

unitTest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g	dominion.o rngs.o	 $(CFLAGS)

randomtestcard.out: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard randomtestcard.c -g dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)

random.out: randomtestadventurer.out randomtestcard.out
	./randomtestadventurer > random.out
	./randomtestcard >> random.out

unittestresults.out: CardTest1 CardTest2 CardTest3 CardTest4 unitTest4 unitTest3 unitTest2 unitTest1
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardTest1 >> unittestresults.out
	./cardTest2 >> unittestresults.out
	./cardTest3 >> unittestresults.out
	./cardTest4 >> unittestresults.out
	gcov unittest1 unittest2 unittest3 unittest4 dominion.c >> unittestresults.out
	gcov cardTest1 cardTest2 cardTest3 cardTest4 dominion.c >> unittestresults.out
	cat unittest*.gcov >> unittestresults.out
	cat cardTest*.gcov >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
