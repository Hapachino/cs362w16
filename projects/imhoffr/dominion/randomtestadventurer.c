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

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "adventurer"



int main(){
    
    int i;
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int seed = 1000;
    int coinsPassed = 1;
    int deckCountPassed = 1;
    int deckSize;
    int numberOfPlayers = 2;
    int player = 0;
    int newGame;
    int originalDeckPile;
    int originalDiscardPile;
    int originalHandPile;
    int coinCount = 0;
    int coinsDrawn;
    int nonCoinsDrawn;
    int coinDecreaser;
    int totalCount;
    int original;
    
    bool testPass = true;
    
    struct gameState testGame, originalGame;
    
    memset(&testGame, 23, sizeof(struct gameState));
    original = initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    // run through random test 1000 times
    for(i = 0; i < 1000; i++){
        memcpy(&testGame, &originalGame, sizeof(struct gameState));
        
        printf("Random Deck Count: %d\n", i);
        
        testGame.deckCount[player] = 0;
        
        // make a deck size of 10 cards
        for(i = 0; i < 10; i++){
            deckSize = floor(Random() * 10);
            testGame.deck[player][i] = cards[deckSize];
            testGame.deckCount[player]++;
        }
        
        // how many coins are in the deck?
        for(i = 0; i < testGame.deckCount[player]; i++){
            if(testGame.deck[player][i] == copper || testGame.deck[player][i] == silver || testGame.deck[player][i] == gold){
                coinCount++;
            }
        }
        
        // empty discard pile
        testGame.discardCount[player] = 0;
        
        // number of cards in hand is five
        testGame.handCount[player] = 0;
        for(i = 0; i < 5; i++){
            testGame.hand[player][i] = mine;
            testGame.handCount[player]++;
        }
        
        originalHandPile = testGame.handCount[player];
        originalDiscardPile = testGame.discardCount[player];
        originalDeckPile = testGame.deckCount[player];
        
    /***** EXPECTED VALUES *****/
        // 0 coins in deck
        if(coinCount == 0){
            coinsDrawn = 0;
            nonCoinsDrawn = testGame.deckCount[player];
        }
        
        // 1 coin in deck
        else if(coinCount == 1){
            coinsDrawn = 1;
            nonCoinsDrawn = testGame.deckCount[player] - coinsDrawn;
        }
        
        // 2+ coins in deck
        else{
            coinsDrawn = 0;
            nonCoinsDrawn = 0;
            
            coinDecreaser = testGame.deckCount[player] - 1;
            
            while(coinsDrawn < 2){
                if(testGame.deck[player][i] == copper || testGame.deck[player][i] == silver || testGame.deck[player][i] == gold){
                    coinsDrawn++;
                    i--;
                }else{
                    nonCoinsDrawn++;
                    i--;
                }
            }
        }
        
        /* Print statements! */
        
        printf("Deck:\n");
        for(i = 0; i < testGame.deckCount[player]; i++){
            printf("Position: %d, Card: %d\n", i, testGame.deck[player][i]);
        }
        
        printf("Hand:\n");
        for(i = 0; i < testGame.handCount[player]; i++){
            printf("Position: %d, Card: %d\n", i, testGame.hand[player][i]);
        }
        
        printf("Discard:\n");
        for(i = 0; i < testGame.discardCount[player]; i++){
            printf("Position %d, Card: %d\n", i, testGame.discard[player][i]);
        }
        
        printf("Play Adventurer done!\n");
        
        playAdventurer(player, &testGame);
        
        /* Test Failed Statements */
        /* Test 1 */
        printf("Display the deck:\n");
        for(i = 0; i < testGame.deckCount[player]; i++){
            printf("Position: %d, Card: %d\n", i, testGame.deck[player][i]);
        }
        
        totalCount = originalDeckPile - nonCoinsDrawn - coinsDrawn;
        printf("Deck count: %d, Expected: %d\n", testGame.deckCount[player], totalCount);
        if(testGame.deckCount[player] != totalCount){
            printf(">>>>>>> ERROR: TEST 1 FAILED: >>>>>>>\n");
            testPass = false;
        }
        
        /* Test 2 */
        printf("Display the discard: \n");
        for(i = 0; i < testGame.discardCount[player]; i++){
            printf("Position: %d, Card: %d\n", i, testGame.discard[player][i]);
        }
        
        totalCount = originalDeckPile + nonCoinsDrawn;
        printf("Discard count: %d, Expected: %d\n", testGame.discardCount[player], totalCount);
        if(testGame.discardCount[player] != totalCount){
            printf(">>>>>>> ERROR: TEST 2 FAILED: >>>>>>>\n");
            testPass = false;
        }
        
        /* Test 3 */
        printf("Display the hand:\n");
        for(i = 0; i < testGame.handCount[player]; i++){
            printf("Position: %d, Card: %d\n", i, testGame.hand[player][i]);
        }
                   
        totalCount = originalDeckPile + coinsDrawn;
        printf("Hand count: %d, Expected: %d\n", testGame.handCount[player], totalCount);
        if(testGame.handCount[player] != totalCount){
            printf(">>>>>>> ERROR: TEST 3 FAILED >>>>>>>\n");
            testPass = false;
        }
    }
    
    if(testPass == true){
        printf("\n ####  ALL TESTS PASSED  #### \n");
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    }else{
        printf("\n >>>>>> ONE OR MORE TESTS FAILED >>>>>>\n");
    }
    
    
    return 0;
}
