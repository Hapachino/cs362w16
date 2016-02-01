CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g $(CFLAGS)
	
refactor.o: refactor.c rngs.o
	gcc -c -g -o refactor.o refactor.c $(CFLAGS)

playdom: dominion.o refactor.o playdom.c rngs.o
	gcc -o playdom playdom.c -g dominion.o refactor.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o refactor.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o refactor.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o refactor.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o refactor.o $(CFLAGS)
	
unittest3: unittest3.c dominion.o rngs.o refactor.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o refactor.o $(CFLAGS)
	
unittest4: unittest4.c dominion.o rngs.o refactor.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o refactor.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o refactor.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o refactor.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o refactor.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o refactor.o $(CFLAGS)
	
testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o refactor.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o refactor.o $(CFLAGS)

all: playdom player unittest1 unittest2 unittest3 unittest4

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
