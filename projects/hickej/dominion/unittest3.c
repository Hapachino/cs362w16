/*
unit test 3
int endTurn(struct gameState *state)


Description:
Changes the current player to the next player or the first player if the last player
has finished their turn. Resets the player gameState and draws cards for the next player.

Assumes Dependencies functions work;

 whoseTurn()
 drawCard()
 updateCoins()


*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int testGameOver(struct gameState *pre)
{
    int i=0;
    int j=0;
    int p=0;
    //create test game
    struct gameState post;
    memcpy(&post,pre,sizeof(struct gameState));
    assert (memcmp(&post,pre, sizeof(struct gameState))==0);

    endTurn(&post);

    //check discard had



    //get pre current player
    p = pre->whoseTurn;



    if(post.discardCount[p] == (pre->handCount[p]+pre->discardCount[p]))
    {
        printf("discard PASS ");
    }
    else{
         printf("discard FAIL ");
    }
    //check if whoseturn worked
    i = pre->whoseTurn;

    if (i < (pre->numPlayers - 1))
        {
            j = i+1; //save for later test
            if(i+1 == post.whoseTurn)
            {
                printf("Player PASS ");
            }
            else
            {
                printf("Player FAIL ");
            }
        }
    else
        {
        //Max player has been reached, loop back around to player 1
            if(post.whoseTurn == 0)
            {
                printf("Player PASS ");
            }
            else
            {
                printf("Player FAIL ");
            }
          }


    //check stats update
    if(post.outpostPlayed == 0 &&
          post.phase == 0 &&
          post.numActions == 1 &&
          post.numBuys == 1 &&
          post.playedCardCount == 0
          )
      {
           printf("Stats PASS ");
      }
      else
      {
           printf("Stats FAIL ");
      }
    //check draw
        if(post.handCount[j] == 5)
        {
            printf("Draw PASS ");
        }
        else
        {
            printf("Draw FAIL ");
        }

    //check coinupdate

    int testCoins = 0;
     i = 0;
    for (i = 0; i < post.handCount[j]; i++)
    {
      if(post.hand[j][i] == copper)
	{
	  testCoins += 1;
	}
      else if(post.hand[j][i] == silver)
	{
	  testCoins += 2;
	}
      else if(post.hand[j][i] == gold)
	{
	  testCoins += 3;
	}
    }

    if (testCoins == post.coins)
    {
        printf("Coins PASS\n");
    }
    else
    {
        printf("Coins FAIL\n");
    }

    return 0;
}



int main()
{
    printf("endTurn test - Unittest3\n");

    //array of cards
      int k[10] = {adventurer, copper, silver, gold, mine,
	       remodel, smithy, village, baron, great_hall};

    struct gameState preState;

    int i, j, n;

    //create intial game
  SelectStream(2);
  PutSeed(3);
    for (n = 0; n < 2000; n++) {
        initializeGame(2,k,1000,&preState);
    //fill in required preconditions with randoms.

        preState.numPlayers = floor(Random() * (MAX_PLAYERS-1))+1;
        preState.whoseTurn = floor(Random() * preState.numPlayers);


        for (i = 0; i < MAX_PLAYERS; i++)
        {
          preState.handCount[i] = floor(Random() * MAX_HAND);

          preState.deckCount[i] = floor(Random() * MAX_DECK);

          j=0;
          for(j=0;j<preState.handCount[i];j++)
            {
            preState.hand[i][j] = floor(Random() * 10);
            }
        }
        //run test
        testGameOver(&preState);
    }



return 0;

}
