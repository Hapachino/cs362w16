# Name: YUNSIK CHOI
# makefile

CFLAGS = -Wall -coverage -fpic -lm

all: rngs.o dominion.o unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 rununit1 rununit2 rununit3 rununit4 runcard1 runcard2 runcard3 runcard4

rngs.o: rngs.h rngs.c
	gcc -c rngs.c

dominion.o: dominion.h dominion.c
	gcc -c dominion.c

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)

rununit1: unittest1
	./unittest1
	gcov unittest1.c -b > unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out

rununit2: unittest2
	./unittest2
	gcov unittest2.c -b >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out

rununit3: unittest3
	./unittest3
	gcov unittest3.c -b >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out

rununit4: unittest4
	./unittest4
	gcov unittest4.c -b >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out

runcard1: cardtest1
	./cardtest1
	gcov cardtest1.c -b >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out

runcard2: cardtest2
	./cardtest2
	gcov cardtest2.c -b >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out

runcard3: cardtest3
	./cardtest3
	gcov cardtest3.c -b >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out

runcard4: cardtest4
	./cardtest4
	gcov cardtest4.c -b >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
