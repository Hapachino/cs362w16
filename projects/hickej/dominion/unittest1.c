/* Unittest 1 for updateCoin()
int updateCoins(int player, struct gameState *state, int bonus);

funcition adds  up all coin cards in player hand.
updates coin in game state

copper =1
sliver =2
gold =3

*/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int testUpdateCoin(int player, struct gameState *state, int bonus);

int main()
{
     printf("updateCoin test - Unittest1/n");

    srand(time(NULL));
	//set up base gamestate

	struct gameState baseGame;

	int seed = 1000;
	int players = 2;;

	int k[10] = {adventurer, council_room, copper, silver, gold
	               , remodel, smithy, village, baron, great_hall};



	initializeGame(players, k, seed, &baseGame);



//set up for test

	int testPlayer = 0;
	int testBonus = 0;
    int i;
    int j;

    int b;

//loops for all needed tests

    i = 0;
    j = 0;

    b = 0;

   //loop to add a new card slot
    for(i=0;i<MAX_HAND;i++)
        {baseGame.handCount[testPlayer]++;



        j=0;
        //build hand
        for(j=0;j<i;j++)
        {
           b= (rand()%10);
           baseGame.hand[testPlayer][j] = k[b];

            testBonus = floor(Random() * 10);

                testUpdateCoin(testPlayer,&baseGame,testBonus);



        }
    }


/*
    baseGame.handCount[testPlayer] = 10;

    for(i=0;i<10;i++)
    {
    b= (rand()%10);
    baseGame.hand[testPlayer][i] = k[b];
    }
    testUpdateCoin(testPlayer,&baseGame,testBonus);
*/

    return 0;
}



int testUpdateCoin(int player, struct gameState *state, int bonus)
{

	struct gameState testGame;
		// make a copy of base game for testing
	memcpy(&testGame, state, sizeof(struct gameState));
    assert (memcmp(&testGame,state, sizeof(struct gameState))==0);


        //run method
    updateCoins(player,&testGame,bonus);

        //count coins

    int testCoins = 0;
    int i = 0;
    for (i = 0; i < state->handCount[player]; i++)
    {
      if(state->hand[player][i] == copper)
	{
	  testCoins += 1;
	}
      else if(state->hand[player][i] == silver)
	{
	  testCoins += 2;
	}
      else if(state->hand[player][i] == gold)
	{
	  testCoins += 3;
	}
    }

    testCoins = testCoins + bonus;

    //result of test
     printf("coin count = %d, expected = %d ", testGame.coins, testCoins) ;
    if(testCoins == testGame.coins)
    {
        printf("Test PASS\n");
    }
    else{
        printf("Test FAIL\n");
    }





    return 0;
}
