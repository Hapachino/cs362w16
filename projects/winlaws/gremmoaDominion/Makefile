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

unittest1: unittest1SW.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1SW.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2SW.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2SW.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3SW.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3SW.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4SW.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4SW.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1SW.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1SW.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2SW.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2SW.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3SW.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3SW.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4SW.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4SW.c dominion.o rngs.o $(CFLAGS)

getRandomGameState.o: getRandomGameStateSW.h getRandomGameStateSW.c dominion.o rngs.o
	gcc -c getRandomGameStateSW.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard.out: randomtestcardSW.c getRandomGameState.o dominion.o rngs.o
	gcc -o randomtestcard -g  randomtestcardSW.c getRandomGameState.o dominion.o rngs.o $(CFLAGS)
	./randomtestcard > randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

randomtestadventurer.out: randomtestadventurerSW.c getRandomGameState.o dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurerSW.c getRandomGameState.o dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer > randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

unittestresults.out: dominion.o rngs.o unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer *.gcov *.gcda *.gcno *.so




