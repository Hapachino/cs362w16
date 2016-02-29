/*Random test: smithy card*/

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

int testSmithy(struct gameState *prestate, int handPos, int player)
{
   int result, preSmithyHandCount, preSmithyDeckCount;
   bool correctHC = 0;
   int currentPlayer = whoseTurn(prestate);

   preSmithyHandCount = prestate->handCount[currentPlayer]; //hand count before playing Smithy
//   printf("Number of cards in hand before playing Smithy: %d\n", preSmithyCards);
   preSmithyDeckCount = prestate->deckCount[currentPlayer];

   result = cardEffect(smithy, 0, 0, 0, prestate, handPos, 0);
//   printf("\nActual number of cards in hand after playing Smithy: %d\n", prestate->handCount[currentPlayer]);
//   printf("Expected number of cards in hand (Smithy is discarded): %d\n", preSmithyCards + 2);

   if((preSmithyHandCount + 2) == prestate->handCount[currentPlayer]) //smithy worked correctly, should have net +2 cards
      correctHC = 0;
   else
      correctHC = 1;

   if((preSmithyDeckCount - 3) == prestate->deckCount[currentPlayer] && correctHC == 0) //smithy worked correctly
      return 0;
   
   return 1; 
}

int main()
{
   int i, n, p, l, m, o, q, handPos, result;
//   bool passTest = 0;
//   int k[10] = {adventurer, council_room, feast, gardens, mine
//               , remodel, smithy, village, baron, great_hall};
   struct gameState G;

   printf("Testing cardSmithy.\n");
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
//	printf("p is %d\n", p);
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
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
     		
      //put smithy in a random handPos
      handPos = floor(Random() * G.handCount[p]);
      G.hand[p][handPos] = smithy;
//	printf("hand pos is %d\n", handPos);

      printf("Test #%d-", n + 1);
      result = testSmithy(&G, handPos, p);
      if(result == 1)
	printf("Test failed.\n");	
   }

   if(result == 0)
       printf("ALL TESTS OK\n");
   
   return(0);
}
