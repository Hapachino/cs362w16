/* -----------------------------------------------------------------------
 * test DrawCard()
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 unittest3.c dominion.o rngs.o
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int checkDrawCard(int p, struct gameState *G) {
	struct gameState G2;
	memcpy (&G2, G, sizeof(struct gameState));

	int r = drawCard(p, G);

	if (G2.deckCount[p] > 0) {
		G2.handCount[p]++;
		G2.hand[p][G2.handCount[p]-1] = G2.deck[p][G2.deckCount[p]-1]; // add card to the hand
		G2.deckCount[p]--;
	}
	else {
		memcpy(G2.deck[p], G->deck[p], sizeof(int)*G2.discardCount[p]);
		memcpy(G2.discard[p], G->discard[p], sizeof(int)*G2.discardCount[p]);

		G2.hand[p][G->handCount[p]-1] = G->hand[p][G->handCount[p]-1];
		G2.handCount[p]++;
		G2.deckCount[p] = G2.discardCount[p]-1;
		G2.discardCount[p] = 0;
	}

	assert(r == 0);

	int result = memcmp(&G2, G, sizeof(struct gameState));
	assert(result == 0);
	if (result == 0)
		printf("Draw card test passed!\n");
	else
		printf("Draw card test failed!\n");

  return 0;
}

int main() {
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing drawCard.\n");

	memset(&G, 23, sizeof(struct gameState));
	initializeGame(2, k, 1000, &G);
	checkDrawCard(0, &G);

	return 0;
}
