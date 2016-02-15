CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o  $(CFLAGS)
    
randomtestadventurer: randomtestadventurer.c dominion.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard: randomtestcard.c dominion.o 
	gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o  $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o  $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	rm -f dominion.gcda
	./randomtestadventurer
	
	gcov dominion.c -b >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	
randomtestcard.out: randomtestcard
	rm -f dominion.gcda
	./randomtestcard

	gcov dominion.c -b >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	gcov dominion.c -b >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

all: playdom player randomtestadventurer randomtestcard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so randomtestadventurer randomtestcard 
