CFLAGS = -Wall -fpic -fprofile-arcs -ftest-coverage -lm

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

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: dominion.h rngs.h dominion_helpers.h dominion.o rngs.o unitTest1.c unitTest2.c unitTest3.c unitTest4.c cardTest1.c cardTest2.c cardTest3.c cardTest4.c
	gcc -o unitTest1.o unitTest1.c dominion.o rngs.o -g $(CFLAGS)
	./unitTest1
	gcov dominion.c >> unitTestResults.out
	cat dominion.c.gcov >> unitTestResults.out
	#unit test2
	gcc -o unitTest2.o unitTest2.c dominion.o rngs.o -g $(CFLAGS)
	./unitTest2
	gcov dominion.c >> unitTestResults.out
	cat dominion.c.gcov >> unitTestResults.out
	#test3
	gcc -o unitTest3.o unitTest3.c dominion.o rngs.o -g $(CFLAGS)
	./unitTest3
	gcov dominion.c >> unitTestResults.out
	cat dominion.c.gcov >> unitTestResults.out
	#test4
	gcc -o unitTest4.o unitTest4.c dominion.o rngs.o -g $(CFLAGS)
	./unitTest4
	gcov dominion.c >> unitTestResults.out
	cat dominion.c.gcov >> unitTestResults.out
	#card 1
	gcc -o cardTest1.o cardTest1.c dominion.o rngs.o -g $(CFLAGS)
	./cardTest1
	gcov dominion.c >> unitTestResults.out
	cat dominion.c.gcov >> unitTestResults.out
	#card 2
	gcc -o cardTest2.o cardTest2.c dominion.o rngs.o -g $(CFLAGS)
	./cardTest2
	gcov dominion.c >> unitTestResults.out
	cat dominion.c.gcov >> unitTestResults.out
	#card 3
	gcc -o cardTest3.o cardTest3.c dominion.o rngs.o -g $(CFLAGS)
	./cardTest3
	gcov dominion.c >> unitTestResults.out
	cat dominion.c.gcov >> unitTestResults.out
	#card 4
	gcc -o cardTest4.o cardTest4.c dominion.o rngs.o -g $(CFLAGS)
	./cardTest4
	gcov dominion.c >> unitTestResults.out
	cat dominion.c.gcov >> unitTestResults.out

randomTestCard.out:dominion.h rngs.h dominion_helpers.h dominion.o rngs.o randomTestCard.c 
	gcc -o randomTestCard.o randomTestCard.c dominion.o rngs.o -g $(CFLAGS)
	./randomTestCard.o
	gcov -b dominion.c >> randomTestCard.out
	cat dominion.c.gcov >> randomTestCard.out


randomTestAdventurer.out:dominion.h rngs.h dominion_helpers.h dominion.o rngs.o randomTestAdventurer.c 
	gcc -o randomTestAdventurer.o randomTestAdventurer.c dominion.o rngs.o -g $(CFLAGS)
	gcov -b dominion.c >> randomTestAdventurer.out
	cat dominion.c.gcov >> randomTestAdventurer.out

randomTestVillage.out:dominion.h rngs.h dominion_helpers.h dominion.o rngs.o randomTestCardVillage.c 
	gcc -o randomTestCardVillage.o randomTestCardVillage.c dominion.o rngs.o -g $(CFLAGS)
	gcov -b dominion.c >> randomTestVillage.out
	cat dominion.c.gcov >> randomTestVillage.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
