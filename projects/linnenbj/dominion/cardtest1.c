/* -----------------------------------------------------------------------
 *playCardSmithy() Unit Testing file
 *Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 *testCard1: cardtest1.c dominion.o rngs.o
 *	gcc -0 cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
 *
 *
 * playCardSmithy() is allows the player to draw three additional cards
 * into their hand.
 *
 * What needs testing:
 *   - Player draws three cards
 *        - final handCount increases by 2 (+3 new cards -1 smithy discard)
 *        - deckCount needs to decrease by 3
 *   - Smithy card is discarded
 *        - discardCount increases by 1
 *        - make sure the smithy card is actually the one played
 *
 *   - detect what happens when there are fewer than 3 cards left to draw
 *     (deck & discard contain less than 3 cards)
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"
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




int main() {
    char buffer[200] = "";
    char buffer2[200] = "";
    int handpos = 0, bonus = 0;
    int seed = 500;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("*** Testing Card: %s \n", TESTCARD);

	// ----------- TEST 1: Enough cards in deck to draw 3 --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 1: Enough cards in player's deck to draw 3\n");
    printf("-------------------------------------------------------------\n");
	assert(G.deckCount[thisPlayer] >= 3);           //make sure there is enough cards in deck
	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = smithy;           //assign the smithy card to the end of the hand

	memcpy(&testG, &G, sizeof(struct gameState));   // copy the game state to a test case

	cardEffect(smithy, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

	//determine if hand/deck is correct
	int count = 1;
	assert(transform_ints_to_string(G.hand[thisPlayer], G.handCount[thisPlayer], buffer2, sizeof buffer2));
	printf("Starting hand: [%s\b\b]\n", buffer2);
	assert(transform_ints_to_string(G.deck[thisPlayer], G.deckCount[thisPlayer], buffer, sizeof buffer));
	printf("Starting deck: [%s\b\b]\n", buffer);

	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);
    drawCard(thisPlayer, &G);
    drawCard(thisPlayer, &G);
    drawCard(thisPlayer, &G);

    printf("After smithy card has been played:\n");
	printf("\tCards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\tCards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]); //drew 3 cards
	printf("\tPlayed cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount); //played 1 smithy card

	assert(transform_ints_to_string(testG.hand[thisPlayer], testG.handCount[thisPlayer], buffer, sizeof buffer));
	printf("\tPlayer's hand: [%s\b\b] \n", buffer);
	assert(transform_ints_to_string(G.hand[thisPlayer], G.handCount[thisPlayer], buffer2, sizeof buffer2));
	printf("\texpected hand: [%s\b\b]\n", buffer2);
	printf("\tGamestates equal: %d\n", statesAreEqual(&G, &testG, 0));
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





	// ----------- TEST 2: Force a Shuffle but still enough to draw 3 cards --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 2: Force a shuffle, drawCount + discardCount >= 3\n");
    printf("-------------------------------------------------------------\n");

    memset(&G, 0, sizeof(struct gameState));              // clear the game state
    memset(&testG, 0, sizeof(struct gameState));          // clear the game state

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = smithy;           //assign the smithy card to the end of the hand

	//move enough cards from the deck into discard so deckCount = 2
	count = 0;
	while(G.deckCount[thisPlayer] > 2)
    {
        G.discard[thisPlayer][count] = G.deck[thisPlayer][G.deckCount[thisPlayer]-1];
        G.deckCount[thisPlayer]--;
        G.discardCount[thisPlayer]++;
        count++;
    }

	//display starting hand/deck/discard
	assert(transform_ints_to_string(G.hand[thisPlayer], G.handCount[thisPlayer], buffer, sizeof buffer));
	printf("Starting hand: [%s\b\b]\n", buffer);
	assert(transform_ints_to_string(G.deck[thisPlayer], G.deckCount[thisPlayer], buffer, sizeof buffer));
	printf("Starting deck: [%s\b\b]\n", buffer);
	assert(transform_ints_to_string(G.discard[thisPlayer], G.discardCount[thisPlayer], buffer, sizeof buffer));
	printf("Starting discard: [%s\b\b]\n", buffer);


    memcpy(&testG, &G, sizeof(struct gameState));   // copy the game state to a test case

    discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);
    drawCard(thisPlayer, &G);
    drawCard(thisPlayer, &G);
    drawCard(thisPlayer, &G);  //should force a shuffle

    cardEffect(smithy, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

    printf("After smithy card has been played:\n");
	printf("\tCards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\tCards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\tPlayed cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount); //played 1 smithy card


    //sort the hands & decks to account for shuffle randomization
    qsort ((void*)(G.deck[0]), G.deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(G.hand[0]), G.handCount[0], sizeof(int), int_cmp);
    qsort ((void*)(testG.deck[0]), testG.deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(testG.hand[0]), testG.handCount[0], sizeof(int), int_cmp);

	assert(transform_ints_to_string(testG.hand[thisPlayer], testG.handCount[thisPlayer], buffer, sizeof buffer));
	printf("\tPlayer's hand: [%s\b\b] \n", buffer);
	assert(transform_ints_to_string(G.hand[thisPlayer], G.handCount[thisPlayer], buffer2, sizeof buffer2));
	printf("\texpected hand: [%s\b\b]\n", buffer2);
	assert(transform_ints_to_string(testG.deck[thisPlayer], testG.deckCount[thisPlayer], buffer, sizeof buffer));
	printf("\tPlayer's deck: [%s\b\b] \n", buffer);
	assert(transform_ints_to_string(G.deck[thisPlayer], G.deckCount[thisPlayer], buffer2, sizeof buffer2));
	printf("\texpected deck: [%s\b\b]\n", buffer2);
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


	// ----------- TEST 3: Empty Deck but discardCount >= 3 --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 3: Empty Deck but discardCount >= 3\n");
    printf("-------------------------------------------------------------\n");

    memset(&G, 0, sizeof(struct gameState));              // clear the game state
    memset(&testG, 0, sizeof(struct gameState));          // clear the game state

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = smithy;           //assign the smithy card to the end of the hand

	//move enough cards from the deck into discard so deckCount = 0
	count = 0;
	while(G.deckCount[thisPlayer] > 0)
    {
        G.discard[thisPlayer][count] = G.deck[thisPlayer][G.deckCount[thisPlayer]-1];
        G.deckCount[thisPlayer]--;
        G.discardCount[thisPlayer]++;
        count++;
    }

	//display starting hand/deck/discard
	assert(transform_ints_to_string(G.hand[thisPlayer], G.handCount[thisPlayer], buffer, sizeof buffer));
	printf("Starting hand: [%s\b\b]\n", buffer);
	if(G.deckCount[thisPlayer] == 0)
    {
        printf("Starting deck: [ ]\n");
    }
    else
    {
        assert(transform_ints_to_string(G.deck[thisPlayer], G.deckCount[thisPlayer], buffer, sizeof buffer));
        printf("Starting deck: [%s\b\b]\n", buffer);
    }
	if(G.discardCount[thisPlayer] == 0)
    {
        printf("Starting discard: [ ]\n");
    }
    else
    {
        assert(transform_ints_to_string(G.discard[thisPlayer], G.discardCount[thisPlayer], buffer, sizeof buffer));
        printf("Starting discard: [%s\b\b]\n", buffer);
    }

    memcpy(&testG, &G, sizeof(struct gameState));   // copy the game state to a test case

    discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);
    drawCard(thisPlayer, &G);  //should force a shuffle
    drawCard(thisPlayer, &G);
    drawCard(thisPlayer, &G);

    cardEffect(smithy, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

    printf("After smithy card has been played:\n");
	printf("\tCards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\tCards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\tPlayed cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount); //played 1 smithy card


    //sort the hands & decks to account for shuffle randomization
    qsort ((void*)(G.deck[0]), G.deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(G.hand[0]), G.handCount[0], sizeof(int), int_cmp);
    qsort ((void*)(testG.deck[0]), testG.deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(testG.hand[0]), testG.handCount[0], sizeof(int), int_cmp);

	assert(transform_ints_to_string(testG.hand[thisPlayer], testG.handCount[thisPlayer], buffer, sizeof buffer));
	printf("\tPlayer's hand: [%s\b\b] \n", buffer);
	assert(transform_ints_to_string(G.hand[thisPlayer], G.handCount[thisPlayer], buffer2, sizeof buffer2));
	printf("\texpected hand: [%s\b\b]\n", buffer2);
	assert(transform_ints_to_string(testG.deck[thisPlayer], testG.deckCount[thisPlayer], buffer, sizeof buffer));
	printf("\tPlayer's deck: [%s\b\b] \n", buffer);
	assert(transform_ints_to_string(G.deck[thisPlayer], G.deckCount[thisPlayer], buffer2, sizeof buffer2));
	printf("\texpected deck: [%s\b\b]\n", buffer2);
	printf("\tGamestates equal: %d  (0 not autofail b/c shuffle)\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 0) != 1)
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


	// ----------- TEST 4: Less than 3 cards available in deck/discard --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 4: deckCount + discardCount < 3\n");
    printf("-------------------------------------------------------------\n");

    memset(&G, 0, sizeof(struct gameState));              // clear the game state
    memset(&testG, 0, sizeof(struct gameState));          // clear the game state

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = smithy;           //assign the smithy card to the end of the hand

	//move enough cards from the deck into discard so deckCount = 1

	//draw 3 cards to get deckCount to 2;
    drawCard(thisPlayer, &G);
    drawCard(thisPlayer, &G);
    drawCard(thisPlayer, &G);	//deck should now be at 2
	assert(G.deckCount[thisPlayer] == 2);


	//display starting hand/deck/discard
	assert(transform_ints_to_string(G.hand[thisPlayer], G.handCount[thisPlayer], buffer, sizeof buffer));
	printf("Starting hand: [%s\b\b]\n", buffer);
	if(G.deckCount[thisPlayer] == 0)
    {
        printf("Starting deck: [ ]\n");
    }
    else
    {
        assert(transform_ints_to_string(G.deck[thisPlayer], G.deckCount[thisPlayer], buffer, sizeof buffer));
        printf("Starting deck: [%s\b\b]\n", buffer);
    }
	if(G.discardCount[thisPlayer] == 0)
    {
        printf("Starting discard: [ ]\n");
    }
    else
    {
        assert(transform_ints_to_string(G.discard[thisPlayer], G.discardCount[thisPlayer], buffer, sizeof buffer));
        printf("Starting discard: [%s\b\b]\n", buffer);
    }

    memcpy(&testG, &G, sizeof(struct gameState));   // copy the game state to a test case

    discardCard(handpos, thisPlayer, &G, 0);
    drawCard(thisPlayer, &G);
    drawCard(thisPlayer, &G);
    drawCard(thisPlayer, &G);   //force draw on empty deck/discard


    cardEffect(smithy, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

    printf("After smithy card has been played:\n");
	printf("\tCards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\tCards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\tPlayed cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount); //played 1 smithy card


    //sort the hands & decks to account for shuffle randomization
    qsort ((void*)(G.deck[0]), G.deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(G.hand[0]), G.handCount[0], sizeof(int), int_cmp);
    qsort ((void*)(testG.deck[0]), testG.deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(testG.hand[0]), testG.handCount[0], sizeof(int), int_cmp);

	assert(transform_ints_to_string(testG.hand[thisPlayer], testG.handCount[thisPlayer], buffer, sizeof buffer));
	printf("\tPlayer's hand: [%s\b\b] \n", buffer);
	assert(transform_ints_to_string(G.hand[thisPlayer], G.handCount[thisPlayer], buffer2, sizeof buffer2));
	printf("\texpected hand: [%s\b\b]\n", buffer2);
    if(testG.deckCount[thisPlayer] == 0)
    {
        printf("player's deck: [ ]\n");
    }
    else
    {
        assert(transform_ints_to_string(testG.deck[thisPlayer], testG.deckCount[thisPlayer], buffer, sizeof buffer));
        printf("Player's deck: [%s\b\b]\n", buffer);
    }
    	if(G.deckCount[thisPlayer] == 0)
    {
        printf("Expected deck: [ ]\n");
    }
    else
    {
        assert(transform_ints_to_string(G.deck[thisPlayer], G.deckCount[thisPlayer], buffer, sizeof buffer));
        printf("Expected deck: [%s\b\b]\n", buffer);
    }
	if(testG.discardCount[thisPlayer] == 0)
    {
        printf("Player's discard: [ ]\n");
    }
    else
    {
        assert(transform_ints_to_string(testG.discard[thisPlayer], testG.discardCount[thisPlayer], buffer, sizeof buffer));
        printf("Player's discard: [%s\b\b]\n", buffer);
    }


	if(G.discardCount[thisPlayer] == 0)
    {
        printf("Expected discard: [ ]\n");
    }
    else
    {
        assert(transform_ints_to_string(G.discard[thisPlayer], G.discardCount[thisPlayer], buffer, sizeof buffer));
        printf("Expected discard: [%s\b\b]\n", buffer);
    }


	printf("\tGamestates equal: %d\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 1) != 1)
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 4 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***\n");
        printf("-------------------------------------------------------------\n");
    }
    else
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 4 STATUS:  PASSED!\n");
        printf("-------------------------------------------------------------\n\n");
    }


	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
