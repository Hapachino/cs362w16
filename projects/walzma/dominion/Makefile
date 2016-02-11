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

unittestresults.out: dominion.h rngs.h dominion_helpers.h dominion.o rngs.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	
	#unit test 1
	gcc -o unittest1 unittest1.c dominion.o rngs.o -g $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov unittest1.c -b >> unittestresults.out
	
	#unittest2
	gcc -o unittest2 unittest2.c dominion.o rngs.o -g $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov unittest2.c -b >> unittestresults.out
	
	#unittest3
	gcc -o unittest3 unittest3.c dominion.o rngs.o -g $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov unittest3.c -b >> unittestresults.out
	
	#unittest4
	gcc -o unittest4 unittest4.c dominion.o rngs.o -g $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov unittest4.c -b >> unittestresults.out
	
	#cardtest1
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o -g $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov cardtest1.c -b >> unittestresults.out
	
	#cardtest2
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o -g $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov cardtest2.c -b >> unittestresults.out
	
	#cardtest3
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o -g $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov cardtest3.c -b >> unittestresults.out
	
	#cardtest4
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o -g $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov cardtest4.c -b >> unittestresults.out
	
	#gcov dominion.c
	gcov dominion.c -b >> unittestresults.out


randomtestadventurer.out: dominion.h rngs.h dominion_helpers.h dominion.o rngs.o randomtestadventurer.c
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	
all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so randomtestadventurer *test1 *test2 *test3 *test4