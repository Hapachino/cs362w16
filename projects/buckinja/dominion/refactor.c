Janel Buckingham
CS 362 Winter 2016
Assignment 2

Added 5 new functions to dominion.h/dominion.c:
int playAdventurer(int currentPlayer, struct gameState *state);
int playSmithy(int currentPlayer, struct gameState *state, int handPos);
int playCutpurse(int currentPlayer, struct gameState *state, int handPos);
int playRemodel(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2);
int playMine(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2);

For each of these, the code was removed from the switch statement in cardEffect(), but they are each called 
from the case within the switch statement where they originally were implemented.  For example, 

	case adventurer:
		return playAdventurer(currentPlayer, state);
		
	instead of 
	
	case adventurer:
		// implementation
		return 0;
		
By having the switch statement return the return value of each of these functions (like 
'return playAdventurer(currentPlayer, state);' above), I was able to preserve the original return statements
in the switch statement.


Introduced the following bugs:

in playAdventurer:
	Changed this line:
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	To this:
		if (cardDrawn == copper && cardDrawn == silver && cardDrawn == gold)
	Which will guarantee that the condition will never be met.

	Changed this line:
		while(z-1>=0){
	To this:
		while(z-1>0){
	This introduces an off-by-one error that will prevent the final card in the temp array from
	being copied to the played card array and therefore being unintentionally removed entirely 
	from play.
	
in playSmithy:
	Changed this line:
		for (i = 0; i < 3; i++)
	To this:
		for (i = 0; i <= 3; i++)
	Which will result in an extra card drawn 
      
	Changed this line:
		discardCard(handPos, currentPlayer, state, 0);
	To this:
	    discardCard(handPos, currentPlayer, state, 1);
	Which will raise the flag to permanently trash the discarded card instead of moving it to
	played cards array.
	
in playCutpurse:
	Changed this line:
		discardCard(j, i, state, 0);
	To this:
		discardCard(i, j, state, 0);
	Which sends the currentPlayer as the handPos parameter and visa versa
	
in playRemodel:
	Removed the break statement from
		for (i = 0; i < state->handCount[currentPlayer]; i++)
		{
		  if (state->hand[currentPlayer][i] == j)
			{
			  discardCard(i, currentPlayer, state, 0);			
			  break;
			}
		}
	which will remove all matching conditions in the loop instead of just the first one.
	
in playMine:
	Changed this line:
		if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
	To this:
		if (state->hand[currentPlayer][choice1] > copper || state->hand[currentPlayer][choice1] > gold)
	Which will cause the function to return an error from a valid input


	
	
	