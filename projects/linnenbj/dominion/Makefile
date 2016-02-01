CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: unittestresults.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

compare_gamestates.o: compare_gamestates.h compare_gamestates.c dominion.o
	gcc -c compare_gamestates.c -g $(CFLAGS)

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c dominion.o rngs.o
	echo "Result for running dominion function unit tests:" >> tests.out
	
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.o rngs.o unittest1.c $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.o rngs.o unittest2.c $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.o rngs.o unittest4.c $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out



testUnit1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 dominion.o rngs.o unittest1.c $(CFLAGS)


testUnit2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 dominion.o rngs.o unittest2.c $(CFLAGS)


testUnit3: unittest3.c dominion.o rngs.o 
	gcc -o unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)


testUnit4: unittest4.c dominion.o rngs.o 
	gcc -o unittest4 dominion.o rngs.o unittest4.c $(CFLAGS)

testCard1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)

testEqual: equaltest.c dominion.o rngs.o compare.o
	gcc -o equaltest dominion.o rngs.o compare.o equaltest.c $(CFLAGS)

clean:
	rm tests.out

cleanall: 
	rm tests.out unittest1 unittest2 unittest3 unittest4 unittest5 *.gcda *.gcno *.gcov

	