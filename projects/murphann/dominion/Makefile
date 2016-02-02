CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c -Wall -fprofile-arcs -ftest-coverage -std=c99 rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c -Wall -fprofile-arcs -ftest-coverage -std=c99 dominion.c -g  $(CFLAGS)

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
	gcc -o cardTest4 cardTest4.c -Wall -fprofile-arcs -ftest-coverage -std=c99 -g	dominion.o rngs.o	 $(CFLAGS)

CardTest3: cardTest3.c dominion.o rngs.o
	gcc -o cardTest3 cardTest3.c -Wall -fprofile-arcs -ftest-coverage -std=c99 -g	dominion.o rngs.o	 $(CFLAGS)

CardTest2: cardTest2.c dominion.o rngs.o
	gcc -o cardTest2 cardTest2.c -Wall -fprofile-arcs -ftest-coverage -std=c99 -g	dominion.o rngs.o	 $(CFLAGS)

CardTest1: cardTest1.c dominion.o rngs.o
	gcc -o cardTest1 cardTest1.c -Wall -fprofile-arcs -ftest-coverage -std=c99 -g	dominion.o rngs.o	 $(CFLAGS)

unitTest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -Wall -fprofile-arcs -ftest-coverage -std=c99 -g	dominion.o rngs.o	 $(CFLAGS)

unitTest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -Wall -fprofile-arcs -ftest-coverage -std=c99 -g	dominion.o rngs.o	 $(CFLAGS)

unitTest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -Wall -fprofile-arcs -ftest-coverage -std=c99 -g	dominion.o rngs.o	 $(CFLAGS)

unitTest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -Wall -fprofile-arcs -ftest-coverage -std=c99 -g	dominion.o rngs.o	 $(CFLAGS)

unittestresult.out: CardTest1 CardTest2 CardTest3 CardTest4 unitTest4 unitTest3 unitTest2 unitTest1
	./unittest1 > unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./cardTest1 >> unittestresult.out
	./cardTest2 >> unittestresult.out
	./cardTest3 >> unittestresult.out
	./cardTest4 >> unittestresult.out
	gcov unittest1 unittest2 unittest3 unittest4 >> unittestresult.out
	gcov cardTest1 cardTest2 cardTest3 cardTest4 >> unittestresult.out
	cat unittest*.gcov >> unittestresult.out
	cat cardTest*.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
