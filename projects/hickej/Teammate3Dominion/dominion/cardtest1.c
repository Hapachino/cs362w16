
/*
card test 1
smithy


int playSmithy(struct gameState *state)
{
    int i;
    int currentPlayer = whoseTurn(state);

     for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);

    return 0;
    }
}


Description:
finds current player (whoseTurn )
calls draw card three on current player
returns 0

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


int testSmithy(struct gameState *pre)
{

     //create test game
    struct gameState post;
    memcpy(&post,pre,sizeof(struct gameState));
    assert (memcmp(&post,pre, sizeof(struct gameState))==0);
//playSmithyCard(int currentPlayer, struct gameState *state, int handPos) {
    // play Smithy;

    playSmithyCard(post.whoseTurn,&post,0);

    //update pre

    int currentPlayer = pre->whoseTurn;

    int preCardHand = pre->handCount[currentPlayer];

    drawCard(currentPlayer,pre);
    drawCard(currentPlayer,pre);
    drawCard(currentPlayer,pre);

     discardCard(0, currentPlayer, pre, 0);

    printf("pretest hand count %d expected %d test amount %d ", preCardHand, pre->handCount[currentPlayer], post.handCount[currentPlayer]);

     if(memcmp(&post,pre, sizeof(struct gameState))==0)
    {
        printf("Smithy Test PASS\n");
    }
    else
    {
        printf("Smithy Test FAIL\n");
    }

    return 0;
}





int main()
{
     printf("PlaySmithy test - cardTest1\n");

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
        preState.numPlayers = floor(Random() * (MAX_PLAYERS-1))+1;
        preState.whoseTurn = floor(Random() * preState.numPlayers);


        for (i = 0; i < MAX_PLAYERS; i++)
        {
            preState.handCount[i] = floor(Random() * (MAX_HAND)); // non zero handcount
            preState.deckCount[i] = floor(Random() * MAX_DECK);

            preState.discardCount[i] = floor(Random() * MAX_DECK);
        }


        //run test
        testSmithy(&preState);
    }
    return 0;

}


