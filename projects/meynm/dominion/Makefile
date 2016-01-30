CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g $(CFLAGS)
	
refactor.o: refactor.c rngs.o
	gcc -c -g -o refactor.o refactor.c $(CFLAGS)

playdom: dominion.o refactor.o playdom.c rngs.o
	gcc -o playdom playdom.c -g dominion.o refactor.o rngs.o $(CFLAGS)

testBuyCard: unittest5.c dominion.o rngs.o refactor.o
	gcc -o testBuyCard -g unittest5.c dominion.o rngs.o refactor.o $(CFLAGS)
	
testShuffle: unittest2.c dominion.o rngs.o refactor.o
	gcc -o testShuffle -g unittest2.c dominion.o rngs.o refactor.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o refactor.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o refactor.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o refactor.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o refactor.o $(CFLAGS)
	
testGainCard: unittest3.c dominion.o rngs.o refactor.o
	gcc -o testGainCard -g unittest3.c dominion.o rngs.o refactor.o $(CFLAGS)
	
testFullDeckCount: unittest4.c dominion.o rngs.o refactor.o
	gcc -o testFullDeckCount -g unittest4.c dominion.o rngs.o refactor.o $(CFLAGS)

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

all: playdom player testDrawCard badTestDrawCard testBuyCard testShuffle testGainCard testFullDeckCount

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
