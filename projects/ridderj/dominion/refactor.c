cardEffect() function switch cases refactored for adventurer, smithy, village,
cutpurse, and steward cards. Code for each card was put into functions with
the following names:

-adventurerCardFunc()
-smithyCardFunc()
-villageCardFunc()
-cutpurseCardFunc()
-stewardCardFunc()

The 5 new card functions were place ahead of the cardEffect() function in the
dominion.c file. Then the functions were called in the same locations as the code was before
refactoring. Prototypes for the 5 new card functions were added to
dominion_helpers.h file.

Bugs introducted to adventurerCardFunc(), smithyCardFunc(), villageCardFunc(), cutpurseCardFunc()

adventurerCardFunc() Bug
--------------------
Original Code Line:
   cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
Changed Code Line with Bug:
   -cardDrawn is now not the top card of hand, it's the second to the top of hand. This is done by changing the -1
   to a -2.
   
   cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-2];

smithyCardFunc() Bugs
--------------------
Original Code Line:
   for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
Changed Code Line with Bug:     
   -after the for loop is called, drawCard is called once again.
   for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
   drawCard(currentPlayer, state);
   
villageCardFunc() Bugs
--------------------
