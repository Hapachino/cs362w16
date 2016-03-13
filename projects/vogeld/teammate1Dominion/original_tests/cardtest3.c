//
// Created by Robert on 1/26/2016.
// the Smithy Test

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
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



int testGreatHall(struct gameState *state, int currentPlayer, int handPos ) {

    //set some beginning vars
    int beginHandCount = state->handCount[currentPlayer];
    int beginDeckCount = state->deckCount[currentPlayer];
    int beginDiscardCount = state->discardCount[currentPlayer];
    int beginActions = state->numActions;
    int beginPlayedCount = state->playedCardCount;
    int status = 0;

    assert(currentPlayer >= 0);
    assert(beginHandCount > 0);

    int i;

    //put greatHall in deck
    state->hand[currentPlayer][0] = great_hall;

    //run great Hall
    great_hallCard(state, currentPlayer, handPos);

    printf("PERFORMING DRAW TEST-------------------------: \n");

    if (state->handCount[currentPlayer] != beginHandCount) {
        status++;
        printf("BeginHand Count was: %i \n", beginHandCount);
        printf("Actual Hand Count was: %i \n", state->handCount[currentPlayer]);
        printf("Hand Count should be: %i \n", beginHandCount);
    } else if (state->deckCount[currentPlayer] != beginDeckCount - 1) {
        status++;
        printf("Begin DECK Count was: %i \n", beginDeckCount);
        printf("Actual DECK Count was: %i \n", state->deckCount[currentPlayer]);
        printf("Hand Count should be: %i \n", beginDeckCount - 1);

    } else {
        printf("PASSED \n");
    }

    //Num actions should increase by one
    printf("PERFORMING TEST on Actions-------------------------: \n");
    if (state->numActions != beginActions + 1) {
        status++;
        printf("FAIL: Actions - discard count mismatch \n");
        printf("BeginAction Count was: %i \n", beginActions);
        printf("Actual Count was: %i \n", state->numActions);
        printf(" should be same %i \n", beginActions + 1);
    } else {
        printf("PASSED \n");
    }
    printf("PERFORMING TEST on Discard-------------------------: \n");
    //Test2

    //should add 1 to played cards pile,

    if (state->playedCardCount != beginPlayedCount + 1) {
        status++;
        printf("FAIL: DISCARD - discard count mismatch \n");

        printf("Begin DiscardCount was:\t\t %i \n", beginDiscardCount);
        printf("Actual Discard Count was:\t %i \n", state->discardCount[currentPlayer]);
        printf("DiscardCount should be:\t\t %i \n", beginDiscardCount + 1);

    }
        //card should be of type great_hall
    else if (state->playedCards[state->playedCardCount - 1] != great_hall) {

        status++;
        printf("FAIL: Wrong card in discard pile - discard count mismatch \n");
        //printHand(currentPlayer, state);
        //printDiscard(currentPlayer, state);
        //printPlayed(currentPlayer, state);
    } else {
        printf("PASSED \n");
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
    int currentPlayer = whoseTurn(&G);


    printf ("\n\nTESTING Great Hall CARD: ------------------ \n");
    int testResult = testGreatHall(&G, currentPlayer, 0);
    if( testResult == 0){
        printf ("test GreatHall: OK\n");

    }else{
        printf ("FAILED : %i tests\n", testResult );
    }

return 0;
}