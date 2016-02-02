/* -----------------------------------------------------------------------
 *isGameOver() Unit Testing file
 *Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 *testUnit1: unittest1.c dominion.o rngs.o
 *	gcc -0 unittest1 dominion.o rngs.o unittest1.c $(CFLAGS)
 *
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"



//Determine if two gameStates are identical or not: Return 1 if identical, 0 if not
int statesAreEqual(struct gameState *g1, struct gameState *g2)
{
    int i, j;

    if(g1->numPlayers != g2->numPlayers) return 0;
    //for(i = 0; i < treasure_map+1; i++)
    //    if(g1->supplyCount[i] != g2->supplyCount[i]) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->embargoTokens[i] != g2->embargoTokens[i]) return 0;
    if(g1->outpostPlayed != g2->outpostPlayed) return 0;
    if(g1->outpostTurn != g2->outpostTurn) return 0;
    if(g1->whoseTurn != g2->whoseTurn) return 0;
    if(g1->phase != g2->phase) return 0;
    if(g1->numActions != g2->numActions) return 01;
    if(g1->coins != g2->coins) return 0;
    if(g1->numBuys != g2->numBuys) return 0;
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(g1->handCount[i] != g2->handCount[i]) return 0;
        if(g1->deckCount[i] != g2->deckCount[i]) return 0;
        if(g1->discardCount[i] != g2->discardCount[i]) return 0;

        for(j = 0; j < MAX_HAND; j++)
            if(g1->hand[i][j] != g2->hand[i][j]) return 0;

        for(j = 0; j < MAX_DECK; j++)
            if(g1->deck[i][j] != g2->deck[i][j]) return 0;
    }

    for(i = 0; i < MAX_DECK; i++)
        if(g1->playedCards[i] != g2->playedCards[i]) return 0;

    if(g1->playedCardCount != g2->playedCardCount) return 0;

    return 1;
}

// set NOISY_TEST to 0 to remove printfs from output or to 2 for FAIL output only
#define NOISY_TEST 0
int main()
{
    int i, j,k,m,  endgame = 0;
    int pass = 0, fail = 0;
    int seed = 500;
    srand(seed);
    struct gameState state, begin;

    printf ("\n\nTESTING isGameOver():\n---------------------------------------------------------------------------\n");
    endgame = 0;


    //load 10 kingdom cards into each stack
    for(i = curse; i <= treasure_map; i++)
    {
        begin.supplyCount[i] = 10;
    }

    //test 0 stacks with 0
    memcpy(&state, &begin, sizeof(struct gameState));     //establish a cloned game state
    printf("Testing 0 supply counts empty....");
    if(isGameOver(&state) != 0 || statesAreEqual(&state, &begin) != 1)
    {
 #if (NOISY_TEST == 1 || NOISY_TEST == 2)
            printf("***FAILED*** ");
            fail++;
#endif
    }
    else
    {
 #if (NOISY_TEST == 1)
            printf("---PASSED---");
            pass++;
#endif
    }
printf("Test results: [%d fails]  [%d passes]\n", fail, pass);

    //test 1 stack has zeros
    fail = 0;
    pass = 0;
    printf("Testing 1 supply count empty....");
    for(i = 0; i < 27; i++)
    {

        memcpy(&state, &begin, sizeof(struct gameState));     //establish a cloned game state
        state.supplyCount[i] = 0; //zero out 1 of the supply cards;
        if(isGameOver(&state) != 0 && i != province)
        {
#if (NOISY_TEST == 1 || NOISY_TEST == 2)
            printf("***FAILED*** ");
            printf("isGameOver(): %d (should be: %d) provinces[%d]  supplyCounts[%d, ", isGameOver(&state), endgame, state.supplyCount[province],state.supplyCount[curse]);
            for(j = duchy; j <= treasure_map; j++)
            {
                printf("%d, ", state.supplyCount[j]);
            }
            printf("\b\b]\n");
            fail++;
#endif
        }

        else
        {
            if(statesAreEqual(&state, &begin) == 1)  //make sure the states have not changed

            {
                pass++;
#if (NOISY_TEST == 1)
                printf("------------ ");
                printf("isGameOver(): %d (should be: %d) provinces[%d]  supplyCounts[%d, ", isGameOver(&state), endgame, state.supplyCount[province],state.supplyCount[curse]);
                for(j = duchy; j <= treasure_map; j++)
                {
                    printf("%d, ", state.supplyCount[j]);
                }
                printf("\b\b]\n");
#endif
            }

            else
            {
                fail++;
#if (NOISY_TEST == 1 || NOISY_TEST == 2)
                printf("***FAILED*** ");
                printf("State Change Error. (%d)", i);
#endif
            }

        }

    }
    printf("Test results: [%d fails]  [%d passes]\n", fail, pass);


    //test 2 stack has zeros
    fail = 0;
    pass = 0;
    printf("Testing 2 supply count empty....");
    for(i = 0; i < 27; i++)
    {
        for(k=0; k < 27; k++)
        {
            if(k != i)
            {
                memcpy(&state, &begin, sizeof(struct gameState));     //establish a cloned game state
                state.supplyCount[i] = 0; //zero out 1 of the supply cards;
                state.supplyCount[k] = 0; //zero out 1 of the supply cards;

                if(isGameOver(&state) != 0 && i != province && k != province)
                {
#if (NOISY_TEST == 1 || NOISY_TEST == 2)
                    printf("***FAILED*** ");
                    printf("isGameOver(): %d (should be: %d) provinces[%d]  supplyCounts[%d, ", isGameOver(&state), endgame, state.supplyCount[province],state.supplyCount[curse]);
                    for(j = duchy; j <= treasure_map; j++)
                    {
                        printf("%d, ", state.supplyCount[j]);
                    }
                    printf("\b\b]\n");
                    fail++;
#endif
                }

                else
                {
                    if(statesAreEqual(&state, &begin) == 1)  //make sure the states have not changed

                    {
                        pass++;
#if (NOISY_TEST == 1)
                        printf("------------ ");
                        printf("isGameOver(): %d (should be: %d) provinces[%d]  supplyCounts[%d, ", isGameOver(&state), endgame, state.supplyCount[province],state.supplyCount[curse]);
                        for(j = duchy; j <= treasure_map; j++)
                        {
                            printf("%d, ", state.supplyCount[j]);
                        }
                        printf("\b\b]\n");
#endif
                    }

                    else
                    {
                        fail++;
#if (NOISY_TEST == 1 || NOISY_TEST == 2)
                        printf("***FAILED*** ");
                        printf("State Change Error. (%d)", i);
#endif
                    }

                }
            }
        }
    }
    printf("Test results: [%d fails]  [%d passes]\n", fail, pass);

    //test 3 stack has zeros
    fail = 0;
    pass = 0;
    printf("Testing 3 supply count empty....");
    for(i = 0; i < 27; i++)
    {
        for(k=0; k < 27; k++)
        {
            if(k != i)
            {
                for(m=0; m < 27; m++)
                {
                    if(m != i && m != k)
                    {
                        memcpy(&state, &begin, sizeof(struct gameState));     //establish a cloned game state
                        state.supplyCount[i] = 0; //zero out 1 of the supply cards;
                        state.supplyCount[k] = 0; //zero out 1 of the supply cards;
                        state.supplyCount[m] = 0; //zero out 1 of the supply cards;

                        if(isGameOver(&state) != 1) //should always be game over now
                        {
#if (NOISY_TEST == 1 || NOISY_TEST == 2)
                            printf("***FAILED*** ");
                            printf("isGameOver(): %d (should be: %d) provinces[%d]  supplyCounts[%d, ", isGameOver(&state), endgame, state.supplyCount[province],state.supplyCount[curse]);
                            for(j = duchy; j <= treasure_map; j++)
                            {
                                printf("%d, ", state.supplyCount[j]);
                            }
                            printf("\b\b]\n");
#endif
                            fail++;

                        }

                        else
                        {
                            if(statesAreEqual(&state, &begin) == 1)  //make sure the states have not changed

                            {
                                pass++;
#if (NOISY_TEST == 1)
                                printf("------------ ");
                                printf("isGameOver(): %d (should be: %d) provinces[%d]  supplyCounts[%d, ", isGameOver(&state), endgame, state.supplyCount[province],state.supplyCount[curse]);
                                for(j = duchy; j <= treasure_map; j++)
                                {
                                    printf("%d, ", state.supplyCount[j]);
                                }
                                printf("\b\b]\n");
#endif
                            }

                            else
                            {
                                fail++;
#if (NOISY_TEST == 1 || NOISY_TEST == 2)
                                printf("***FAILED*** ");
                                printf("State Change Error. (%d)", i);
#endif
                            }

                        }
                    }
                }
            }
        }
    }
    printf("Test results: [%d fails]  [%d passes]\n", fail, pass);


    return 0;
}
