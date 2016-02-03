/* -----------------------------------------------------------------------
 *playCardVillage() Unit Testing file
 *Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 *testCard3: cardtest3.c dominion.o rngs.o
 *	gcc -0 cardtest3 dominion.o rngs.o cardtest3.c $(CFLAGS)
 *
 *
 * playCardVillage() allows the player to draw 1 additional card
 * into their hand and adds 2 more actions to their turn.
 *
 *
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//-----------------------------------


#define TESTCARD "village"
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
            for(j = 0; j < g1->playedCardCount; j++)
            {
                if(g1->playedCards[j] != g2->playedCards[j]) return 0;
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




int main()
{
    int count;
    int handpos = 0, bonus = 0;
    int seed = 1800;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("*** Testing Card: %s \n", TESTCARD);

	// ----------- TEST 1: At least 1 cards in the deck --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 1: At least 1 cards in the player's deck\n");
    printf("-------------------------------------------------------------\n");
	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = village;           //assign the village card to the end of the hand

	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(village, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

	//determine if hand/deck is correct
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    drawCard(thisPlayer, &G);  //+1 card
    G.numActions += 2;        //+2 actions



    printf("After village card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);
	printf("\t  Player actions: %d [%d expected]\n", testG.numActions, G.numActions);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Expected deck");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Expected discard");


	printf("\tGamestates equal: %d\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 1) != 1)
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 1 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***\n");
        printf("-------------------------------------------------------------\n");
    }
    else
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 1 STATUS:  PASSED!\n");
        printf("-------------------------------------------------------------\n\n");
    }


// ----------- TEST 2: Force a shuffle (0 in deck, discard > 0) --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 2: Force a shuffle for the card\n");
    printf("-------------------------------------------------------------\n");

    memset(&G, 0, sizeof(struct gameState));              // clear the game state
    memset(&testG, 0, sizeof(struct gameState));          // clear the game state
    initializeGame(numPlayers, k, seed, &G);               //initialize a new game

	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = village;           //assign the village card to the end of the hand


	//move enough cards from the deck into discard so deckCount = 0
	count = 0;
	while(G.deckCount[thisPlayer] > 0)
    {
        G.discard[thisPlayer][count] = G.deck[thisPlayer][G.deckCount[thisPlayer]-1];
        G.deckCount[thisPlayer]--;
        G.discardCount[thisPlayer]++;
        count++;
    }

	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(village, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

    //determine if hand/deck is correct
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    drawCard(thisPlayer, &G);  //+1 card
    G.numActions += 2;        //+2 actions



    printf("After village card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);
	printf("\t  Player actions: %d [%d expected]\n", testG.numActions, G.numActions);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Expected deck");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Expected discard");


	printf("\tGamestates equal: %d\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 1) != 1)
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 2 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***\n");
        printf("-------------------------------------------------------------\n");
    }
    else
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 2 STATUS:  PASSED!\n");
        printf("-------------------------------------------------------------\n\n");
    }


// ----------- TEST 3: 0 Cards available for drawing --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 3: 0 cards in deck/discard piles\n");
    printf("-------------------------------------------------------------\n");

    memset(&G, 0, sizeof(struct gameState));              // clear the game state
    memset(&testG, 0, sizeof(struct gameState));          // clear the game state
    initializeGame(numPlayers, k, seed, &G);               //initialize a new game

	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = village;           //assign the village card to the end of the hand


	//set deckCount to 0
	G.deckCount[thisPlayer] = 0;


	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(village, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

    //determine if hand/deck is correct
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    drawCard(thisPlayer, &G);  //+1 card
    G.numActions += 2;        //+2 actions



    printf("After village card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);
	printf("\t  Player actions: %d [%d expected]\n", testG.numActions, G.numActions);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Expected deck");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Expected discard");


	printf("\tGamestates equal: %d\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 1) != 1)
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 3 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***\n");
        printf("-------------------------------------------------------------\n");
    }
    else
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 3 STATUS:  PASSED!\n");
        printf("-------------------------------------------------------------\n\n");
    }

        printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);
    return 0;
}

