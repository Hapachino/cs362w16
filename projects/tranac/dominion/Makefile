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

getCost: unittest1.c dominion.o rngs.o
	gcc -o unit1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

isGameOver: unittest2.c dominion.o rngs.o
	gcc -o unit2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

shuffle: unittest3.c dominion.o rngs.o
	gcc -o unit3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

drawCard: unittest4.c dominion.o rngs.o
	gcc -o unit4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

smithy: cardtest1.c dominion.o rngs.o
	gcc -o card1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

adventurer: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

village: cardtest3.c dominion.o rngs.o
	gcc -o card3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

council_room: cardtest4.c dominion.o rngs.o
	gcc -o card4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

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

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe badTestDrawCard.exe testDrawCard.exe unit1 unittest1.exe unit2 unittest2.exe unit3 unittest3.exe unit4 unittest4.exe card1 cardtest1.exe card2 cardtest2.exe card3 cardtest3.exe card4 cardtest4.exe unittestresults.out unittestresults.out? *.gcov *.gcda *.gcno *.so

unittestresults.out:
	make clean; make tests; make runmytests;

tests: cardtest4.c cardtest3.c cardtest2.c cardtest1.c unittest4.c unittest3.c unittest2.c unittest1.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

runmytests:
	rm -f unittestresults.out
	./unittest1 >> unittestresults.out
	gcov -b unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out