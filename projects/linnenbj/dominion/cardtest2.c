/* -----------------------------------------------------------------------
 *playCardAdventurer() Unit Testing file
 *Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 *testCard2: cardtest2.c dominion.o rngs.o
 *	gcc -0 cardtest2 dominion.o rngs.o cardtest2.c $(CFLAGS)
 *
 *
 * playCardAdventurer() is allows the player to draw three additional cards
 * into their hand.
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


#define TESTCARD "adventurer"
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




int main()
{
    int coinsInHand = 0;
    int handpos = 0, bonus = 0;
    int seed = 1800;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    shuffle(thisPlayer, &G);

	printf("*** Testing Card: %s \n", TESTCARD);

	// ----------- TEST 1: At least 2 treasure cards in player's deck --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 1: At least 2 treasure cards in player's deck\n");
    printf("-------------------------------------------------------------\n");
	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = adventurer;           //assign the smithy card to the end of the hand

	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(adventurer, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

	//determine if hand/deck is correct

	coinsInHand = handCoins(&G, thisPlayer); //how many coins are in player's hand
	int coinCount = coinsInHand;
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
    printf("# coin cards: %d\n", coinsInHand);
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    while(coinCount < coinsInHand + 2 && (G.deckCount[thisPlayer] + G.discardCount[thisPlayer] != 0))
    {
        drawCard(thisPlayer, &G);
        if(handCoins(&G, thisPlayer) > coinCount)
            coinCount++;
        else
            discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);
    }



    printf("After adventurer card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);

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

	// ----------- TEST 2: Force a Shuffle to get to treasure cards --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 2: Force a shuffle\n");
    printf("-------------------------------------------------------------\n");

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = adventurer;           //assign the smithy card to the end of the hand

    //move enough cards from the deck into discard so deckCount = 0
	int count = 0;
	while(G.deckCount[thisPlayer] > 0)
    {
        G.discard[thisPlayer][count] = G.deck[thisPlayer][G.deckCount[thisPlayer]-1];
        G.deckCount[thisPlayer]--;
        G.discardCount[thisPlayer]++;
        count++;
    }


	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(adventurer, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

	//determine if hand/deck is correct

	coinsInHand = handCoins(&G, thisPlayer); //how many coins are in player's hand
	coinCount = coinsInHand;
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
    printf("# coin cards: %d\n", coinsInHand);
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    while(coinCount < coinsInHand + 2 && (G.deckCount[thisPlayer] + G.discardCount[thisPlayer] != 0))
    {
        drawCard(thisPlayer, &G);
        if(handCoins(&G, thisPlayer) > coinCount)
            coinCount++;
        else
            discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);
    }



    printf("After adventurer card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printf("Due to shuffle, there is no Expected deck.\n");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printf("Due to shuffle, there is no Expected discard.\n");

	printf("\tGamestates equal: %d (0 can be ok with shuffle)\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 0) != 1)
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


	// ----------- TEST 3: Only 1 treasure left in deck/discard --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 3: Only 1 treasure available\n");
    printf("-------------------------------------------------------------\n");

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = adventurer;           //assign the smithy card to the end of the hand

    //deck has 3 coppers as initialized
    coinCount = 3;
    count = 0;
    while(coinCount > 1)
    {
        if(G.deck[thisPlayer][count] == 4)
        {
            coinCount--;
            G.deck[thisPlayer][count] = 1;
        }
        count++;
    }

	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(adventurer, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

	//determine if hand/deck is correct

	coinsInHand = handCoins(&G, thisPlayer); //how many coins are in player's hand
	coinCount = coinsInHand;
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
    printf("# coin cards: %d\n", coinsInHand);
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    while(coinCount < coinsInHand + 2 && (G.deckCount[thisPlayer] + G.discardCount[thisPlayer] != 0))
    {
        drawCard(thisPlayer, &G);
        if(handCoins(&G, thisPlayer) > coinCount)
            coinCount++;
        else
            discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);
    }



    printf("After adventurer card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Expected deck");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Expected discard");

	printf("\tGamestates equal: %d (0 can be ok with shuffle)\n", statesAreEqual(&G, &testG, 1));
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


	// ----------- TEST 4: 0 treasures left in deck/discard --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 4: 0 treasures available\n");
    printf("-------------------------------------------------------------\n");

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = adventurer;           //assign the smithy card to the end of the hand

    //deck has 3 coppers as initialized
    coinCount = 3;
    count = 0;
    while(coinCount > 0)
    {
        if(G.deck[thisPlayer][count] == 4)
        {
            coinCount--;
            G.deck[thisPlayer][count] = 1;
        }
        count++;
    }

	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(adventurer, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

	//determine if hand/deck is correct

	coinsInHand = handCoins(&G, thisPlayer); //how many coins are in player's hand
	coinCount = coinsInHand;
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
    printf("# coin cards: %d\n", coinsInHand);
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    while(coinCount < coinsInHand + 2 && (G.deckCount[thisPlayer] + G.discardCount[thisPlayer] != 0))
    {
        drawCard(thisPlayer, &G);
        if(handCoins(&G, thisPlayer) > coinCount)
            coinCount++;
        else
            discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);
    }



    printf("After adventurer card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Expected deck");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Expected discard");

	printf("\tGamestates equal: %d (0 can be ok with shuffle)\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 0) != 1)
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


	// ----------- TEST 5: silvers and golds --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 5: silver and gold\n");
    printf("-------------------------------------------------------------\n");

    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = adventurer;           //assign the smithy card to the end of the hand

    //deck has 3 coppers as initialized -- set deck to 2 silver and 1 gold
    coinCount = 3;
    count = 0;
    while(coinCount > 0)
    {
        if(G.deck[thisPlayer][count] == 4)
        {
            coinCount--;
            if(coinCount == 1)
                G.deck[thisPlayer][count] = 6;  //assign it a gold
            else
                G.deck[thisPlayer][count] = 5;  //assign it a silver
        }
        count++;
    }

	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(adventurer, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

	//determine if hand/deck is correct

	coinsInHand = handCoins(&G, thisPlayer); //how many coins are in player's hand
	coinCount = coinsInHand;
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
    printf("# coin cards: %d\n", coinsInHand);
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    while(coinCount < coinsInHand + 2 && (G.deckCount[thisPlayer] + G.discardCount[thisPlayer] != 0))
    {
        drawCard(thisPlayer, &G);
        if(handCoins(&G, thisPlayer) > coinCount)
            coinCount++;
        else
            discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);
    }



    printf("After adventurer card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Expected deck");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Expected discard");

	printf("\tGamestates equal: %d (0 can be ok with shuffle)\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 0) != 1)
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 5 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***\n");
        printf("-------------------------------------------------------------\n");
    }
    else
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 5 STATUS:  PASSED!\n");
        printf("-------------------------------------------------------------\n\n");
    }

        printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}

