# Name: YUNSIK CHOI
# CS 362 Winter 16
# Creates randomtestcard.out and randomtestadventurer.out
# makefile

CFLAGS = -Wall -coverage -fpic -lm

all: randomtestcard randomtestadventurer runrandomtestcard runrandomtestadventurer

randomtestcard: randomtestcard.c dominion.c rngs.c
	gcc -o randomtestcard randomtestcard.c dominion.c rngs.c $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.c rngs.c
	gcc -o randomtestadventurer randomtestadventurer.c dominion.c rngs.c $(CFLAGS)
	
runrandomtestcard: randomtestcard
	./randomtestcard
	gcov randomtestcard.c -b > randomtestcard.out
	cat randomtestcard.c.gcov >> randomtestcard.out

runrandomtestadventurer: randomtestadventurer
	./randomtestadventurer
	gcov randomtestadventurer.c -b > randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out
