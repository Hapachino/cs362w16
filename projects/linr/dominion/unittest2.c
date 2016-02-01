/*This tests updateCoins() function (used some code from Assignment 3 example)*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
   int i, p, handCount, bonus;
   int seed = 1000;
   int r;
   int maxHandCount = 5;
   int maxBonus = 7;
   int numPlayers = 3;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   int testCase[10];

   //fill copper, silver, and gold arrays
   int coppers[MAX_HAND];
   int silvers[MAX_HAND];
   int golds[MAX_HAND];
   for (i = 0; i < MAX_HAND; i++)
   {
      coppers[i] = copper;
      silvers[i] = silver;
      golds[i] = gold;
   }

   printf("TESTING updateCoins():\n");

   for(p = 0; p < numPlayers; p++)
   {
      for(handCount = 1; handCount <= maxHandCount; handCount++)
      {
         for (bonus = 0; bonus <= maxBonus; bonus++)
         {
	    printf("Checking player %d with %d treasure card(s) & %d bonus.\n", p, handCount, bonus);

	    memset(&G, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayers, k, seed, &G); // initialize new game
            G.handCount[p] = handCount;                 // set the number of cards on hand
            memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
            updateCoins(p, &G, bonus);
	    assert(G.coins == handCount * 1 + bonus);
            printf("Actual coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
	 }
      }
   }

   printf("\n");
   //Additional test cases
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayers, k, seed, &G); // initialize new game

   for(p = 0; p < numPlayers; p++)
   {
      for (bonus = 0; bonus <= maxBonus; bonus++)
      {
	printf("Additional test cases (set 1): Checking player %d with 5 treasure card(s) & %d bonus.\n", p, bonus);

        G.handCount[p] = 5;
	testCase[0] = copper; //2 silvers, 3 coppers
	testCase[1] = copper;
	testCase[2] = copper;
	testCase[3] = silver;
	testCase[4] = silver;
        memcpy(G.hand[p], testCase, sizeof(int) * 5); 
        updateCoins(p, &G, bonus);
	assert(G.coins == (handCount * 1) + 1 + bonus);
        printf("Actual coins = %d, expected = %d\n", G.coins, (handCount * 1) + 1 + bonus);
      }
   }

   printf("\n");

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayers, k, seed, &G); // initialize new game

   for(p = 0; p < numPlayers; p++)
   {
      for (bonus = 0; bonus <= maxBonus; bonus++)
      {
	printf("Additional test cases (set 2): Checking player %d with 4 treasure card(s) & %d bonus.\n", p, bonus);

        G.handCount[p] = 4;
	testCase[0] = copper; //2 golds, 2 coppers
	testCase[1] = copper;
	testCase[2] = gold;
	testCase[3] = gold;
        memcpy(G.hand[p], testCase, sizeof(int) * 5); 
        updateCoins(p, &G, bonus);
	assert(G.coins == (handCount * 1) + 2 + bonus);
        printf("Actual coins = %d, expected = %d\n", G.coins, (handCount * 1) + 2 + bonus);
      }
   }

   printf("All tests passed!\n");

   return 0;
}	   
