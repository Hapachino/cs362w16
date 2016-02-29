#include "dominion.h"
#include "test_helper.h"
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <math.h>

/*************************************
 * Update Coins Unit Test
 * We're going to randomize the player's hand
 * both in terms of number of cards and types of cards
 *
 * We're going to randomize the number of coins in bonus.
 *
 * We're going to test to see if updateCoins properly
 * calculates the number of coins to play
 * ***********************************/

void unittest3(long seed)
{
    int i, j, bonus, count, fail, control, validFlag;
    
    count = 1000;
    fail = 0;

    for( i = 0; i < count; i++)
    {
        control = 0;
        validFlag = count % 2;
        int k[10];
        randomizeKingdomCards(k);
        struct gameState Tester;

        initializeGame(2, k, seed, &Tester);
        

        int player = floor(Random() * MAX_PLAYERS);
        Tester.handCount[player] = floor(Random() * MAX_HAND);
        for (j = 0; j < Tester.handCount[player]; j++)
            Tester.hand[player][j] = floor(Random() * (treasure_map + 1));

        bonus = floor(Random() * 100);
    
        //calculate control value
        for (j = 0; j < Tester.handCount[player]; j++){
            switch(Tester.hand[player][j])
            {
                case (copper):
                    control += 1;
                    break;
                case (silver):
                    control += 2;
                    break;
                case (gold):
                   control +=3;
                    break;
            }
        }
        control += bonus;

        updateCoins(player, &Tester, bonus);
        if (control != Tester.coins)
            fail++;
    }


    printf("Update Coins Test Results: Tests %d\tPassed: %d\tFailed: %d\n", count, count - fail, fail);


}

