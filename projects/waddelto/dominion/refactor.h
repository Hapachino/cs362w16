#ifndef _REFACTOR_H
#define _REFACTOR_H

#include "refactor.c"

//car effect takes the following elements
//int cardeffect(int card, int choice1, int choice2, int choice3, struct gamestate *state, int handpos, int *bonus)
int adventureEffect(struct gameState *state);
int smithyEffect(struct gameState *state, int handPos);
int feastEffect(int choice1, struct gameState *state); 
int mineEffect(int choice1, int choice2, struct gameState *state, int handPos);
int cutpurseEffect(struct gameState *state, int handPos);





#endif
