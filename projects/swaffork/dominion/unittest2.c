/* -----------------------------------------------------------------------
 * discardCard()
 *
 * The discardCard() function works as follows:
 *  -add card to playedCards pile
 *  -set the played card to -1
 *  -decrement hand count
 *  -if there are cards left in the player's hand, move last hard to empty
 *  space left by discarded card
 *
 * Things to check:
 *  -playedCards contains the card that was discarded (df.flags[PLAYED_CARDS] == 1)
 *  -playedCardCount increased by 1 (df.flags[PLAYED_CARD_COUNT] == 1)
 *  -player's hand has decreased by 1 (df.flags[HAND] == df.flags[HAND_COUNT] == 1)
 *  -nothing else in gamestate has changed
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare(const void* a, const void* b);

int main()
{
    int i;
    int count;
    int player;
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

    // Put card into player's hand
    player = 0;
    count = 0;

    int deckCounter = state.deckCount[player];

    if (deckCounter == 0)
    {
        printf("ERROR: Could not draw card.\n");
        return -1;
    }

    state.hand[player][count] = state.deck[player][deckCounter - 1];//Add card to hand
    state.deckCount[player]--;
    state.handCount[player]++;//Increment hand count

    // Preserve the original game state to compare result of shuffle()
    memcpy(&originalState, &state, sizeof(struct gameState));

    printf ("Testing discardCard():\n");


    if (discardCard(0, player, &state, 0) < 0)
    {
        printf("\tERROR: discardCard() failed.\n");
        return -1;
    }

    struct StateDiff df = compareStates(&originalState, &state);
    
    for (i = 0; i < NUM_FIELDS; i++)
    {
        flag = df.flags[i];

        if (flag == 1 && i != PLAYED_CARDS
                      && i != PLAYED_CARD_COUNT
                      && i != HAND
                      && i != HAND_COUNT)
        {
            printf("\tERROR: unexpected state change at df.flags[%d]\n", i);
            return -1;
        }
        else if (flag == 0 && (i == PLAYED_CARDS
                               || i == PLAYED_CARD_COUNT
                               || i == HAND
                               || i == HAND_COUNT))
        {
            printf("\tERROR: expected state change at df.flags[%d]\n", i);
            return -1;
        }
    }

    printf("All state changes as expected."\n);

 /*  -playedCards contains the card that was discarded (df.flags[PLAYED_CARDS] == 1)
 *  -playedCardCount increased by 1 (df.flags[PLAYED_CARD_COUNT] == 1)
 *  -player's hand has decreased by 1 (df.flags[HAND] == df.flags[HAND_COUNT] == 1)
 *  -nothing else in gamestate has changed */

    printf ("All tests passed.\n");
    return 0;
}
