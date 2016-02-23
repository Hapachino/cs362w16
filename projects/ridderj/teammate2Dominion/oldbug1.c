/*

bug1.c
James Linnenburger
CS362 Winter 2016
Assignment 3

Function Tests written:

	isGameOver()    - unittest1.c
	getCost()       - unittest2.c
        updateCoins()   - unittest3.c
	fullDeckCount() - unittest4.c

Card Tests written:
	playCardSmithy() - cardtest1.c


                       Bugs Report

isGameOver()
------------------------------------------------------------------
In the loop that counts how many supply stacks are zero, 
the loop does not go far enough, so it misses several cards
at the end of the list.
 
	Here is the actual loop from the isGameOver() code:
        -----------------------------------------------------
        for (i = 0; i < 25; i++)	//HERE IS THE PROBLEM
  	   //implementation here
        ------------------------------------------------------

This is only checking supplyCounts for the cards 0 - 24.  There
are in fact 27 different cards so the loop statement should read
    for (i = 0; i < 27; i++).

The loop as implemented is not looking at the sea_hag cards (#25)  
or the treasure_map cards (#26).
------------------------------------------------------------------


getCost()
------------------------------------------------------------------
Using my tester, all tests passed.  
------------------------------------------------------------------

updateCoins()
------------------------------------------------------------------
Using my tester, all tests passed. 
------------------------------------------------------------------


fullDeckCount()
------------------------------------------------------------------
Using my tester, all tests passed. 
------------------------------------------------------------------


playCardSmithy()
------------------------------------------------------------------
The testing of the playCardSmithy() resulted in a few bugs.

1) The played card count was off for every test.  The reason for
this was the determined to be that the discarded card was being
trashed instead of moved to the played card pile.  When the 
discardCard() call is adjusted to set the trashflag to 0 instead
of 1, this test passes everything.

2) The ordering of the hand after the smithy card was played did
not match what was expected.  The reason for this is that the
the value for 'handPos' is being mistakenly incremented with each
draw of the card.  (When that line is commented out, those
tests all pass).

*/