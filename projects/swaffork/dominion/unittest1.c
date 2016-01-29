/* -----------------------------------------------------------------------
 * shuffle()
 *
 * The shuffle() function works as follows:
 *  -create a new deck to hold shuffled deck
 *  -sort the player's cards
 *  -pick random cards from the player's deck and place into new deck
 *  -copy new deck into player's deck
 *
 * Things to check:
 *  -Set of cards in deck is the same (check first that deck count is unchanged)
 *  -Order of cards in deck is not the same
 *  -Set and order of other players' decks is the same
 *  -If the player has <= 1 card in his or her deck, everything should be the same
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int compare(const void* a, const void* b);

// This function differs from the original initializeGame() in dominion.c
// in that it does not call shuffle() and does not draw cards for first player
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

    //set player decks
    for (i = 0; i < numPlayers; i++)
    {
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

int main() {
    int i;
    int player;
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *state = malloc(sizeof(struct gameState));
    struct gameState *originalState = malloc(sizeof(struct gameState));

    // Initialize gameState
    if (initializeState(numPlayers, cards, seed, state) != 0)
    {
        printf("Error: Could not initialize state.\n");
    }

    // Preserve the original game state to compare result of shuffle()
    memcpy(originalState, state, sizeof(struct gameState));

    printf ("Testing shuffle():\n");

    for (player = 0; player < numPlayers; player++)
    {
        printf("Player %d:\n", player);

        if (shuffle(player, state) < 0)
        {
            printf("\tERROR: shuffe() failed.\n");
            return -1;
        }
        
        // FUNCTION TO RETURN WHAT CHANGED IN STATE: STATECOMPARE(*STATE, *ORIGINALSTATE)

        // Check first that each player's deck count is unchanged)
        int p;
        for (p = 0; p < numPlayers; p++)
        {
            if (state->handCount[p] != originalState->handCount[p])
            {
                printf("\tERROR: handCount not the same at player%d\n", p);
                return -1;
            }
        }

        // Check order of cards for each player 
        for (p = 0; p < numPlayers; p++)
        {
            i = 0;
            while ( (i < state->deckCount[p]) &&
                    (state->deck[p][i] == originalState->deck[p][i]) )
            {
                printf("\tshuffled card %d: %d\n", i, state->deck[p][i]);
                printf("\toriginal card %d: %d\n", i, originalState->deck[p][i]);
                i++;
            }
            
            // Check if order of cards in shuffled deck is the same
            if (p == player && i >= state->deckCount[p])
            {
                printf("Error: Order of shuffled deck is the same.\n");
                return -1;
            }

            // Check if order of cards in unshuffled deck is the same
            if (p != player && i < state->deckCount[p])
            {
                printf("Error: Order of non-shuffled deck is different.\n");
                return -1;
            }
        }
        
        // Check that shuffled deck has same set of cards
        qsort((void*)(state->deck[0]), state->deckCount[player], sizeof(int), compare);
        qsort((void*)(originalState->deck[0]), state->deckCount[player], sizeof(int), compare);

        if (memcmp(state, originalState, sizeof(struct gameState)) != 0)
        {
            printf("\tERROR: memcmp failed.\n");
            return -1;
        }
    }

    printf("All tests passed!\n");

    return 0;
}
