#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <time.h>

int testStewardCard(int p, int handPos, int choice1, int choice2, int choice3, struct gameState *G1, int *s)
{
    struct gameState G2;
    int r;
    
    memcpy(&G2, G1, sizeof(struct gameState));
    
    SelectStream(2);
    
    r = cardEffect(steward, choice1, choice2, choice3, G1, handPos, 0);
    
    PutSeed(3);

    switch (choice1) {
        case 1:
            // draws 2 cards (reminder: discards one card)
            drawCard(p, &G2);
            drawCard(p, &G2);
            assert(G2.handCount[p] == G1->handCount[p] + 1);
            break;
        case 2:
            G2.coins += 2;
            assert(G2.coins == G1->coins);
            break;
        default:
            discardCard(choice2, p, &G2, 1);
            discardCard(choice3, p, &G2, 1);
            assert(G2.handCount[p] == G1->handCount[p] - 3);
    }
    
    discardCard(handPos, p, &G2, 0);
    
    assert(r == 0);
    assert(memcmp(&G2, G1, sizeof(struct gameState)) == 0);
    if (memcmp(&G2, G1, sizeof(struct gameState)) == 0) {
        (*s)++;
    } else if (memcmp(&G2, G1, sizeof(struct gameState)) != 0 && s > 0) {
        (*s)--;
    }
    
    return *s;
}

int main() {
    struct gameState G1;
    int p, i, n, s = 0;
    int choice1, choice2, choice3, handPos = 0;
    
    PutSeed(3);
    
    printf("Testing Card: Steward\n");
    
    srand(time(NULL));
    
    for (n = 0; n < 2000; n++) {
        SelectStream(3);
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G1)[i] = floor(Random() * 256);
        }
        p = floor(Random() * MAX_PLAYERS);
        G1.whoseTurn = p;
        G1.deckCount[p] = floor(Random() * MAX_DECK);
        G1.playedCardCount = floor(Random() * MAX_DECK);
        G1.discardCount[p] = floor(Random() * MAX_DECK);
        G1.handCount[p] = floor(Random() * (rand() % MAX_HAND));
        G1.coins = floor(Random() * (rand() % MAX_HAND));
        choice1 = floor(Random() * (rand() % 3) + 1);
        choice2 = floor(Random() * (rand() % treasure_map + 1));
        choice3 = floor(Random() * (rand() % treasure_map + 1));
        testStewardCard(p, handPos, choice1, choice2, choice3, &G1, &s);
    }
    
    printf("Successes: %d, Failures: %d\n", s, 2000 - s);
    
    return 0;
}

