CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: unittestresults.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

compare_gamestates.o: compare_gamestates.h compare_gamestates.c dominion.o
	gcc -c compare_gamestates.c -g $(CFLAGS)

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "Result for running dominion function unit tests:" >> tests.out
	
	echo "unittest1.c:" >> unittestresult.out
	gcc -o unittest1 dominion.o rngs.o unittest1.c $(CFLAGS)
	./unittest1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "unittest2.c:" >> unittestresult.out
	gcc -o unittest2 dominion.o rngs.o unittest2.c $(CFLAGS)
	./unittest2 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	
	echo "unittest3.c:" >> unittestresult.out
	gcc -o unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)
	./unittest3 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "unittest4.c:" >> unittestresult.out
	gcc -o unittest4 dominion.o rngs.o unittest4.c $(CFLAGS)
	./unittest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "cardtest1.c:" >> unittestresult.out
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
	./cardtest1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "cardtest2.c:" >> unittestresult.out
	gcc -o cardtest2 dominion.o rngs.o cardtest2.c $(CFLAGS)
	./cardtest2 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "cardtest3.c:" >> unittestresult.out
	gcc -o cardtest3 dominion.o rngs.o cardtest3.c $(CFLAGS)
	./cardtest3 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "cardtest4.c:" >> unittestresult.out
	gcc -o cardtest4 dominion.o rngs.o cardtest4.c $(CFLAGS)
	./cardtest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

testUnit1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 dominion.o rngs.o unittest1.c $(CFLAGS)


testUnit2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 dominion.o rngs.o unittest2.c $(CFLAGS)


testUnit22: newunit2test.c dominion.o rngs.o
	gcc -o newunit2test dominion.o rngs.o newunit2test.c $(CFLAGS)

testUnit3: unittest3.c dominion.o rngs.o 
	gcc -o unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)


testUnit4: unittest4.c dominion.o rngs.o 
	gcc -o unittest4 dominion.o rngs.o unittest4.c $(CFLAGS)

newtestCard1: newcardtest1.c dominion.o rngs.o
	gcc -o newcardtest1 dominion.o rngs.o newcardtest1.c $(CFLAGS)


testCard1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)

testCard2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 dominion.o rngs.o cardtest2.c $(CFLAGS)

testCard3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 dominion.o rngs.o cardtest3.c $(CFLAGS)

testCard4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 dominion.o rngs.o cardtest4.c $(CFLAGS)

testEqual: equaltest.c dominion.o rngs.o compare.o
	gcc -o equaltest dominion.o rngs.o compare.o equaltest.c $(CFLAGS)

clean:
	rm unittestresult.out

cleanall: 
	rm unittestresult.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *.gcda *.gcno *.gcov dominion.o

	