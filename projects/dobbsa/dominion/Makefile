CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testadv: dominion.o rngs.o cardtest1.c
	gcc -o testadv cardtest1.c -g dominion.o rngs.o $(CFLAGS)

testcouncil: dominion.o rngs.o cardtest2.c
	gcc -o testcouncil cardtest2.c -g dominion.o rngs.o $(CFLAGS)

testsmithy: dominion.o rngs.o cardtest3.c
	gcc -o testsmithy cardtest3.c -g dominion.o rngs.o $(CFLAGS)

testvillage: dominion.o rngs.o cardtest4.c
	gcc -o testvillage cardtest4.c -g dominion.o rngs.o $(CFLAGS)

testbuy: dominion.o rngs.o unittest1.c
	gcc -o testbuy unittest1.c -g dominion.o rngs.o $(CFLAGS)

testdiscard: dominion.o rngs.o unittest2.c
	gcc -o testdiscard unittest2.c -g dominion.o rngs.o $(CFLAGS)

testgameover: dominion.o rngs.o unittest3.c
	gcc -o testgameover unittest3.c -g dominion.o rngs.o $(CFLAGS)

testscore: dominion.o rngs.o unittest4.c
	gcc -o testscore unittest4.c -g dominion.o rngs.o $(CFLAGS)

unittestresult.out: testadv testcouncil testsmithy testvillage testbuy testdiscard testgameover testscore
	./testadv > unittestresult.out
	./testcouncil >> unittestresult.out
	./testsmithy >> unittestresult.out
	./testvillage >> unittestresult.out
	./testbuy >> unittestresult.out
	./testdiscard >> unittestresult.out
	./testgameover >> unittestresult.out
	./testscore >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

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
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
