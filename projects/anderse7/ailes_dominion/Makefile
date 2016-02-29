CFLAGS = -Wall -fpic -lm -fprofile-arcs -ftest-coverage
CC = gcc

rngs.o: rngs.h rngs.c
	$(CC) -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	$(CC) -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	$(CC) -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

randomtestAdventurer: randomtestadventurer.c dominion.o rngs.o
	$(CC) -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestCard: randomtestcard.c dominion.o rngs.o
	$(CC) -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestresults.out: dominion.o randomtestAdventurer randomtestCard
	./randomtestadventurer >> randomtestadventurer.out
	gcov -f -b randomtestadventurer >> randomtestadventurer.out
	./randomtestcard >> randomtestcard.out
	gcov -f -b randomtestcard >> randomtestcard.out
	gcov -f -b dominion.c >> randomtestresults.out

interface.o: interface.h interface.c
	$(CC) -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	$(CC) -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randomtestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe testInit randomtestresults.out randomtestadventurer.out randomtestcard.out randomtestadventurer randomtestadventurer.exe randomtestcard randomtestcard.exe *.gcov *.gcda *.gcno *.so