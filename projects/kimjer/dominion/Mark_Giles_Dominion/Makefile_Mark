CFLAGS = -Wall -fpic -coverage -lm
DOMINIONOBJECTS = rngs.o dominion.o interface.o
UNITTESTFILES = unittest1.c unittest2.c unittest3.c unittest4.c
CARDTESTFILES = cardtest1.c cardtest2.c cardtest3.c cardtest4.c
EXECUTABLES = unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer
OUTPUTFILES = *.gcov *.out

default: unittestresults.out

unittestresults.out: $(DOMINIONOBJECTS) unitTests cardTests
	unittest1 >> unittestresults.out
	unittest2 >> unittestresults.out
	unittest3 >> unittestresults.out
	unittest4 >> unittestresults.out
	cardtest1 >> unittestresults.out
	cardtest2 >> unittestresults.out
	cardtest3 >> unittestresults.out
	cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out 

randomtestcard.out: $(DOMINIONOBJECTS) randomtestcard
	randomtestcard >> randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

randomtestadventurer.out: $(DOMINIONOBJECTS) randomtestadventurer
	randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c $(CFLAGS)

dominion.o: dominion.h dominion.c dominion_helpers.h rngs.o
	gcc -c dominion.c $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c $(CFLAGS)

unitTests: $(TESTFILES) $(DOMINIONOBJECTS)
	gcc -o unittest1 unittest1.c $(DOMINIONOBJECTS) $(CFLAGS)
	gcc -o unittest2 unittest2.c $(DOMINIONOBJECTS) $(CFLAGS)
	gcc -o unittest3 unittest3.c $(DOMINIONOBJECTS) $(CFLAGS)
	gcc -o unittest4 unittest4.c $(DOMINIONOBJECTS) $(CFLAGS)
	
cardTests: $(CARDTESTFILES) $(DOMINIONOBJECTS)
	gcc -o cardtest1 cardtest1.c $(DOMINIONOBJECTS) $(CFLAGS)
	gcc -o cardtest2 cardtest2.c $(DOMINIONOBJECTS) $(CFLAGS)
	gcc -o cardtest3 cardtest3.c $(DOMINIONOBJECTS) $(CFLAGS)
	gcc -o cardtest4 cardtest4.c $(DOMINIONOBJECTS) $(CFLAGS)

randomtestcard: randomtestcard.c $(DOMINIONOBJECTS)
	gcc -o randomtestcard randomtestcard.c $(DOMINIONOBJECTS) $(CFLAGS)

randomtestadventurer: randomtestadventurer.c $(DOMINIONOBJECTS) 
	gcc -o randomtestadventurer randomtestadventurer.c $(DOMINIONOBJECTS) $(CFLAGS)

clean:
	rm -f *.o *.gcda *.gcno *.gch *.so $(EXECUTABLES)

cleanall:
	rm -f *.o *gcda *.gcno *.gch *.so $(EXECUTABLES) $(OUTPUTFILES)
