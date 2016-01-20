#ifndef _TEST_HELPERS_H
#define _TEST_HELPERS_H

#include "dominion.h"

#define MAX_CURSE 30
#define MAX_VICTORY 12
#define MAX_TREASURE 40
#define MAX_ACTION 12
#define MAX_EMBARGO 3
#define MAX_COINS 10

struct gameState* randomGame();
void printGameState(struct gameState *g);

#endif