/*
Kyle Johnson
johnsky3
CS 362
1/13/16

Documentation for card function implementations and bug descriptions.

Changes made to dominion.c 1/14/16:

Functions added:

/*********************************************************************
** Function: smithyCard
** Description: activates smithy card action (draw 3 cards)
** Parameters: gameState, currentPlayer, handPos
** Pre-Conditions: called within cardEffect()
** Post-Conditions: +3 cards in hand
*********************************************************************/ 

/*********************************************************************
** Function: adventurerCard
** Description: drawCard until 2 treasures have been added to hand, discard 
** other drawn cards.
** Parameters: gameState, currentPlayer
** Pre-Conditions: called within cardEffect()
** Post-Conditions: +2 treasure cards
*********************************************************************/ 

/*********************************************************************
** Function: villageCard
** Description: +1 card, +2 actions
** Parameters: gameState, currentPlayer, handPos
** Pre-Conditions: called within cardEffect()
** Post-Conditions: +1 card, +2 actions
*********************************************************************/ 

/*********************************************************************
** Function: greatHallCard
** Description: +1 card, +1 actions
** Parameters: gameState, currentPlayer, handPos
** Pre-Conditions: called within cardEffect()
** Post-Conditions: +1 card, +1 actions
*********************************************************************/ 

/*********************************************************************
** Function: outpostCard
** Description: increment state->outpostPlayed by one
** Parameters: gameState, currentPlayer, handPos
** Pre-Conditions: called within cardEffect()
** Post-Conditions: outpostPlayed + 1
*********************************************************************/ 

/*
All added functions were used to replace switch statement case code for the appropriate card in
the cardEffect() function.  Function prototypes were also added to dominion_helpers.h
*/

/*

bugs introduced:

adventurerCard() - counter for the temp hand loop initialized to z = 1 instead of 0, so player
will have 1 extra card in hand that was not discarded after drawing for treasure cards.

smithyCard() - drawCard() currentPlayer parameter changed to currentPlayer+1, which is the nextPlayer,
so the other player will draw three cards instead.

villageCard() - state->numActions changed from +2 to +1, so only 1 action will be added instead of 2.

greatHallCard() - discardCard() parameter for the trash flag changed from 0 to 1, so card will
be trashed instead of added to the played cards pile.

*/




