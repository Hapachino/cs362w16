/*

adventurer




Description:
finds current player (whoseTurn )
creates temp hand

loops till two treasure cards are drawn
    if deck is empty shuffle discards into deck
    calls drawCard
    if top card in hand (most recent drawn) is treasure card ups drawnTreasere count
    if card is not a treasure card removes from hand adds to temphand
        reduces hand count
after loop discards temp hand.



Assumes Dependencies functions work;
shuffle()
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


int testAdventurer(struct gameState *pre)
{

     //create test game
    struct gameState post;
    memcpy(&post,pre,sizeof(struct gameState));
    assert (memcmp(&post,pre, sizeof(struct gameState))==0);

    // play adventurer;
    playAdventurer(&post);

    //update pre
    int currentPlayer = pre->whoseTurn;
    int i;
    //add the two cards drawn

    for(i=0; i<2 ; i++)
    {
        pre->hand[currentPlayer][pre->handCount[currentPlayer]] = post.hand[currentPlayer][pre->handCount[currentPlayer]];
        pre->handCount[currentPlayer]++;
    }

    //update deck and discard in case of shuffle.

    for (i=0; i< post.deckCount[currentPlayer]; i++)
    {
        pre->deck[currentPlayer][i] =post.deck[currentPlayer][i];
    }
    pre->deckCount[currentPlayer] = post.deckCount[currentPlayer];

    for (i=0; i< post.discardCount[currentPlayer]; i++)
    {
        pre->discard[currentPlayer][i] =post.discard[currentPlayer][i];
    }
    pre->discardCount[currentPlayer] = post.discardCount[currentPlayer];



 printf("hand count expected %d test amount %d ",  pre->handCount[currentPlayer], post.handCount[currentPlayer]);

      if(memcmp(&post,pre, sizeof(struct gameState))==0)
    {
        printf("adventurer Test PASS\n");
    }
    else
    {
        printf("adventurer Test FAIL\n");
    }

return 0;
}


int main()
{
    printf("playAdventurer test - cardtest2/n");

    //array of cards
      int k[10] = {adventurer, copper, silver, gold, mine,
	       remodel, smithy, village, baron, great_hall};

    struct gameState preState;

    int i, j, n;

    //create intial game
  SelectStream(2);
  PutSeed(3);


    for (n = 0; n < 2000; n++) {
       ;

        initializeGame(2,k,n+1,&preState);
    //fill in required preconditions with randoms.

        preState.numPlayers = floor(Random() * (MAX_PLAYERS-1))+1;
        preState.whoseTurn = floor(Random() * preState.numPlayers);

        preState.handCount[preState.whoseTurn] = floor(Random() * MAX_HAND);
        preState.discardCount[preState.whoseTurn] = floor(Random() * MAX_DECK);
        preState.deckCount[preState.whoseTurn] = floor(Random() * MAX_DECK);

    for(i=0;i<preState.handCount[preState.whoseTurn];i++)
        {
        preState.hand[preState.whoseTurn][i] = floor(Random() * 10);
        }
    for(i=0;i<preState.deckCount[preState.whoseTurn];i++)
        {
        preState.hand[preState.whoseTurn][i] = floor(Random() * 10);
        }

        //run test
        testAdventurer(&preState);
    }



return 0;

}



