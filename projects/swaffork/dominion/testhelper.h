#ifndef _TESTHELPER_
#define TESTHELPER

#include "dominion.h"

struct StateDiff
{
    enum
    {
        NUM_PLAYERS = 0,
        SUPPLY_COUNT, // 1
        EMBARGO_TOKENS, // 2
        OUTPOST_PLAYED, // 3
        OUTPOST_TURN, //4
        WHOSE_TURN, // 5
        PHASE, // 6
        NUM_ACTIONS, // 7
        COINS, // 8
        NUM_BUYS, // 9
        HAND, // 10
        HAND_COUNT, // 11
        DECK, // 12
        DECK_COUNT, // 13
        DISCARD, // 14
        DISCARD_COUNT, // 15
        PLAYED_CARDS, // 16
        PLAYED_CARD_COUNT, // 17
        NUM_FIELDS // 18
    } Fields;

    int flags[NUM_FIELDS];
};

int initializeState(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
struct StateDiff compareStates(struct gameState* state1, struct gameState* state2);

#endif
