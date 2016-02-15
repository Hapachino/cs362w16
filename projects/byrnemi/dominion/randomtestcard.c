

//*********************************************
//a program to test embargo card from
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
    int testCard, choice1, cardPos, flag, retFlag;
    int supplyInPlay = 0;
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


    printf("starting testing for embargo card\n");
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
            if (j != 2){
                G.hand[player][j] = testCard;
                testHand[j] = testCard;
            }
            else{
                G.hand[player][j] = embargo;
                testHand[j] = embargo;
            }
            //printf("hand %d start %d\n",i,testCard);
        }
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

        //produce a random choice between 0 and treasure for supply pile to embargo
        int choice1 = rand () % treasure_map;
        //printf("embargo %d pile\n",choice1);




    //------------------- PART TWO: EXECUTE SYSTEM UNDER TEST ------------------------------------------//

        retFlag = playCard(2,choice1,0,0,&G);
        int beforeCoins = G.coins;
        cardEffect(22,choice1,0,0,&G,2,0);
        int afterCoins = G.coins;


    //------------------- PART THREE: EXECUTE ORACLE TESTS ---------------------------------------------//


        supplyInPlay = 0;
        for (j=0;j<10;j++){
            if (choice1 == k[j]){
                supplyInPlay = 1;
                printf("selected supply is in play\n");
            }
        }
        //step 1: verify that there is an embargo on randomly chosen pile
        if (G.embargoTokens[choice1] != 1 && supplyInPlay == 1){
            printf("something went wrong pile not embargoed!\n");
            errors++;
        }

        //step 2: verify that pile is embargoed, try to draw from embargoed pile
        int gainFlag = gainCard(choice1,&G,0,0);
        if (gainFlag != -1 && choice1 != curse && choice1 != village && choice1 != gold && choice1 != silver && choice1 != copper != choice1 != province && choice1 != estate && choice1 != duchy){
            printf("embargo not acknowledged\n");
            errors;
        }
        //step 3: check coins
        if (beforeCoins+2 != afterCoins)
        {
            printf("coins not added correctly\n");
            errors++;
        }

        //bug: gaincard does not check for embargo




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



