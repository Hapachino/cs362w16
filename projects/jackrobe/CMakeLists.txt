cmake_minimum_required(VERSION 3.3)
project(jackrobe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fpic -coverage -lm ")
add_executable (rngs $(RNGS_FILES))

set(RNGS_FILES
        dominion/rngs.c
        dominion/rngs.h)


set(SOURCE_FILES
        dominion/tests/badTestDrawCard.c
        dominion/tests/betterTestDrawCard.c
    dominion/documentation.c
        dominion/dominion.c
        dominion/dominion.h
    dominion/dominion_helpers.h
    dominion/interface.c
    dominion/interface.h
    dominion/playdom.c
    dominion/player.c
    dominion/refactor.c
    dominion/rngs.c
    dominion/rngs.h
    dominion/rt.c
        dominion/tests/supplyTest.c
        dominion/tests/testBuyCard.c
        dominion/tests/testDrawCard.c
    dominion/testInit.c
        dominion/testShuffle.c dominion/smithyTest.c)

add_executable (rngs $(RNGS_FILES))

dominion.o: dominion.h dominion.c rngs.o
gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

# Smithy
cardtest1: cardtest1.c dominion.o rngs.o
gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

# Adventurer
cardtest2: cardtest2.c dominion.o rngs.o
gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

# greatHall
cardtest3: cardtest3.c dominion.o rngs.o
gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

# councilRoom
cardtest4: cardtest4.c dominion.o rngs.o
gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

#drawCard
unittest1: unittest1.c dominion.o rngs.o
gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

#ScoreFor
unittest2: unittest2.c dominion.o rngs.o
gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

#gainCard
unittest3: unittest3.c dominion.o rngs.o
gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

#discardCard
unittest4: unittest4.c dominion.o rngs.o
gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
gcc -o testDrawCard g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
gcc -c interface.c -g  $(CFLAGS)

unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4

./cardtest1 2 &> unittestresult.out
./cardtest2 2 >> unittestresult.out
./cardtest3 2 >> unittestresult.out
./cardtest4 2 >> unittestresult.out
./unittest1 2 >> unittestresult.out
./unittest2 2 >> unittestresult.out
./unittest3 2 >> unittestresult.out
./unittest4 2 >> unittestresult.out

gcov dominion.c -b -f >> unittestresult.out
cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4

clean:
rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.stackdump
executable(jackrobe ${SOURCE_FILES})