#include "dominion.h"
#include "test_helper.h"
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <math.h>

/*****************************
 * Minion Card Tester
 *
 *  Minion is a big card and testing it is going to be intersting
 *  Here are the effects of Minion:
 *      +1 Action
 *      Choose 1:
 *          +2 coins
 *      or
 *          discard your hand and draw 4 cards
 *          Each other player with at least 5 cards in hand discards his
 *          hand and draws four cards
 *
 *          Wow
 *
 *  Okay, so here's how we're going to test it.
 *  We're going to do our standard randomization bit:
 *      randomize the number of players, 
 *      the number of cards in hand and deck 
 *      and the composition of those cards. 
 * *  We're going to set each player's discard to 0 so it's easier to track
 *  if they discarded their hand. 
 *
 *  We want to get decent code coverage on the routine if the other players
 *  have more or less than five cards in hand. So rather than set each
 *  players' hand to Random() * MAX_HAND, we're going to set it to 10.
 *  That should give us a number of test cases where the other players
 *  don't discard their hands. 
 *
 *  If we really want to, we can make some array[10] and track which cards
 *  are in the players' hands and match them up to the discard piles.
 *  We'll see if we want to tackle that.
 *
 *  **************************************/

void minionTest(long seed)
{

    int i, j, m, n, p, r,  res;
    int count, tests, fail, playFail, handPos;
    count = 1000;
    tests = 0;
    fail = 0;

    for (i = 0; i < count; i++)
    {

        int k[10];
        randomizeKingdomCards(k);
        struct gameState Tester;
        struct gameState Control;

        int numPlayers = floor(Random() * (MAX_PLAYERS - 2) + 2);
        assert (numPlayers >= 2 && numPlayers <= 4);

        res = initializeGame(numPlayers, k, seed, &Tester);
        assert(res != -1); //initialization fail

        Tester.whoseTurn = Random() * Tester.numPlayers;

        for (j = 0; j < Tester.numPlayers; j++)
        {
            tests++;
            Tester.phase = 0;
            Tester.numActions = 1;
            Tester.coins = 0;
            Tester.handCount[j] = floor(Random() * (11 - 1) + 1);
            assert(Tester.handCount[j] >= 1 && Tester.handCount[j] <= 10);

            for (m = 0; m < Tester.handCount[j]; m++){
                Tester.hand[j][m] = floor(Random() * (treasure_map + 1));
                assert(Tester.hand[j][m] < treasure_map+1);
            }

            handPos = 0;
            //handPos = floor(Random() * Tester.handCount[j]);
            assert (handPos < Tester.handCount[j]);

            Tester.hand[j][handPos] = minion;

            Tester.discardCount[j] = 0;
            Tester.playedCardCount = 0;

        }

        //unlike the other tests, we're going to randomize everyone's hand
        //(j loop) before we call the card
        
        memcpy(&Control, &Tester, sizeof(Control));

        //randomize choice one or two
        n = floor(Random() * 100);
        n = n % 2;
        p = 0;
        r = 0;
        (n) ? (p = 1) : (r = 1);
        res = playCard(handPos, p, r, 0, &Tester);
        if (res == -1){
            printf("playCard function failure.\n");
            playFail++;
            continue;
        }
        int currentPlayer;
        currentPlayer = Tester.whoseTurn;
        //check the effects
        //check action increased
        if (Tester.numActions != 1){
            printf("Minion: failed to add 1 action.\n");
            fail++;
            continue;
        }
        //Check effects of each path
        if (p == 1){
            //check increased coins
            if (Tester.coins != 2){
                printf("Minion: Path 1: Failed to record coins correctly.\n");
                fail++;
                continue;
            }
            //check discarded minion
            if (Tester.playedCardCount != 1){
                printf("Minion: Path 1: failed to discard played minion.\n");
                fail++;
                continue;
            }
        }
        else{
            //current player effects
            if (Tester.discardCount[currentPlayer] != Control.handCount[currentPlayer]){
                printf("Tester.discardCount: %d\tControl.handCount: %d\n", Tester.discardCount[currentPlayer], Control.handCount[currentPlayer]);
                printf("Minion: Path 2: failed to discard current player path.\n");
                fail++;
                continue;
            }
            //check current handcount = 4 and that the deck is 4 less
            if (Tester.handCount[currentPlayer] != 4 && Tester.deckCount[currentPlayer] != Control.deckCount[currentPlayer] -4){
                printf("Minion: Path 2: Current Player failed to draw four cards.\n");
                fail++;
                continue;
            }
            //Check other players
            for(j = 0; j < Tester.numPlayers; j++){
                if (j != currentPlayer){
                    //check to see if other player handsize >= 5
                    if (Control.handCount[j] >= 5) {
                       if(Tester.discardCount[j] != Control.handCount[j]){
                           printf("Tester.discard: %d\tControl.hand: %d \t", Tester.discardCount[j], Control.handCount[j]);
                            printf("Minion: Path 2: Didn't discard other player's hand.\n");
                            fail++;
                            continue;
                       }
                       if(Tester.handCount[j] != 4 && Tester.deckCount[j] != Control.deckCount[j] - 4){
                            printf("Minion Path 2: Didn't draw new hand.\n");
                            fail++;
                            continue;
                       }
                    }

                }
            }
        }

    }
    printf("Minion Results: Tests: %d\tPassed: %d\tFailed: %d\n", tests, tests-fail, fail);
    return;
}
