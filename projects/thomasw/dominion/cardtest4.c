/*******************************************
* Test for Adventurer
* Add this to your dominion makefile
* cardtest3: cardtest3.c dominion.o rngs.o
     gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)


     //This test utilizes the card enum in dominion.h to modify card values in hand
*******************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Adventurer"

int main(int argc, char const *argv[])
{
	int i;

	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	//initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


	//Test 1: Coppers at top of deck: 1, 1, 4, 4, 4
	int pass = 1;
	printf("TEST 1: Testing 5 card deck; 3 copper on top:\n");
    printf("\nDeck Contents: \n");
    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
        printf("%d, ", testG.deck[thisPlayer][i]);
    }

    // Empty
    printf("\nDiscard contents:\n");
    for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
        printf("%d, ", testG.discard[thisPlayer][i]);
    }

    // 4, 4, 1, 4, 4
    printf("\nHand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//Expecting 1, 1, 4
 	printf("\nDeck Contents: \n");
    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
        printf("%d, ", testG.deck[thisPlayer][i]);
    }

    printf("\nExpected Deck:\n1, 1, 4");

    if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 2)
    {
    	printf("Test Failed: Deck contents incorrect");
    	pass = 0;
    }

    // Expecting Empty
    printf("\nDiscard contents:\n");
    for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
        printf("%d, ", testG.discard[thisPlayer][i]);
    }

    printf("\nExpected discard:\n");

    if (testG.discardCount[thisPlayer] != G.discardCount[thisPlayer])
    {
    	printf("Test Failed: Discard contents incorrect");
    	pass = 0;
    }

    // Expecting 4, 4, 1, 4, 4, 4, 4
    printf("\nHand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    printf("\nExpected Hand:\n4, 4, 1, 4, 4, 4, 4");

    if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] +2)
    {
    	printf("Test Failed: hand contents incorrect");
    	pass = 0;
    }

    if(pass)
    {
    	printf("\n----------------- TEST PASSED -----------------\n");
    }
    else
    	printf("\n----------------- TEST FAILED -----------------\n");

    //Test 2: 2 silver at top of deck: 1, 1, 4, 5, 5
    pass = 1;
	memcpy(&testG, &G, sizeof(struct gameState));
    
    for (i = 3; i < 5; i++) {
        testG.deck[thisPlayer][i] = silver;
    }

	printf("\nTEST 2: Testing 5 card deck; silver on top:\n");
    printf("\nInitial Deck Contents: \n");
    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
        printf("%d, ", testG.deck[thisPlayer][i]);
    }

    // Empty
    printf("\nInitial Discard contents:\n");
    for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
        printf("%d, ", testG.discard[thisPlayer][i]);
    }

    printf("\nInitial Hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//Expecting 1, 1, 4
 	printf("\nDeck Contents: \n");
    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
        printf("%d, ", testG.deck[thisPlayer][i]);
    }

    printf("\nExpected Deck: 1, 1, 4");

    if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 2)
    {
    	printf("Test Failed: Deck contents incorrect");
    	pass = 0;
    }

    // Expecting Empty
    printf("\nDiscard contents:\n");
    for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
        printf("%d, ", testG.discard[thisPlayer][i]);
    }

    printf("\nExpected discard:\n");

    if (testG.discardCount[thisPlayer] != G.discardCount[thisPlayer])
    {
    	printf("Test Failed: Discard contents incorrect\n");
    	pass = 0;
    }

    // Expecting 4, 4, 1, 4, 4, 5, 5
    printf("\nHand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    printf("\nExpected Hand:\n4, 4, 1, 4, 4, 5, 5");

    if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] +2)
    {
    	printf("Test Failed: hand contents incorrect");
    	pass = 0;
    }

    if(pass)
    {
    	printf("\n----------------- TEST PASSED -----------------\n");
    }
    else
    	printf("\n----------------- TEST FAILED -----------------\n");

    //Test 3: 2 gold at top of deck: 1, 1, 4, 6, 6
    pass = 1;
	memcpy(&testG, &G, sizeof(struct gameState));
    
    for (i = 3; i < 5; i++) {
        testG.deck[thisPlayer][i] = gold;
    }

	printf("\nTEST 3: Testing 5 card deck; 2 gold on top:\n");
    printf("\nInitial Deck Contents: \n");
    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
        printf("%d, ", testG.deck[thisPlayer][i]);
    }

    // Empty
    printf("\nInitial Discard contents:\n");
    for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
        printf("%d, ", testG.discard[thisPlayer][i]);
    }

    printf("\nInitial Hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//Expecting 1, 1, 4
 	printf("\nDeck Contents: \n");
    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
        printf("%d, ", testG.deck[thisPlayer][i]);
    }

    printf("\nExpected Deck: 1, 1, 4");

    if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 2)
    {
    	printf("Test Failed: Deck contents incorrect");
    	pass = 0;
    }

    // Expecting Empty
    printf("\nDiscard contents:\n");
    for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
        printf("%d, ", testG.discard[thisPlayer][i]);
    }

    printf("\nExpected discard:\n \n");

    if (testG.discardCount[thisPlayer] != G.discardCount[thisPlayer])
    {
    	printf("Test Failed: Discard contents incorrect\n");
    	pass = 0;
    }

    // Expecting 4, 4, 1, 4, 4, 6, 6
    printf("\nHand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    printf("\nExpected Hand: 4, 4, 1, 4, 4, 6, 6");

    if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] +2)
    {
    	printf("Test Failed: hand contents incorrect");
    	pass = 0;
    }

    if(pass)
    {
    	printf("\n----------------- TEST PASSED -----------------\n");
    }
    else
    	printf("\n----------------- TEST FAILED -----------------\n");

    //Test 4: Treasure at bottom of deck: 4, 5, 6, 1, 1
    pass = 1;
	memcpy(&testG, &G, sizeof(struct gameState));

    testG.deck[thisPlayer][0] = copper;
    testG.deck[thisPlayer][1] = silver;
    testG.deck[thisPlayer][2] = gold;

    for (i = 3; i < 5; i++) {
        testG.deck[thisPlayer][i] = estate;
    }

	printf("\nTEST 4: Testing 5 card deck; 3 treasure at bottom:\n");
    printf("\nInitial Deck Contents: \n");
    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
        printf("%d, ", testG.deck[thisPlayer][i]);
    }

    // Empty
    printf("\nInitial Discard contents:\n");
    for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
        printf("%d, ", testG.discard[thisPlayer][i]);
    }

    printf("\nInitial Hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//Expecting 4
 	printf("\nDeck Contents: \n");
    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
        printf("%d, ", testG.deck[thisPlayer][i]);
    }

    printf("\nExpected Deck:\n4");

    if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 4)
    {
    	printf("Test Failed: Deck contents incorrect");
    	pass = 0;
    }

    // Expecting 1, 1
    printf("\nDiscard contents:\n");
    for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
        printf("%d, ", testG.discard[thisPlayer][i]);
    }

    printf("\nExpected discard:\n1, 1\n");

    if (testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] +2)
    {
    	printf("Test Failed: Discard contents incorrect\n");
    	pass = 0;
    }

    // Expecting 4, 4, 1, 4, 4, 6, 5
    printf("\nHand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    printf("\nExpected Hand: 4, 4, 1, 4, 4, 6, 5");

    if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] +2)
    {
    	printf("Test Failed: hand contents incorrect");
    	pass = 0;
    }

    if(pass)
    {
    	printf("\n----------------- TEST PASSED -----------------\n");
    }
    else
    	printf("\n----------------- TEST FAILED -----------------\n");

    //TEST 5: Checking gamestate for next player. Should be unchanged.
	printf("\nTesting unchanged state for player2:\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1]);
	printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer+1], G.discardCount[thisPlayer+1]);
	if ((testG.handCount[thisPlayer+1]) != (G.handCount[thisPlayer+1]) || (testG.deckCount[thisPlayer+1]) != (G.deckCount[thisPlayer+1]) || (testG.discardCount[thisPlayer+1]) != (G.discardCount[thisPlayer+1]))
	{
		printf("----------------- TEST FAILED -----------------\n");
	}
	else
		printf("----------------- TEST PASSED -----------------\n");

	return 0;
}