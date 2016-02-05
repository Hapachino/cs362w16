CFLAGS = -Wall -fpic -fprofile-arcs -ftest-coverage -lm

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

Card1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
    
Card2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

Card3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

Card4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

Unit1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

Unit2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

Unit3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

Unit4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

assignment3: Card1 Card2 Card3 Card4 Unit1 Unit2 Unit3 Unit4

unittestresults.out:
	make clean
	make all
	make assignment3
	
	echo "cardtest1 -" >> unittestresultsrobust.out
	./cardtest1 >> unittestresultsrobust.out
	
	echo "cardtest2 -" >> unittestresultsrobust.out
	./cardtest2 >> unittestresultsrobust.out
	
	echo "cardtest3 -" >> unittestresultsrobust.out
	./cardtest3 >> unittestresultsrobust.out
	
	echo "cardtest4 -" >> unittestresultsrobust.out
	./cardtest4 >> unittestresultsrobust.out
	
	echo "unittest1 -" >> unittestresultsrobust.out
	./unittest1 >> unittestresultsrobust.out
	
	echo "unittest2 -" >> unittestresultsrobust.out
	./unittest2 >> unittestresultsrobust.out
	
	echo "unittest3 -" >> unittestresultsrobust.out
	./unittest3 >> unittestresultsrobust.out
	
	echo "unittest4 -" >> unittestresultsrobust.out
	./unittest4 >> unittestresultsrobust.out
	
	echo "all results -"
	gcov -b dominion.c >> unittestresultsrobust.out
	gcov -b dominion.c >> unittestresults.out
	chmod 777 dominion.c.gcov
	cat dominion.c.gcov >> unittestresultsrobust.out
	cat dominion.c.gcov >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittestresults.out unittestresultsrobust.out
