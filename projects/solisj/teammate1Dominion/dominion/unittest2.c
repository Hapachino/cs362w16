#include "dominion.h"
#include "test_helper.h"
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <math.h>

/********************
 * Testing buyCard
 *
 *
 *
 *
 * *******************/
int unit2tester(int k[10], struct gameState *Control, struct gameState *Tester, int testPath, int validFlag);
void unittest2(long seed)
{
    int i, j, count, validFlag, res, tests_failed;
    count = 1000;
    tests_failed = 0;
    //we're going to run the tester through a series of valid values
    //then we're going to run a series of tests with invalid values
    
    //validTests:
    for (i = 0; i < count; i++)
    {
        validFlag = 1;
        int k[10];
        int testPath;

        struct gameState Control;
        struct gameState Tester;

        randomizeKingdomCards(k);

        res = initializeGame(2, k, seed, &Tester);

        testPath = floor(Random() * 5);
        //default values for  tests
        Tester.phase = 1;
        Tester.numBuys = 1;
        Tester.coins = 10;

        switch (testPath)
        {
            case(0):
                Tester.numBuys = ceil(Random() * 1000000);
                break;
            case(1):
                //vary supply of kingdom cards
                for (j = 0; j < 10; j++)
                Tester.supplyCount[k[j]] = ceil(Random() * 1000000);
                break;
            case(2):
                //vary supply of victory cards
                for (j = 0; j < 4; j++)
                Tester.supplyCount[j] = ceil(Random() * 1000000);
                break;
            case(3):
                Tester.coins = ceil((Random() * 1000000)+10);
                break;
            case (4):
                Tester.phase = 1;
                break;
    }

        memcpy(&Control, &Tester, sizeof(Control));    
        res = unit2tester(k, &Control, &Tester, testPath, validFlag);
        if (res == 0){
            tests_failed++;
            printf("Buy Test Failed: Valid Path Case: %d\n", testPath);
        }
    }



    //invalid tests
    for (i = 0; i < count; i++)
    {
        validFlag = -1;
        int testPath;
        int k[10];
        
        struct gameState Control;
        struct gameState Tester;

        randomizeKingdomCards(k);

        res = initializeGame(2, k, seed, &Tester);
        testPath = floor(Random() * 5);

        //default values for tests
        Tester.phase = 1;
        Tester.numBuys = 1;
        Tester.coins = 10;


        switch(testPath)
        {
            case(0):
                //vary invalid numBuys
                Tester.numBuys = -1 * (floor(Random() * 1000000));
                break;
            case(1):
                //vary invlid supply of kingdom cards
                for (j = 0; j < 10; j++)
                Tester.supplyCount[k[j]] = -1 * (floor(Random() * 1000000));
                break;
            case(2):
                //vary supply of victory cards
                for (j = 0; j < 4; j++)
                Tester.supplyCount[j] = -1 * (floor(Random() * 1000000));
                break;
            case(3):
                Tester.coins = -1 * (floor ((Random() * 1000000)+10));
                break;
            case(4):
                Tester.phase = ceil(Random() * 3) + 1;
        }

        memcpy(&Control, &Tester, sizeof(Control));    
        res = unit2tester(k, &Control, &Tester, testPath, validFlag);
        if (res == 0) {
            tests_failed++;
            printf("Buy Test Failed: Invalid Path Case: %d\n", testPath);
        }
    }
    printf("\nBuyCard Tests Results: Tests: %d\tPassed: %d\tFailed: %d\n", count, count - tests_failed, tests_failed);
    return;
}


int unit2tester(int k[10], struct gameState *Control, struct gameState *Tester, int testPath, int validFlag)
{

    int i, res; 

    switch(testPath)
    {
        case(0):
            //check no buys < 1
            if (Tester->numBuys < 1){
                if (buyCard(k[1], Tester) == -1){
                    return flagCheck(-1, validFlag);
                }
            }
            else{ //check number buys >= 1
                if (buyCard(k[1], Tester) == -1){
                    return flagCheck(-1, validFlag);
                }
            }
            break;
        case(1):
            i = floor(Random() * 10);
            assert(i >= 0);
            if(buyCard(k[i], Tester) != -1){
                return flagCheck(-1, validFlag);
            }
            break;
        case(2):
            //test curses and victory cards empty
            i = floor(Random() * 4);
            assert(i >=0);
            if(buyCard(i, Tester) != -1){
                return flagCheck(-1, validFlag);
                }
            break;
        case(3):
            //test not enough money
            i = floor(Random() * 10);
            assert(i >= 0); 
            if (buyCard(k[i], Tester) != -1){
                return flagCheck(-1, validFlag);
            }
            break;
        case(4):
            //test phase
            i = floor(Random() * 10);
            assert (i >= 0);
            if (buyCard(k[i], Tester) ==1){
                return flagCheck(-1, validFlag);
            }
        case(5):
            //test buying each kingdom card
            for (i = 0; i < 10; i++){
                assert (Tester->supplyCount[k[i]] >= 1);
                Tester->coins =10;
                Tester->numBuys = 1;
                res = buyCard(k[i], Tester);
                if (res == -1){
                    return flagCheck(-1, validFlag);
                }
                else if (Control->supplyCount[k[i]] - 1 != Tester->supplyCount[k[i]] ){
                    return flagCheck(-1, validFlag);
                }
                else if (Tester->coins != (Control->coins - getCost(k[i]))){
                    return flagCheck(-1, validFlag);
                }
                else if (Tester->numBuys != (Control->numBuys - 1)){
                    return flagCheck(-1, validFlag);
                }
                
            }

            for (i = 0; i < 4; i++){
                assert (Tester->supplyCount[i] >= 1);
                Tester->coins =10;
                Tester->numBuys = 1;
                res = buyCard(k[i], Tester);
                if (res == -1){
                    return flagCheck(-1, validFlag);
                }
                else if (Control->supplyCount[k[i]] - 1 != Tester->supplyCount[k[i]] ){
                    return flagCheck(-1, validFlag);
                }
                else if (Tester->coins != (Control->coins - getCost(k[i]))){
                    return flagCheck(-1, validFlag);
                }
                else if (Tester->numBuys != (Control->numBuys - 1)){
                    return flagCheck(-1, validFlag);
                }
            }
            break;
    }

    return (flagCheck(1, validFlag));

}
