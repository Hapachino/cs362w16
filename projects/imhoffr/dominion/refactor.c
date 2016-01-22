/*
Regina Imhoff
CS 362 Winter 2016
Assignment 2

I added five new functions to dominion.c:
  int playAdventurer(int currentPlayer, struct gameState *state)
  int playSmithy(int currentPlayer, struct gameState *state, int handPos)
  int playCouncilRoom(int currentPlayer, struct gameState *state, int handPos)
  int playSeaHag(int currentPlayer, struct gameState *state)
  int playMine(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2)

For all of these functions code was moved from the switch statement and called from the case 
in the switch statement. 

Bugs:
  playAdventurer:
    changed this line:
	while(z-1>=0)
    to:
	while(z-1>0)
    Making this an off-by-one error that will stop the final card in temp hand from being
    copied to the played cards, removing it entirely.  

  playSmithy:
    change this line:
    	for(i = 0; i <= 3; i++)
    to:
	for(i = 1; i <= 3; i++)
    This will make an error where only 2 cards will be drawn instead of 3.  
  
  playCouncilRoom:
    change this line:
	state->numBuys++;
    to:
	state->numBuys+=2;
    This will make an error where the number of buys increases by 2 instead by 1.

  playSeaHag:
    change this line:
	if(i != currentPlayer){
    to:
	if(i = currentPlayer){
    This will make an error where the current player gets the curse instead of the other players.

  playMine:
    No bugs made in this function.  

*/
