#include "dominion.h"
#include "test_helper.h"
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <math.h>

/******************************
 * Testing fullDeckCount
 *
 * First we're going to randomize a deck, 
 * including hand, deck, and discard counts.
 * Then we'll randomize the cards in those decks
 * Then we'll pass the game state to fullDeckCount 
 * and check them.
 * ***************************/

void unittest4(long seed)
{
    int i, j, m, n, res;
    int count;
    int fail;
    int card;
    count = 1000;
    fail = 0;

    for (i = 0; i < count; i++)
    {
        int k[10];
        randomizeKingdomCards(k);

        struct gameState Tester;
        int numPlayers = floor(Random() * MAX_PLAYERS);
        initializeGame(numPlayers, k, seed, &Tester);

        card = floor(Random() * (treasure_map + 1));

        for (j = 0; j < Tester.numPlayers; j++)
        {
            Tester.handCount[j] = floor(Random() * MAX_HAND);
            for (m = 0; m < Tester.handCount[j]; m++){
                Tester.hand[j][m] = floor(Random() * (treasure_map + 1));
            }

            Tester.deckCount[j] = floor(Random() * MAX_DECK);
            for (m = 0; m < Tester.deckCount[j]; m++){
                Tester.deck[j][m] = floor(Random() * (treasure_map + 1));
            }

            Tester.discardCount[j] = floor(Random() * MAX_DECK);
            for (m = 0; m < Tester.discardCount[j]; m++){
                Tester.discard[j][m] = floor(Random() * (treasure_map + 1));
            }
        }

        for (j = 0; j < Tester.numPlayers; j++){
            n = 0;
            for (m = 0; m < Tester.handCount[j]; m++)
                if (Tester.hand[j][m] == card) n++;
            
            for (m = 0; m < Tester.deckCount[j]; m++)
                if (Tester.deck[j][m] == card) n++;

            for (m = 0; m < Tester.discardCount[j]; m++)
                if (Tester.discard[j][m] == card) n++;
            
            
            res = fullDeckCount(j, card, &Tester); 

            if (n != res) fail++;
        }


    }

    printf("fullDeckCount Test: Tests: %d\tPassed: %d\tFailed: %d\n", count, count - fail, fail);
    return;
}
