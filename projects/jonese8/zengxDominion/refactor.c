// cs 362 Xiaohan Zeng assignment2

playAdventurer()
Description:
Play adventurer card
Input:
struct gameState state – holds a pointer to a gameState variable
int currentplayer
 int temphand[MAX_HAND]- tempcard save arr

Return:
No return;

playSmithy()
Description:
Play smithy card; 
Input:
struct gameState state – holds a pointer to a gameState variable
int currentplayer
handpost – the position of the card which will be play

Return:
No return;

playVillage ()
Description:
Play village card; 
Input:
 struct gameState state – holds a pointer to a gameState variable
 int currentplayer
 handpost – the position of the card which will be play

Return:
No return;

play playSteward ()
Description:
Play playSteward card; 
Input:
struct gameState state – holds a pointer to a gameState variable
 int currentplayer
 handpost – the position of the card which will be play
 choice1-3 : 3 different actions this card can do, player needs to choose one


Return:
No return;

playCutpurse ()
Description:
Play Cutpurse card; 
Input:
struct gameState state – holds a pointer to a gameState variable
int currentplayer
handpost – the position of the card which will be play

Return:
No return;

Bugs:
for playAdventurer : delete in "=" in "while (z - 1 > 0)" you will dismiss one less card(the first card you draw that is not a treasure card);
for playSmithy: change i = 0 to i = 1 in "for (i = 1; i < 3; i++)" you will get 2 cards instead of 3 cards
for playVillage : change + 2 to + 1 in "state->numActions = state->numActions + 1;" action will only get 1 more instead of 2
for playSteward : switch 1 and 2 for choice1; action will be switched for this choice
for playCutpurse: add "=" to "for (i = 0; i <= state->numPlayers; i++)" : every player will drop copper or other as the action, including this player 

