CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

getCost: unittest1.c dominion.o rngs.o
	gcc -o unit1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

updateCoins: unittest2.c dominion.o rngs.o
	gcc -o unit2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

isGameOver: unittest3.c dominion.o rngs.o
	gcc -o unit3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

buyCard: unittest4.c dominion.o rngs.o
	gcc -o unit4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

testVillage: cardtest1.c dominion.o rngs.o
	gcc -o card1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	
testSalvager: cardtest2.c dominion.o rngs.o
	gcc -o card2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	
testSmithy: cardtest3.c dominion.o rngs.o
	gcc -o card3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	
testAdventurer: cardtest4.c dominion.o rngs.o
	gcc -o card4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)
	
randomtestSmithy: randomtestcard.c dominion.o rngs.o
	gcc -o randomtest -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

test: getCost updateCoins isGameOver buyCard testVillage testAdventurer testSalvager testSmithy

randomtests: randomtestadventurer randomtestcard

runrandomtests:
	./randomtest >> randomtestcard.out
	./randomadventurer >> randomtestadventurer.out
	
assignment4:
	make clean
	rm -f randomtestcard.out
	rm -f randomtestadventurer.out
	make randomtestSmithy
	./randomtest
	gcov dominion.c -b >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out
	rm -f dominion.gcda
	make randomtestadventurer
	./randomadventurer
	gcov dominion.c -b >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	rm -f dominion.gcda
	
assignment3total:
	make clean
	make testSmithy
	./card3
	make testAdventurer
	./card4
	gcov dominion.c -b >> smithyadventurer.out
	cat dominion.c.gcov >> smithyadventurer.out
	rm -f dominion.gcda
	
	
assignment4total:
	make clean
	make testSmithy
	./card3
	make testAdventurer
	./card4
	make randomtestSmithy
	./randomtest
	make randomtestadventurer
	./randomadventurer
	gcov dominion.c -b >> randomsmithyadventurer.out
	cat dominion.c.gcov >> randomsmithyadventurer.out
	rm -f dominion.gcda
	
previous:
	make clean
	make testSmithy
	./card3
	gcov dominion.c -b >> Smithy.out
	cat dominion.c.gcov >> Smithy.out
	rm -f dominion.gcda
	make testAdventurer
	./card4
	gcov dominion.c -b >> Adventurer.out
	cat dominion.c.gcov >> Adventurer.out
	rm -f dominion.gcda
	
runtest: 
	./unit1 >> unittestresults.out
	./unit2 >> unittestresults.out
	./unit3 >> unittestresults.out
	./unit4 >> unittestresults.out
	./card1 >> unittestresults.out
	./card2 >> unittestresults.out
	./card3	>> unittestresults.out
	./card4 >> unittestresults.out

unittestresults.out: 
	make clean
	rm -f unittestresults.out
	make test	
	make runtest
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
