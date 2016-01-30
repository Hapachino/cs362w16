CFLAGS = -lm
#-Wall -fpic -coverage -lm
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

cardFunctions.o: cardFunctions.c cardFunctions.h
	gcc -c cardFunctions.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o cardFunctions.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o 
	gcc -o playdom playdom.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o cardFunctions.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o cardFunctions.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o cardFunctions.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: dominion.o unittest1.c 
	gcc -o unittest1 unittest1.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

unittest2: dominion.o unittest2.c 
	gcc -o unittest2 unittest2.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o cardFunctions.o rngs.o interface.o

all: playdom player testDrawCard testBuyCard badTestDrawCard 

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
