CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)
	
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	
unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

all: cardtest1 cardtest2 cardtest3 cardtest4 unittest4 unittest3 unittest2 unittest1 

randomtestcard.out: randomtestcard
	./randomtestcard >> randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out

unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4 unittest4 unittest3 unittest2 unittest1 
	./unittest1 >> unittest1.out
	./unittest2 >> unittest2.out
	./unittest3 >> unittest3.out
	./unittest4 >> unittest4.out
	./cardtest1 >> cardtest1.out
	./cardtest2 >> cardtest2.out
	./cardtest3 >> cardtest3.out
	./cardtest4 >> cardtest4.out
	gcov dominion.c >> dominiongcov.out
	cat dominion.c.gcov >> dominiongcov.out
	
clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out
