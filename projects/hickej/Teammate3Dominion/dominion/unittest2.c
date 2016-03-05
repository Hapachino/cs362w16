/*
unit test 2
isGameOver(struct gameState *state)

checks to see if game is over
game ends if
Provinces is empty
state->supplyCount[province] == 0) returns 1
Or
all three supply piles is empty
state->supplyCount[0,1,2] == 0) return1

if game is not over returns 0

no changes to state.

*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int testGameOver(struct gameState *pre);



int main()
{
     printf("isGameOver test - Unittest2/n");

    //array of cards
      int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

    struct gameState preState;

    int i, n;

    //create random seed
  SelectStream(2);
  PutSeed(3);
    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          //fill game state with random bits
          ((char*)&preState)[i] = floor(Random() * 256);
        }
    //fill in required preconditions
        preState.supplyCount[province] = floor(Random() * 50);
        for (i = 0; i < 25; i++)
        {
          preState.supplyCount[i] = floor(Random() * 50);
        }
        //run test
        testGameOver(&preState);
    }



    return 0;
}




int testGameOver(struct gameState *pre)
{
    int i,j;

    int result;
    //create test game
    struct gameState post;
    memcpy(&post,pre,sizeof(struct gameState));
    assert (memcmp(&post,pre, sizeof(struct gameState))==0);

    result = isGameOver(&post);

    //test if result is 1;
    if (result == 1)
    {
        if(post.supplyCount[province] == 0)
        {
            printf("0 provinces -Test PASS\n");
            return 0;
        }

        j = 0;
      for (i = 0; i < 25; i++)
        {
          if (post.supplyCount[i] == 0)
        {
          j++;
        }
        }
      if ( j >= 3)
        {
           printf("three empty supplyCount -Test PASS\n");
            return 0;
        }

         printf("Error game ended early  -Test Fail\n");
            return 0;

    }
    else if(result == 0)
    {
         //test if result is zero
         if(post.supplyCount[province] == 0)
        {
            printf("0 provinces -Test Fail\n");
            return 0;
        }

        j = 0;
      for (i = 0; i < 25; i++)
        {
          if (post.supplyCount[i] == 0)
        {
          j++;
        }
        }
      if ( j >= 3)
        {
           printf("three empty supplyCount -Test FAIL\n");
            return 0;
        }

         printf("Game successfully continues  -Test PASS\n");
            return 0;

    }


    return 0;


}


