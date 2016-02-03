/* -----------------------------------------------------------------------
 *fullDeckCount() Unit Testing file
 *Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 *testUnit4: unittest4.c dominion.o rngs.o
 *	gcc -0 unittest4 dominion.o rngs.o unittest1.c $(CFLAGS)
 *
 *
 * fullDeckCount() is supposed to return the number of a specified type
 * of card a player currently has in their hand, deck and discard combined.
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
//-----------------------------------


#define TESTFUNCTION "fullDeckCount()"
/* qsort int comparison function */
int int_cmp(const void *a, const void *b)
{
    const int *ia = (const int *)a; // casting pointer types
    const int *ib = (const int *)b;
    return *ia  - *ib;
	/* integer comparison: returns negative if b > a
	and positive if a > b */
}

//Determine if two gameStates are identical or not: Return 1 if identical, 0 if not
int statesAreEqual(struct gameState *g1, struct gameState *g2, int arraychecks)
{
    int i, j;

    if(g1->numPlayers != g2->numPlayers) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->supplyCount[i] != g2->supplyCount[i]) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->embargoTokens[i] != g2->embargoTokens[i]) return 0;
    if(g1->outpostPlayed != g2->outpostPlayed) return 0;
    if(g1->outpostTurn != g2->outpostTurn) return 0;
    if(g1->whoseTurn != g2->whoseTurn) return 0;
    if(g1->phase != g2->phase) return 0;
    if(g1->numActions != g2->numActions) return 0;
    if(g1->coins != g2->coins) return 0;
    if(g1->numBuys != g2->numBuys) return 0;
    if(g1->playedCardCount != g2->playedCardCount) return 0;

    qsort ((void*)(g1->deck[0]), g1->deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g1->hand[0]), g1->handCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g1->discard[0]), g1->discardCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g1->playedCards), g1->playedCardCount, sizeof(int), int_cmp);
    qsort ((void*)(g2->deck[0]), g2->deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g2->hand[0]), g2->handCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g2->discard[0]), g2->discardCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g2->playedCards), g2->playedCardCount, sizeof(int), int_cmp);




    for(i = 0; i < g1->numPlayers; i++)
    {
        if(g1->handCount[i] != g2->handCount[i]) return 0;
        if(g1->deckCount[i] != g2->deckCount[i]) return 0;
        if(g1->discardCount[i] != g2->discardCount[i]) return 0;

        if(arraychecks == 1)
        {
            for(j = 0; j < g1->discardCount[i]; j++)
            {
                if(g1->discard[i][j] != g2->discard[i][j]) return 0;
            }

            for(j = 0; j < g1->handCount[i]; j++)
            {
                if(g1->hand[i][j] != g2->hand[i][j]) return 0;
            }

            for(j = 0; j < g1->deckCount[i]; j++)
            {
                if(g1->deck[i][j] != g2->deck[i][j]) return 0;
            }
            for(i = 0; i < g1->playedCardCount; i++)
            {
                if(g1->playedCards[i] != g2->playedCards[i]) return 0;
            }
        }
    }
        return 1;
}



int transform_ints_to_string(int const* data, int data_length,
                             char* output, int output_length)
{
  // if not enough space was available, returns -1
  // otherwise returns the number of characters written to
  // output, not counting the additional null character

  // precondition: non-null pointers
  assert(data);
  assert(output);
  // precondition: valid data length
  assert(data_length >= 0);
  // precondition: output has room for null
  assert(output_length >= 1);

  int written = 0;
  for (; data_length; data_length--) {
    int length = snprintf(output, output_length, "%d, ", *data++);
    if (length >= output_length) {
      // not enough space
      return -1;
    }
    written += length;
    output += length;
    output_length -= length;
  }
  return written;
}
void printArray(int const* d, int len, char* str)
{
    char buf[200] = "";
    printf("%s: ", str);
    if(len <= 0)
    {
        printf("[ ]\n");
        return;
    }
    else
    {
        transform_ints_to_string(d, len, buf, sizeof buf);
        printf("[%s\b\b]\n", buf);
    }
}

int handCoins(struct gameState *g, int player)
{
    int i;
    int coins = 0;
    for(i = 0; i < g->handCount[player]; i++)
    {
        if(g->hand[player][i] == copper || g->hand[player][i] == silver || g->hand[player][i] == gold)
        {
            coins++;
        }
    }
    return coins;
}


void validateTest(struct gameState *G,  struct gameState *testG, int card, int expected)
{
    int result = fullDeckCount(thisPlayer, card, &testG);
    if(result == expected && statesAreEqual(G, testG, 1))
        printf("PASSED!\n");
    else
        printf("FAILED!\n");
    return 0;
}

int main()
{
    int count;
    int handpos = 0, result;
    int seed = 500;
    srand(seed);
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("*** Testing Function: %s \n", TESTCARD);

	// ----------- TEST 1: All of the card in players hand (counting village cards)----------
	printf("-------------------------------------------------------------\n");
	printf("TEST 1: 1 card in player's hand...");

	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = village;           //assign the great_hall card to the end of the hand
	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case
    validateTest(&G, &testG, village, 1);


	printf("TEST 2: 1 card in player's deck...");
	memset(&G, 0, sizeof(struct gameState));              // clear the game state
    memset(&testG, 0, sizeof(struct gameState));          // clear the game state
    initializeGame(numPlayers, k, seed, &G);               //initialize a new game
	G.deck[thisPlayer][rand() % G.deckCount[thisPlayer]] = village; //add card to deck
    memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case
    validateTest(&G, &testG, village, 1);


        printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);
    return 0;
}

