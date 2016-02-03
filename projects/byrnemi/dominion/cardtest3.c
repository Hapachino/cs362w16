
//*********************************************
//a program to test smithy card from
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
#include <time.h>

int main (int argc, char** argv) {
    int i, j, m;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int errors=0;
    int smithyPos;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int numPlayers = 0;
    int player = 1;
    int otherPlayer = 0;
    int testCard;
    struct gameState G;
    time_t t;
    srand((unsigned) time(&t));


    int testHand[50];
    int testDiscard[50];
    int testDeck[50];
    G.handCount[player] = 50;
    G.deckCount[player] = 50;

//------------------- end prologue, begin tests: 20 randomized tests of 50 card hands --------------//

    printf("starting testing for smith card\n");
    for(i;i<20;i++){
        //printf("game %d\n",i);
        initializeGame(2, k, 2, &G);
        G.handCount[player] = 50;
        //G.handCount[otherPlayer] = 50;
        G.whoseTurn = 1;
        G.deckCount[player] = 50;


        //here we create a random hand
        for(j=0;j<50;j++){
            testCard = rand () % treasure_map;
            G.hand[player][j] = testCard;
            testHand[j] = testCard;
            //printf("added card %d\n",testCard);

        }

        //now we make a discard pile
        for(j=0;j<50;j++){
            testCard = rand () % treasure_map;
            G.discard[player][j] = testCard;
            testDiscard[j] = testCard;
            //printf("added discard %d\n",testCard);

        }

        //now we make a player deck
        for(j=0;j<50;j++){
            testCard = rand () % treasure_map;
            G.deck[player][j] = testCard;
            testDeck[j] = testCard;
            //printf("added deck %d\n",testCard);

        }

        //now we find a smithy to play
        for (j=0;j<50;j++){
            if (G.hand[player][j]== smithy){
                //printf("found smithy at %d\n",j);
                smithyPos = j;
                break;

            }
        }
//------------------- half the time we test in cases where the deck is not empty --------------//
        if (i % 2 == 1){
            playSmithy(player,&G,smithyPos);
            //printf("deck count %d   hand count %d\n",G.deckCount[player],G.handCount[player]);
            if (G.deckCount[player] != 47){
                printf("deckcount is incorrect!\n");
                errors++;
            }
            if(G.handCount[player]!= 52){
                printf("deckcount is incorrect!\n");
                errors++;
            }

            //verify one card from draw

            int counterPre = 0;
            int counterPost =0;
            int checkDex = 51;
            //printf("checking card %d at %d\n",G.hand[player][checkDex],checkDex);
            for (j=0;j<50;j++){
                if (testDeck[j]==G.hand[player][checkDex])
                    counterPre++;
            }
            for (j=0;j<48;j++){
                if (G.deck[player][j]==G.hand[player][checkDex])
                    counterPost++;
            }
            //printf("pre %d post %d\n",counterPre,counterPost);
        }
//------------------- half the time we test in cases where it is--------------//

        else{
            playSmithy(player,&G,smithyPos);
            //printf("deck count %d   hand count %d\n",G.deckCount[player],G.handCount[player]);
            //the counts should be the same as above, since the discard pile also has 50 cards
            if (G.deckCount[player] != 47){
                printf("deckcount is incorrect!\n");
                errors++;
            }
            if(G.handCount[player]!= 52){
                printf("deckcount is incorrect!\n");
                errors++;
            }
            //but we also need to check that the discard pile is empty
            if (G.discardCount[player]!= 0){
                printf("discard count is incorrect!\n");
                errors++;
            }
        }
//------------------- test card with bad values -------------------------------//
        for (j=0;j<50;j++){
            G.deck[player][j] = -1;
        }
        int ret = playSmithy(player,&G,smithyPos);
        if (ret > 0){
            printf("no error code on failure\n");
            errors++;
        }


//        shuffle(player,&G);
//        for (i=0;i<50;i++){
//            for (j=0;j<50;j++){
//                if (G.deck[player][i] == testDeck[j]){
//                    printf("card found\n");
//                    break;
//                }
//                if (j==50){
//                    printf("card not found\n");
//                    errors++;
//                }
//            }
//        }


    }



printf("testing complete! %d errors found\n",errors);




  return 0;
}

