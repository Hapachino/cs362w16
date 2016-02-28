/********************************************************************************************************************************************************
*** Filename: BugsInTeammates.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Due date: 2/27/2016
*** Assignment 5
*** Description: Provide a documentation file to discuss which bugs you fix and mention your code changes. 
***
*******************************************************************************************************************************************************


The following bugs were found by teammates:

     ==================
     playAdventurer()
     =================
          The adventurer card effect was adding only 1 treasure card instead of two. The issue was that the counter for drawtreasure was starting at 1 and the for loop would therefore
          only loop once. 

          Fixed by:
               playAdventurer() - changed int drawntreasure = 1 to int drawntreasure = 0.


     ====================
     playSmithy()
     ====================
          The smithy card effect was not correctly adding three cards to the player's hand and was only adding 2. The issue was that the for loop was only looping twice instead of 3 times.

          Fixed by: 
               playSmithy() - Set i = 0 in the for loop from (i = 1; i < 3; i++).


     ======================
     playVillage()
     ======================
          The village card effect should increase the game state number of actions by exactly 2 but instead is increased by 3.

          Fixed by:
               playVillage() - changed state->numActions = state->numActions + 3 to state->numActions = state->numActions + 2.

     =====================
     minion card effect
     ====================
          When choice 1 was passed to the minion, it failed to add the 2 bonus coins. The issue was that the coins were being 
          credited to gamestate->coins which is zero'ed out when update coins is called.

          Fixed by:
               Changed "state->coins = state->coins + 2; " to "updateCoins(currentPlayer, state, 2);" It now calls updatecoins() with the bonus set to 2. 


The following were additional bug fixes not found by teammates:

     =========================
     playCutpurse()
     =========================
          cutPurse card is supposed to discard a copper card from opposing players but instead was discarding silver cards. 

          Fixed by:
               playCutpurse() - changed if (state->hand[i][j] == silver) to if (state->hand[i][j] == copper).


     ==========================
     isGameOver()
     =========================
         When at least 3 supply piles were empty. I discovered that the function only checks supply piles for cards 0-24. This means that when seahag or treasure_map were empty it would
         not correctly return 1 for the game to end.

         Fixed by: 
          Changeed "for (i = 0; i < 25; i++)" to "for (i = 0; i < 27; i++)"
      
       
