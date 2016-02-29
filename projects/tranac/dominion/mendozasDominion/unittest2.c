/* -----------------------------------------------------------------------
 * Testing isGameOver()
 * Pre conditions
 *  1) Passes in the gameState 
 * Post conditions
 *  1) Game ends if province supply is empty
 *  2) Game ends if 3 kingdom card supplies are empty
 *  3) Supply of cards is unchanged  
 *  
 * isGameOver: unittest2.c dominion.o rngs.o
 *      gcc -o unit2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------*/

#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

// set NOISY to 0 to remove printfs from output
#define NOISY 1

int main() {
    int seed = 1004; // random seed
    int numPlayer = 2; 
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int result;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	//set card supply of province, adventurer, council_room, and feast to 1
	G.supplyCount[province] = 1;
	G.supplyCount[adventurer] = 1;
	G.supplyCount[council_room] = 1;
	G.supplyCount[feast] = 1;

	printf ("TESTING isGameOver():\n");
	
    // test with remaining supply in each pile
    result = isGameOver(&G);
#if (NOISY == 1)
    printf("Test 1: All piles not empty\n");
#endif
	assert(G.supplyCount[province] == 1);  //expect card supplies to remain at 1
	assert(G.supplyCount[adventurer] == 1);
	assert(G.supplyCount[council_room] == 1);
	assert(G.supplyCount[feast] == 1);
    assert(result == 0); //expect to not end 
#if (NOISY == 1)
    printf("Test 1 passed\n");
#endif

    // test with 0 provinces left in supply
    G.supplyCount[province] = 0;
    result = isGameOver(&G);
#if (NOISY == 1)
    printf("Test 2: 0 Provinces\n");
#endif
	assert(G.supplyCount[province] == 0);  //expect card supply to be at 0
	assert(G.supplyCount[adventurer] == 1); //expect remaining card supplies to be at 1
	assert(G.supplyCount[council_room] == 1);
	assert(G.supplyCount[feast] == 1);
    assert(result == 1); //expect to end
#if (NOISY == 1)
    printf("Test 2 passed\n");
#endif

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	//set card supply of provinces, adventurer, council_room, and feast to 1
	G.supplyCount[province] = 1;
	G.supplyCount[adventurer] = 1;
	G.supplyCount[council_room] = 1;
	G.supplyCount[feast] = 1;

    // test with 1 empty pile
    G.supplyCount[adventurer] = 0;
    result = isGameOver(&G);
#if (NOISY == 1)
    printf("Test 3: only adventurer pile empty\n");
#endif
	assert(G.supplyCount[province] == 1);  //expect adventurer supply to be at 0
	assert(G.supplyCount[adventurer] == 0); //expect remaining card supplies to be at 1
	assert(G.supplyCount[council_room] == 1);
	assert(G.supplyCount[feast] == 1);
    assert(result == 0); // expect to not end
#if (NOISY == 1)
    printf("Test 3 passed\n");
#endif

    // test with 2 empty piles
    G.supplyCount[council_room] = 0;
    result = isGameOver(&G);
#if (NOISY == 1)
    printf("Test 4: adventurer and council_room piles empty\n");
#endif
    assert(G.supplyCount[province] == 1);  //expect council_room and adventurer supplies to be at 0
	assert(G.supplyCount[adventurer] == 0); //expect remaining card supplies to be at 1
	assert(G.supplyCount[council_room] == 0);
	assert(G.supplyCount[feast] == 1);
    assert(result == 0); // expect to not end
#if (NOISY == 1)
    printf("Test 4 passed\n");
#endif

    // test with 3 empty supply piles
    G.supplyCount[feast] = 0;
    result = isGameOver(&G);
#if (NOISY == 1)
    printf("Test 5: 3 empty piles\n");
#endif
    assert(G.supplyCount[province] == 1);  //expect province pile to be at 1
	assert(G.supplyCount[adventurer] == 0); //expect remaining card supplies to be at 0
	assert(G.supplyCount[council_room] == 0);
	assert(G.supplyCount[feast] == 0);
    assert(result == 1); // expect to end
#if (NOISY == 1)
    printf("Test 5 passed\n");
#endif


    printf("All tests passed\n!\n");

    return 0;
}
