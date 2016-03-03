# Name: YUNSIK CHOI
# CS 362 Winter 16
# Creates BugsInTeammate1.out
# makefile
# Usage: make -f Makefile

MEMBERFLAG = 1
CFLAGS = -Wall -lm

all: testcard runtestcard_adventurer runtestcard_smithy

testcard: testcard.c dominion.c rngs.c
	gcc -o testcard testcard.c dominion.c rngs.c $(CFLAGS)
	
runtestcard_adventurer: testcard
	./testcard adventurer > BugsInTeammate$(MEMBERFLAG).out
	
runtestcard_smithy: testcard
	./testcard smithy >> BugsInTeammate$(MEMBERFLAG).out
