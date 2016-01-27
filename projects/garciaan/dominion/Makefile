CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testFunctions.o: testFunctions.h testFunctions.c dominion.o rngs.o
	gcc -c testFunctions.c -g $(CFLAGS)

unittest1: dominion.o testFunctions.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

unittest2: dominion.o testFunctions.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

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

unittests: unittest1 unittest2

rununittests: unittest1
	./unittest1 &> myunittestsresults.out

all: playdom player unittest1 unittest2 testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test unittest1 unittest2 player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so

remake: 
	make clean
	make unittest2
