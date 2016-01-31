#ifndef _TEST_HELPER
#define _TEST_HELPER
#include "dominion.h"

//function to randomize the game state
void randomizeGameState(struct gameState game);
void randomizeKingdomCards(int k[10]);
void printGame(struct gameState control);
void resetGameState(struct gameState *Game);
int flagCheck(int testState, int validFlag);
void printDeck(struct gameState *game);
void printHand(struct gameState *game);






#endif
