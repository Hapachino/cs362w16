/* Author: Shaun Stapleton
 * Assignment 4
 * randomtestadventurer.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *	echo "Result for running Dominion Random Test Adventurer:" > randomtestadventurer.out
 *	echo "randomtestadventurer.c:" >> randomtestadventurer.out
 *	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 *	randomtestadventurer >> randomtestadventurer.out
 *	gcov dominion.c >> randomtestadventurer.out
 *	gcov dominion.c -b >> randomtestadventurer.out
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
	//int cardTotal = 7;
    int m, r, s, t;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	const char* cardNames[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer",
	"council_room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion",
	"steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	
	//set up random seed for tests
	int tseed = time(NULL);
	srand(tseed);
	//toggle for success or failure
	int successful;
	//for totals at end
	int totalsuc, totalfail;
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	//printf("\n");

	int testCount = 1000;
	totalfail = 0;
	totalsuc = 0;
	
	for(r = 0; r < testCount; r++){
		
		printf("\n----------------- Iteration: %d ----------------\n", r + 1);
		//printf("\n---------- Test 1 - Pre state for each player, victory cards, and treasure cards: ----------\n");

		//reset successful each time
		successful = 1;
		
			G.hand[thisPlayer][0] = adventurer;
			G.hand[thisPlayer][1] = estate;
			G.hand[thisPlayer][2] = smithy;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = feast;
			
			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			
			//Randomize the players deck cards to find different types of bugs
			testG.deck[thisPlayer][0] = rand() % 27;
			testG.deck[thisPlayer][1] = rand() % 27;
			testG.deck[thisPlayer][2] = rand() % 27;
			//Make sure two cards are treasure cards
			testG.deck[thisPlayer][3] = rand() % 3 + 4;
			testG.deck[thisPlayer][4] = rand() % 3 + 4;
			
			//check victory cards
			//printf("Victory cards count: Estate = %d, Duchy = %d, Province = %d ... expected values are 8,8,8\n", testG.supplyCount[estate], testG.supplyCount[duchy], testG.supplyCount[province]);
			
			//error victory cards
			if(testG.supplyCount[estate] != 8 || testG.supplyCount[duchy] != 8 || testG.supplyCount[province] != 8){
				printf("\nTEST FAILED: Victory Card totals are incorrect. \n");
				successful = 0;
			}
			
			//check treasure cards
			//printf("Treasure cards count: Copper = %d, Silver = %d, Gold = %d ... expected values are 46,40,30\n", testG.supplyCount[copper], testG.supplyCount[silver], testG.supplyCount[gold]);
			
			//error treasure cards
			if(testG.supplyCount[copper] != 46 || testG.supplyCount[silver] != 40 || testG.supplyCount[gold] != 30){
				printf("\nTEST FAILED: Treasure Card totals are incorrect. \n");
				successful = 0;
			}
			
			//Test player 1 hand and deck count before adventurer is played
			newCards = 0;
			discarded = 0;
			
			//printf("player 1 hand count before = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
			
			//error check player 1 hand count
			if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded){
				printf("\nTEST FAILED: Player 1 hand count is incorrect. \n");
				successful = 0;
			}
			
			//printf("player 1 deck count before = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			
			//error check player 1 deck count
			if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + shuffledCards){
				printf("\nTEST FAILED: Player 1 deck count is incorrect. \n");
				successful = 0;
			}
			
			//player 1 discard count
			//printf("player 1 discard count before = %d\n", testG.discardCount[thisPlayer]);
			
			//test player 2 deck state
			//printf("player 2 deck count before = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1] - newCards + shuffledCards);
			
			//error check player 2 deck count
			if(testG.deckCount[thisPlayer + 1] != G.deckCount[thisPlayer + 1] - newCards + shuffledCards){
				printf("\nTEST FAILED: Player 2 deck count is incorrect. \n");
				successful = 0;
			}
			
			printf("\nstarting cards for player 1: ");
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%s)", cardNames[testG.hand[thisPlayer][m]]);
			}
			
			printf("\nstarting cards in DECK for player 1: ");
			for (m=0; m<testG.deckCount[thisPlayer]; m++) {
				printf("(%s)", cardNames[testG.deck[thisPlayer][m]]);
			}

			//printf("; ");
			
			//Play card and see results
			//printf("\n\n----------Test 2 - play adventurer - add 2 treasure cards to player 1: -------------\n");
			cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("\nending cards for player 1: ");

			// tests that the two treasure cards are added to players hand
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%s)", cardNames[testG.hand[thisPlayer][m]]);				
			}
			//assert(testG.handCount[thisPlayer] == cardTotal);
			
			printf("\nending cards in DECK for player 1: ");
			for (m=0; m<testG.deckCount[thisPlayer]; m++) {
				printf("(%s)", cardNames[testG.deck[thisPlayer][m]]);
			}			
			
			newCards = 2;
			//test total cards
			if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards){
				printf("\nTEST FAILED: Player 1 cards gained is incorrect. \n");
				successful = 0;
			}
			
			
			//printf("\n");
			
			//printf("\n---------- Test 3 - Post state for each player, victory cards, and treasure cards: ----------\n");
			
			//check treasure cards
			//printf("Treasure cards count: Copper = %d, Silver = %d, Gold = %d ... expected values to total 116\n", testG.supplyCount[copper], testG.supplyCount[silver], testG.supplyCount[gold]);
			
			//error treasure cards
			if((testG.supplyCount[copper] + testG.supplyCount[silver] + testG.supplyCount[gold]) != 116){
				printf("\nTEST FAILED: Treasure Cards totals is incorrect. \n");
				successful = 0;
			}
			
			//check victory cards
			//printf("Victory cards count: Estate = %d, Duchy = %d, Province = %d ... expected values are 8,8,8\n", testG.supplyCount[estate], testG.supplyCount[duchy], testG.supplyCount[province]);
			
			//error victory cards
			if(testG.supplyCount[estate] != 8 || testG.supplyCount[duchy] != 8 || testG.supplyCount[province] != 8){
				printf("\nTEST FAILED: Victory Card totals are incorrect. \n");
				successful = 0;
			}
			
			// tests for the appropriate number of remaining cards
			newCards = 3;
			discarded = 1;
			
			//printf("player 1 hand count after = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
										
			//error check player 1 hand count
			if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded){
				printf("TEST FAILED: Player 1 hand count is incorrect. \n");
			}
			
			//printf("player 1 deck count after = %d\n", testG.deckCount[thisPlayer]);
			//printf("player 1 discard count after = %d\n", testG.discardCount[thisPlayer]);
			
			t = 0;
			//cycle through discarded pile to confirm no treasure cards were tossed out.
			for( s = 0; s < testG.discardCount[thisPlayer]; s++){
				if(testG.discard[thisPlayer][s] == 4 || testG.discard[thisPlayer][s] == 5 || testG.discard[thisPlayer][s] == 6){
					t++;
				}
			}
			
			//error check player 1 discard pile for treasure cards
			if(t > 0){
				printf("\nTEST FAILED: Player 1 discard pile contains treasure %d cards. \n", t);
				successful = 0;
			}
			
			newCards = 0;
			discarded = 0;
			//test player 2 deck state
			//printf("player 2 deck count after = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1] - newCards + shuffledCards);
			
			//error check player 2 deck count
			if(testG.deckCount[thisPlayer + 1] != G.deckCount[thisPlayer + 1] - newCards + shuffledCards){
				printf("\nTEST FAILED: Player 2 deck count is incorrect. \n");
				successful = 0;
			}
			
			//tally up success and failures
			if(successful == 1){
				totalsuc++;
			}
			else{
				totalfail++;
			}

	}
	
	printf("\n >>>>> Testing complete for: %s <<<<<\n\n", TESTCARD);
	printf("\n >>>>> Total Tests: %d <<<<<\n\n", testCount);
	printf("\n >>>>> Total Successful: %d <<<<<\n\n", totalsuc);
	printf("\n >>>>> Total Failed: %d <<<<<\n\n", totalfail);
	
	return 0;
}