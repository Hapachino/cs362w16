#include "dominion.h"
#include "test_helper.h"
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <math.h>

/******************************
 * Adventure card test
 * This card draws cards until it adds
 * 2 coins to the hand.  Other cards are discarded.
 *
 * We're going to:
 *  a. Randomize kingdom cards 
 *  b. randomize the number of players
 *  c. initialize a game
 *  d. we're not going to test the shuffle
 *  e. so we're going to set up a deck that has a random number of cards
 *  f. and we're going to randomly insert in that deck three coin cards 
 *      in the deck to ensure that there are coins in the deck
 *  g.  we're going to copy the tester into a control
 *  g.  we're going to call int playCard
 *  h.  we're going to ignore error messages from the playCard function
 *  i.  We're going to check that the tester hand has two additional coins
 *  j.  we're going to draw cards from the control deck until we get to the
 *  two additional coins
 *  k.  we're going to check that the cards in the hand are the same as the
 *  three coins we drew.
 *  l.  we're going to check that the discard piles for the control and
 *  tester are the same size. 
 **********************************/
void adventurerTest(long seed)
{

    int i, j, m, res;
    int count, tests, fail, playFail;
    count = 1000;
    tests = 0;
    fail = 0;

    for (i = 0; i < count; i++)
    {
        int k[10];
        randomizeKingdomCards(k);
        struct gameState Tester;
        struct gameState Control;

        int numPlayers = floor(Random() * (MAX_PLAYERS -2) + 2);
        assert(numPlayers >= 2 && numPlayers <= 4);

        initializeGame(numPlayers, k, seed, &Tester);

        for (j = 0; j < Tester.numPlayers; j++)
        {
            tests++;
            Tester.whoseTurn = j;
            Tester.phase = 0;
            Tester.numActions = 1;
            Tester.handCount[j] = floor(Random() * (MAX_HAND -2));
            assert(Tester.handCount[j] <= MAX_HAND -2);
            
            for (m = 0; m < Tester.handCount[j]; m++){
                Tester.hand[j][m] = floor(Random() * (treasure_map + 1));
                assert(Tester.hand[j][m] <= treasure_map + 1);   
            }

            //we're going to set a minimum size of 30 cards so we can
            //insert three treasure cards, just to be sure they're in there
            Tester.deckCount[j] = floor(Random() * (MAX_HAND - 30) + 30);
            assert(Tester.handCount[j] <= MAX_HAND - 2);

            for (m = 0; m < Tester.deckCount[j]; m++){
                Tester.deck[j][m] = floor(Random() * (treasure_map + 1));
                assert(Tester.hand[j][m] <= treasure_map + 1);
            }

            int insertionPoint1 = floor(Random() * Tester.deckCount[j]);
            assert(insertionPoint1 < Tester.deckCount[j]);
            
            int insertionPoint2;
            while(1){
                insertionPoint2 = floor(Random() * Tester.deckCount[j]);
                assert(insertionPoint2 < Tester.deckCount[j]);
                if (insertionPoint2 != insertionPoint1) break;
            }

            int insertionPoint3;
            while(1){
                insertionPoint3 = floor(Random() * Tester.deckCount[j]);
                assert(insertionPoint3 < Tester.deckCount[j]);
                if (insertionPoint3 != insertionPoint1 && 
                        insertionPoint3 != insertionPoint2) break;
            }

            Tester.deck[j][insertionPoint1] = copper;
            Tester.deck[j][insertionPoint2] = silver;
            Tester.deck[j][insertionPoint3] = gold;

            Tester.discardCount[j] = 0;

            //insert adventure card into deck
            int handPos;
            handPos = floor(Random() * Tester.handCount[j]);
            Tester.hand[j][handPos] = adventurer;

            //copy tester into control
            memcpy(&Control, &Tester, sizeof(Control));

            res = playCard(handPos, 0, 0, 0, &Tester);
            if (res == -1){
                printf("playCard function failure.\n");
                playFail++;
                continue;
            }

            //check effects
           //Does the tester have two additional coins in the hand?
           //How many coins in the control hand?
           int testerCount = 0;
           for (m = 0; m < Tester.handCount[j]; m++){
                int card = Tester.hand[j][m];
                if (card == copper || card == silver || card == gold)
                    testerCount++;
           }

           int controlCount= 0;
           for (m = 0; m < Control.handCount[j]; m++){
               int card = Control.hand[j][m];
               if (card == copper || card == silver || card == gold)
                   controlCount++;
           }

           //printf("TesterCount: %d\tControlCount:%d\n", testerCount, controlCount);
           if (testerCount != controlCount + 2){
               printf("Adventurer drew the wrong amount of treasure.\n");
               fail++;
               continue;
           }

           //check to see that the tester only has two additional cards
           if(Tester.handCount[j] != Control.handCount[j] + 2){
                printf("Adventurer didn't discard properly.\n");
                fail++;
                continue;
           }

           //check to see if adventurer drew the correct cards
           //& number of cards
           int drawnTreasure = 0;
           int counter = 0;
           while (drawnTreasure <= 2){
                int card = Control.deck[j][Control.deckCount[j] - (counter + 1)];
                counter++;
                if (card == copper || card == silver || card == gold)
                    drawnTreasure++;

            }
           //printf("Tester.discardCount: %d\tTest Counter:%d\n", Tester.discardCount[j], counter);
           if (Tester.discardCount[j] != counter - 3){
               printf("Adventurer drew the wrong cards.\n");
               fail++;
               continue;
           }


        }

    }
    printf("Adventurer Test Results:\tTests: %d\tPassed: %d\tFailed: %d\n",
            tests, tests - fail, fail);
    printf("Adventurer associated functions fail: %d\n",
            playFail);


    return;

}

