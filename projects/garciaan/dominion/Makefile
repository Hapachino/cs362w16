CFLAGS = -Wall -fpic -coverage -lm
DOMINION = dominion.c
DOMINION1 = teammate1dominion.c
DOMINION2 = teammate2dominion.c

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h $(DOMINION) rngs.o
	gcc -c $(DOMINION) -o dominion.o -g  $(CFLAGS)

teammate1dominion.o: teammate1dominion.h $(DOMINION1) rngs.o
	gcc -c $(DOMINION1) -o teammate1dominion.o -g $(CFLAGS)

teammate2dominion.o: teammate2dominion.h $(DOMINION2) rngs.o
	gcc -c $(DOMINION2) -o teammate2dominion.o -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testFunctions.o: testFunctions.h testFunctions.c dominion.o rngs.o
	gcc -c testFunctions.c -g $(CFLAGS)

testplay: dominion.o testplay.c testFunctions.o
	gcc -o testplay testplay.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

unittest1: dominion.o testFunctions.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

unittest2: dominion.o testFunctions.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

unittest3: dominion.o testFunctions.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

unittest4: dominion.o testFunctions.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

cardtest1: dominion.o testFunctions.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

cardtest2: dominion.o testFunctions.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

cardtest3: dominion.o testFunctions.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

cardtest4: dominion.o testFunctions.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

randomtestadventurer: dominion.o testFunctions.o randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

randomtestcard: dominion.o testFunctions.o randomtestcard.c
	gcc -o randomtestcard randomtestcard.c -g dominion.o rngs.o testFunctions.o $(CFLAGS)

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

printtests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1
	./unittest2
	./unittest3
	./unittest4
	./cardtest1
	./cardtest2
	./cardtest3
	./cardtest4

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittests: unittest1 unittest2 unittest3 unittest4

cardtests: cardtest1 cardtest2 cardtest3 cardtest4

teammate1: teammate1dominion.o testFunctions.o teammate1testsuite.c
	gcc -o testteammate1 teammate1testsuite.c -g teammate1dominion.o rngs.o testFunctions.o $(CFLAGS)

teammate2: teammate2dominion.o testFunctions.o teammate2testsuite.c
	gcc -o testteammate2 teammate2testsuite.c -g teammate2dominion.o rngs.o     testFunctions.o $(CFLAGS)

printrandomtests: randomtestadventurer randomtestcard
	./randomtestadventurer
	./randomtestcard

unittestresults.out: unittests cardtests
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

randomtestcard.out: randomtestcard
	./randomtestcard &> randomtestcardresults.out
	gcov -b dominion.c >> randomtestcardresults.out

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer &> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out

all: playdom player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard player player.exe testInit testInit.exe *.out *.gcov *.gcda *.gcno *.so

remake: 
	make clean
	make randomtestcard
