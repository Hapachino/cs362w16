/*
**Random test card: Salvager
**Written by: Tom Gariepy
**CS 325 Winter 2016
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	time_t curSeed = time(NULL);

	srand((unsigned int)curSeed);

	int result = 1;

    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount, correctBuys, correctCoins, toTrash;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    // array fro the salvager test
    int salv[11];
    salv[0] = salvager;
    for (i = 1; i < 11; i++)
    {
        salv[i] = k[i - 1];
    }

    printf ("TESTING Salvager card with seed: %d\n", (unsigned int)curSeed);

    while (result < 100) {
    	numPlayer = rand() % (MAX_PLAYERS - 2) + 2;
    	p = rand() % numPlayer;
	   	handCount = rand() % 9 + 2;
	   	toTrash = rand() % (handCount - 1) + 1;

	    printf("Test #%d: %d players, player %d playing Salvager card, hand size: %d, hand to trash: %d\n", result, numPlayer, p, handCount, toTrash);
    		
	    memset(&G, 23, sizeof(struct gameState));   // clear the game state
	    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	    //Get selected card amount
	    G.whoseTurn = p;
	    G.handCount[p] = handCount;
	    correctBuys = G.numBuys + 1;
	    correctCoins = G.coins + getCost(salv[toTrash]);

    	memcpy(G.hand[p], salv, sizeof(int) * handCount);

    	r = playCard(0, toTrash, 0, 0, &G); //choice 1 will be changing

    	printf("G.numBuys = %d, expected = %d\n", G.numBuys, correctBuys);
    	printf("G.coins = %d, expected = %d\n", G.coins, correctCoins);

    	if (G.numBuys == correctBuys + 2 && G.coins == correctCoins) {
    		printf("The Salvager card worked correctly\n");
    		result++;
    	}
    	else {
    		printf("The Salvager card did not work correctly\n");
    		// result = 0;
    		result++;
    	}
	
	}

	return 0;
}