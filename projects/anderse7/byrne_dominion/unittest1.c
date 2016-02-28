/* unittest1.c
 * Author: Eric Anderson
 * Class: CS362w16
 * Description: Unit test for the Full Deck Count function in dominion.c
 *  Full Deck Count counts the number of cards in the player's hand, deck and discard.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

#define DEBUG 0
#define NOISY_TEST 0


/**********************************************************
 * function: checkFullDeckCount
 * description: This function executes the fullDeckCount function
 * against the condition where the decks have 0 cards for 0 to 3 
 * players up to 5 cards for 0 to 3 players any combination of input 
 * should have the same output number  e.g. if player 0 has 15 
 * cards inserted into the struct, fullDeckCount should return 15 cards.
 * input: the player number (0-3), a prefilled out struct and a card number
 * returns: result, 0 for success, 1 for failure
 ***********************************************************/
int checkFullDeckCount(int p, int c, struct gameState *post) {
	
	//define variables
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	int r = 0;
	int i = 0;
	int count = 0;
	int result = 0;

#if (NOISY_TEST)

  printf ("FullDeckCount PRE: player =  %d handCount = %d deckCount =  %d discardCount %d\n",
        p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);

#endif	


	// execute the Smithy action against the "pre" version of the struct
    // this is the same content as in the playSmithy code in dominion.c
	r = fullDeckCount(p, c, post);

#if (NOISY_TEST)
  printf ("FullDeckCount POST: player =  %d handCount = %d deckCount =  %d discardCount %d\n",
        p, post->handCount[p], post->deckCount[p], post->discardCount[p]);
#endif
	
	// now set up pre
	for (i = 0; i < pre.deckCount[p]; i++) {
		if (pre.deck[p][i] == c) {
			count++;
		}
	}
	for (i = 0;i < pre.handCount[p]; i++) {
		if (pre.hand[p][i] == c) {
			count++;
		}
	}
	for (i = 0; i < pre.discardCount[p]; i++) {
		if (pre.discard[p][i] == c) {
			count++;
		}
	}

#if (DEBUG)
	//test1: make sure we got the right return from fullDeckCount
	assert(r == count);
	
	//test2: pre and post should look the same if the function works all the time
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);

#endif

	// The asserts, if false will terminate the program so print out the same tests
  	// so the program keeps executing
	if(r != count) {
#if (NOISY_TEST) 
		printf("the returned value was not equal to count");
#endif
		result = 1;
	}


  	if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
#if (NOISY_TEST) 
    printf("pre and post don't match");
#endif
    result = 1;
  }
	
	return result;
}

/**********************************************************
 * function: main
 * description: Controls test flow. Uses code from 
 * betterCardTest.c
 ***********************************************************/
int main (void) {
	
	//define variables  
	int r, p, deckCount, discardCount, handCount, c;
	int result = 0;
	
	//define a array of cards
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	
	//define a gamestate
	struct gameState G;
	
	printf ("Testing FullDeckCount.\n");
	
	//Loop through players, decks and hands to fill the struct
  	// and initiate game play.
	printf ("SIMPLE FIXED TESTS.\n");
	for (p = 0; p < 2; p++) {
		for (deckCount = 0; deckCount < 5; deckCount++) {
			for (discardCount = 0; discardCount < 5; discardCount++) {
				for (handCount = 0; handCount < 5; handCount++) {
					for (c = curse; c < treasure_map; c++) {
						memset(&G, 23, sizeof(struct gameState)); 
						r = initializeGame(2, k, 1, &G);
						G.deckCount[p] = deckCount;
						memset(G.deck[p], 0, sizeof(int) * deckCount);
						G.discardCount[p] = discardCount;
						memset(G.discard[p], 0, sizeof(int) * discardCount);
						G.handCount[p] = handCount;
						memset(G.hand[p], 0, sizeof(int) * handCount);
						G.whoseTurn = p;
						//run unit test.
						checkFullDeckCount(p, c, &G);
					}
				}
			}
		}
	}
	
	  // print out results
	  if (result == 1) {
	    printf("fullDeckCount tests failed.\n");
	  } else {
	    printf("fullDeckCount tests passed.\n");
	  }
	printf ("FIXED TESTS COMPLETE\n");
	
	return 0;
}