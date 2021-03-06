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

unittestresults.out:  dominion.h rngs.h dominion_helpers.h dominion.o rngs.o unitTest1.c unitTest2.c unitTest3.c unitTest4.c cardTest1.c cardTest2.c cardTest3.c cardTest4.c
	#unitTest1
	gcc -o unitTest1 unitTest1.c dominion.o rngs.o -g $(CFLAGS)
	./unitTest1
	gcov dominion.c >> unittestresults.out
	gcov unitTest1.c >> unittestresults.out
	cat unitTest1.c.gcov >> unittestresults.out
	#unitTest2
	gcc -o unitTest2 unitTest2.c dominion.o rngs.o -g $(CFLAGS)
	./unitTest2
	gcov unitTest2.c >> unittestresults.out
	cat unitTest2.c.gcov >> unittestresults.out
	#unitTest3
	gcc -o unitTest3 unitTest3.c dominion.o rngs.o -g $(CFLAGS)
	./unitTest3
	gcov unitTest3.c >> unittestresults.out
	cat unitTest3.c.gcov >> unittestresults.out
	#unitTest4
	gcc -o unitTest4 unitTest4.c dominion.o rngs.o -g $(CFLAGS)
	./unitTest4
	gcov unitTest4.c >> unittestresults.out
	cat unitTest4.c.gcov >> unittestresults.out
	#cardTest1
	gcc -o cardTest1 cardTest1.c dominion.o rngs.o -g $(CFLAGS)
	./cardTest1
	gcov cardTest1.c >> unittestresults.out
	cat cardTest1.c.gcov >> unittestresults.out
	#cardTest2
	gcc -o cardTest2 cardTest2.c dominion.o rngs.o -g $(CFLAGS)
	./cardTest2
	gcov cardTest2.c >> unittestresults.out
	cat cardTest2.c.gcov >> unittestresults.out
	#cardTest3
	gcc -o cardTest3 cardTest3.c dominion.o rngs.o -g $(CFLAGS)
	./cardTest3
	gcov cardTest3.c >> unittestresults.out
	cat cardTest3.c.gcov >> unittestresults.out
	#cardTest4
	gcc -o cardTest4 cardTest4.c dominion.o rngs.o -g $(CFLAGS)
	./cardTest4
	gcov cardTest4.c >> unittestresults.out
	cat cardTest4.c.gcov >> unittestresults.out

randomtestcard: dominion.h rngs.h dominion_helpers.h dominion.o rngs.o
	gcc -o randomtestcard randomtestcard.c dominion.o rngs.o -g $(CFLAGS)
	./randomtestcard
	gcov -b dominion.c >> randomtestcard.out
	gcov -b randomtestcard.c >> randomtestcard.out
	cat randomtestcard.c.gcov >> randomtestcard.out

randomtestadventurer: dominion.h rngs.h dominion_helpers.h dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o -g $(CFLAGS)
	./randomtestadventurer
	#gcov dominion.c >> randomtestadventurer.out
	gcov -b randomtestadventurer.c >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out

all: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard randomtestadventurer

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
