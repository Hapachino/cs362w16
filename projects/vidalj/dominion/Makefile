CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
    
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
    
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
    
cardtest44: cardtest44.c dominion.o rngs.o
	gcc -o cardtest44 -g  cardtest44.c dominion.o rngs.o $(CFLAGS)    
    
randomtestcard: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
    
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
    
unittestresults.out: unittest1

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer >> $@
	gcov -b dominion >> $@
	@cat dominion.c.gcov >> $@

randomtestcard.out: randomtestcard
	./randomtestcard >> $@
	gcov -b dominion >> $@  
	@cat dominion.c.gcov >> $@
    
all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 randomtestadventurer randomtestcard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
