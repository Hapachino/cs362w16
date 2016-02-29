CFLAGS = -Wall -fpic -coverage -lm
#CFLAGS =  -coverage
TESTS?=100
VERB?=0

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

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


interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

rSmithy: smithyRandomTest.c dominion.o rngs.o interface.o
	gcc -o rSmithy -g smithyRandomTest.c dominion.o interface.o rngs.o $(CFLAGS)

rAdv: adventurerRandomTest.c dominion.o rngs.o interface.o
	gcc -o rAdv -g adventurerRandomTest.c dominion.o interface.o rngs.o $(CFLAGS)

sndbx: sndbx.c rngs.o
	gcc -o sndbx -g sndbx.c rngs.o $(CFLAGS)

random: rSmithy rAdv cardtest1 cardtest2 cardtest4 unittest1 unittest2 unittest3 unittest4 playdom player

	./rSmithy 2 5000 0 &> benderiTest.out
	./rAdv 2 5000 0 &> benderiTest.out
	./cardtest1 2 >> benderiTest.out
	./cardtest2 2 >> benderiTest.out
	./cardtest4 2 >> benderiTest.out
	./unittest1 2 >> benderiTest.out
	./unittest2 2 >> benderiTest.out
	./unittest3 2 >> benderiTest.out
	./unittest4 2 >> benderiTest.out

	gcov dominion.c -b -f >> benderiTest.out
	cat dominion.c.gcov >> benderiTest.out
	cat dominion.c.gcov >> benderiTest.out

regular: cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4

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

all: playdom player

clean:
	rm -f *.o playdom.exe playdom *.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.stackdump
