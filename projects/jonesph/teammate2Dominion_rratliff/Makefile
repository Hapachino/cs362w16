CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: clean randomtestadventurer
	./randomtestadventurer &> randomtestadventurer.out
	echo " "    >> randomtestadventurer.out
	gcov -f -b dominion.c >> randomtestadventurer.out
	echo " "    >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard.out: clean randomtestcard
	./randomtestcard &> randomtestcard.out
	echo " "    >> randomtestcard.out
	gcov -f -b dominion.c >> randomtestcard.out
	echo " "    >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

random: randomtestadventurer.out randomtestcard.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o interface.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o interface.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o interface.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o interface.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: clean unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresults.out
	echo " "    >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo " "    >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo " "    >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo " "    >> unittestresults.out
	./cardtest1 >> unittestresults.out
	echo " "    >> unittestresults.out
	./cardtest2 >> unittestresults.out
	echo " "    >> unittestresults.out
	./cardtest3 >> unittestresults.out
	echo " "    >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo " "    >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	echo " "    >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: clean playdom player unittestresults.out random

clean:
	rm -f *.o playdom player *.gcov *.gcda *.gcno *.so *.out *~
	rm -f unittest1	unittest2 unittest3 unittest4
	rm -f cardtest1 cardtest2 cardtest3 cardtest4
	rm -f randomtestadventurer randomtestcard
