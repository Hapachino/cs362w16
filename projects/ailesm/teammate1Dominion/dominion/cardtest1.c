
//*********************************************
//a program to test cutpurse card from
//dominion as implemented in dominion.c using
//randomized inputs.
//Author: Michael Byrne, OSU byrnemi
//For: CS 362 Software Engineering 2
//Sources: as noted
//*********************************************
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

int main (int argc, char** argv) {
    int i, j, m;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int errors=0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int numPlayers = 0;
    int player = 1;
    int otherPlayer = 0;
    int testCard;
    struct gameState G;


    SelectStream(1);
    PutSeed(2);

    int testHand1[50];
    int testHand2[50];

//------------------- end prologue, begin tests: 20000 randomized tests of 50 card hands --------------//

    printf("starting testing for cutpurse card\n");
    for(i;i<20000;i++){
        //printf("game %d\n",i);
        initializeGame(2, k, 2, &G);
        G.handCount[player] = 50;
        G.handCount[otherPlayer] = 50;
        G.whoseTurn = 1;
        int testHandCount = 50;
        int copperCount = 0;
        int testCopperCount = 0;
        int cutPos;

        //here we create random hands for both players
        for(j=0;j<50;j++){
            testCard = floor(Random()*treasure_map);
            G.hand[player][j] = testCard;
            testHand1[j] = testCard;
            if (testCard == cutpurse){
                cutPos = j;
            }
            //if verbose
            //printf("added %d at handpos %d\n",testCard,j);
        }
        for(j=0;j<50;j++){
            testCard = floor(Random()*treasure_map);
            G.hand[otherPlayer][j] = testCard;
            testHand2[j] = testCard;
            if (testCard == copper){
                //printf("copper alert\n");
                copperCount++;
            }
            //if verbose
            //printf("added %d at handpos %d\n",testCard,j);
        }
        //run the function
        playCard(cutPos, c1, c2, c3, &G);

        //count the number of coppers post-card
         for(j=0;j<50;j++){
            int peekAt = G.hand[otherPlayer][j];
            if (peekAt==copper){
                testCopperCount++;
            }
            //if verbose
            //printf("added %d at handpos %d\n",testCard,j);
        }
        //other player's hand should now have one less copper card
        if (copperCount != testCopperCount+1){
            printf("mismatch in copper counts\n");
            errors++;
        }
        //check to make sure that the other player has the correct number of cards
        if (G.handCount[otherPlayer] != 49){
            printf("other player has wrong card count: %d\n",G.handCount[otherPlayer]);
            errors++;
        }

        //run cutpurse with otherplayer hand having 0 copper
        memset(G.hand[otherPlayer], 0, sizeof(G.hand[otherPlayer]));
        G.handCount[otherPlayer] = 50;
        playCard(cutPos, c1, c2, c3, &G);
        //otherplayer should have 50 cards
        if (G.handCount[otherPlayer] != 50){
            printf("other player has wrong card count on zero copper hand: %d\n",G.handCount[otherPlayer]);
            errors++;
        }



    }



printf("testing complete! %d errors found\n",errors);




  return 0;
}
