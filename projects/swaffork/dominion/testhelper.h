#ifndef _TESTHELPER_
#define TESTHELPER

#include "dominion.h"

struct StateDiff
{
    enum
    {
        NUM_PLAYERS = 0,
        SUPPLY_COUNT,
        EMBARGO_TOKENS,
        OUTPOST_PLAYED,
        OUTPOST_TURN,
        WHOSE_TURN,
        PHASE,
        NUM_ACTIONS,
        COINS,
        NUM_BUYS,
        HAND,
        HAND_COUNT, 
        DECK,
        DECK_COUNT,
        DISCARD,
        DISCARD_COUNT,
        PLAYED_CARDS,
        PLAYED_CARD_COUNT,
        NUM_FIELDS
    } Fields;

    int flags[NUM_FIELDS];
};

int initializeState(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
struct StateDiff compareStates(struct gameState* state1, struct gameState* state2);

#endif
