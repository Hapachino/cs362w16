//
// Created by Robert on 1/26/2016.
// the Smithy Test

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<stdio.h>
#include "interface.h"

#include "rngs.h"


void cardNumToName(int card, char *name){
    switch(card){
        case curse: strcpy(name,"Curse");
            break;
        case estate: strcpy(name,"Estate");
            break;
        case duchy: strcpy(name,"Duchy");
            break;
        case province: strcpy(name,"Province");
            break;
        case copper: strcpy(name,"Copper");
            break;
        case silver: strcpy(name,"Silver");
            break;
        case gold: strcpy(name,"Gold");
            break;
        case adventurer: strcpy(name,"Adventurer");
            break;
        case council_room: strcpy(name,"Council Room");
            break;
        case feast: strcpy(name,"Feast");
            break;
        case gardens: strcpy(name,"Gardens");
            break;
        case mine: strcpy(name,"Mine");
            break;
        case remodel: strcpy(name,"Remodel");
            break;
        case smithy: strcpy(name,"Smithy");
            break;
        case village: strcpy(name,"Village");
            break;
        case baron: strcpy(name,"Baron");
            break;
        case great_hall: strcpy(name,"Great Hall");
            break;
        case minion: strcpy(name,"Minion");
            break;
        case steward: strcpy(name,"Steward");
            break;
        case tribute: strcpy(name,"Tribute");
            break;
        case ambassador: strcpy(name,"Ambassador");
            break;
        case cutpurse: strcpy(name,"Cutpurse");
            break;
        case embargo: strcpy(name,"Embargo");
            break;
        case outpost: strcpy(name,"Outpost");
            break;
        case salvager: strcpy(name,"Salvager");
            break;
        case sea_hag: strcpy(name,"Sea Hag");
            break;
        case treasure_map: strcpy(name,"Treasure Map");
            break;

        default: strcpy(name,"?");
    }

}



int getCardCost(int card) {
    int cost;
    switch(card) {
        case curse: cost = CURSE_COST;
            break;
        case estate: cost = ESTATE_COST;
            break;
        case duchy: cost = DUCHY_COST;
            break;
        case province: cost = PROVINCE_COST;
            break;
        case copper: cost = COPPER_COST;
            break;
        case silver: cost = SILVER_COST;
            break;
        case gold: cost = GOLD_COST;
            break;
        case adventurer: cost = ADVENTURER_COST;
            break;
        case council_room: cost = COUNCIL_ROOM_COST;
            break;
        case feast: cost = FEAST_COST;
            break;
        case gardens: cost = GARDEN_COST;
            break;
        case mine:  cost = MINE_COST;
            break;
        case remodel: cost = REMODEL_COST;
            break;
        case smithy: cost = SMITHY_COST;
            break;
        case village: cost = VILLAGE_COST;
            break;
        case baron: cost = BARON_COST;
            break;
        case great_hall: cost = GREAT_HALL_COST;
            break;
        case minion: cost = MINION_COST;
            break;
        case steward: cost = STEWARD_COST;
            break;
        case tribute: cost = TRIBUTE_COST;
            break;
        case ambassador: cost = AMBASSADOR_COST;
            break;
        case cutpurse: cost = CUTPURSE_COST;
            break;
        case embargo: cost = EMBARGO_COST;
            break;
        case outpost: cost = OUTPOST_COST;
            break;
        case salvager: cost = SALVAGER_COST;
            break;
        case sea_hag: cost = SEA_HAG_COST;
            break;
        case treasure_map: cost = TREASURE_MAP_COST;
            break;
        default: cost = ONETHOUSAND;
    }
    return cost;
}






void printHand(int player, struct gameState *game) {
    int handCount = game->handCount[player];
    int handIndex;
    printf("Player %d's hand:\n", player);
    if(handCount > 0) printf("#  Card\n");
    for(handIndex = 0; handIndex < handCount; handIndex++) {
        int card = game->hand[player][handIndex];
        char name[MAX_STRING_LENGTH];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", handIndex, name);
    }
    printf("\n");
}



void printDeck(int player, struct gameState *game) {
    int deckCount = game->deckCount[player];
    int deckIndex;
    printf("Player %d's deck: \n", player);
    if(deckCount > 0) printf("#  Card\n");
    for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
        int card = game->deck[player][deckIndex];
        char name[MAX_STRING_LENGTH];
        cardNumToName(card, name);
        printf("%-2d %-13s\n", deckIndex, name);
    }
    printf("\n");
}

int get_value(int card, int cPlayer, struct gameState *state){

    int val =0;
    if (card == curse) { val =  - 1; };
    if (card == estate) {  val =  1; };
    if (card == duchy) {  val =  3; };
    if (card == province) {  val =  6; };
    if (card == great_hall) {  val =  1; };
    if (card == gardens) {  val = ( fullDeckCount(cPlayer, 0, state) / 10 ); };

    return val;
}

int testscoreFor(int cPlayer, struct gameState *state ) {

    //set some beginning vars
    int i,k;
    int status = 0;
    int card[6] = {0,1,2,3,10,16};

   //todo set this up for random so that it tries all combos of cards

   for (k=0; k < 6; k++){

       int sumScore = 0;
       int score = 0;

       int c1 = k;
       int c2 = (k+1)%6;
       int c3 = (k+2)%6;

       int deckScore;
       int handScore;
       int disScore;

       int maxHand = MAX_DECK;
       int maxDeck= MAX_DECK-100;
       int maxDis= MAX_DECK-200;

       //stack Deck
       for(i=0; i < MAX_DECK; i++){
           state->deck[cPlayer][i] = card[c1];
       }

       //stack hand
       for(i=0; i < maxHand; i++){
           state->hand[cPlayer][i] = card[c2];
       }

       //stack Discard
       for(i=0; i < maxDis; i++){
           state->discard[cPlayer][i] = card[c3];

       }
       state->handCount[cPlayer] = maxHand;
       state->deckCount[cPlayer] = maxDeck;
       state->discardCount[cPlayer] = maxDis;
        //printDeck(cPlayer, state);



        //num cards by the val by  discard, hand, and deck)
       deckScore = get_value(c1, cPlayer, state);
       handScore = get_value(c2, cPlayer, state);
       disScore = get_value(c3, cPlayer, state);

       sumScore = (maxDeck*deckScore + maxHand*handScore + maxDis*disScore);

       score = scoreFor(cPlayer, state);

       if(score != sumScore){
           status ++;
           char name[MAX_STRING_LENGTH];
           cardNumToName(card[c1], name);
           printf("Scenario: %-13s , ", name);
           cardNumToName(card[c2], name);
           printf("Scenario: %-13s , ", name);
           cardNumToName(card[c3], name);
           printf("Scenario: %-13s \n", name);
           printf("Score is not correct scoreFor retuned: %i, but should have returned %i\n",score,sumScore);
       }

   }

    return status;
}


int main(int argc, char** argv) {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    printf ("Starting game.\n");

    initializeGame(2, k, atoi(argv[1]), &G);

    int money = 0;
    int smithyPos = -1;
    int adventurerPos = -1;
    int i=0;

    int numSmithies = 0;
    int numAdventurers = 0;
    srand(time(NULL));
    //VIP Must start at player 0
    int currentPlayer = 0;

    printf ("\n\nTESTING scoreFor: ------------------ \n");
    int testResult = testscoreFor( currentPlayer, &G );

    if( testResult == 0){
        printf ("test Score for: OK \n");

    }else{
        printf ("FAILED : %i tests\n", testResult );
    }


return 0;
}