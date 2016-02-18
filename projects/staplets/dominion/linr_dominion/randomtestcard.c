/* Author: Shaun Stapleton
 * Assignment 4
 * randomtestcard.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard: randomtestcard.c dominion.o rngs.o
 *	echo "Result for running Dominion Random Test Adventurer:" > randomtestcard.out
 *	echo "randomtestcard.c:" >> randomtestcard.out
 *	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
 *	randomtestcard >> randomtestcard.out
 *	gcov dominion.c >> randomtestcard.out
 *	gcov dominion.c -b >> randomtestcard.out
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "remodel"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
	
    int i, m, n, r;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1;
    int seed = 100;
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
	
	//loop through for test size
	for(r = 0; r < testCount; r++){
		
		printf("\n----------------- Iteration: %d ----------------\n", r + 1);
		
		G.hand[thisPlayer][0] = remodel;
		G.hand[thisPlayer][1] = rand() % 27;
		G.hand[thisPlayer][2] = rand() % 27;
		G.hand[thisPlayer][3] = rand() % 27;
		G.hand[thisPlayer][4] = rand() % 27;
		
		//reset successful each time
		successful = 1;
		
		// cycle through each eligible card that's not remodel and confirm model is not removed.
		//Additionally check to make sure the gainCard is no more than 2 cost of the trashed card.
		for (i = 1; i<G.handCount[thisPlayer]; i++) {
			
			//printf("\n---------- Test 1 - Pre state for each player and victory cards: ----------\n");

			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			
			//check victory cards
			//printf("Victory cards count: Estate = %d, Duchy = %d, Province = %d ... expected values are 8,8,8\n", testG.supplyCount[estate], testG.supplyCount[duchy], testG.supplyCount[province]);
			
			//error victory cards
			if(testG.supplyCount[estate] != 8 || testG.supplyCount[duchy] != 8 || testG.supplyCount[province] != 8){
				printf("\nTEST FAILED: Victory Card totals are incorrect. \n");
				successful = 0;
			}
			
			//Test player 1 hand and deck count before smithy is played
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
			
			//test player 2 deck state
			//printf("player 2 deck count before = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1] - newCards + shuffledCards);
			
			//error check player 2 deck count
			if(testG.deckCount[thisPlayer + 1] != G.deckCount[thisPlayer + 1] - newCards + shuffledCards){
				printf("\nTEST FAILED: Player 2 deck count is incorrect. \n");
				successful = 0;
			}
			

			printf("\nstarting cards for player: ");
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%s)", cardNames[testG.hand[thisPlayer][m]]);
			}
			//printf("; ");

			// ----------- TEST21: choice1 tested against all cards that can be trashed  --------------
			//printf("\n\n---------- Test 2 - choice1 = test against each card per iteration: ----------\n");
						
			choice1 = i;
			//choice2 = 1; //Each time we will go through and select an Estate. This keeps the gained card from being
			
			int remCost = getCost(testG.hand[thisPlayer][i]);
			int newCost;
			
			//make sure we grab a card that is no more than 2 cost of the removed
			do{
				//randomize the card that is chosen, but make sure it's an acceptable value
				choice2 = rand() % 27;
				newCost = getCost(choice2);
				
			}while(remCost + 2 <= newCost);
			
			printf("\nUser chooses: (%s)", cardNames[choice2]);
			testG.supplyCount[choice2]--;
			
			//more than the trashed card for the sake of testing. It will lead to a seg fault if not.
			remove1 = testG.hand[thisPlayer][i];
			
			int p = 0;
			//get number of removed cards for testing
			for (m=1; m < testG.handCount[thisPlayer]; m++) {
				if(testG.hand[thisPlayer][m] == remove1){
					p++;
				}
			}
			
			//call card
			cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("\nremoved: (%s); ", cardNames[remove1]);
			printf("\nending cards: ");
		
			n = 0;
			// tests that the removed cards are no longer in the player's hand
			for (m=0; m < testG.handCount[thisPlayer]; m++) {
				printf("(%s)", cardNames[testG.hand[thisPlayer][m]]);
				if(testG.hand[thisPlayer][m] == remove1){
					n++;
				}
			}
			//if we have an error output it
			if( n != (p - 1)){
				printf("\nTEST FAILED: There was a failure calling remodel.\n");
				successful = 0;
			}
			printf("\nexpected: ");
			int once = 0;
			for (m=1; m<G.handCount[thisPlayer]; m++) {
				if ((G.hand[thisPlayer][m] != G.hand[thisPlayer][i]) || (once > 0)) {
						printf("(%s)", cardNames[G.hand[thisPlayer][m]]);
				}
				else{
					once++;
				}
			}
			printf("\n");
			
			//TEST 3: Check to make sure the card gained is no more than 2 cost of the discarded card.
			//printf("\n\n---------- Test 3 - choice2 = 1 Make sure gained card is no more than 2 the cost of the trashed: ----------\n");
			printf("Cost of card gained: (%d) \n", getCost(choice2));
			printf("Cost of card trashed: (%d) \n", getCost(remove1));
			
			if ( (getCost(G.hand[thisPlayer][i]) + 2) < getCost(testG.discard[thisPlayer][0]) )
			{
				printf("\nTEST FAILED: The card failed to gain a card costing 2 or less.\n");
				successful = 0;
			}
			
			//post state cards counts
			//printf("\n\n---------- Test 4 - Post state for each player and victory cards: ----------\n");
			
			//check victory cards
			//printf("Victory cards count: Estate = %d, Duchy = %d, Province = %d ... expected values are 8,8,8\n", testG.supplyCount[estate], testG.supplyCount[duchy], testG.supplyCount[province]);
			
			//error victory cards
			if(testG.supplyCount[estate] != 8 || testG.supplyCount[duchy] != 8 || testG.supplyCount[province] != 8){
				
				if(!(choice2 == 1 || choice2 == 2 || choice2 == 3)){
					printf("\nTEST FAILED: Victory Card totals are incorrect. \n");
					successful = 0;
				}
			}
			
			// tests for the appropriate number of remaining cards
			newCards = 0;
			discarded = 2;
			
			//printf("player 1 hand count after = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
										
			//error check player 1 hand count
			if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded){
				printf("\nTEST FAILED: Player 1 hand count is incorrect. \n");
				successful = 0;
			}
			
			//printf("player 1 deck count after = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			
			//error check player 1 deck count
			if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + shuffledCards){
				printf("\nTEST FAILED: Player 1 deck count is incorrect. \n");
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

	}
	
	printf("\n >>>>> Testing complete for: %s <<<<<\n\n", TESTCARD);
	printf("\n >>>>> Total Test Iterations through Deck: %d <<<<<\n\n", testCount);
	printf("\n >>>>> Total Tests Successful: %d <<<<<\n\n", totalsuc);
	printf("\n >>>>> Total Tests Failed: %d <<<<<\n\n", totalfail);

	return 0;
}