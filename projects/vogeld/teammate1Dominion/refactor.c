/*
Made changes to dominion.c
Include the addition of the following functions:
int adventurerCard(struct gameState * state);
int baronCard(struct gameState *state, int choice1);
int smithyCard(struct gameState *state, int handPos);
int councilRoomCard(struct gameState *state, int handPos);
int villageCard(struct gameState *state, int handPos);


They take the place of existing code that was present in the swtich statement of cardEffect.

The same arguments that are present in the cardEffect function are also used again in the the 
implemented card functions. With the exception of iterators, and the currentPlayer declaration
 which as only set on a case by case basis within the function. 


*/


/* Adventurer bug  
Second while loop should be (z - 1 >= 0)
*/

/* Smithy bug
should be:
for (i = 0; i < 3; i++)
{
*/

/*Council Room Bug

second for loop i is not initilaized to 0
//Each other player draws a card
for ( i = 0; i < state->numPlayers; i++)
{

*/

/*Village Bug 
missing statement:
//+1 Card
drawCard(currentPlayer, state);

*/

/*baron Bug
should be:
int card_not_discarded = 1;

*/