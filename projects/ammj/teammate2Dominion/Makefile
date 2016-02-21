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
	
testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittest.o: unittest.h unittest.c
	gcc -c unittest.c -g  $(CFLAGS)
	
unittest1: dominion.o unittest1.c unittest.o rngs.o
	gcc -o unittest1 unittest1.c -g  dominion.o rngs.o unittest.o $(CFLAGS)
	
unittest2: dominion.o unittest2.c unittest.o rngs.o
	gcc -o unittest2 unittest2.c -g  dominion.o rngs.o unittest.o $(CFLAGS)
	
unittest3: dominion.o unittest3.c unittest.o rngs.o
	gcc -o unittest3 unittest3.c -g  dominion.o rngs.o unittest.o $(CFLAGS)

unittest4: dominion.o unittest4.c unittest.o rngs.o
	gcc -o unittest4 unittest4.c -g  dominion.o rngs.o unittest.o $(CFLAGS)
	
cardtest1: dominion.o cardtest1.c unittest.o rngs.o
	gcc -o cardtest1 cardtest1.c -g  dominion.o rngs.o unittest.o $(CFLAGS)

cardtest2: dominion.o cardtest2.c unittest.o rngs.o
	gcc -o cardtest2 cardtest2.c -g  dominion.o rngs.o unittest.o $(CFLAGS)

cardtest3: dominion.o cardtest3.c unittest.o rngs.o
	gcc -o cardtest3 cardtest3.c -g  dominion.o rngs.o unittest.o $(CFLAGS)

cardtest4: dominion.o cardtest4.c unittest.o rngs.o
	gcc -o cardtest4 cardtest4.c -g  dominion.o rngs.o unittest.o $(CFLAGS)
	
randomtestadventurer: dominion.o randomtestadventurer.c unittest.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o unittest.o $(CFLAGS)
	
randomtestcard: dominion.o randomtestcard.c unittest.o rngs.o
	gcc -o randomtestcard randomtestcard.c -g dominion.o rngs.o unittest.o $(CFLAGS)
	
runcardtest4:
	./cardtest4 >> cardtest4.out
	
runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
randomtestcard.out: randomtestcard
	./randomtestcard >> randomtestcard.out
	wait
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out
	gcov -b dominion.c >> randomtestcardgcov.out
	cat dominion.c.gcov >> randomtestcardgcov.out
	
randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out
	wait
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurergcov.out 
	cat dominion.c.gcov >> randomtestadventurergcov.out

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f unittestresults.out dominion.c.gcov cardtest*.g* unittest*.g*
	./unittest1 >> unittestresults.out
	wait
	./unittest2 >> unittestresults.out
	wait
	./unittest3 >> unittestresults.out
	wait
	./unittest4 >> unittestresults.out
	wait
	./cardtest1 >> unittestresults.out
	wait
	./cardtest2 >> unittestresults.out
	wait
	./cardtest3 >> unittestresults.out
	wait
	./cardtest4 >> unittestresults.out
	wait
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcov -b dominion.c >> unittestresultsgcov.out
	cat dominion.c.gcov >> unittestresultsgcov.out

runALLtests: cleanAll unittestresults.out randomtestcard.out randomtestadventurer.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o *.exe randomtestcard randomtestadventurer unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 playdom test player testInit badTestDrawCard testDrawCard *.gcov *.gcda *.gcno *.so
	
cleanAll: clean
	rm -f *.out cardtest*.g* unittest*.g* rngs*.g* randomtest*.g*