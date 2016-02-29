#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "cardFunctions.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
// 1. Current player should receive exact 3 cards.

// 2. 3 cards should come from his own pile.

// 3. No state change should occur for other players.

// 4. No state change should occur to the victory card piles and kingdom card piles.

int drawCard2(int player, struct gameState *state);

//random hand with smithy at the end
int createRandomHand(int *k, int max) 
{
  int j;
  for(j = 0; j < max-1; j++) 
  {
    k[j] = (rand()%15);
  }
  k[j] = smithy;
}

//random hand with smithy at the end
int createRandomDeck(int *k, int max) 
{
  int j;
  for(j = 0; j < max; j++) 
  {
    k[j] = (rand()%15);
  }
}

int setDiscardDeck(int *k, int max) {
  int i;
  for(i = 0; i < max; i++)
  {
    k[i] = -1;
  }
}


int main() {
  srand(time(NULL));
  struct gameState G;

  struct gameState Gcopy;
  struct infosStruct infos;
  int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};  
  int numPlayers = 4;
  int handCountBefore, handCountAfter;
  int deckCountBefore, deckCountAfter;
  int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
  int i;
  G.numPlayers = numPlayers;
  G.whoseTurn = 0;
  infos.currentPlayer = 0;
  infos.handPos = 4;

  int handCount = 5;
  int deckCount = MAX_DECK - handCount;
  createRandomHand(G.hand[p1], handCount);
  createRandomHand(G.hand[p2], handCount);
  createRandomHand(G.hand[p3], handCount);
  createRandomHand(G.hand[p4], handCount);

  G.handCount[p1] = handCount;
  G.handCount[p2] = handCount;  
  G.handCount[p3] = handCount;  
  G.handCount[p4] = handCount;

  createRandomDeck(G.deck[p1], deckCount);
  createRandomDeck(G.deck[p2], deckCount);
  createRandomDeck(G.deck[p3], deckCount);
  createRandomDeck(G.deck[p4], deckCount);

  G.deckCount[p1] = deckCount;
  G.deckCount[p2] = deckCount;  
  G.deckCount[p3] = deckCount;  
  G.deckCount[p4] = deckCount;
  printf("handCount: %d\n", G.deckCount[p2]);

  setDiscardDeck(G.discard[p1], MAX_DECK);
  setDiscardDeck(G.discard[p2], MAX_DECK);
  setDiscardDeck(G.discard[p3], MAX_DECK);
  setDiscardDeck(G.discard[p4], MAX_DECK);

  G.discardCount[p1] = 0;
  G.discardCount[p2] = 0; 
  G.discardCount[p3] = 0; 
  G.discardCount[p4] = 0;


    memcpy (&Gcopy, &G, sizeof(G) );
  curPlayer = p1;
    int nextPlayer = 1;
  printf("handCount: %d\n", G.handCount[0]);


  //check handCount and deckCount of current player
  handCountBefore = G.handCount[curPlayer];
  deckCountBefore = G.deckCount[curPlayer];

  effectCouncil(&G, &infos);

    handCountAfter = G.handCount[curPlayer];
    deckCountAfter = G.deckCount[curPlayer];


 //check state of other player(s)
  //  printf("size: %d\n", G.deckCount[p1]);

    assert((Gcopy.deckCount[p1]-4) == G.deckCount[p1]);
    assert(Gcopy.deckCount[p2] == G.deckCount[p2]);
    assert(Gcopy.deckCount[p3] == G.deckCount[p3]);
    assert(Gcopy.deckCount[p4] == G.deckCount[p4]);


    printf("TEST: player 2 deck is unchanged\n");
    for(i = 0; i < G.deckCount[p2]; i++)
    {
      assert(Gcopy.deck[p2][i] == G.deck[p2][i]);
    }
    printf("PASS");

    printf("TEST: player 3 deck is unchanged\n");
    for(i = 0; i < G.deckCount[p3]; i++)
    {
      assert(Gcopy.deck[p3][i] == G.deck[p3][i]);
    }

    printf("TEST: player 4 deck is unchanged\n");
    for(i = 0; i < G.deckCount[p4]; i++)
    {
      assert(Gcopy.deck[p4][i] == G.deck[p4][i]);
    }

    printf("TEST: player 2 hand is unchanged\n");
    for(i = 0; i < G.handCount[p2]; i++)
    {
      assert(Gcopy.hand[p2][i] == G.hand[p2][i]);
    }

    printf("TEST: player 3 hand is unchanged\n");
    for(i = 0; i < G.handCount[p3]; i++)
    {
      assert(Gcopy.hand[p3][i] == G.hand[p3][i]);
    }

    printf("TEST: player 4 hand is unchanged\n");
    for(i = 0; i < G.handCount[p4]; i++)
    {
      assert(Gcopy.hand[p4][i] == G.hand[p4][i]);
    }
  return 0;
}


// int effectCouncil(struct gameState *state, struct infosStruct *infos)
// {
//       //+4 Cards
//   int currentPlayer = infos->currentPlayer;
//   int handPos = infos->handPos;
//   int i = infos->i;
//       for (i = 0; i < 4; i++)
//       {
//         drawCard(currentPlayer, state);
//       }
      
//       //+1 Buy
//       state->numBuys++;
      
//       //Each other player draws a card
//       for (i = 0; i < state->numPlayers; i++)
//       {
//         if ( i != currentPlayer )
//           {
//             drawCard(i, state);
//           }
//       }
      
//       //put played card in played card pile
//       discardCard(handPos, currentPlayer, state, 0);

//       return 0;
// }