CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o  $(CFLAGS)

unittest1: unittest1.c dominion.o 
	gcc -o unittest1 -g -w unittest1.c dominion.o rngs.o  $(CFLAGS)
    
unittest2: unittest2.c dominion.o 
	gcc -o unittest2 -g -w unittest2.c dominion.o rngs.o  $(CFLAGS)
    
unittest3: unittest3.c dominion.o 
	gcc -o unittest3 -g -w unittest3.c dominion.o rngs.o  $(CFLAGS)
    
unittest4: unittest4.c dominion.o 
	gcc -o unittest4 -g -w unittest4.c dominion.o rngs.o  $(CFLAGS)

cardtest1: cardtest1.c dominion.o 
	gcc -o cardtest1 -g -w cardtest1.c dominion.o rngs.o  $(CFLAGS)

cardtest2: cardtest2.c dominion.o 
	gcc -o cardtest2 -g -w cardtest2.c dominion.o rngs.o  $(CFLAGS)

cardtest3: cardtest3.c dominion.o 
	gcc -o cardtest3 -g -w cardtest3.c dominion.o rngs.o  $(CFLAGS)

cardtest2: cardtest4.c dominion.o 
	gcc -o cardtest4 -g -w cardtest4.c dominion.o rngs.o  $(CFLAGS)

tests: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	gcc -o unittest1 -g -w unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g -w unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 -g -w unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 -g -w unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 -g -w cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g -w cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g -w cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 -g -w cardtest4.c dominion.o rngs.o $(CFLAGS)

runtests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2
	touch unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out



player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player unittest1 unittest2 unittest3 unittest4 rngs.o dominion.o

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4