#ifndef _TESTHELPER_
#define TESTHELPER

struct StateDiff
{
    enum Fields
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
    };

    int flags[NUM_FIELDS];
};

int* stateDiff(struct gameState* state1, struct gameState* state2);

#endif
