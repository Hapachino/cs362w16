#ifndef _TEST_HELPERS_H
#define _TEST_HELPERS_H

#include "dominion.h"

#define MAX_CURSE 30
#define MAX_VICTORY 12
#define MAX_TREASURE 40
#define MAX_ACTION 12
#define MAX_EMBARGO 3
#define MAX_COINS 10

struct gameState* randomGame(int randInt);
void printGameState(struct gameState *g);
int checkGameState(struct gameState *before, struct gameState *after);
int checkNumPlayers(struct gameState *before, struct gameState *after);
int checkSupply(struct gameState *before, struct gameState *after);
int checkEmbargo(struct gameState *before, struct gameState *after);
int checkOutpost(struct gameState *before, struct gameState *after);
int checkTurn(struct gameState *before, struct gameState *after);
int checkPhase(struct gameState *before, struct gameState *after);
int checkCoins(struct gameState *before, struct gameState *after);
int checkNumActions(struct gameState *before, struct gameState *after);
int checkNumBuys(struct gameState *before, struct gameState *after);
int checkHands(struct gameState *before, struct gameState *after);
int checkDecks(struct gameState *before, struct gameState *after);
int checkDiscards(struct gameState *before, struct gameState *after);
int checkPlayed(struct gameState *before, struct gameState *after);

#endif