/****************************************************************************
* Author: Isaiah Perrotte-Fentress
* Class: CS362w16
* Assignment: Assignment2
* File: Contains refactor notes on changes made to dominion.c and dominion.h,
* and also documents the bugs introduced for each card.
*****************************************************************************

/*
Summary: For all of the cards, I moved the code for completing the action to 
functions at the end of dominion.c. I added the functions to dominion.h so 
they were  accessible to the switch statement. Now the case statement only 
contains the  function call and a return 0.

Card: Adventurer
Refactored function: int playAdventurer(struct gameState *state);
Bug: Introduced 3 errors to the adventurer card. In the first while loop 
changed drawntreasure < 2 to drawntreasure <= 2. This causes 3 treasures 
to be found before the function is considered complete. Additionally, I 
introduced a bug that makes it so that gold aren't counted as treasure in 
the IF statement by deleting || cardDrawn == gold. This causes users to add 
this card to their temp hand instead. Finally, in the final while loop I 
changed it from while (z-1>=0) to while (z-1>0). This causes the user to not 
receive all cards from their temp hand to the discard. This effectively 
removes a card from the game.  

Card: Smithy
Refactored function: int playSmithy(struct gameState *state, int handPos);
Bug: Added an error to the if statmeent by changing from < to <=, which 
causes 4 extra cards to be given instead of 3. Also added a second drawCard 
function which always gives cards to player 2. This causes both current 
player and player 2 to get 4 cards. 

Card: Village
Refactored function: int playVillage(struct gameState *state, int handPos);
Bug: Changed the number of actions granted from +2 to +5, which will granted
more actions than intended. Additionally, changed input to draw card from 
currentPlayer to 1, which causes the first player to always get the card. 

Card: Great Hall
Refactored function: int playGreatHall(struct gameState *state, int handPos);
Bug: Changed the draw card function so that the first player always gets the 
card, not the current player. CurrentPlayer = 1 is how the int is passed. 

Card: Council Room
Refactored function: int playCouncilRoom(struct gameState *state, int handPos)
Bug: Changed the if statement from != to ==, so that only the current player 
gets an extra card, and not all other players as designed. Also changed the
trash flag on the discard card function. Changed from 0 to 1, meaning the card
will now no longer be available in the game. 
*/