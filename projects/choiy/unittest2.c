/* -----------------------------------------------------------------------
 * test Shuffle()
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 unittest2.c dominion.o rngs.o
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int compare(const void *a, const void *b);

int main() {
	struct gameState G1, G2;
	memcpy(&G2, &G1, sizeof(struct gameState)); // make G1 and G2 identical

    // shuffle both games
    int val = shuffle(0, &G1);
    shuffle(0, &G2);

    // sort the deck of both games
    if (G1.deckCount[0] > 0) {
    	assert(val != -1);
    	qsort((void*)(G1.deck[0]), G1.deckCount[0], sizeof(int), compare);
    	qsort((void*)(G2.deck[0]), G2.deckCount[0], sizeof(int), compare);
    }
    else
    	assert(val == -1);

    // should be the same each other
    int result = memcmp(&G1, &G2, sizeof(struct gameState));
    assert(result == 0);
    
    if (result == 0) {
    	printf("Shuffle test passed!\n");
    }
    else {
    	printf("Shuffle test failed!\n");
    }

    return 0;
}
