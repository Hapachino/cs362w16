

//*********************************************
//a program to test adventurer card from
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


int isInHand(int cardType, int player, int handSize, struct gameState *state);

int main (int argc, char** argv) {
    int i, j, m;
    int testCard, choice1, choice1Val, choice2, choice2Val, cardPos, flag, retFlag;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int numPlayers = 2;
    int player = 0;
    int errors=0;

    struct gameState G;
    time_t t;
    srand((unsigned) time(&t));


    int testHand[50];
    int testDiscard[50];
    int testDeck[50];
//------------------- end prologue, begin tests: 20 randomized tests of 50 card hands --------------//


    printf("starting testing for remodel card\n");
    for(i=0;i<10;i++){

//------------------- PART ONE: BUILD TEST CASE GENERATOR ------------------------------------------//
        //printf("game %d\n",i);
        retFlag = 0;
        flag = 0;
        initializeGame(2, k, 2, &G);
        G.handCount[player] = 5;
        G.whoseTurn = 0;
        G.deckCount[player] = 5;

        //here we create a random hand
        for(j=0;j<5;j++){
            testCard = rand () % treasure_map;
            G.hand[player][j] = testCard;
            testHand[j] = testCard;
            //printf("hand %d start %d\n",i,testCard);
        }
        //we'll make the first card the remodel card
        G.hand[player][0] = remodel;
        testCard = 0;

         //and a random deck
        for(j=0;j<5;j++){
            testCard = rand () % treasure_map;
            G.deck[player][j] = testCard;
            testDeck[j] = testCard;
            //printf("added card %d\n",testCard);
         }
        testCard = 0;
          //and a random discard
        for(j=0;j<5;j++){
            testCard = rand () % treasure_map;
            G.discard[player][j] = testCard;
            testDiscard[j] = testCard;
            //printf("added discard %d\n",testCard);
         }
        testCard = 0;

        choice1 = rand () % G.handCount[player];
        choice1Val = getCost(handCard(choice2,&G));
        int choice1Type = handCard(choice1,&G);
        choice2 = rand () % treasure_map;
        choice2Val = getCost(choice2);

        int numInHand = isInHand(choice2,0,G.handCount[player],&G);
        int toDiscardInHand = isInHand(choice1Type,0,G.handCount[player],&G);


        if (numInHand != 0 && toDiscardInHand != 0){
            if ((choice1Val+2)>choice2Val){
                flag = -1;
            }

            //printf("handcount before %d\n",G.handCount[player]);
    //------------------- PART TWO: EXECUTE SYSTEM UNDER TEST ------------------------------------------//

            retFlag = playCard(0,choice1,choice2,0,&G);

    //------------------- PART THREE: EXECUTE ORACLE TESTS ---------------------------------------------//
            printf("choice 1 %d\n",choice1Type);
            printf("choice 2 %d\n",choice2);
            for (j=0;j<6;j++){
                printf("before hand %d at %d is %d\n",i,j,testHand[j]);
            }
            for (j=0;j<6;j++){
                printf("after hand %d at %d is %d\n",i,j,G.hand[player][j]);
            }
            for (j=0;j<6;j++){
                printf("before hand %d at %d is %d\n",i,j,testDiscard[j]);
            }
            for (j=0;j<6;j++){
                printf("after hand %d at %d is %d\n",i,j,G.discard[player][j]);
            }
            //we need to make sure that the card selected has cost less that +2 second choice
            //if it does not, then the the playcard and cardeffect functions must return -1
            //printf("run %d\n",i);
            if (retFlag != flag){
                printf("%d %d\n",retFlag,flag);
                //errors++;
            }
            else if (retFlag != -1){
                //printf("%d\n",G.handCount[player]);
                if (G.handCount != 48){
                    //printf("cards not trashed\n");
                    //errors++;
                }
            }

            if (retFlag != -1 && G.playedCards[0]==remodel)
            {
                if (G.playedCards[1] != choice1Type){
                    printf("discarded wrong card\n");
                    errors++;
                }
            }

        }



        }


    printf("tests complete! %d errors\n",errors);
	return 0;
}



int isInHand(int cardType, int player, int handSize, struct gameState *state){
    int count = 0;
    int i = 0;
    for (i;i<handSize;i++){
        if (state->hand[player][i]==cardType){
            count++;
        }
    }
    return count;
}


