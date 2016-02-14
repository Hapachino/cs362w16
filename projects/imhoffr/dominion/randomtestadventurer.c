/*****************************************************
 * Regina Imhoff
 * stabbymcduck on github
 * imhoffr@oregonstate.edu
 * Date due: 02/14/2016
 * randomtestadventurer.c
 * random test of the adventurer card
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
#define HAND_SIZE 5
#define KINGDOM_CARDS_LENGTH 10
#define TESTCARD "adventurer"
#define TEST_COUNT 1


int isCoin(int card) {
    return card == copper || card == silver || card == gold;
}

int deckCoinCount(int player, struct gameState *state) {
    int coinCount = 0;
    
    for(int i = 0; i < state->deckCount[player]; i++){
        if(isCoin(state->deck[player][i])) {
            coinCount++;
        }
    }
    
    return coinCount;
}

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

void printPositionCard(int position, int card) {
    printf("Position %d, Card: ", position);
    
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

int randomCard(int kingdomCards[KINGDOM_CARDS_LENGTH]) {
    int cardIndex = floor(Random() * KINGDOM_CARDS_LENGTH);
    assert(cardIndex >= 0 && cardIndex < KINGDOM_CARDS_LENGTH);
    
    return kingdomCards[cardIndex];
}

void randomDeck(int player, int size, int kingdomCards[KINGDOM_CARDS_LENGTH], struct gameState *state) {
    state->deckCount[player] = 0;
    
    for(int i = 0; i < size; i++){
        state->deck[player][i] = randomCard(kingdomCards);
        state->deckCount[player]++;
    }
}

void randomHand(int player, int size, int kingdomCards[KINGDOM_CARDS_LENGTH], struct gameState *state) {
    state->handCount[player] = 0;
    
    for(int i = 0; i < size; i++){
        state->hand[player][i] = randomCard(kingdomCards);
        state->handCount[player]++;
    }
}

bool randomTest(struct gameState *originalGame, int cards[KINGDOM_CARDS_LENGTH]) {
    int player = 0;
    struct gameState testGame;
    bool allPassed = true;
    
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    
    randomDeck(player, DECK_SIZE, cards, &testGame);
    int deckCoinCountBefore = deckCoinCount(player, &testGame);
    
    // empty discard pile
    testGame.discardCount[player] = 0;
    
    randomHand(player, HAND_SIZE, cards, &testGame);
    
    int deckCountBefore = testGame.deckCount[player];
    
    printf("Before Play Adventurer\n");
    printDeck(player, &testGame);
    printHand(player, &testGame);
    printDiscard(player, &testGame);
    
    playAdventurer(player, &testGame);
    printf("After Play Adventurer\n");
    
    /* Test Failed Statements */
    /* Test 1 */
    
    printDeck(player, &testGame);

    int actualDeckCountAfter = testGame.deckCount[player];
    int expectedDeckCountAfter = deckCountBefore - deckCoinCountBefore;
    printf("Deck count: %d, Expected: %d\n", actualDeckCountAfter, expectedDeckCountAfter);
    
    if(actualDeckCountAfter != expectedDeckCountAfter){
        printf(">>>>>>> ERROR: TEST 1 FAILED: >>>>>>>\n");
        allPassed &= false;
    }
    
    /* Test 2 */
    printDiscard(player, &testGame);
    
    int actualDiscardCountAfter = testGame.discardCount[player];
    int expectedDiscardCountAfter = 0; // TODO
    printf("Discard count: %d, Expected: %d\n", actualDiscardCountAfter, expectedDiscardCountAfter);
    
    if(actualDiscardCountAfter != expectedDiscardCountAfter){
        printf(">>>>>>> ERROR: TEST 2 FAILED: >>>>>>>\n");
        allPassed &= false;
    }
    
    /* Test 3 */
    printHand(player, &testGame);
    
    int actualHandCountAfter = testGame.handCount[player];
    int expectedHandCountAfter = 0; // TODO
    printf("Hand count: %d, Expected: %d\n", actualHandCountAfter, expectedHandCountAfter);
    
    if(actualHandCountAfter != expectedHandCountAfter){
        printf(">>>>>>> ERROR: TEST 3 FAILED >>>>>>>\n");
        allPassed &= false;
    }
    
    return allPassed;
}


int main(){
    
    int i;
    int cards[KINGDOM_CARDS_LENGTH] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int seed = 1000;
    int numberOfPlayers = 2;
    
    bool allPassed = true;
    
    struct gameState originalGame;
    
    initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    // run through random test 1000 times
    for(i = 0; i < TEST_COUNT; i++){
        printf("Random Test %d/%d\n", i + 1, TEST_COUNT);
        allPassed &= randomTest(&originalGame, cards);
    }
    
    if(allPassed){
        printf("\n ####  ALL TESTS PASSED  #### \n");
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    }else{
        printf("\n >>>>>> ONE OR MORE TESTS FAILED >>>>>>\n");
    }
    
    
    return 0;
}
