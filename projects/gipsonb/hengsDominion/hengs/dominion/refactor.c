Stephen Heng
CS362 Winter 2016
Assignment 2: refactor.c and bugs

In the dominion.c file, I have refactored the following cases:

int playAdventurer(struct gameState *state, int currentPlayer, int drawntreasure, int cardDrawn, int temphand[], int z);
int playSmithy(int currentPlayer, struct gameState *state, int handPos);
int playVillage(int currentPlayer, struct gameState *state, int handPos);
int playMine(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2, int i, int j);
int playSteward(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2, int choice3);

I have added these functions in the dominion.h file.

Bugs for 4 of the 5 cases:

1. int playSmithy
  
correct:

  for (i = 0; i < 3; i++)
  
bug:

  for (i = 1; i < 3; i++)

This will result in 2 cards drawn to the player instead of 3.  

2. int playAdventurer

correct:
	state->handCount[currentPlayer]--;

bug:
    //state->handCount[currentPlayer]--; 

I have whitedout the statement which will not remove the top card(the most recently drawn one)

3. playVillage

correct:
	state->numActions = state->numActions + 2;

bug:
	state->numActions = state->numActions + 1;
	
This will allow the player to only have 1 bonus action instead of 2.

4. playSteward

correct:
    drawCard(currentPlayer, state);
    drawCard(currentPlayer, state);
bug:
	drawCard(currentPlayer, state);
    //drawCard(currentPlayer, state);
	
I have whitedout one of the drawcards which will allow the player in choice1==1 to only draw 1 card
instead of 2