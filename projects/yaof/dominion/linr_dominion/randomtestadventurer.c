/*Random test: adventurer card*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int testAdvent(struct gameState *prestate, int handPos)
{
   int i, result, preAdventCount, card;
   int preAdventCoins = 0;
   int postAdventCoins = 0;
   int currentPlayer = whoseTurn(prestate);

   preAdventCount = prestate->handCount[currentPlayer]; //hand count before playing Adventurer
//   printf("Number of cards in hand before playing Adventurer: %d\n", preAdventCount);

   for(i = 0; i < preAdventCount; i++) //count treasure cards in player's hand
   {
      card = prestate->hand[currentPlayer][i];
      if(card == copper || card == silver || card == gold)
	preAdventCoins++;
   }
//   printf("Number of treasure cards in hand before playing Adventurer: %d\n", preAdventCoins);

   result = cardEffect(adventurer, 0, 0, 0, prestate, handPos, 0);

   //discard Adventurer
   discardCard(handPos, currentPlayer, prestate, 0);

//   printf("\nActual number of cards in hand after playing Adventurer: %d\n", prestate->handCount[currentPlayer]);
//   printf("Expected number of cards in hand (Adventurer is discarded): %d\n", preAdventCount + 1);

   for(i = 0; i < prestate->handCount[currentPlayer]; i++) //count cards in player's hand
   {
      card = prestate->hand[currentPlayer][i];
      if(card == copper || card == silver || card == gold)
	postAdventCoins++;
   }
//   printf("Actual number of treasure cards in hand after playing Adventurer: %d\n", postAdventCoins);
//   printf("Expected number of treasure cards in hand: %d\n", preAdventCoins + 2);

   if((preAdventCount + 1) == prestate->handCount[currentPlayer] && (preAdventCoins + 2 == postAdventCoins)) //correct card and treasure card count
      return 0;

   return 1;
}

int main()
{
   int i, n, p, l, m, o, q, handPos, result;
//   int k[10] = {adventurer, council_room, feast, gardens, mine
//               , remodel, smithy, village, baron, great_hall};
   struct gameState G;

   printf("Testing cardAdventurer.\n");
   printf("RANDOM TESTS.\n");

   SelectStream(2);
   PutSeed(3);

   for(n = 0; n < 1000; n++) //loop through games
   {
      for(i = 0; i < sizeof(struct gameState); i++)
      {
	((char*)&G)[i] = floor(Random() * 256); //fill gamestate G with random bytes
      }
      p = floor(Random() * 4);
      if(p == 0) //if Random returns 0
	p = 1;
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
//	printf("discardCount %d", G.discardCount[p]);
      G.handCount[p] = floor(Random() * MAX_HAND);
      G.playedCardCount = floor(Random() * MAX_DECK);
      G.whoseTurn = p;

      for(l = 0; l < G.deckCount[p]; l++)
      {
	G.deck[p][l] = floor(Random() * treasure_map);
      }
      for(m = 0; m < G.discardCount[p]; m++)
      {
	G.discard[p][m] = floor(Random() * treasure_map);
      }
      for(o = 0; o < G.handCount[p]; o++)
      {
	G.hand[p][o] = floor(Random() * treasure_map);
      }
      for(q = 0; q < G.playedCardCount; q++)
      {
	G.playedCards[p] = floor(Random() * treasure_map);
      }

      //put adventurer in a random handPos
      handPos = floor(Random() * G.handCount[p]);
      G.hand[p][handPos] = adventurer;

      printf("Test #%d-", n + 1);
      result = testAdvent(&G, handPos);
      if(result == 1)
	printf("Test failed.\n");
      else
	printf("Test passed.\n");
   }

   if(result == 0)
      printf("ALL TESTS OK\n");

   return(0);
}
