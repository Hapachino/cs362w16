#include "dominion.h"
#include "test_helper.h"
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <math.h>

/********************
 * Sea Hag Test
 *
 * We're going to randomize the kingdom cards
 * we're going to randomize the number of players
 *
 * we're going to intialize the game
 *
 * we're going to insure we have some curse cards
 * We're going to randomize hands and decks
 * We're going to copy the game state in to a control
 * we're going to check the effects:
 *  did the player discard the top card of his deck?
 *  did the player put a curse card on the top of his deck
 *  we're going to run the cycle a few times until we run out of curse
 *  cards
 *  Then we're going to run it some more and make sure the routine can
 *  handle the no curse cards state?
 *  *****************************/

void seaHagTest(long seed)
{

    int i, j, m, handPos, res;
    int playFail = 0;
    int count = 1000;
    int tests = 0;
    int fail = 0;

    for (i = 0; i < count; i++)
    {
        tests++;
        int k[10];
        randomizeKingdomCards(k);
        
        struct gameState Tester;
        struct gameState Control;

        int numPlayers = (Random() * (MAX_PLAYERS + 1 -2) + 2);
        assert(numPlayers >= 2 && numPlayers <= 4);

        initializeGame(numPlayers, k, seed, &Tester);

        for (j = 0; j < Tester.numPlayers; j++)
        {
            Tester.handCount[j] = floor(Random() * MAX_HAND);
            assert(Tester.handCount[j] < MAX_HAND);

            //we'll control the hand and deck and won't put any curse
            //cards in either, so we know that any curse cards that are
            //present were inserted by seahag
            for(m = 0; m < Tester.handCount[j]; m++){
                Tester.hand[j][m] = floor(Random() * (treasure_map + 1) + 1);
                assert(Tester.hand[j][m] != curse);
            }

            Tester.deckCount[j] = 5;
            Tester.deckCount[j] = floor(Random() * MAX_HAND);
            assert(Tester.handCount[j] < MAX_HAND);

            for (m= 0; m <Tester.deckCount[j]; m++){
                Tester.deck[j][m] = floor(Random() * (treasure_map + 1) + 1);
                assert(Tester.deck[j][m] != curse);
            }

            Tester.discardCount[j] = 0;
            handPos = floor(Random() * Tester.handCount[j]);
            Tester.hand[j][handPos] = sea_hag;
            Tester.phase = 0;
            Tester.numActions = 1;

        }
         //Let's run just a few tests where the curse cards supply is empty
        if (count - tests >= (.9 * count)){
            Tester.supplyCount[0] = 0;
        }


        Tester.whoseTurn = floor(Random() * Tester.numPlayers);
        memcpy(&Control, &Tester, sizeof(Control)); 

        res = playCard(handPos, 0, 0, 0, &Tester);
        if (res == -1){
            printf("playCard Routine Failure.\n");
            playFail++;
            continue;
        }

        //check effects

        if (Tester.supplyCount == 0){
            for (j = 0; j < Tester.numPlayers; j++){
                for (j = 0; j < MAX_HAND; j++){
                    if(Tester.hand[j][m] == curse){
                        printf("Sea Hag didn't check for 0 curse supply.\n");
                        fail++;
                }
            }
        }
            continue;
        }

        for (j = 0; j < Tester.numPlayers; j++)
        {
            if (j != Tester.whoseTurn) {
            //check to see if the discardCount has been incremented and if
            //the card in the discard stack was the card on the top of the
            //deck
                if(Tester.discardCount[j] != 1 && Tester.discard[j][0] == Control.deck[j][Control.deckCount[j] -1]){
                    printf("Sea Hag didn't move discard the top card of the deck.\n");
                    fail++;
                    break;
                }
                //check to see if the top card of the deck is a curse card
                if (Tester.deck[j][Tester.deckCount[j] -1] != curse){
                    printf("Sea hag didn't put a curse card on the top of the deck.\n");
                    fail++;
                    break;
                }
            }
        }

        //Let's run another set of tests to see what happens when the curse
        //cards are all out of stock.
        

    }

    printf("Sea Hag results: Tests: %d\t: Passed: %d\tFailed: %d\n", tests, tests-fail, fail);

    return;
}
