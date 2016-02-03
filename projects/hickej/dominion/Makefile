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

unitTest1: unittest1.c dominion.o rngs.o
	gcc -o unitTest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
  
unitTest2: unittest2.c dominion.o rngs.o
	gcc -o unitTest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
  
unitTest3: unittest3.c dominion.o rngs.o
	gcc -o unitTest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
  
unitTest4: unittest4.c dominion.o rngs.o
	gcc -o unitTest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
  
cardTest1: cardtest1.c dominion.o rngs.o
	gcc -o cardTest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
  
cardTest2: cardtest2.c dominion.o rngs.o
	gcc -o cardTest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
  
cardTest3: cardtest3.c dominion.o rngs.o
	gcc -o cardTest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
  
cardTest4: cardtest4.c dominion.o rngs.o
	gcc -o cardTest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out:
	gcc -c rngs.c -g  $(CFLAGS)
	gcc -c dominion.c -g  $(CFLAGS)

	gcc -o unitTest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unitTest1 >> unittestresults.out
	gcov unittest1.c >> unittestresults.out
  
	gcc -o unitTest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unitTest2 >> unittestresults.out
	gcov unittest2.c >> unittestresults.out
  
	gcc -o unitTest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unitTest3 >> unittestresults.out
	gcov unittest3.c >> unittestresults.out
  
	gcc -o unitTest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unitTest4 >> unittestresults.out
	gcov unittest4.c >> unittestresults.out
  
	gcc -o cardTest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardTest1 >> unittestresults.out
	gcov cardtest1.c >> unittestresults.out
  
	gcc -o cardTest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardTest2 >> unittestresults.out
	gcov cardtest2.c >> unittestresults.out
  
	gcc -o cardTest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardTest3 >> unittestresults.out
	gcov cardtest3.c >> unittestresults.out
  
	gcc -o cardTest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardTest4 >> unittestresults.out
	gcov cardtest4.c >> unittestresults.out  
  
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unitTest1.exe unitTest1 unitTest2.exe unitTest2 unitTest3.exe unitTest3 unitTest4.exe unitTest4 cardTest1.exe cardTest1 cardTest2.exe cardTest2 cardTest3.exe cardTest3 cardTest4.exe cardTest4 *.gcov *.gcda *.gcno *.so *.out
