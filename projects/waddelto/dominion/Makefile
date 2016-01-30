CFLAGS = -std=c99 -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

testcontrol: dominion.o test_helper.o test1.o test2.o test3.o test4.o cardtest1.o cardtest2.o cardtest3.o cardtest4.o
	gcc -o testcontrol -g testcontrol.c test_helper.o dominion.o rngs.o $(CFLAGS)

cardtest1.o: cardtest1.c
	gcc -c cardtest1.c -g $(CFLAGS)

cardtest2.o: cardtest2.c
	gcc -c cardtest2.c -g $(CFLAGS)

cardtest3.o: cardtest3.c
	gcc -c cardtest3.c -g $(CFLAGS)

cardtest4.o: cardtest4.c
	gcc -c cardtest4.c -g $(CFLAGS)

test_helper.o: test_helper.h test_helper.c rngs.o
	gcc -c test_helper.c -g $(CFLAGS)

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

unittestresults.out: testcontrol 
	touch unittestresult.out
	./testcontrol 2 >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

test1.o: unittest1.c 
	gcc -c unittest1.c -g $(CFLAGS)

test2.o: unittest2.c
	gcc -c unittest1.c -g $(CFLAGS)

test3.o: unittest3.c
	gcc -c unittest3.c -g $(CFLAGS)

test4.o: unittest4.c
	gcc -c unittest4.c -g $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom playdom test test player player testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out unittestresult.out
