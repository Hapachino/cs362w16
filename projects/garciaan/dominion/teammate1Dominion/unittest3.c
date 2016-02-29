/* -----------------------------------------------------------------------
 * gainCard()
 *
 * The gainCard() function works as follows:
 *  -checks if chosen card is in supply
 *  -adds card to 1: deck OR 2: hand OR 3: discard pile of current player
 *  -decrements count of card in supply
 *
 * Things to check:
 *  -if dest == 1: player's deckCount increased, card on top of deck is chosen card
 *  -if dest == 2: player's handCount is increased, card on top of hand is chosen card
 *  -if dest == 3: player's discardCount is increased, card on top of discard is chosen card
 *  -supply count of chosen card has decreased
 *  -nothing else in state has changed
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int i;
    int player;
    int dest;
    int supplyPos;
    int flag;
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
    struct gameState state;
    struct gameState originalState;

    // Initialize gameState
    if (initializeState(numPlayers, cards, seed, &state) != 0)
    {
        printf("Error: Could not initialize state.\n");
        return -1;
    }

    // Preserve the original game state to compare result of shuffle()
    memcpy(&originalState, &state, sizeof(struct gameState));

    printf ("Testing gainCard():\n");
    player = 0;
    state.deckCount[player] = 0;
    state.handCount[player] = 0;
    state.discardCount[player] = 0;
    supplyPos = adventurer;

    for (dest = 1; dest < 4; dest++)
    {
        if (gainCard(supplyPos, &state, dest, player) < 0)
        {
            printf("ERROR: gainCard() failed, dest = %d\n", dest);
            return -1;
        }

        struct StateDiff df = compareStates(&originalState, &state);
        for (i = 0; i < NUM_FIELDS; i++)
        {
            flag = df.flags[i];

            if (flag == 1 && i != SUPPLY_COUNT 
                          && i != DECK
                          && i != DECK_COUNT
                          && i != HAND
                          && i != HAND_COUNT
                          && i != DISCARD
                          && i != DISCARD_COUNT)
            {
                printf("\tERROR: unexpected state change at df.flags[%d]\n", i);
                return -1;
            }
        }

        // dest == 1: player's deckCount increased, card on top of deck is chosen card
        if (dest == 1 && (state.deckCount[player] != originalState.deckCount[player] + 1
                          || state.deck[player][0] != supplyPos))
        {
            printf("\tERROR: card not gained into deck. dest = %d\n", dest);
            printf("\tNew deck count: %d\n", state.deckCount[player]);
            printf("\tExpected deck count: %d\n", originalState.deckCount[player] + 1);
        }
        // dest == 2: player's handCount is increased, card on top of hand is chosen card
        if (dest == 2 && (state.handCount[player] != originalState.handCount[player] + 1
                          || state.hand[player][0] != supplyPos))
        {
            printf("\tERROR: card not gained into hand.\n");
        }
        // dest == 3: player's discardCount is increased, card on top of discard is chosen card
        if (dest == 3 && (state.discardCount[player] != originalState.discardCount[player] + 1
                          || state.discard[player][0] != supplyPos))
        {
            printf("\tERROR: card not gained into discard.\n");
        }

        // supply count of chosen card has decreased
        if (state.supplyCount[supplyPos] != originalState.supplyCount[supplyPos] - 1)
        {
            printf("ERROR: supplyCount() is incorrect.\n");
            printf("New supplyCount: %d\n", state.supplyCount[supplyPos]);
            printf("Expected supplyCount: %d\n", originalState.supplyCount[supplyPos] - 1);
        }

        // after each dest tested, restore original game state for new test
        memcpy(&state, &originalState, sizeof(struct gameState));
    }

    printf ("End of gainCard() test.\n");
    return 0;
}
