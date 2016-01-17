#Fanninme 
#Note: this is not code but rather documentation please ignore .c file type.
#Refactor.c describes refactoring done to create functions for Smithy,Adventurer and other cards additionally documenting bugs which were added to these functions.

//#Adventurer
Function:
Removed variable z, cardDrawn and drawntreasure from cardEffect and incorported them into the adventurer function.The variable extraCardsCount replaces z as a counter and drawn treasures is initialized to 0. 
The parameters of the function are a pointer to the state and the current player
Bugs: off by 1 error
line 653 :[state->handCount[currentPlayer]-1]; changed to
[state->handCount[currentPlayer]]; 


//#Feast
Function: removed int x from card effect
function receives current player,state and the choice1 (the players card choice).
Bugs:infinite loop
line 710:x = 0;//No more buying cards
is removed creating an infinite loop.

//#Smithy
Function: Function accepts currentplayer and stated. added int i to function
Bugs:extra discarded cards
//gives player +3 cards from their deck
    for (i = 0; i < 3; i++){
	    drawCard(currentPlayer, state);
	}		
is altered to
    for (i = 0; i < 3; i++){
	    drawCard(currentPlayer, state);
        discardCard(handPos, currentPlayer, state, 0);

	}	
resulting in discarding 4 cards instead of drawing 3 and discarding 1

//#Village
Function:parameters: currentPlayer, gameState, handPos
Bugs:
state->numActions = state->numActions + 2;
becomes:    state->numActions = state->numBuys + 2;/
			
//#Baron
Function:Moved game over clause to the end of the function since both if and else should check the gamestatus. Parameters:currentPlayer, gameState, choice1
Bugs:off by one error
for (;p < state->handCount[currentPlayer]; p++){
    state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
becomes:
  for (;p < state->handCount[currentPlayer]; p++){
    state->hand[currentPlayer][p] = state->hand[currentPlayer][p];

