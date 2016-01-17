/********************************************************************************************************************************************************
*** Filename: refactor.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/15/2015
*** Due date: 1/17/2015
*** Assignment 2
*** Description: Pick five cards implemented in dominion.c. Choose 3 cards of your choice and smithy and adventurer cards are mandatory. 
***              Refactor the code so that these cards are implemented in their own functions, rather than as part of the switch statement in cardEffect. 
***              You should call the functions for these cards in the appropriate place in cardEffect. Check in your changes, with appropriate git commit messages.
***              Document your changes in a text file in your dominion source directory, called “refactor.c.” Your implementation of at least 4 of these 5 cards
***              should be incorrect in some way, i.e., you should introduce subtle bugs that are hard to catch in your changes. Introducing bugs in smithy and 
***              adventurer is mandatory.  Write information of your bugs also in refactor.c 
***
*******************************************************************************************************************************************************
Changes:

     dominion.h: Added function declarations for 5 new refactored card functions
          int playAdventurer(int currentPlayer, struct gameState *state);
          int playSmithy(int currentPlayer, struct gameState *state, int handPos);
          int playVillage(int currentPlayer, struct gameState *state, int handPos);
          int playSeahag(int currentPlayer, struct gameState *state);
          int playCutpurse(int currentPlayer, struct gameState *state, int handPos);

     dominion.c: Refactored 5 cards from the cardEffect() switch function into their own functions:
          These new functions can be located above the cardEffect() switch statement. 
          All 5 new functions are called from cardEffect() switch statement.


Bugs:
     playAdventurer() - changed int drawntreasure = 0 to int drawntreasure = 1.
     playSmithy() - changed i = 0 in the for loop to (i = 1; i < 3; i++).
     playVillage() - changed state->numActions = state->numActions + 2 to state->numActions = state->numActions + 3.
     playCutpurse() - changed if (state->hand[i][j] == copper) to if (state->hand[i][j] == silver).
          
*/