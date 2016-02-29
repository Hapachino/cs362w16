CFLAGS = -lm -Wall -fpic -coverage
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o 
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o 
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: _drawCardTest.c dominion.o rngs.o 
	gcc -o testDrawCard -g  _drawCardTest.c dominion.o rngs.o  $(CFLAGS)

badTestDrawCard: _drawCardTest.c dominion.o rngs.o 
	gcc -o badTestDrawCard -g  _drawCardTest.c dominion.o rngs.o  $(CFLAGS)

testBuyCard: _drawCardTest.c dominion.o rngs.o 
	gcc -o testDrawCard -g  _drawCardTest.c dominion.o rngs.o  $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittest1: dominion.o _unittest1.c
	gcc -o unittest1 _unittest1.c -g dominion.o  rngs.o $(CFLAGS)
	./unittest1 &> unittestresult.out

unittest2: dominion.o _unittest2.c dominion.o rngs.o 
	gcc -o unittest2 _unittest2.c -g dominion.o  rngs.o $(CFLAGS)
	
unittest3: dominion.o _unittest3.c dominion.o rngs.o 
	gcc -o unittest3 _unittest3.c -g dominion.o  rngs.o $(CFLAGS)

unittest4: dominion.o _unittest4.c dominion.o rngs.o 
	gcc -o unittest4 _unittest4.c -g dominion.o  rngs.o $(CFLAGS)

smithytest: dominion.o rngs.o  _smithyTest.c
	gcc -o smithytest _smithyTest.c -g dominion.o  rngs.o $(CFLAGS)

adventurertest: dominion.o rngs.o  adventurertest.c
	gcc -o adventurertest _adventurerTest.c -g dominion.o  rngs.o $(CFLAGS)

counciltest: dominion.o rngs.o  _councilTest.c
	gcc -o counciltest _councilTest.c -g dominion.o  rngs.o $(CFLAGS)

villagetest: dominion.o rngs.o
	gcc -o villagetest _villageTest.c -g dominion.o  rngs.o $(CFLAGS)

unittests: smithytest unittest2 
	gcc -o smithytest _smithyTest.c -g dominion.o  rngs.o $(CFLAGS)
	./smithytest &> unittestresult.out
	gcov -b smithyTest.c >> unittestresult.out	
	cat smithyTest.c.gcov >> unittestresult.out

	gcc -o unittest2 _unittest2.c -g dominion.o  rngs.o $(CFLAGS)
	./unittest2 >> unittestresult.out
	gcov -b _unittest2.c >> unittestresult.out	
	cat unittest2.c.gcov >> unittestresult.out
	cat unittest2.c.gcov >> coverage.c

	gcc -o unittest1 _unittest1.c -g dominion.o  rngs.o $(CFLAGS)
	./unittest1 >> unittestresult.out
	gcov -b _unittest1.c >> unittestresult.out	
	cat unittest1.c.gcov >> unittestresult.out
	cat unittest1.c.gcov >> coverage.c

	gcc -o unittest3 _unittest3.c -g dominion.o  rngs.o $(CFLAGS)
	./unittest3 >> unittestresult.out
	gcov -b _unittest3.c >> unittestresult.out	
	cat unittest3.c.gcov >> unittestresult.out
	cat unittest3.c.gcov >> coverage.c

	# gcc -o adventurertest adventurertest.c -g dominion.o  rngs.o $(CFLAGS)
	# ./adventurertest >> unittestresult.out
	# gcov -b adventurertest.c >> unittestresult.out	
	# cat adventurertest.c.gcov >> unittestresult.out
	# cat adventurertest.c.gcov >> coverage.c

	gcc -o unittest4 _unittest4.c -g dominion.o  rngs.o $(CFLAGS)
	./unittest4 >> unittestresult.out
	gcov -b _unittest4.c >> unittestresult.out
	cat unittest4.c.gcov >> unittestresult.out
	cat unittest4.c.gcov >> coverage.c

	gcc -o villageTest _villageTest.c -g dominion.o  rngs.o $(CFLAGS)
	./villageTest >> unittestresult.out
	gcov -b _villageTest.c >> unittestresult.out
	cat _villageTest.c.gcov >> unittestresult.out
	cat _villageTest.c.gcov >> coverage.c

	gcov -b dominion.c >> unittestresult.out	
	cat dominion.c.gcov >> unittestresult.out

	gcc -o randomtestcard _randomtestcard.c -g dominion.o  rngs.o $(CFLAGS)
	./randomtestcard > randomtestcard.out

	gcov -b dominion.c >> randomtestcard.out

	gcc -o randomtestadventurer _randomtestadventurer.c -g dominion.o  rngs.o $(CFLAGS)
	./randomtestadventurer > randomtestadventurer.out

	gcov -b dominion.c >> randomtestadventurer.out
	
randomtests: dominion.o rngs.o
	#gcc -o randomtestcard.out randomtestcard.c -g dominion.o rngs.o $(CFLAGS)
	#./randomtestcard.out >> randomhistory.c
	#gcov -b randomtestcard.c >> randomhistory.c
	gcc -o randomtestcard randomtestcard.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestadventurer _randomtestadventurer.c -g dominion.o  rngs.o $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out	
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o  rngs.o interface.o

all: playdom player testDrawCard testBuyCard badTestDrawCard 

clean:
	rm -f *.gch *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so

cleanprogs: 
	rm -f unittest1 unittest2 unittest3 unittest4 smithytest randomtestcard villagetest randomtestadventurer