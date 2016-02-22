CFLAGS = -Wall -fpic  -fprofile-arcs -ftest-coverage  -lm

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

loop:
	while sleep 5; do make clean; sleep 1; make tests; sleep 1; make runtests; done;

unittestresults.out:
	make clean; make tests; make runtests;

tests: cardtest4.c cardtest3.c cardtest2.c cardtest1.c unittest4.c unittest3.c unittest2.c unittest1.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

runtests:
	rm -f unittestresult.out
	./unittest1 >> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

ap:
	make clean; make advtest; gcov -b dominion.c; ./randomtestadventurer

ap2:
	make clean
	make smtest
	gcov -b dominion.c
	./randomtestcard

ap3:
	rm -f randomtest.out
	make clean
	make smtest
	./randomtestcard >> randomtest.out
	gcov -b dominion.c >> randomtest.out
	cat dominion.c.gcov >> randomtest.out

randomtestcard.out:
	rm -f randomtestcard.out
	make clean
	make smtest
	./randomtestcard >> randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

smtest: randomtestcard.c dominion.h dominion.o rngs.o
	gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)


advtest: randomtestadventurer.c dominion.h dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

runadvtest:
	rm -f randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

both:
	make clean
	make advtest
	make smtest
	rm -f randomtestcard.out
	rm -f randomtestadventurer.out
	./randomtestcard >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out


randomtestadventurer.out:
	make clean; make advtest; make runadvtest;

testDrawCards: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unitTest1

clean:
	rm -f *.o playdom.exe randomtestcard.out randomtestcard randomtestadventurer.out randomtestadventurer playdom test.exe test player testDrawCard cardtest1 cardtest2 cardtest3 cardtest4 badTestDrawCard unittest1 unittest2 unittest3 unittest4 player.exe testInit testInit.exe  *.gcov *.gcda *.gcno *.so
	rm -rf *.dSYM
