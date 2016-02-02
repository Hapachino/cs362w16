/* Unit Test Helper Extraordinaire for Dominion */
#include "testhelper.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

struct StateDiff compareStates(struct gameState* state1, struct gameState* state2)
{
    struct StateDiff sd;
    int i;
    int j;
    // initialize all flags to true
    for (i = 0; i < NUM_FIELDS; i++)
    {
        sd.flags[i] = 1;
    }

    if (state1->numPlayers == state2->numPlayers)
    {
        sd.flags[NUM_PLAYERS] = 0;
    }

    // Check supply count of every card; if any have changed, set flag to true
    for (i = 0; i < treasure_map + 1; i++)
    {
        if (state1->supplyCount[i] == state2->supplyCount[i])
        {
            sd.flags[SUPPLY_COUNT] = 0;
        }
        else
        {
            sd.flags[SUPPLY_COUNT] = 1;
            break;
        }
    }

    for (i = 0; i < treasure_map + 1; i++)
    {
        if (state1->embargoTokens[i] == state2->embargoTokens[i])
        {
            sd.flags[EMBARGO_TOKENS] = 0;
        }
        else
        {
            sd.flags[EMBARGO_TOKENS] = 1;
            break;
        }
    }

    if (state1->outpostPlayed == state2->outpostPlayed)
    {
        sd.flags[OUTPOST_PLAYED] = 0;
    }

    if (state1->outpostTurn == state2->outpostTurn)
    {
        sd.flags[OUTPOST_TURN] = 0;
    }

    if (state1->whoseTurn == state2->whoseTurn)
    {
        sd.flags[WHOSE_TURN] = 0;
    }

    if (state1->phase == state2->phase)
    {
        sd.flags[PHASE] = 0;
    }

    if (state1->numActions == state2->numActions)
    {
        sd.flags[NUM_ACTIONS] = 0;
    }

    if (state1->coins == state2->coins)
    {
        sd.flags[COINS] = 0;
    }

    if (state1->numBuys == state2->numBuys)
    {
        sd.flags[NUM_BUYS] = 0;
    }

    // Check if any player's hand has changed
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        for (j = 0; j < MAX_HAND; j++)
        {
            if (state1->hand[i][j] == state2->hand[i][j])
            {
                sd.flags[HAND] = 0;
            }
            else
            {
                sd.flags[HAND] = 1;
                break;
            }
        }
        if (sd.flags[HAND] == 1)
        {
            break;
        }
    }

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (state1->handCount[i] != state2->handCount[j])
        {
            sd.flags[HAND_COUNT] = 1;
            break;
        }
        sd.flags[HAND_COUNT] = 0;
    }

    // Check if any player's deck has changed
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        for (j = 0; j < MAX_DECK; j++)
        {
            if (state1->deck[i][j] != state2->deck[i][j])
            {
                sd.flags[DECK] = 1;
                break;
            }
            else
            {
                sd.flags[DECK] = 0;
            }
        }
        if (sd.flags[DECK] == 1)
        {
            break;
        }
    }
    
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (state1->deckCount[i] != state2->deckCount[j])
        {
            sd.flags[DECK_COUNT] = 1;
            break;
        }
        sd.flags[DECK_COUNT] = 0;
    }

    // Check if any player's discard pile has changed
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        for (j = 0; j < MAX_DECK; j++)
        {
            if (state1->discard[i][j] != state2->discard[i][j])
            {
                sd.flags[DISCARD] = 1;
                break;
            }
            sd.flags[DISCARD] = 0;
        }
        if (sd.flags[DISCARD] == 1)
        {
            break;
        }
    }
    
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (state1->discardCount[i] != state2->discardCount[j])
        {
            sd.flags[DISCARD_COUNT] = 1;
            break;
        }
        sd.flags[DISCARD_COUNT] = 0;
    }

    for (i = 0; i < MAX_DECK; i++)
    {
        if (state1->playedCards[i] != state2->playedCards[i])
        {
            sd.flags[PLAYED_CARDS] = 1;
            break;
        }
        sd.flags[PLAYED_CARDS] = 0;
    }

    if (state1->playedCardCount == state2->playedCardCount)
    {
        sd.flags[PLAYED_CARD_COUNT] = 0;
    }

    return sd;
}

