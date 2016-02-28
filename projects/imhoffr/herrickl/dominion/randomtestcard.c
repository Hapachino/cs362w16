/*****************************************************
 * Regina Imhoff
 * stabbymcduck on github
 * imhoffr@oregonstate.edu
 * Date due: 02/14/2016
 * randomtestcard.c
 * random test of the village card
 * village adds one card to hand and adds 2 actions
 * randomtestcard: randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(FLAGS)
 ******************************************************/

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define DECK_SIZE 10
#define KINGDOM_CARDS_SIZE 10
#define MAX_ACTIONS 5 // This is an arbitrary number!!
#define TESTCARD "village"
#define TEST_COUNT 1000

char *cardName(int card) {
    char *name = NULL;
    
    switch (card) {
        case adventurer:
            name = "adventurer";
            break;
        case council_room:
            name = "council room";
            break;
        case curse:
            name = "curse";
            break;
        case cutpurse:
            name = "cutpurse";
            break;
        case embargo:
            name = "embargo";
            break;
        case mine:
            name = "mine";
            break;
        case minion:
            name = "minion";
            break;
        case sea_hag:
            name = "sea hag";
            break;
        case smithy:
            name = "smithy";
            break;
        case tribute:
            name = "smithy";
            break;
        case village:
            name = "village";
            break;
    }
    
    return name;
}


void printActions(struct gameState *state){
    printf("Number of Actions: %d\n", state->numActions);
}

void printPositionCard(int position, int card) {
    printf("  Position %d, Card: ", position);
    
    char *name = cardName(card);
    
    if (name == NULL) {
        printf("%d", card);
    } else {
        printf("%s", name);
    }
    
    printf("\n");
}

void printDeck(int player, struct gameState *state) {
    printf("Deck:\n");
    
    for(int i = 0; i < state->deckCount[player]; i++){
        printPositionCard(i, state->deck[player][i]);
    }
}

void printDiscard(int player, struct gameState* state) {
    printf("Discard:\n");
    
    for(int i = 0; i < state->discardCount[player]; i++){
        printPositionCard(i, state->discard[player][i]);
    }
}

void printHand(int player, struct gameState *state) {
    printf("Hand:\n");
    
    for(int i = 0; i < state->handCount[player]; i++){
        printPositionCard(i, state->hand[player][i]);
    }
}

void printPlayedCards(struct gameState *state) {
    printf("Played Cards:\n");
    
    for(int i = 0; i < state->playedCardCount; i++){
        printPositionCard(i, state->playedCards[i]);
    }
}

int randomCard(int kingdomCards[KINGDOM_CARDS_SIZE]) {
    int cardIndex = floor(Random() * KINGDOM_CARDS_SIZE);
    assert(cardIndex >= 0 && cardIndex < KINGDOM_CARDS_SIZE);
    
    return kingdomCards[cardIndex];
}

void randomDeck(int player, int size, int kingdomCards[KINGDOM_CARDS_SIZE], struct gameState *state) {
    state->deckCount[player] = 0;
    
    for(int i = 0; i < size; i++){
        state->deck[player][i] = randomCard(kingdomCards);
        state->deckCount[player]++;
    }
}

bool randomTest(struct gameState *originalGame, int kingdomCards[KINGDOM_CARDS_SIZE]) {
    int player = 0;
    struct gameState testGame;
    bool allPassed = true;
    int handPos = 0;
    int bonus = 0;
    
    memcpy(&testGame, originalGame, sizeof(struct gameState));
    
    randomDeck(player, DECK_SIZE, kingdomCards, &testGame);

    // empty discard pile
    int playedCardCountBefore = testGame.playedCardCount;
    int deckCountBefore = testGame.deckCount[player];
    
    int handCountBefore = 1;
    testGame.handCount[player] = handCountBefore;
    testGame.hand[player][handPos] = village;

    int numActionsBefore = Random() * MAX_ACTIONS;
    testGame.numActions = numActionsBefore;
    
    printf("Before Play Village\n");
    printDeck(player, &testGame);
    printHand(player, &testGame);
    printPlayedCards(&testGame);
    
    printf("After Play Village\n");
    
    cardEffect(village, 0, 0, 0, &testGame, handPos, &bonus);

    
    /* Test Failed Statements */
    /* Test 1 */
    // deck decreases by 1
    printDeck(player, &testGame);
    
    int actualDeckCountAfter = testGame.deckCount[player];
    int expectedDeckCountAfter = deckCountBefore - 1;
    printf("Deck count: %d, Expected: %d\n", actualDeckCountAfter, expectedDeckCountAfter);
    
    if(actualDeckCountAfter != expectedDeckCountAfter){
        printf(">>>>>>> ERROR: TEST 1 FAILED: >>>>>>>\n");
        allPassed &= false;
    }
    
    /* Test 2 */
    // played card count increases by 1 to indicated discardCard is called.
    printPlayedCards(&testGame);
    
    int actualPlayedCardCountAfter = testGame.playedCardCount;
    int expectedPlayedCardCountAfter = playedCardCountBefore + 1;
    printf("Played card count: %d, Expected: %d\n", actualPlayedCardCountAfter, expectedPlayedCardCountAfter);
    
    if(actualPlayedCardCountAfter != expectedPlayedCardCountAfter){
        printf(">>>>>>> ERROR: TEST 2 FAILED: >>>>>>>\n");
        allPassed &= false;
    }
    
    /* Test 3 */
    // hand count should stay the same because card is drawn and village is discarded
    printHand(player, &testGame);
    
    int actualHandCountAfter = testGame.handCount[player];
    int expectedHandCountAfter = handCountBefore;
    printf("Hand count: %d, Expected: %d\n", actualHandCountAfter, expectedHandCountAfter);
    
    if(actualHandCountAfter != expectedHandCountAfter){
        printf(">>>>>>> ERROR: TEST 3 FAILED >>>>>>>\n");
        allPassed &= false;
    }
    
    /* Test 4 */
    // number of actions increased by 2
    printActions(&testGame);
    
    int actualActionsCountAfter = testGame.numActions;
    int expectedActionsCountAfter = numActionsBefore + 2;
    printf("Action count: %d, Expected: %d\n", actualActionsCountAfter, expectedActionsCountAfter);
    
    if(actualActionsCountAfter != expectedActionsCountAfter){
        printf(">>>>>>> ERROR: TEST 4 FAILED >>>>>>>\n");
        allPassed &= false;
    }
    
    return allPassed;
}

int main(){
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int seed = 1000;
    int numberOfPlayers = 2;
    int initializeGameStatus;
    bool allPassed = true;
    struct gameState originalGame;

    initializeGameStatus = initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    assert(initializeGameStatus == 0);
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // run through random test 1000 times
    for(int i = 0; i < TEST_COUNT; i++){
        printf("Random Trial %d/%d\n", i + 1, TEST_COUNT);
        allPassed &= randomTest(&originalGame, cards);
    }

    printf("%d Random Trials complete\n", TEST_COUNT);
    
    if(allPassed == true){
        printf("\n ####  ALL TESTS PASSED  #### \n");
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    }else{
        printf("\n >>>>>> ONE OR MORE TESTS FAILED >>>>>>\n");
    }
    
    return 0;
}