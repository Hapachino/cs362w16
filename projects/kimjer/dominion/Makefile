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

unittest4: dominion.o unittest4.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest4 unittest4.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

smithytest: dominion.o rngs.o cardFunctions.o smithytest.c
	gcc -o smithytest smithytest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

adventurertest: dominion.o rngs.o cardFunctions.o adventurertest.c
	gcc -o adventurertest adventurertest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

counciltest: dominion.o rngs.o cardFunctions.o counciltest.c
	gcc -o counciltest counciltest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

villagetest: dominion.o rngs.o cardFunctions.o villagetest.c
	gcc -o villagetest villagetest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

unittests: smithytest adventurertest unittest2 
	gcc -o smithytest smithytest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./smithytest &> unittestresult.out
	gcov -b smithytest.c >> unittestresult.out	
	cat smithytest.c.gcov >> unittestresult.out

	gcc -o unittest2 unittest2.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresult.out
	gcov -b unittest2.c >> unittestresult.out	
	cat unittest2.c.gcov >> unittestresult.out
	cat unittest2.c.gcov >> coverage.c

	gcc -o unittest1 unittest1.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresult.out
	gcov -b unittest1.c >> unittestresult.out	
	cat unittest1.c.gcov >> unittestresult.out
	cat unittest1.c.gcov >> coverage.c

	gcc -o unittest3 unittest3.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresult.out
	gcov -b unittest3.c >> unittestresult.out	
	cat unittest3.c.gcov >> unittestresult.out
	cat unittest3.c.gcov >> coverage.c

	# gcc -o adventurertest adventurertest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	# ./adventurertest >> unittestresult.out
	# gcov -b adventurertest.c >> unittestresult.out	
	# cat adventurertest.c.gcov >> unittestresult.out
	# cat adventurertest.c.gcov >> coverage.c

	gcc -o unittest4 unittest4.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresult.out
	gcov -b unittest4.c >> unittestresult.out
	cat unittest4.c.gcov >> unittestresult.out
	cat unittest4.c.gcov >> coverage.c

	gcc -o villagetest villagetest.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./villagetest >> unittestresult.out
	gcov -b villagetest.c >> unittestresult.out
	cat villagetest.c.gcov >> unittestresult.out
	cat villagetest.c.gcov >> coverage.c

	gcov -b dominion.c >> unittestresult.out	
	cat dominion.c.gcov >> unittestresult.out

	gcc -o randomtestcard randomtestcard.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./randomtestcard > randomtestcard.out

	gcov -b dominion.c >> randomtestcard.out

	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./randomtestadventurer > randomtestadventurer.out

	gcov -b dominion.c >> randomtestadventurer.out
	
randomtests: dominion.o cardFunctions.o rngs.o
	gcc -o randomtestcard.out randomtestcard.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	./randomtestcard.out >> randomhistory.c
	gcov -b randomtestcard.c >> randomhistory.c
	gcc -o randomtestcard randomtestcard.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o cardFunctions.o rngs.o $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out	
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o cardFunctions.o rngs.o interface.o

all: playdom player testDrawCard testBuyCard badTestDrawCard 

clean:
	rm -f *.gch *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so

cleanprogs: 
	rm -f unittest1 unittest2 unittest3 unittest4 smithytest randomtestcard villagetest randomtestadventurer