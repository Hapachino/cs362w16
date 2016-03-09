/* unittest4.c
 * Author: Eric Anderson
 * Class: CS362w16
 * Description: Unit test for the updateCoins function in dominion.c
 *  updateCoins loops through all the cards in the player's hand and add coins 
 * for each Treasure card in player's hand.  It then adds bonus coins if any
 * are accrued.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

#define NOISY_TEST 0

/**********************************************************
 * function: testupdateCoins
 * description: This function executes the updateCoins function
 * to count the number of copper, silver and gold cards a player 
 * has. We test this by "stuffing" the player's hand with some 
 * of each and testing if we got the right number of coins back.
 * Based on the number of cards, we can calculate the coins.  
 * We see if we got the right number of coins added.
 * input: the player number (0-3), a prefilled out struct and a card number
 * returns: result, 0 for success, 1 for failure
 ***********************************************************/
int testupdateCoins(int p, struct gameState *G, int bonus, int handCount) 
{
	//define variables
	int r;
    int result = 0;
	
    // execute the updateCoins action against the "pre" version of the struct
    // this is the same content as in the updateCoins code in dominion.c	
    r = updateCoins(p, G, bonus);

#if (DEBUG)
    // test 1: Test to see if function worked correctly
    assert (r == 0);
#endif	



#if (NOISY_TEST)
	
    if(*G->hand[p] == copper)
    {
    	printf("Coins = %d, expected = %d\n", G->coins, handCount * 1 + bonus);
    } else if(*G->hand[p] == silver) {
    	printf("Coins = %d, expected = %d\n", G->coins, handCount * 2 + bonus);
    } else {
    	printf("Coins = %d, expected = %d\n", G->coins, handCount * 3 + bonus);
    }
    
#endif

    //test 2: Check if the expected values are the same as what we got from the function
    if(*G->hand[p] == copper)
    {
#if (DEBUG)
    	assert(G->coins == handCount * 1 + bonus); // check if the number of coins is correct
#endif  
        if (G->coins != handCount * 1 + bonus) {
            result = 1;
        }
    } else if(*G->hand[p] == silver) {
#if (DEBUG)
    	assert(G->coins == handCount * 2 + bonus); // check if the number of coins is correct
#endif  
        if (G->coins != handCount * 2 + bonus) {
            result = 1;
        }
    } else {
#if (DEBUG)
    	assert(G->coins == handCount * 3 + bonus); // check if the number of coins is correct
#endif
        if (G->coins != handCount * 3 + bonus) {
            result = 1;
        }
    }


	return result;
}

/**********************************************************
 * function: main
 * description: Controls test flow. Uses code from 
 * betterCardTest.c
 ***********************************************************/
int main () {
	
	//define variables
    int i, r, p, handCount, bonus;
	int seed = 1000;
    int numPlayer = 4;
    int maxBonus = 10;
    int result = 0;
	
    //define a array of cards
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	//define a gamestate
	struct gameState G;

	 int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
	
	printf ("Testing UpdateCoins.\n");


    //Loop through players, decks and hands to fill the struct
    // and initiate game play.	
	printf ("SIMPLE FIXED TESTS.\n");
	for (p = 0; p < numPlayer; p++)
	{
       for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {

#if (NOISY_TEST)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif                
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                //run unit test.
                result = testupdateCoins(p, &G, bonus, handCount);

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                //run unit test.
                result = testupdateCoins(p, &G, bonus, handCount);

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                //run unit test.
                result = testupdateCoins(p, &G, bonus, handCount);

            }
        }
    }

    // print out results
    if (result == 1) {
      printf("updateCoins tests failed.\n");
    } else {
      printf("updateCoins tests passed.\n");
    }

	printf ("FIXED TESTS COMPLETE\n");
	
	return 0;
}



