#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int countTreasure(int p, struct gameState *G1) {
    int cnt = 0;
    int i;
    
    for (i = 0; i < G1->handCount[p]; i++) {
        if (G1->hand[p][i] == copper || G1->hand[p][i] == silver || G1->hand[p][i] == gold) {
            cnt++;
        }
    }
    return(cnt);
}

int testAdventurerCard(int p, struct gameState *G1, int *s)
{
    int preCount = 0;
    int postCount = 0;

    preCount = countTreasure(p, G1); // counts the number of Treasure in hand
    cardEffect(adventurer, 0, 0, 0, G1, 0, 0);
    postCount = countTreasure(p, G1); // counts the number of Treasure after playing adventurer card
    //assert((postCount - preCount) == 2);
    
    int r = (postCount - preCount);
    
    if (r == 2) {
        (*s)++;
    } else {
        (*s)--;
    }
    
    return *s;
}

int main() {
    struct gameState G1;
    int p, i, n, s = 0;
        
    printf("Testing Card: Adventurer\n");
    
    srand(time(NULL));
    
    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G1)[i] = floor(Random() * 256);
        }
        p = floor(Random() * MAX_PLAYERS);
        G1.whoseTurn = p;
        G1.deckCount[p] = floor(Random() * MAX_DECK);
        G1.discardCount[p] = floor(Random() * MAX_DECK);
        G1.handCount[p] = floor(Random() * MAX_HAND);
    
        // change value 27 to variable treasure_map + 1 which also equals 27
        for(i = 0; i < G1.deckCount[p]; i++){
            G1.deck[p][i] = floor(Random() * (rand() % treasure_map + 1));
        }
        for(i = 0; i < G1.handCount[p]; i++){
            G1.hand[p][i] = floor(Random() * (rand() % treasure_map + 1));
        }
        for(i = 0; i < G1.discardCount[p]; i++){
            G1.discard[p][i] = floor(Random() * (rand() % treasure_map + 1));
        }
        
        testAdventurerCard(p, &G1, &s);
    }
    
    printf("Successes: %d, Failures: %d\n", s, 2000 - s);
    
    return 0;
}

