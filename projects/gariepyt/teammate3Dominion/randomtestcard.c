
/*
Random card test - council room


+4 cards
+1 buy
every other player

Description:
finds current player
call draw card for 4 times
add 1 to buy

loops through every player
    if not current player then calls draw card


Assumes Dependencies functions work;

 whoseTurn()
 drawCard()

*/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int testCouncilRoom(struct gameState *pre)
{
      printf(".");
    //break loop
    time_t endwait;
    int seconds = 5;

    int i;
     //create test game
    struct gameState post;
    memcpy(&post,pre,sizeof(struct gameState));
    assert (memcmp(&post,pre, sizeof(struct gameState))==0);

    endwait = time (NULL) + seconds ;
    while (time (NULL) < endwait)
     {

        // play council room;
       playCouncil_Room(&post);

        //update pre

        int currentPlayer = pre->whoseTurn;


        //draw 4
        drawCard(currentPlayer,pre);
        drawCard(currentPlayer,pre);
        drawCard(currentPlayer,pre);
        drawCard(currentPlayer,pre);


        //buy +1
        pre->numBuys += 1;

        //Each other player draws a card
        printf("%d- ", currentPlayer);
        for (i = 0; i < pre->numPlayers; i++)
        {
          if ( i != currentPlayer )
            {


              drawCard(i, pre);


            }

             printf("player %d expected %d test  %d, ", i,  pre->handCount[i], post.handCount[i]);
        }



         if(memcmp(&post,pre, sizeof(struct gameState))==0)
        {
            printf("Council Room Test PASS\n");
        }
        else
        {
            printf("Council room Test FAIL\n");
        }




    return 0;
    }

    printf("timeout");
    return 0;
}





int main()
{
     printf("PlayCouncil_Room test - randomtestcard\n");

    //array of cards
      int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

    struct gameState preState;

    int i,j, n;

    //create random seed
  SelectStream(2);
  PutSeed(3);
    for (n = 0; n < 2000; n++)
    {
           printf("-");
        for (i = 0; i < sizeof(struct gameState); i++) {
          //fill game state with random bits
          ((char*)&preState)[i] = floor(Random() * 256);
        }
    //fill in required preconditions
        //set players and current play
        preState.numPlayers = floor(Random() * (MAX_PLAYERS-1)+1);   // to exclude 0 players.
        preState.whoseTurn = floor(Random() * preState.numPlayers);
        preState.numBuys = floor(Random() * 100);

        for (i = 0; i < preState.numPlayers; i++)
        {
            preState.handCount[i] = floor(Random() * (100)); // non zero handcount
            preState.deckCount[i] = floor(Random() * (100));
            preState.discardCount[i] = floor(Random() * (100));


            for(j=0;j<preState.handCount[i];j++)
            {
            preState.hand[i][j] = floor(Random() * 10);
            }
             for(j=0;j<preState.deckCount[i];j++)
            {
            preState.hand[i][j] = floor(Random() * 10);
            }
            for(j=0;j<preState.discardCount[i];j++)
            {
            preState.discard[i][j] = floor(Random() * 10);
            }


        }




        //run test
        testCouncilRoom(&preState);
    }
    return 0;

}


