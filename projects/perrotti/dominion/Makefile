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
    
all: playdom player testDrawCard testBuyCard badTestDrawCard

Card1: cardtest1.c dominion.o rngs.out
    gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
    
Card2: cardtest2.c dominion.o rngs.out
    gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

Card3: cardtest3.c dominion.o rngs.out
    gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

Card4: cardtest4.c dominion.o rngs.out
    gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

Unit1: unittest1.c dominion.o rngs.out
    gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

Unit2: unittest2.c dominion.o rngs.out
    gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

Unit3: unittest3.c dominion.o rngs.out
    gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

Unit4: unittest4.c dominion.o rngs.out
    gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

assignment3: Card1 Card2 Card3 Card4 Unit1 Unit2 Unit3 Unit4

unittestresults.out:
    make clean
    rm -rf unittestresults.out
    make assignment3
    ./cardtest1 >> unittestresults.out
    ./cardtest2 >> unittestresults.out
    ./cardtest3 >> unittestresults.out
    ./cardtest4 >> unittestresults.out
    ./unittest1 >> unittestresults.out
    ./unittest2 >> unittestresults.out
    ./unittest3 >> unittestresults.out
    ./unittest4 >> unittestresults.out
    gcov -b dominion.c >> unittestresults.out
    cat dominion.c.gcov >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
