CFLAGS = -lm -Wall -fpic -coverage
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

unittest1: dominion.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./unittest1 &> unittestresult.out

unittest2: dominion.o unittest2.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest2 unittest2.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	
unittest3: dominion.o unittest3.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest3 unittest3.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

smithytest: dominion.o rngs.o cardFunctions.o smithytest.c
	gcc -o smithytest smithytest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

adventurertest: dominion.o rngs.o cardFunctions.o adventurertest.c
	gcc -o adventurertest adventurertest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

unittests: smithytest adventurertest unittest2
	gcc -o smithytest smithytest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./smithytest &> unittestresult.out
	gcov smithytest.c >> unittestresult.out	
	#cat smithytest.c.gcov >> unittestresult.out

	gcc -o unittest2 unittest2.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresult.out
	gcov unittest2.c >> unittestresult.out	
	#cat unittest2.c.gcov >> unittestresult.out

	gcc -o unittest1 unittest1.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresult.out
	gcov unittest1.c >> unittestresult.out	
	#cat unittest1.c.gcov >> unittestresult.out

	gcc -o unittest3 unittest3.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresult.out
	gcov unittest3.c >> unittestresult.out	
	#cat unittest1.c.gcov >> unittestresult.out

	gcc -o adventurertest adventurertest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./adventurertest >> unittestresult.out
	gcov adventurertest.c >> unittestresult.out	
	#cat unittest1.c.gcov >> unittestresult.out

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out	
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o cardFunctions.o rngs.o interface.o

all: playdom player testDrawCard testBuyCard badTestDrawCard 

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
