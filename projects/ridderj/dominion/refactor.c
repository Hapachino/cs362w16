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

********************
Bugs introducted to adventurerCardFunc(), smithyCardFunc(), villageCardFunc(), cutpurseCardFunc()
********************


adventurerCardFunc() Bug
--------------------
Original Code:
   cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
Changed Code with Bug:
   -cardDrawn is now not the top card of hand, it's the second to the top of hand. This is done by changing the -1
   to a -2.
   
   cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-2];

   
   
   
smithyCardFunc() Bug
--------------------
Original Code:
   for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
Changed Code with Bug:     
   -after the for loop is called, drawCard is called once again.
   for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
   drawCard(currentPlayer, state);
   
   
   
   
   
villageCardFunc() Bug
--------------------
Original Code:
   state->numActions = state->numActions + 2;
Changed Code with Bug: 
   -Changed the 2 to MAX_PLAYERS. If codes is tested with only
   two players, everything will seem fine, but 3 players and up
   will alter the amount of actions.

   state->numActions = state->numActions + state->numPlayers;
   

   
   
   
cutpurseCardFunc() Bug
--------------------
Original Code:
      updateCoins(currentPlayer, state, 2);
      for (i = 0; i < state->numPlayers; i++)
	{
	  if (i != currentPlayer)
 Changed Code with Bug: 
       - Card now skips currentPlayer and player 3.
       
       if (i != currentPlayer || i != 3)
       
