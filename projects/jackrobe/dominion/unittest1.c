//
// Created by Robert on 1/26/2016.
// the Smithy Test

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
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



int testDrawCard(int cPlayer, struct gameState *state ) {

    //set some beginning vars
    int i;
    int status = 0;
    struct gameState preState;
    preState = *state;

    //call draw card
    drawCard(cPlayer, state);

    //Troubleshooting
    //printf("state hand %i", state->handCount[cPlayer]);
    //printf("prestate hand %i",preState.handCount[cPlayer]);
    //printf("state deck %i", state->deckCount[cPlayer]);
    //printf("prestate deck %i",preState.deckCount[cPlayer]);

    //check hand count
    if (state->handCount[cPlayer] != preState.handCount[cPlayer] +1){
        status ++;
        printf("HandCount not correct \n");
        printf("HandCount is %i\n", state->handCount[cPlayer]);
        printf("HandCount should be %i\n\n", preState.handCount[cPlayer] +1);
    }

    //check deck count
    if (state->deckCount[cPlayer] != preState.deckCount[cPlayer]-1){
        status ++;
        printf("Deck Count not correct\n");
        printf("Deck Count is %i\n", state->deckCount[cPlayer]);
        printf("Deck Count should be %i\n\n", preState.deckCount[cPlayer]-1);
    }

    //NOW check when the deck is empty
    assert( state->deckCount[cPlayer] > 0);
    assert( state->discardCount[cPlayer] == 0);

    //move the deck to discard
    //printf("preDeck %i:\n", state->deckCount[cPlayer]);
    //printf("preDiscard %i:\n", state->discardCount[cPlayer]);

    for ( i = 0; i < state->deckCount[cPlayer];i++){
        state->discard[cPlayer][i]= state->deck[cPlayer][i];
        state->deck[cPlayer][i] = -1;
    }
    //printf("postDeck %i:\n", state->deckCount[cPlayer]);
    //printf("postDiscard %i:\n", state->discardCount[cPlayer]);

    state->discardCount[cPlayer] = state->deckCount[cPlayer];

    //reset the deck
    state->deckCount[cPlayer] = 0;

    drawCard(cPlayer, state);

    //check hand count
    if (state->handCount[cPlayer] != preState.handCount[cPlayer] +2){
        status ++;
        printf("Empty Deck HandCount not correct \n");
        printf("Empty Deck HandCount is %i\n", state->handCount[cPlayer]);
        printf("Empty Deck HandCount should be %i\n\n", preState.handCount[cPlayer] +2);
    }

    //check deck count
    if (state->deckCount[cPlayer] != preState.deckCount[cPlayer]-2){
        status ++;
        printf("Empty Deck, Deck Count not correct\n");
        printf("Empty Deck, Deck Count is %i\n", state->deckCount[cPlayer]);
        printf("Empty Deck, Deck Count should be %i\n\n", preState.deckCount[cPlayer]-2);
    }


     //Make sure no one elses hand was affected
    for (i = 1; i < state->numPlayers; i++){
        if (checkNoChange(i, state, preState) != 0){
            status ++;
            printf("Player %i 's values were changed", i);
            //printf("DeckCount is %i", state->deckCount[cPlayer]);
            //printf("DeckCount should be %i", preState.deckCount[cPlayer]-1);
        }
    }

    //This code is ok, just not useful because there is a shuffle inside of drawcard
//    if(state->hand[cPlayer][state->handCount[cPlayer]] != preState.deck[cPlayer][ preState.deckCount[cPlayer] -1 ]){
//        status ++;;
//        printf("Card not correct");
//        int handIndex;
//
//            int card = state->hand[cPlayer][state->handCount[cPlayer]];
//            char name[MAX_STRING_LENGTH];
//            cardNumToName(card, name);
//            printf("CARD in hand was:  %-13s\n",  name);
//
//
//            card = preState.deck[cPlayer][preState.deckCount[cPlayer] -1];
//            cardNumToName(card, name);
//            printf("CARD Should have been:  %-13s\n",  name);
//
//       // printf("Card is %s", state->hand[cPlayer][state->handCount[cPlayer]]);
//        //printf("Card should be %s", preState.deck[cPlayer][preState.deckCount -1] );
//
//    }

    return status;
}



/*
 * Function to check if the off players' hand was changed
 * @params Takes the player(should be the player not under test)
 * @params, states (a current and initial)
 * */

int checkNoChange(int cPlayer, struct gameState *state, struct gameState preState ) {

    int status =0;
    int i;
    //check hand count
    if (state->handCount[cPlayer] != preState.handCount[cPlayer]) {
        status++;
        printf("Hand Count not correct\n");
        printf("Hand Count is %i\n", state->handCount[cPlayer]);
        printf("Hand Count should be %i\n\n", preState.handCount[cPlayer]);
    }

    //check deck count
    if (state->deckCount[cPlayer] != preState.deckCount[cPlayer]) {
        status++;
        printf("Deck Count not correct\n");
        printf("Deck Count is %i\n", state->deckCount[cPlayer]);
        printf("Deck Count should be %i\n\n", preState.deckCount[cPlayer]);
    }

    //check discard count
    if (state->discardCount[cPlayer] != preState.discardCount[cPlayer]) {
        status++;
        printf("Discard Count not correct\n");
        printf("Discard Count is %i\n", state->discardCount[cPlayer]);
        printf("Discard Count should be %i\n\n", preState.discardCount[cPlayer]);
    }


    // If counts failed we wont check this it'll crash
    if(status == 0) {
//    //check hand
        for (i = 0; i < state->handCount[cPlayer]; i++) {
            if (state->hand[cPlayer][i] != preState.hand[cPlayer][i]) {
                status++;;
                printf("Players Hand was altered %i: %i\n",state->hand[cPlayer][i], preState.hand[cPlayer][i] );

            }
        }

        //check deck
        for (i = 0; i < state->deckCount[cPlayer]; i++) {
            if (state->deck[cPlayer][i] != preState.deck[cPlayer][i]) {
                status++;;
                printf("Players Deck was altered %i: %i\n",state->deck[cPlayer][i], preState.deck[cPlayer][i] );
                //printDeck(cPlayer, state);
                //printDeck(cPlayer, &preState);
            }
        }
//    //check discard
        for (i = 0; i < state->discardCount[cPlayer]; i++) {
            if (state->discard[cPlayer][i] != preState.discard[cPlayer][i]) {
                status++;
                printf("Players Discard was altered %i: %i\n",state->discard[cPlayer][i], preState.discard[cPlayer][i] );

            }
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

    //VIP Must start at player 0
    int currentPlayer = 0;

    int testResult = testDrawCard( currentPlayer, &G );
    if( testResult == 0){
        printf ("test drawCard: OK \n");

    }else{
        printf ("FAILED : %i tests", testResult );
    }


return 0;
}