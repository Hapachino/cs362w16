/*
unit test 4
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)


Description:
place in played piled if trash flag not trigger
removes card from hand and places it into discard pile
reduces hand count and turns card into -1(proxy for empty)
a

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

int testDiscardCard(struct gameState *pre)
{
        //create test game
    struct gameState post;
    memcpy(&post,pre,sizeof(struct gameState));
    assert (memcmp(&post,pre, sizeof(struct gameState))==0);


    //create inputs
    int p = post.whoseTurn;
    int testHandPOS = floor(Random() * post.handCount[p]);
    int testTrashFlag = round(Random() * 1);

    //run funciton on post state
    discardCard(testHandPOS,p,&post,testTrashFlag);

    //updated pre with changes

   //if card is not trashed, added to Played pile
    if (testTrashFlag < 1)
    {
      //add card to played pile
      pre->playedCards[pre->playedCardCount] = pre->hand[p][testHandPOS];
      pre->playedCardCount++;
    }

  //set played card to -1
  pre->hand[p][testHandPOS] = -1;

  //remove card from player's hand
    if ( testHandPOS == (pre->handCount[p] - 1) ) 	//last card in hand array is played
    {
      //reduce number of cards in hand
      pre->handCount[p]--;
    }
    else if ( pre->handCount[p] == 1 ) //only one card in hand
    {
      //reduce number of cards in hand
      pre->handCount[p]--;
    }
    else
    {
      //replace discarded card with last card in hand
      pre->hand[p][testHandPOS] = pre->hand[p][ (pre->handCount[p] - 1)];
      //set last card to -1
      pre->hand[p][pre->handCount[p] - 1] = -1;
      //reduce number of cards in hand
      pre->handCount[p]--;
    }

    if(memcmp(&post,pre, sizeof(struct gameState))==0)
    {
        printf("DiscardCard Test PASS\n");
    }
    else
    {
        printf("DiscardCard Test FAIL\n");
    }

return 0;
}



int main()
{
     printf("discardCard test - Unittest4/n");

    //array of cards
      int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

    struct gameState preState;

    int i, j, n;

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
            preState.handCount[i] = floor(Random() * (MAX_HAND-1))+1; // non zero handcount
            preState.deckCount[i] = floor(Random() * MAX_DECK);
            preState.playedCardCount = floor(Random() * MAX_DECK);


            j=0;
            for(j=0;j<preState.handCount[i];j++)
                {
                preState.hand[i][j] = floor(Random() * 10);
                }
        }

        //run test
        testDiscardCard(&preState);
    }

    return 0;
}
