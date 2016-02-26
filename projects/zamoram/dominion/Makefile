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

#all: playdom player testDrawCard testBuyCard badTestDrawCard
all: playdom player 

clean:
	rm -f *.o playdom.exe playdom test.exe testDrawCard badTestDrawCard test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *.out
	rm -f randomtestadventurer randomtestcard
	
unittestresults.out: dominion.o rngs.o unittest1.c
	make all
	make unittests
	make rununittests
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
unittests: dominion.o rngs.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)
	#gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -g -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)
	make cardtest4
	
rununittests:
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	
randomtestadventurer:  dominion.o rngs.o randomtestadventurer.c
	gcc -g -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard:  dominion.o rngs.o randomtestcard.c
	gcc -g -o randomtestcard randomtestcard.c dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer.out: dominion.o rngs.o randomtestadventurer.c
	make all
	make randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	
randomtestcard.out: dominion.o rngs.o randomtestcard.c
	make all
	make randomtestcard
	./randomtestcard >> randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out
	
cardtest4: dominion.o rngs.o cardtest4.c
	gcc -g -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)