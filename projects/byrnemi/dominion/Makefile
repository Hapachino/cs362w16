CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o  $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o 
	gcc -o randomtestadventurer -g -w randomtestadventurer.c dominion.o rngs.o  $(CFLAGS)

randomtestcard: randomtestcard.c dominion.o 
	gcc -o randomtestcard -g -w randomtestcard.c dominion.o rngs.o  $(CFLAGS)


tests: randomtestadventurer.c randomtestcard.c dominion.c
	gcc -o randomtestcard -g -w randomtestcard.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestadventurer -g -w randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

	

runtests: randomtestcard randomtestadventurer
	touch randomtestresults.out
	./randomtestcard >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov -f -b dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out



player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randomtestadventurer randomtestcard rngs.o dominion.o

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4