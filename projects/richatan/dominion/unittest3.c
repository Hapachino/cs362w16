/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Unit test for: buyCard()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PLAYERS 2
#define TEST_CARD mine
 
int main () {
	int i, j;			//loop controls
	int result;			//return value for function calls
	int failed;			//flags for tests
	
	struct gameState *g = malloc(sizeof(struct gameState));		//working game state
	struct gameState *pre = malloc(sizeof(struct gameState));	//reference game state; stored before functions run
	int selectedCards[10] = {adventurer, council_room, feast, gardens, mine, smithy, village, tribute, salvager, sea_hag};	
	int seed = 10;

	
//---Test numBuys = 0 
//---Expected result: error
	printf("*** Testing numBuys = 0 ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	}
	//Set numBuys to 0
	g->numBuys = 0;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to buy card
	result = buyCard(TEST_CARD, g);
	failed = 0;
	if (result != -1){
		printf("\nReturn value: %d, Expected: %d", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("\ngameState changed");
		failed = 1;
	} 
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}

	
//---Test no supply remaining 
//---Expected result: error
	printf("*** Testing supplyCount = 0 ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	}
	//Set supplyCount for test card to 0
	g->supplyCount[TEST_CARD] = 0;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to buy card
	result = buyCard(TEST_CARD, g);
	failed = 0;
	if (result != -1){
		printf("\nReturn value: %d, Expected: %d", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("\ngameState changed");
		failed = 1;
	} 
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}
	

//---Test insufficient funds
//---Expected result: error
	printf("*** Testing coins < cost ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	}
	//Set coins to cost of card - 1
	g->coins = getCost(TEST_CARD) - 1;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to buy card
	result = buyCard(TEST_CARD, g);
	failed = 0;
	if (result != -1){
		printf("\nReturn value: %d, Expected: %d", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("\ngameState changed");
		failed = 1;
	} 
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}

	
//---Test invalid supply position
//---Expected result: error
	printf("*** Testing invalid position ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	}
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to buy card at invalid position
	result = buyCard(treasure_map+1, g);
	failed = 0;
	if (result != -1){
		printf("\nReturn value: %d, Expected: %d", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("\ngameState changed");
		failed = 1;
	} 
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}
	
//---Test valid buy
/*---Expected results: 
	- Game and turn settings are unchanged except as noted below
	- Phase set to 1
	- numBuys decreased by 1
	- coins decreased by card cost
	- Supply count for other cards are unchanged
	- Supply count for selected card is decreased by 1
	- Other player's cards (hand, deck, discard) are unchanged
	- Played cards are unchanged		
	- Current player's hand and deck are unchanged
	- Current player's discardCount is 1 more than before buyCard
	- Current player's discard is the same except additional card in last position
*/
	printf("*** Testing valid buy ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	} 
	//Add sufficient coins and numBuys
	g->coins = getCost(TEST_CARD);
	g->numBuys = 1;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Run buyCard and check results
	failed = 0;
	result = buyCard(TEST_CARD, g);
	if (result == -1){
		printf("\nReturn value: %d, Expected: %d", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("\nNumPlayers: %d, Expected: %d", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("\nEmbargo for card %d: %d, Expected: %d", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("\noutpostPlayed: %d, Expected: %d", g->outpostPlayed, pre->outpostPlayed);
		printf("\noutpostTurn: %d, Expected: %d", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("\nwhoseTurn: %d, Expected: %d", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkNumActions(pre, g) < 0){
		printf("\nnumActions: %d, Expected: %d", g->numActions, pre->numActions);
		failed = 1;
	}	
	//Check phase = 1
	if (g->phase != 1){
		printf("\nphase: %d, Expected: %d", g->phase, 1);
		failed = 1;
	}	
	//Check coins = coins_before - cost of card
	if (g->coins != pre->coins - getCost(TEST_CARD)){
		printf("\ncoins: %d, Expected: %d", g->coins, pre->coins - getCost(TEST_CARD));
		failed = 1;
	}
	//Check numBuys decreased by 1
	if (g->numBuys != pre->numBuys - 1){
		printf("\nnumBuys: %d, Expected: %d", g->numBuys, pre->numBuys - 1);
		failed = 1;
	}
	//Check supply for bought card is decreased by 1
	if (g->supplyCount[TEST_CARD] != pre->supplyCount[TEST_CARD]-1){
		printf("\nSupply count for card %d: %d, Expected: %d", TEST_CARD, g->supplyCount[TEST_CARD], pre->supplyCount[TEST_CARD]-1);
		failed = 1;
	}
	//Check supply for other cards remains the same
	for (i = 0; i <= treasure_map; i++){
		//if test card, skip
		if (i == TEST_CARD){
			continue;
		}
		if (pre->supplyCount[i] != g->supplyCount[i]){
			printf("\nSupply count for card %d: %d, Expected: %d", i, g->supplyCount[i], pre->supplyCount[i]);
			failed = 1;
		}
	}
	//Check all hand, deck and played cards unchanged
	if (checkHands(pre, g) < 0){
		printf("\nHands changed after buyCard\n");
		//Print expected and actual hand for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Hand for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->handCount[i], pre->handCount[i]);
			if (g->handCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->handCount[i]; j++){
					printf("%d ", g->hand[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->handCount[i]; j++){
					printf("%d ", pre->hand[i][j]);
				}
			}
		}
		failed = 1;
	}
	if (checkDecks(pre, g) < 0){
		printf("\nDecks changed after buyCard\n");
		//Print expected and actual deck for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Deck for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->deckCount[i], pre->deckCount[i]);
			if (g->deckCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->deckCount[i]; j++){
					printf("%d ", g->deck[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->deckCount[i]; j++){
					printf("%d ", pre->deck[i][j]);
				}
			}
		}
		failed = 1;
	}
	if (checkPlayed(pre, g) < 0){
		printf("\nPlayed cards changed after buyCard\n");
		//Print expected and actual played cards
		printf("    Played count: %d, Expected: %d\n", g->playedCardCount, pre->playedCardCount);
		if (g->playedCardCount > 0){
			printf("    Actual Cards: ");
			for (i = 0; i < g->playedCardCount; i++){
				printf("%d ", g->playedCards[i]);
			}
			printf("\n    Expected Cards: ");
			for (i = 0; i < pre->playedCardCount; i++){
				printf("%d ", pre->playedCards[i]);
			}
		}
		failed = 1;
	}
	//Check discard unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->discardCount[i] != g->discardCount[i]){
			printf("\nPlayer %d's discardCount: %d, Expected: %d", i, g->discardCount[i], pre->discardCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->discardCount[i]; j++){
				if (pre->discard[i][j] != g->discard[i][j]){
					printf("\nPlayer %d's discard[%d]: %d, Expected: %d", i, j, g->discard[i][j], pre->discard[i][j]);
					failed = 1;
				}
			}
		}
	}	
	//Check current player's discardCount increased by 1
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)]+1){
			printf("\nCurrent player's discardCount: %d, Expected: %d", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)]+1);
			failed = 1;
	}
	//Check current player's discard contains same cards plus new card in last position
	for (i = 0; i < g->discardCount[whoseTurn(g)]-1; i++){
		if (pre->discard[whoseTurn(g)][i] != g->discard[whoseTurn(g)][i]){
			printf("\nCurrent player's discard[%d]: %d, Expected: %d", i, g->discard[whoseTurn(g)][i], pre->discard[whoseTurn(g)][i]);
			failed = 1;
		}
	}
	if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1] != TEST_CARD){
		printf("\nGained card: %d, Expected: %d", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1], TEST_CARD);
		failed = 1;		
	}
	
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}

//---Test buy with embargo
/*---Expected results: 
	- Game and turn settings are unchanged except as noted below
	- Phase set to 1
	- numBuys decreased by 1
	- coins decreased by card cost
	- Supply count for other cards are unchanged
	- Supply count for selected card is decreased by 1
	- Supply count for curse card decreased by 1
	- Embargo tokens for other cards are unchanged
	- Embargo tokens for selected card is decreased by 1
	- Other player's cards (hand, deck, discard) are unchanged
	- Played cards are unchanged		
	- Current player's hand and deck are unchanged
	- Current player's discardCount is 2 more than before buyCard
	- Current player's discard is the same except additional card and curse card
*/
	printf("*** Testing valid buy with embargo ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	} 
	//Add sufficient coins and numBuys
	g->coins = getCost(TEST_CARD);
	g->numBuys = 1;
	//Add embargo to test card
	g->embargoTokens[TEST_CARD] = 1;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Run buyCard and check results
	failed = 0;
	result = buyCard(TEST_CARD, g);
	if (result == -1){
		printf("\nReturn value: %d, Expected: %d", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("\nNumPlayers: %d, Expected: %d", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("\noutpostPlayed: %d, Expected: %d", g->outpostPlayed, pre->outpostPlayed);
		printf("\noutpostTurn: %d, Expected: %d", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("\nwhoseTurn: %d, Expected: %d", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkNumActions(pre, g) < 0){
		printf("\nnumActions: %d, Expected: %d", g->numActions, pre->numActions);
		failed = 1;
	}	
	//Check phase = 1
	if (g->phase != 1){
		printf("\nphase: %d, Expected: %d", g->phase, 1);
		failed = 1;
	}	
	//Check coins = coins_before - cost of card
	if (g->coins != pre->coins - getCost(TEST_CARD)){
		printf("\ncoins: %d, Expected: %d", g->coins, pre->coins - getCost(TEST_CARD));
		failed = 1;
	}
	//Check numBuys decreased by 1
	if (g->numBuys != pre->numBuys - 1){
		printf("\nnumBuys: %d, Expected: %d", g->numBuys, pre->numBuys - 1);
		failed = 1;
	}
	//Check supply for bought card is decreased by 1
	if (g->supplyCount[TEST_CARD] != pre->supplyCount[TEST_CARD]-1){
		printf("\nSupply count for card %d: %d, Expected: %d", TEST_CARD, g->supplyCount[TEST_CARD], pre->supplyCount[TEST_CARD]-1);
		failed = 1;
	}
	//Check supply for curse card is decreased by 1
	if (g->supplyCount[0] != pre->supplyCount[0]-1){
		printf("\nSupply count for curse card: %d, Expected: %d", g->supplyCount[0], pre->supplyCount[0]-1);
		failed = 1;
	}
	//Check supply for other cards remains the same
	for (i = 1; i <= treasure_map; i++){
		//if test card, skip
		if (i == TEST_CARD){
			continue;
		}
		if (pre->supplyCount[i] != g->supplyCount[i]){
			printf("\nSupply count for card %d: %d, Expected: %d", i, g->supplyCount[i], pre->supplyCount[i]);
			failed = 1;
		}
	}
	//Check embargo tokens for bought card is decreased by 1
	if (g->embargoTokens[TEST_CARD] != pre->embargoTokens[TEST_CARD]-1){
		printf("\nEmbargo tokens for card %d: %d, Expected: %d", TEST_CARD, g->embargoTokens[TEST_CARD], pre->embargoTokens[TEST_CARD]-1);
		failed = 1;
	}
	//Check embargo tokens for other cards remains the same
	for (i = 0; i <= treasure_map; i++){
		//if test card, skip
		if (i == TEST_CARD){
			continue;
		}
		if (pre->embargoTokens[i] != g->embargoTokens[i]){
			printf("\nEmbargo tokens for card %d: %d, Expected: %d", i, g->embargoTokens[i], pre->embargoTokens[i]);
			failed = 1;
		}
	}
	//Check all hand, deck and played cards unchanged
	if (checkHands(pre, g) < 0){
		printf("\nHands changed after buyCard\n");
		//Print expected and actual hand for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Hand for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->handCount[i], pre->handCount[i]);
			if (g->handCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->handCount[i]; j++){
					printf("%d ", g->hand[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->handCount[i]; j++){
					printf("%d ", pre->hand[i][j]);
				}
			}
		}
		failed = 1;
	}
	if (checkDecks(pre, g) < 0){
		printf("\nDecks changed after buyCard\n");
		//Print expected and actual deck for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Deck for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->deckCount[i], pre->deckCount[i]);
			if (g->deckCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->deckCount[i]; j++){
					printf("%d ", g->deck[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->deckCount[i]; j++){
					printf("%d ", pre->deck[i][j]);
				}
			}
		}
		failed = 1;
	}
	if (checkPlayed(pre, g) < 0){
		printf("\nPlayed cards changed after buyCard\n");
		//Print expected and actual played cards
		printf("    Played count: %d, Expected: %d\n", g->playedCardCount, pre->playedCardCount);
		if (g->playedCardCount > 0){
			printf("    Actual Cards: ");
			for (i = 0; i < g->playedCardCount; i++){
				printf("%d ", g->playedCards[i]);
			}
			printf("\n    Expected Cards: ");
			for (i = 0; i < pre->playedCardCount; i++){
				printf("%d ", pre->playedCards[i]);
			}
		}
		failed = 1;
	}
	//Check discard unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->discardCount[i] != g->discardCount[i]){
			printf("\nPlayer %d's discardCount: %d, Expected: %d", i, g->discardCount[i], pre->discardCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->discardCount[i]; j++){
				if (pre->discard[i][j] != g->discard[i][j]){
					printf("\nPlayer %d's discard[%d]: %d, Expected: %d", i, j, g->discard[i][j], pre->discard[i][j]);
					failed = 1;
				}
			}
		}
	}	
	//Check current player's discardCount increased by 2
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)]+2){
			printf("\nCurrent player's discardCount: %d, Expected: %d", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)]+2);
			failed = 1;
	}
	//Check current player's discard contains same cards plus new card and curse in last two positions
	for (i = 0; i < g->discardCount[whoseTurn(g)]-2; i++){
		if (pre->discard[whoseTurn(g)][i] != g->discard[whoseTurn(g)][i]){
			printf("\nCurrent player's discard[%d]: %d, Expected: %d", i, g->discard[whoseTurn(g)][i], pre->discard[whoseTurn(g)][i]);
			failed = 1;
		}
	}
	if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1] == TEST_CARD){
		if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-2] != 0){
			printf("\nGained card: %d, Expected: %d", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1], 0);
			failed = 1;		
		}
	} else if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1] == 0){
		if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-2] != TEST_CARD){
			printf("\nGained card: %d, Expected: %d", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1], TEST_CARD);
			failed = 1;		
		}
	} else {
		printf("\nGained card: %d, Expected: %d or %d", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1], TEST_CARD, 0);
		failed = 1;			
	}
	
	//Final check
	if (failed){
		printf("\nResult: FAIL\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n");
	}

	
	return 0;
}
