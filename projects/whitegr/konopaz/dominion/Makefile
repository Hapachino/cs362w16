CFLAGS= -std=c99 -Wall -fpic -coverage -lm

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

all: playdom player testDrawCard testBuyCard badTestDrawCard

#Targets for Assignment 3
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.c rngs.c $(CFLAGS)
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.c rngs.c $(CFLAGS)
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.c rngs.c $(CFLAGS)
unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.c rngs.c $(CFLAGS)
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.c rngs.c $(CFLAGS)
cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.c rngs.c $(CFLAGS)
cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.c rngs.c $(CFLAGS)
cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.c rngs.c $(CFLAGS)

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o interface.o
	#unittest1
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 unittest1.c -g dominion.c rngs.o interface.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#unittest2
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 unittest2.c -g dominion.c rngs.o interface.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#unittest3
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 unittest3.c -g dominion.c rngs.o interface.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#unittest4
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 unittest4.c -g dominion.c rngs.o interface.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#cardtest1
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c -g dominion.c rngs.o interface.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#cardtest2
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c -g dominion.c rngs.o interface.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#cardtest3
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c -g dominion.c rngs.o interface.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#cardtest4
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c -g dominion.c rngs.o interface.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

randomtestadventurer: randomtestadventurer.c dominion.c rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.c rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out

randomtestcard: randomtestcard.c dominion.c rngs.o
	gcc -o randomtestcard randomtestcard.c -g dominion.c rngs.o $(CFLAGS)

randomtestcard.out: randomtestcard
	./randomtestcard >> randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so testSuite badTestDrawCard testDrawCard
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out unittestresult.out randomtestadventurer randomtestadventurer.out randomtestcard randomtestcard.out

gw_randomtestadventurer.out: gw_randomtestadventurer.c interface.o dominion.o rngs.o
	gcc -o gw_randomtestadventurer -g  gw_randomtestadventurer.c interface.o dominion.o rngs.o $(CFLAGS)
	./gw_randomtestadventurer >> gw_randomtestadventurer.out
	gcov gw_randomtestadventurer >> gw_randomtestadventurer.out
	gcov -a -b dominion.c >> gw_randomtestadventurer.out
	cat dominion.c.gcov >> gw_randomtestadventurer.out

gw_randomtestcardsmithy.out: gw_randomtestcardsmithy.c interface.o dominion.o rngs.o
	gcc -o gw_randomtestcardsmithy -g  gw_randomtestcardsmithy.c interface.o dominion.o rngs.o $(CFLAGS)
	./gw_randomtestcardsmithy >> gw_randomtestcardsmithy.out
	gcov gw_randomtestcardsmithy >> gw_randomtestcardsmithy.out
	gcov -a -b dominion.c >> gw_randomtestcardsmithy.out
	cat dominion.c.gcov >> gw_randomtestcardsmithy.out



