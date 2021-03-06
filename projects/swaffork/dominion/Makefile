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

unittest1: unittest1.c dominion.o rngs.o testhelper.o
	gcc -o unittest1 -g unittest1.c testhelper.o dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o testhelper.o
	gcc -o unittest2 -g unittest2.c testhelper.o dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o testhelper.o
	gcc -o unittest3 -g unittest3.c testhelper.o dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o testhelper.o
	gcc -o unittest4 -g unittest4.c testhelper.o dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o testhelper.o
	gcc -o cardtest1 -g cardtest1.c testhelper.o dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o testhelper.o
	gcc -o cardtest2 -g cardtest2.c testhelper.o dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o testhelper.o
	gcc -o cardtest3 -g cardtest3.c testhelper.o dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o testhelper.o
	gcc -o cardtest4 -g cardtest4.c testhelper.o dominion.o rngs.o $(CFLAGS)

testhelper.o: testhelper.h testhelper.c
	gcc -c testhelper.c -g $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randomtestcard.out: randomtestcard.c dominion.o rngs.o testhelper.o
	echo "*** Results for randomtestcard.c ***" >> randomtestcard.out
	gcc -o randomtestcard -g randomtestcard.c testhelper.o dominion.o rngs.o $(CFLAGS)
	./randomtestcard &>> randomtestcard.out
	gcov dominion.c >> randomtestcard.out
	cat dominion.c >> randomtestcard.out
	gcov randomtestcard.c >> randomtestcard.out
	cat randomtestcard.c.gcov >> randomtestcard.out

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o testhelper.o
	echo "*** Results for randomtestadventurer.c ***" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c testhelper.o dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer &>> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c >> randomtestadventurer.out
	gcov randomtestadventurer.c >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out

runtests: cardtest1 cardtest2 
	./unittest1 &> unittestresult.out
	./unittest2 &>> unittestresult.out
	./unittest3 &>> unittestresult.out
	./unittest4 &>> unittestresult.out
	./cardtest1 &>> unittestresult.out
	./cardtest2 &>> unittestresult.out
	./cardtest3 &>> unittestresult.out
	./cardtest4 &>> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	gcov unittest1.c >> unittestresult.out
	cat unittest1.c.gcov >> unittestresult.out
	gcov unittest2.c >> unittestresult.out
	cat unittest2.c.gcov >> unittestresult.out
	gcov unittest3.c >> unittestresult.out
	cat unittest3.c.gcov >> unittestresult.out
	gcov unittest4.c >> unittestresult.out
	cat unittest4.c.gcov >> unittestresult.out
	gcov cardtest1.c >> unittestresult.out
	cat cardtest1.c.gcov >> unittestresult.out
	gcov cardtest2.c >> unittestresult.out
	cat cardtest2.c.gcov >> unittestresult.out
	gcov cardtest3.c >> unittestresult.out
	cat cardtest3.c.gcov >> unittestresult.out
	gcov cardtest4.c >> unittestresult.out
	cat cardtest4.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestcard.out randomtestadventurer.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer *.gcov *.gcda *.gcno *.so *.out
