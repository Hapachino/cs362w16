/*
**Unit test 4: endTurn()
**Written by: Tom Gariepy
**CS 325 Winter 2016
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(int argc, char const *argv[]) {
    int seed = 1000;
    int numTurns;
    int numPlayer = 2;
    int p, r, endT, turnRes, disNum, curP;
    // int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int i;
    int cards[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        cards[i] = adventurer;
    }

    printf ("TESTING endTurn():\n");
    for (p = 0; p < numPlayer; p++)	{
    	for (disNum = 0; disNum <= maxHandCount; disNum++) {
    		for (numTurns = 1; numTurns <= 10; numTurns++) {
    				printf("Testing start player %d with %d end turns and %d cards in discard pile\n", p, numTurns, disNum);
    				memset(&G, 23, sizeof(struct gameState));
    				r = initializeGame(p, k, seed, &G);
    				int steps = 0;

    				// Something wrong with initializing the game
    				G.whoseTurn = p;

    				// endTun() isn't working
    				while (steps < numTurns) {
/*    					G.handCount[p] = disNum;                 // set the number of cards on hand
               			memcpy(G.hand[p], cards, sizeof(int) * disNum);

               			G.discardCount[p] = disNum;                 // set the number of cards on hand
                		memcpy(G.discard[p], cards, sizeof(int) * disNum);
     
               			G.playedCardCount = disNum;                 // set the number of cards on hand
                		memcpy(G.playedCards, cards, sizeof(int) * disNum);*/

    					// endT = endTurn(&G);
    					// printf("Current hand count = %d\n", G.handCount[p]);
    					steps++;
    				}

    				turnRes = G.whoseTurn;

					printf("turn =  %d, expected = %d \n", turnRes, numTurns % 2);

    				if (turnRes == numTurns % 2) {
    					printf("The turn is correct\n");
    				}
    				else {
    					printf("The turn is not correct\n");
    				}
    		}
    	}
    }

	return 0;
}