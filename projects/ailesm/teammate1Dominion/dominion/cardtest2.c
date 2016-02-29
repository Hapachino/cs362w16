

//*********************************************
//a program to test salvager card from
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
#include<time.h>

int main (int argc, char** argv) {
    int i, j, m;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int errors = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int numPlayers = 2;
    int player = 0;
    int otherPlayer = 0;
    int testCard;
    int cardPick;
    int salPos;
    struct gameState G, testG;
    time_t t;
    srand((unsigned) time(&t));

    int testHand1[50];
    int testHand2[50];

//------------------- end prologue, begin tests: 50 randomized tests of 50 card hands --------------//

    printf("starting testing for scavenger card\n");
    for(i;i<50;i++){
        //printf("game %d\n",i);

        initializeGame(2, k, 2, &G);

        G.handCount[player] = 50;
        G.handCount[otherPlayer] = 50;
        G.whoseTurn = 0;
        G.coins = 0;
        int coins = 0;
        int salFound = 0;



        //here we create random hands for current player
        for(j=0;j<50;j++){
            testCard = rand() % treasure_map;
            G.hand[player][j] = testCard;
            testHand1[j] = testCard;
            //as we make the random hand, we count the coins for our control value
            if (testCard == salvager){
                salPos = j;
                salFound = 1;
            }
            if (testCard== copper)
                {
                  coins += 1;
                }
            else if (testCard== silver)
                {
                  coins += 2;
                }
            else if (testCard== gold)
                {
                  coins += 3;
                }
            //if verbose
            //printf("added %d at handpos %d\n",testCard,j);
        }

        //pick a random card (the card the player chooses)

        c1 = rand() % 48;
        int cardVal = handCard(c1, &G); //get the card type from its position
        if (cardVal == gold ){
            coins = coins - 3;
        }
        if (cardVal == silver){
            coins = coins - 2;
        }
        if (cardVal == copper){
            coins = coins - 1;
        }


        int numCard = 0;
        int postNumCard = 0;

        //count instances of card
        for (j=0;j<50;j++){
            if (G.hand[player][j]==cardVal)
                numCard++;
        }

        //run the function
        if (salFound){
            playCard(salPos, c1, c2, c3, &G);



            //count after function
            for (j=0;j<50;j++){

                if (G.hand[player][j]==-1){
                    //printf("card removed\n %d",c1);
                    break;
                }
                if (G.hand[player][j]==cardVal){
                    postNumCard++;
                }

            }

            if (numCard == postNumCard){
                printf("card not removed from deck! %d %d %d\n",numCard,postNumCard,cardVal);
                errors++;
            }

            if (coins != G.coins){
                int value = getCost(cardVal);
                printf("card value not added to coins! %d %d %d %d\n",coins,G.coins, value, cardVal);
                errors++;
            }
        }
        else{
            //printf("no salvager in hand\n");
        }

    }




printf("testing complete! %d errors\n",errors);



  return 0;
}
