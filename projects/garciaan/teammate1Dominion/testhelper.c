/* Unit Test Helper Extraordinaire for Dominion */
#include "testhelper.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int testHelperSetUpState(struct gameState* state)
{
    int player = 0;
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};

    if (initializeGame(numPlayers, cards, seed, state) != 0)
    {
        return 0;
    }
    state->whoseTurn = player;
    return 1;
}

// This function differs from the original initializeGame() in dominion.c in
// that it does not call shuffle() and does not draw cards for first player and
// has different initial cards in each deck for easier debugging
int initializeState(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)
{
    printf("Beginning initializing state.\n");

    int i;
    int j;
    //set up random number generator
    SelectStream(1);
    PutSeed((long)randomSeed);

    //check number of players
    if (numPlayers > MAX_PLAYERS || numPlayers < 2)
    {
        return -1;
    }

    //set number of players
    state->numPlayers = numPlayers;

    //check selected kingdom cards are different
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (j != i && kingdomCards[j] == kingdomCards[i])
            {
                return -1;
            }
        }
    }
    //initialize supply
    ///////////////////////////////

    //set number of Curse cards
    if (numPlayers == 2)
    {
        state->supplyCount[curse] = 10;
    }
    else if (numPlayers == 3)
    {
        state->supplyCount[curse] = 20;
    }
    else
    {
        state->supplyCount[curse] = 30;
    }

    //set number of Victory cards
    if (numPlayers == 2)
    {
        state->supplyCount[estate] = 8;
        state->supplyCount[duchy] = 8;
        state->supplyCount[province] = 8;
    }
    else
    {
        state->supplyCount[estate] = 12;
        state->supplyCount[duchy] = 12;
        state->supplyCount[province] = 12;
    }

    //set number of Treasure cards
    state->supplyCount[copper] = 60 - (7 * numPlayers);
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    //set number of Kingdom cards
    for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
        for (j = 0; j < 10; j++)           		//loop chosen cards
        {
            if (kingdomCards[j] == i)
            {
                //check if card is a 'Victory' Kingdom card
                if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
                {
                    if (numPlayers == 2){ 
                        state->supplyCount[i] = 8; 
                    }
                    else{ state->supplyCount[i] = 12; }
                }
                else
                {
                    state->supplyCount[i] = 10;
                }
                break;
            }
            else    //card is not in the set choosen for the game
            {
                state->supplyCount[i] = -1;
            }
        }

    }

    ////////////////////////
    //supply intilization complete

    // Set player decks:
    for (i = 0; i < numPlayers; i++)
    {
        /*
        state->deckCount[i] = 0;
        for (j = 0; j < 3; j++)
        {
            state->deck[i][j] = estate;
            state->deckCount[i]++;
        }
        for (j = 3; j < 10; j++)
        {
            state->deck[i][j] = copper;
            state->deckCount[i]++;		
        }
        */
        state->deck[i][0] = estate;
        state->deck[i][1] = copper;
        state->deck[i][2] = silver;
        state->deck[i][3] = gold;
        state->deck[i][4] = adventurer;
        state->deck[i][5] = council_room;
        state->deck[i][6] = feast;
        state->deck[i][7] = gardens;
        state->deck[i][8] = mine;
        state->deck[i][9] = remodel;
        state->deckCount[i] = 10;
    }
    
    // Initialize hand sizes to zero
    for (i = 0; i < numPlayers; i++)
    {  
        state->handCount[i] = 0;
        state->discardCount[i] = 0;
    }

    //set embargo tokens to 0 for all supply piles
    for (i = 0; i <= treasure_map; i++)
    {
        state->embargoTokens[i] = 0;
    }
    
    //initialize first player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = 0;
    state->handCount[state->whoseTurn] = 0;

    printf("Completed initializing state.\n");
    
    return 0;
}

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
        if (state1->deckCount[i] != state2->deckCount[i])
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
        if (state1->discardCount[i] != state2->discardCount[i])
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

