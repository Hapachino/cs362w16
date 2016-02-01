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
	playCardSmithy()     - cardtest1.c
	playCardAdventurer() - cardtest2.c
	playCardVillage()    - cardtest3.c
	playCardGreatHall()  - cardtest4.c


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


playCardAdventurer()
------------------------------------------------------------------
1) It was discovered that this was drawing up to 3 treasure cards
instead of only 2.

2) Cards that were drawn and not treasure cards were being placed
into the discard pile instead of the played card pile.  This is
not how this card is supposed to function, and it could lead to 
infinte loop situation of constantly re-shuffling the same set
of cards that lack a treasure card.

3) If there are not 2 treasure cards to draw from the deck or the
discard pile, the loop does not stop when cards run out until the
handCount for that player has been thrown into negative numbers.
(I'm not sure why the loop stops at all to be honest.)  This is
a cause of several other issues going on with this function.

playCardVillage()
-------------------------------------------------------------------
1) The number of actions in the game state does not update properly
instead of adding 2, it always just sets the actions to 2.

2) The player's hand after playing the village card does not match
what it is supposed to.  The issue here is that the village card
is never actually discarded from the player's hand.
*/