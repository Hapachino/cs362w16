CFLAGS = -Wall -fpic  -fprofile-arcs -ftest-coverage  -lm
smtest: randomtestcard.c dominion.h dominion.o rngs.o
	gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)


advtest: randomtestadventurer.c dominion.h dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

runadvtest:
	rm -f randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

both:
	make clean
	make advtest
	make smtest
	rm -f randomtestcard.out
	rm -f randomtestadventurer.out
	./randomtestcard >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

tests: unittest4.c unittest3.c unittest2.c unittest1.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

runtests:
	rm -f unittestresult.out
	./unittest1 >> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestadventurer.out:
	make clean; make advtest; make runadvtest;

# rngs.o: rngs.h rngs.c
# 	gcc -c rngs.c -g  $(CFLAGS)
#
# dominion.o: dominion.h dominion.c rngs.o
# 	gcc -c dominion.c -g  $(CFLAGS)
#
# playdom: dominion.o playdom.c
# 	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#
# testDrawCard: testDrawCard.c dominion.o rngs.o
# 	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)
#
# badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
# 	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)
#
# testBuyCard: testDrawCard.c dominion.o rngs.o
# 	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)
#
# testAll: dominion.o testSuite.c
# 	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)
#
# interface.o: interface.h interface.c
# 	gcc -c interface.c -g  $(CFLAGS)
#
# runtests: testDrawCard
# 	./unittest1 &> unittestresult.out
# 	gcov dominion.c >> unittestresult.out
# 	cat dominion.c.gcov >> unittestresult.out
#
# player: player.c interface.o
# 	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
#
# all: playdom player
#
# tests: unittest4.c unittest3.c unittest2.c unittest1.c dominion.o rngs.o
# 	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
# 	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
# 	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
# 	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
# 	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
# 	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
# 	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
# 	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
#
# alltests.out:
# 	gcc -c rngs.c -g $(CFLAGS)
# 	gcc -c dominion.c -g $(CFLAGS)
#
# 	gcc -o rtcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
# 	./rtcard
# 	gcc -o rtadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
# 	./rtadventurer
#
# 	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
# 	./unittest1
# 	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
# 	./unittest2
# 	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
# 	./unittest3
# 	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
# 	./unittest4
#
# 	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
# 	./cardtest1
# 	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
# 	./cardtest2
# 	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
# 	./cardtest3
# 	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
# 	./cardtest4
#
# 	gcov dominion.c >> alltests.out
# 	cat dominion.c.gcov >> alltests.out
#
# 	gcov dominion.c -b >> alltests.out
# 	cat dominion.c.gcov >> alltests.out
#
# randomtestcard.out:
# 	gcc -c rngs.c -g $(CFLAGS)
# 	gcc -c dominion.c -g $(CFLAGS)
#
# 	gcc -o rtcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
# 	./rtcard >> randomtestcard.out
# 	gcov randomtestcard.c >> randomtestcard.out
#
# 	gcov dominion.c >> randomtestcard.out
# 	cat dominion.c.gcov >> randomtestcard.out
#
# 	gcov dominion.c -b >> randomtestcard.out
# 	cat dominion.c.gcov >> randomtestcard.out
#
# randomtestadventurer.out:
# 	gcc -c rngs.c -g $(CFLAGS)
# 	gcc -c dominion.c -g $(CFLAGS)
#
# 	gcc -o rtadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
# 	./rtadventurer >> randomtestadventurer.out
# 	gcov randomtestadventurer.c >> randomtestadventurer.out
#
# 	gcov dominion.c >> randomtestadventurer.out
# 	cat dominion.c.gcov >> randomtestadventurer.out
#
# 	gcov dominion.c -b >> randomtestadventurer.out
# 	cat dominion.c.gcov >> randomtestadventurer.out
#
# unittestresults.out:
# 	gcc -c rngs.c -g $(CFLAGS)
# 	gcc -c dominion.c -g $(CFLAGS)
#
# 	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
# 	./unittest1 >> unittestresults.out
# 	gcov unittest1.c >> unittestresults.out
#
# 	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
# 	./unittest2 >> unittestresults.out
# 	gcov unittest2.c >> unittestresults.out
#
# 	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
# 	./unittest3 >> unittestresults.out
# 	gcov unittest3.c >> unittestresults.out
#
# 	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
# 	./unittest4 >> unittestresults.out
# 	gcov unittest4.c >> unittestresults.out
#
# 	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
# 	./cardtest1 >> unittestresults.out
# 	gcov cardtest1.c >> unittestresults.out
#
# 	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
# 	./cardtest2 >> unittestresults.out
# 	gcov cardtest2.c >> unittestresults.out
#
# 	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
# 	./cardtest3 >> unittestresults.out
# 	gcov cardtest3.c >> unittestresults.out
#
# 	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
# 	./cardtest4 >> unittestresults.out
# 	gcov cardtest4.c >> unittestresults.out
#
# 	gcov dominion.c >> unittestresults.out
# 	cat dominion.c.gcov >> unittestresults.out
#
# 	gcov dominion.c -b >> unittestresults.out
# 	cat dominion.c.gcov >> unittestresults.out
#
# clean:
# 	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out


clean:
	rm -f *.o playdom.exe randomtestcard.out randomtestcard randomtestadventurer.out randomtestadventurer playdom test.exe test player testDrawCard cardtest1 cardtest2 cardtest3 cardtest4 badTestDrawCard unittest1 unittest2 unittest3 unittest4 player.exe testInit testInit.exe  *.gcov *.gcda *.gcno *.so
	rm -rf *.dSYM
