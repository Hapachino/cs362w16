/* -----------------------------------------------------------------------
 * Cierra Shawe 
 * CS362 - W16
 * Unit test 2, testing isGameOver
 * Tests for provineces 0, and greater than 0 
 * Randomly decrements cards until 0,
 * then tests if the game was eneded
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set VERBOSE to 0 to remove printfs from output
#define VERBOSE 0

int main() {
	
	//Things needed to init game
	struct gameState Game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1234;
	int players = 2;
	
	// Other Variables
	int i;
	int j;
	int m;
	int player;
	int count = 0;
	int pos = 0;
	int over = 0;
	
	//test 1000 itterations
	printf("unittest2\n");
	for(i = 0; i < 1000; i++) {
		/* Set Up */
		// clear the game state
		memset(&Game, 23, sizeof(struct gameState));
		
		// initialize a new game
		initializeGame(players, k, seed, &Game);
		
		// Random game state from lecture and test code
		for (m = 0; m < sizeof(struct gameState); m++) {
			((char*)&Game)[m] = (int)(Random() * 256);
		}
		// we need our game it be somewhat feasible
		player = (int)(Random() * 2);
		Game.deckCount[player] = (int)(Random() * MAX_DECK);
		Game.discardCount[player] = (int)(Random() * MAX_DECK);
		Game.handCount[player] = (int)(Random() * MAX_HAND);;
		
		//init supply counts
		for (j = 0; j < 25; j++) {
			//set supplies equal
			Game.supplyCount[j] = 10; //reduce itterations
		}
		
		//now checking if there are not
		Game.supplyCount[province] = 0;
		assert(isGameOver(&Game) == 1);
		
		//Checking the province case  first if there are still cards
		Game.supplyCount[province] = 1;
		assert(isGameOver(&Game) == 0);
		
		
		
		//random decrement until finished
		for (count = 0; count < 3;){
			over = 0;
			pos = (int)(Random() * 10);
			
			if (Game.supplyCount[k[pos]] != 0) {
				assert(isGameOver(&Game) == 0);
				// Makes sure we don't decrement below 0
				Game.supplyCount[k[pos]]--; 
				// After decrementing, if we're at 0, increment count
				if (Game.supplyCount[k[pos]] == 0){
					count++;
				}
			}	
		}
	
		over = isGameOver(&Game);
		assert(over == 1 && count >= 3);
		
	}
	
	printf("isGameOver passed all tests!\n\n");
	return 0;
}