CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

refactor.o: dominion.h dominion_helpers.h cardFunctions.c
	gcc -g -c cardFunctions.c -o refactor.o $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o refactor.o
	gcc -o dominion.o -c dominion.c -g refactor.o $(CFLAGS)

playdom: dominion.o playdom.c refactor.o
	gcc -o playdom playdom.c -g dominion.o rngs.o refactor.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o refactor.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o refactor.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o refactor.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o refactor.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o refactor.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o refactor.o $(CFLAGS)

testAll: dominion.o testSuite.c refactor.o
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o refactor.o $(CFLAGS)

interface.o: interface.h interface.c refactor.o
	gcc -c interface.c -g refactor.o -o interface.o $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c cardFunctions.c  dominion.h interface.o
	gcc -o player player.c cardFunctions.c -g interface.o dominion.o rngs.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
