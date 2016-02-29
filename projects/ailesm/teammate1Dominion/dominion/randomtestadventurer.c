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

int main (int argc, char** argv) {
    int i, j, m;
    int testCard;
    int errors=0;
    int adPos;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int numPlayers = 2;
    int player = 0;
    int otherPlayer = 0;
    struct gameState G;
    time_t t;
    srand((unsigned) time(&t));


    int testHand[50];
    int testDiscard[50];
    int testDeck[50];
//------------------- end prologue, begin tests: 20 randomized tests of 50 card hands --------------//

    printf("starting testing for adventurer card\n");
    for(i=0;i<20;i++){
//------------------- PART ONE: BUILD TEST CASE GENERATOR ------------------------------------------//
        //printf("game %d\n",i);
        initializeGame(2, k, 2, &G);
        G.handCount[player] = 50;
        //G.handCount[otherPlayer] = 50;
        G.whoseTurn = 1;
        G.deckCount[player] = 50;
        int treasureCount = 0;

        //here we create a random hand
        for(j=0;j<50;j++){
            testCard = rand () % treasure_map;
            G.hand[player][j] = testCard;
            testHand[j] = testCard;
            //printf("added card %d\n",testCard);
            if (testCard == copper || testCard == silver || testCard == gold){
                treasureCount++;
            }

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

        //now we find an adventurer to play
        for (j=0;j<50;j++){
            if (G.hand[player][j]== adventurer){
                //printf("found smithy at %d\n",j);
                adPos = j;
                break;

            }
        }
  //------------------- PART TWO: EXECUTE SYSTEM UNDER TEST ------------------------------------------//
        //first we look at the players deck
        int found = 0;
        int flipped =0;
        int unflippedActual = 0;
        //we count the number of cards flipped until we hit two treasures
        for (j=50;j>0;j--){
            int revealed = G.deck[player][j];
            if (revealed == copper || revealed == silver || revealed == gold){
                //printf("found coin\n");
                found++;
            }
            if (found == 2){
                break;
            }
        }
        flipped = j;

        //printf("deck should have %d cards\n",flipped);
        int temp[50];
        int actual = 0;
        playAdventurer(0,&G,0,0,&temp);
   //------------------- PART THREE: EXECUTE ORACLE TESTS ---------------------------------------------//
        //did we flip as many as the function?
        if(flipped != G.deckCount[player]){
            printf("too many/few cards flipped\n");
            errors++;
        }
        int postCount = 0;
        //let's check players hand for two extra treasures
        for (j=0;j<52;j++){
            if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold){
                //printf("found coin\n");
                postCount++;
            }
        }
        if(treasureCount+2 != postCount){
            printf("treasures added incorrectly\n");
            errors++;
        }
    //------------------- ADDITIONAL TESTS -------------------------------------------------------------//
        //try running adventurer with no deck
        G.deckCount[player] = -1;
        playAdventurer(0,&G,0,0,&temp);
        if (G.handCount[player] != 52){
            printf("no treasure cards added on 0 deck attempt\n");
            errors++;
        }
        //try running with no treasures
        int newTmp[50];
        G.deckCount[player] = 50;
        for (j=0;j<50;j++){
            if (G.deck[player][j]== copper || G.deck[player][j]== silver || G.deck[player][j]== gold ){
                G.deck[player][j] = 0;
            }

        }
        playAdventurer(0,&G,0,0,&newTmp);
        if (G.deckCount[player] != 0){
            printf("adventurer failed with 0 initial treasures in deck\n");
            errors++;
        }
           //try running with one treasure
        int newTmp2[50];
        G.deckCount[player] = 50;
        int randomInsert = rand () % 50;
        for (j=0;j<50;j++){
            if (G.deck[player][j]== copper || G.deck[player][j]== silver || G.deck[player][j]== gold ){
                G.deck[player][j] = 0;
            }
        }
        G.deck[player][randomInsert] = copper;
        playAdventurer(0,&G,0,0,&newTmp2);
        if (G.deckCount[player] != 0){
            printf("adventurer failed with 1 initial treasures\n");
            errors++;
        }






    }
    printf("tests complete! %d errors\n",errors);
	return 0;
}

