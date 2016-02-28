CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomTestAdventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomTestAdventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomTestCard: randomtestcard.c dominion.o rngs.o
	gcc -o randomTestCard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomTestAdventurer
	./randomTestAdventurer &> randomtestadventurer.out
	echo " "    >> randomtestadventurer.out
	gcov -f -b dominion.c >> randomtestadventurer.out
	echo " "    >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard.out: randomTestCard
	./randomTestCard &> randomtestcard.out
	echo " "    >> randomtestcard.out
	gcov -f -b dominion.c >> randomtestcard.out
	echo " "    >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

random: randomtestadventurer.out randomtestcard.out

unitTest1: unittest1.c dominion.o rngs.o
	gcc -o unitTest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unitTest2: unittest2.c dominion.o rngs.o
	gcc -o unitTest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unitTest3: unittest3.c dominion.o rngs.o
	gcc -o unitTest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unitTest4: unittest4.c dominion.o rngs.o
	gcc -o unitTest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardTest1: cardtest1.c dominion.o rngs.o interface.o
	gcc -o cardTest1 -g  cardtest1.c dominion.o rngs.o interface.o $(CFLAGS)

cardTest2: cardtest2.c dominion.o rngs.o interface.o
	gcc -o cardTest2 -g  cardtest2.c dominion.o rngs.o interface.o $(CFLAGS)

cardTest3: cardtest3.c dominion.o rngs.o interface.o
	gcc -o cardTest3 -g  cardtest3.c dominion.o rngs.o interface.o $(CFLAGS)

cardTest4: cardtest4.c dominion.o rngs.o interface.o
	gcc -o cardTest4 -g  cardtest4.c dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4
	./unitTest1 &> unittestresults.out
	echo " "    >> unittestresults.out
	./unitTest2 >> unittestresults.out
	echo " "    >> unittestresults.out
	./unitTest3 >> unittestresults.out
	echo " "    >> unittestresults.out
	./unitTest4 >> unittestresults.out
	echo " "    >> unittestresults.out
	./cardTest1 >> unittestresults.out
	echo " "    >> unittestresults.out
	./cardTest2 >> unittestresults.out
	echo " "    >> unittestresults.out
	./cardTest3 >> unittestresults.out
	echo " "    >> unittestresults.out
	./cardTest4 >> unittestresults.out
	echo " "    >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	echo " "    >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: clean playdom player unittestresults.out random

clean:
	rm -f playdom.exe playdom test.exe test player player.exe testInit testInit.exe
	rm -f unitTest1.exe unitTest1 unitTest2.exe unitTest2 unitTest3.exe unitTest3 unitTest4.exe unitTest4
	rm -f cardTest1.exe cardTest1 cardTest2.exe cardTest2 cardTest3.exe cardTest3 cardTest4.exe cardTest4
	rm -f randomTestCard.exe randomTestCard randomTestAdventurer.exe randomTestAdventurer
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out *~
