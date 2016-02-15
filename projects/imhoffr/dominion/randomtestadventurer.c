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
#define KINGDOM_CARDS_SIZE 10
#define TESTCARD "adventurer"
#define TEST_COUNT 2

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
        case ambassador:
            name = "ambassador";
            break;
        case adventurer:
            name = "adventurer";
            break;
        case baron:
            name = "baron";
            break;
        case copper:
            name = "copper";
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
        case duchy:
            name = "duchy";
            break;
        case embargo:
            name = "embargo";
            break;
        case estate:
            name = "estate";
            break;
        case feast:
            name = "feast";
            break;
        case gardens:
            name = "gardens";
            break;
        case gold:
            name = "gold";
            break;
        case great_hall:
            name = "great hall";
            break;
        case mine:
            name = "mine";
            break;
        case minion:
            name = "minion";
            break;
        case outpost:
            name = "outpost";
            break;
        case province:
            name = "province";
            break;
        case remodel:
            name = "remodel";
            break;
        case salvager:
            name = "salvager";
            break;
        case sea_hag:
            name = "sea hag";
            break;
        case silver:
            name = "silver";
            break;
        case smithy:
            name = "smithy";
            break;
        case steward:
            name = "steward";
        case treasure_map:
            name = "treasure map";
            break;
        case tribute:
            name = "tribute";
            break;
        case village:
            name = "village";
            break;
    }
    
    return name;
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

int randomCard() {
    int card = floor(Random() * (treasure_map + 1));
    
    assert(card >= 0 && card <= treasure_map + 1);
    
    return card;
}

void randomDeck(int player, int size, struct gameState *state) {
    state->deckCount[player] = 0;
    
    for(int i = 0; i < size; i++){
        state->deck[player][i] = randomCard();
        state->deckCount[player]++;
    }
}

#define DECK_COIN_INDEX_NOT_FOUND -1

int deckCoinIndex(int player, int coinCount, struct gameState *state) {
    int foundCoinCount = 0;
    // -1 for not found
    int coinCountIndex = DECK_COIN_INDEX_NOT_FOUND;
    
    for(int i = 0; i < state->deckCount[player]; i++){
        if (isCoin(state->deck[player][i])) {
            foundCoinCount++;
            
            if(foundCoinCount == coinCount) {
                coinCountIndex = i;
                break;
            }
        }
    }
    
    return coinCountIndex;
}

bool randomTest(struct gameState *originalGame, int cards[KINGDOM_CARDS_SIZE]) {
    int player = 0;
    struct gameState testGame;
    bool allPassed = true;
    
    memcpy(&testGame, originalGame, sizeof(struct gameState));
    
    randomDeck(player, DECK_SIZE, &testGame);
    int deckCoinCountBefore = deckCoinCount(player, &testGame);
    int thirdDeckCoinIndex = deckCoinIndex(player, 3, &testGame);
    
    // empty discard pile
    testGame.discardCount[player] = 0;
    
    int deckCountBefore = testGame.deckCount[player];
    int handCountBefore = testGame.handCount[player];
    
    printf("Before Play Adventurer\n");
    printDeck(player, &testGame);
    printHand(player, &testGame);
    printDiscard(player, &testGame);
    
    playAdventurer(player, &testGame);
    printf("After Play Adventurer\n");
    
    
    /* Test 1 */
    printHand(player, &testGame);
    
    int actualHandCountAfter = testGame.handCount[player];
    int expectedHandCoinCountDelta;
    
    if (deckCoinCountBefore > 3) {
        expectedHandCoinCountDelta = 3;
    } else {
        expectedHandCoinCountDelta = deckCoinCountBefore;
    }
    
    int expectedHandCountAfter = handCountBefore + expectedHandCoinCountDelta;
    printf("Hand count: %d, Expected: %d\n", actualHandCountAfter, expectedHandCountAfter);
    
    if(actualHandCountAfter != expectedHandCountAfter){
        printf(">>>>>>> ERROR: TEST 1 FAILED >>>>>>>\n");
        allPassed &= false;
    }
    
    /* Test Failed Statements */
    /* Test 2 */
    
    printDeck(player, &testGame);
    int actualDeckCountAfter = testGame.deckCount[player];
    int expectedDeckCountAfter;
    
    if (thirdDeckCoinIndex == DECK_COIN_INDEX_NOT_FOUND) {
       expectedDeckCountAfter = 0;
    } else {
       expectedDeckCountAfter = deckCountBefore - (thirdDeckCoinIndex + 1);
    }
    
    printf("Deck count: %d, Expected: %d\n", actualDeckCountAfter, expectedDeckCountAfter);
    
    if(actualDeckCountAfter != expectedDeckCountAfter){
        printf(">>>>>>> ERROR: TEST 2 FAILED: >>>>>>>\n");
        allPassed &= false;
    }
    
    /* Test 3 */
    printDiscard(player, &testGame);
    int actualDiscardCountAfter = testGame.discardCount[player];
    int expectedDiscardCountAfter;
    
    if (thirdDeckCoinIndex == DECK_COIN_INDEX_NOT_FOUND) {
        expectedDiscardCountAfter = deckCountBefore - deckCoinCountBefore;
    } else {
        assert(NULL != NULL);
        expectedDiscardCountAfter = thirdDeckCoinIndex - 3;
    }
    
    printf("Discard count: %d, Expected: %d\n", actualDiscardCountAfter, expectedDiscardCountAfter);
    
    if(actualDiscardCountAfter != expectedDiscardCountAfter){
        printf(">>>>>>> ERROR: TEST 3 FAILED: >>>>>>>\n");
        allPassed &= false;
    }
    
    return allPassed;
}


int main(){
    int cards[KINGDOM_CARDS_SIZE] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int seed = 4;
    int numberOfPlayers = 2;
    
    bool allPassed = true;
    
    struct gameState originalGame;
    
    initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    // run through random test 1000 times
    for(int i = 0; i < TEST_COUNT; i++){
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
