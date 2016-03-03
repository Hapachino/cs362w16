# Name: YUNSIK CHOI
# CS 362 Winter 16
#
# ************************************************************************************************
# Please change file name of dominion_bug_introduced.c to dominion.c before running this makefile.
# ************************************************************************************************
#
# Creates BugsInTeammate1.out
# makefile
# Usage: make -f Makefile

MEMBERFLAG = 0
CFLAGS = -Wall -lm

all: testcard runtestcard_adventurer runtestcard_smithy runtestcard_village runtestcard_great_hall

testcard: testcard.c dominion.c rngs.c
	gcc -o testcard testcard.c dominion.c rngs.c $(CFLAGS)
	
runtestcard_adventurer: testcard
	./testcard adventurer > BugsInTeammate$(MEMBERFLAG).out
	
runtestcard_smithy: testcard
	./testcard smithy >> BugsInTeammate$(MEMBERFLAG).out

runtestcard_village: testcard
	./testcard village >> BugsInTeammate$(MEMBERFLAG).out

runtestcard_great_hall: testcard
	./testcard great_hall >> BugsInTeammate$(MEMBERFLAG).out
