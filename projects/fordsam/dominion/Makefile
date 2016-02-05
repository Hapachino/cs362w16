CFLAGS = -Wall -fpic -coverage -lm

all: playdom player testDrawCard testBuyCard badTestDrawCard

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

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

fordsamTest.o: fordsamTest.c
	gcc -c $^ -g $(CFLAGS)

unittest*.c: dominion.o rngs.o fordsamTest.o
	gcc -o $(@:.c=) -g $@ $^ $(CFLAGS)

cardtest*.c: dominion.o rngs.o fordsamTest.o
	gcc -o $(@:.c=) -g $@ $^ $(CFLAGS)

unittestresults.out: unittest*.c cardtest*.c
	@printf "Assignment 3 Test Results:\n" &> $@
	@printf "\n---------- unittest1 ----------\n" >> $@
	./unittest1 >> $@
	@printf "\n\n---------- unittest2 ----------\n" >> $@
	./unittest2 >> $@
	@printf "\n\n---------- unittest3 ----------\n" >> $@
	./unittest3 >> $@
	@printf "\n\n---------- unittest4 ----------\n" >> $@
	./unittest4 >> $@
	@printf "\n\n---------- cardtest1 ----------\n" >> $@
	./cardtest1 >> $@
	@printf "\n\n---------- cardtest2 ----------\n" >> $@
	./cardtest2 >> $@
	@printf "\n\n---------- cardtest3 ----------\n" >> $@
	./cardtest3 >> $@
	@printf "\n\n---------- cardtest4 ----------\n" >> $@
	./cardtest4 >> $@
	@printf "\n\n\n---------- Gcov Output ----------\n\n" >> $@
	gcov -b dominion.c >> $@
	@printf "\ndominion.c.gcov contents:\n" >> $@
	@cat dominion.c.gcov >> $@

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so playdom playdom.exe test test.exe player player.exe badTestDrawCard testBuyCard testDrawCard testInit testShuffle testInit.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out
	rm -rf *.dSYM
