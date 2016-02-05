/*This tests the adventurer card*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int testAdvent(struct gameState *, int); //function declaration

int main() {
   int seed = 1000;
   int numPlayer = 3;
   int r, result;
   int handPos = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

   struct gameState G;

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

   result = testAdvent(&G, handPos);

   if(result == 0)
      printf("All tests passed!\n");
   else
      printf("Adventurer did not pass test!\n");

   return 0;
}

int testAdvent(struct gameState *prestate, int handPos)
{
   int i, result, preAdventCount, card;
   int preAdventCoins = 0;
   int postAdventCoins = 0;
   int currentPlayer = whoseTurn(prestate);

   preAdventCount = prestate->handCount[currentPlayer]; //hand count before playing Adventurer
   printf("Number of cards in hand before playing Adventurer: %d\n", preAdventCount);

   for(i = 0; i < preAdventCount; i++) //count treasure cards in player's hand
   {
      card = prestate->hand[currentPlayer][i];
      if(card == copper || card == silver || card == gold)
	preAdventCoins++;
   } 
   printf("Number of treasure cards in hand before playing Adventurer: %d\n", preAdventCoins);

   result = cardEffect(adventurer, 0, 0, 0, prestate, handPos, 0);

   //discard Adventurer
   discardCard(handPos, currentPlayer, prestate, 0);

   printf("\nActual number of cards in hand after playing Adventurer: %d\n", prestate->handCount[currentPlayer]);
   printf("Expected number of cards in hand (Adventurer is discarded): %d\n", preAdventCount + 1);

   for(i = 0; i < prestate->handCount[currentPlayer]; i++) //count treasure cards in player's hand
   {
      card = prestate->hand[currentPlayer][i];
      if(card == copper || card == silver || card == gold)
	postAdventCoins++;
   } 
   printf("Actual number of treasure cards in hand after playing Adventurer: %d\n", postAdventCoins);
   printf("Expected number of treasure cards in hand: %d\n", preAdventCoins + 2);

   if((preAdventCount + 1) == prestate->handCount[currentPlayer] && (preAdventCoins + 2 == postAdventCoins)) //correct card and treasure card count
      return 0;
   
   return 1; 
}
