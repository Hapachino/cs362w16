
/*
card test 4
greatHall


int playGreat_Hall(struct gameState *state)
{
     int currentPlayer = whoseTurn(state);
      //+1 Card
      drawCard(currentPlayer, state);

      //+1 Actions
      state->numActions++;

    return 0 ;
}

Description:
finds current player
call draw card

adds 1 to action total

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


int testGreatHall(struct gameState *pre)
{

     //create test game
    struct gameState post;
    memcpy(&post,pre,sizeof(struct gameState));
    assert (memcmp(&post,pre, sizeof(struct gameState))==0);

    // play great hall;
    playGreat_Hall(&post);

    //update pre

    int currentPlayer = pre->whoseTurn;



    drawCard(currentPlayer,pre);
    pre->numActions += 1;



     if(memcmp(&post,pre, sizeof(struct gameState))==0)
    {
        printf("Great Hall Test PASS\n");
    }
    else
    {
        printf("Great Hall FAIL\n");
    }

    return 0;
}





int main()
{
     printf("PlayGreatHall test - cardTest4\n");

    //array of cards
      int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

    struct gameState preState;

    int i, n;

    //create random seed
  SelectStream(2);
  PutSeed(3);
    for (n = 0; n < 2000; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++) {
          //fill game state with random bits
          ((char*)&preState)[i] = floor(Random() * 256);
        }
    //fill in required preconditions
        //set players and current play
        preState.numPlayers = floor(Random() * (MAX_PLAYERS));
        preState.whoseTurn = floor(Random() * preState.numPlayers);
        preState.numActions = floor(Random() * 100);

        for (i = 0; i < MAX_PLAYERS; i++)
        {
            preState.handCount[i] = floor(Random() * (MAX_HAND)); // non zero handcount
            preState.deckCount[i] = floor(Random() * MAX_DECK);
            preState.discardCount[preState.whoseTurn] = floor(Random() * MAX_DECK);
        }

        for(i=0;i<preState.handCount[preState.whoseTurn];i++)
        {
        preState.hand[preState.whoseTurn][i] = floor(Random() * 10);
        }
         for(i=0;i<preState.deckCount[preState.whoseTurn];i++)
        {
        preState.hand[preState.whoseTurn][i] = floor(Random() * 10);
        }
        for(i=0;i<preState.discardCount[preState.whoseTurn];i++)
        {
        preState.discard[preState.whoseTurn][i] = floor(Random() * 10);
        }


        //run test
        testGreatHall(&preState);
    }
    return 0;

}




