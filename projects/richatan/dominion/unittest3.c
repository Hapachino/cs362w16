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

	printf("---Testing buyCard()---\n");
	
//---Test numBuys = 0 
//---Expected result: error
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
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
		printf("FAIL when numBuys = 0\n");
		printf("  Return value: %d, Expected: %d\n", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL when numBuys = 0\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Final check
	if (!failed){
		printf("PASS when numBuys = 0\n");
	}

	
//---Test no supply remaining 
//---Expected result: error
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
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
		printf("FAIL when supplyCount = 0\n");
		printf("  Return value: %d, Expected: %d\n", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL when supplyCount = 0\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Final check
	if (!failed){
		printf("PASS when supplyCount = 0\n");
	}	
	

//---Test insufficient funds
//---Expected result: error
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
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
		printf("FAIL when coins < cost\n");
		printf("  Return value: %d, Expected: %d\n", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL when coins < cost\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Final check
	if (!failed){
		printf("PASS when coins < cost\n");
	}	

	
//---Test invalid supply position
//---Expected result: error
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to buy card at invalid position
	result = buyCard(treasure_map+1, g);
	failed = 0;
	if (result != -1){
		printf("FAIL invalid position check\n");
		printf("  Return value: %d, Expected: %d\n", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL invalid position check\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Final check
	if (!failed){
		printf("PASS invalid position check\n");
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
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
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
		printf("FAIL valid buy\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("FAIL valid buy\n");
		printf("  NumPlayers: %d, Expected: %d\n", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("FAIL valid buy\n");
		printf("  Embargo for card %d: %d, Expected: %d\n", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("FAIL valid buy\n");
		printf("  outpostPlayed: %d, Expected: %d\n", g->outpostPlayed, pre->outpostPlayed);
		printf("  outpostTurn: %d, Expected: %d\n", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("FAIL valid buy\n");
		printf("  whoseTurn: %d, Expected: %d\n", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkNumActions(pre, g) < 0){
		printf("FAIL valid buy\n");
		printf("  numActions: %d, Expected: %d\n", g->numActions, pre->numActions);
		failed = 1;
	}	
	//Check phase = 1
	if (g->phase != 1){
		printf("FAIL valid buy\n");
		printf("  phase: %d, Expected: %d\n", g->phase, 1);
		failed = 1;
	}	
	//Check coins = coins_before - cost of card
	if (g->coins != pre->coins - getCost(TEST_CARD)){
		printf("FAIL valid buy\n");
		printf("  coins: %d, Expected: %d\n", g->coins, pre->coins - getCost(TEST_CARD));
		failed = 1;
	}
	//Check numBuys decreased by 1
	if (g->numBuys != pre->numBuys - 1){
		printf("FAIL valid buy\n");
		printf("  numBuys: %d, Expected: %d\n", g->numBuys, pre->numBuys - 1);
		failed = 1;
	}
	//Check supply for bought card is decreased by 1
	if (g->supplyCount[TEST_CARD] != pre->supplyCount[TEST_CARD]-1){
		printf("FAIL valid buy\n");
		printf("  Supply count for card %d: %d, Expected: %d\n", TEST_CARD, g->supplyCount[TEST_CARD], pre->supplyCount[TEST_CARD]-1);
		failed = 1;
	}
	//Check supply for other cards remains the same
	for (i = 0; i <= treasure_map; i++){
		//if test card, skip
		if (i == TEST_CARD){
			continue;
		}
		if (pre->supplyCount[i] != g->supplyCount[i]){
			printf("FAIL valid buy\n");
			printf("  Supply count for card %d: %d, Expected: %d\n", i, g->supplyCount[i], pre->supplyCount[i]);
			failed = 1;
		}
	}
	//Check all hand, deck and played cards unchanged
	if (checkHands(pre, g) < 0){
		printf("FAIL valid buy\n");
		printf("  Hands changed after buyCard\n");
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
				printf("\n");
			}
		}
		failed = 1;
	}
	if (checkDecks(pre, g) < 0){
		printf("FAIL valid buy\n");
		printf("  Decks changed after buyCard\n");
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
				printf("\n");
			}
		}
		failed = 1;
	}
	if (checkPlayed(pre, g) < 0){
		printf("FAIL valid buy\n");
		printf("  Played cards changed after buyCard\n");
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
			printf("\n");
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
			printf("FAIL valid buy\n");
			printf("  Player %d's discardCount: %d, Expected: %d\n", i, g->discardCount[i], pre->discardCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->discardCount[i]; j++){
				if (pre->discard[i][j] != g->discard[i][j]){
					printf("FAIL valid buy\n");
					printf("  Player %d's discard[%d]: %d, Expected: %d\n", i, j, g->discard[i][j], pre->discard[i][j]);
					failed = 1;
				}
			}
		}
	}	
	//Check current player's discardCount increased by 1
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)]+1){
			printf("FAIL valid buy\n");
			printf("  Current player's discardCount: %d, Expected: %d\n", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)]+1);
			failed = 1;
	}
	//Check current player's discard contains same cards plus new card in last position
	for (i = 0; i < g->discardCount[whoseTurn(g)]-1; i++){
		if (pre->discard[whoseTurn(g)][i] != g->discard[whoseTurn(g)][i]){
			printf("FAIL valid buy\n");
			printf("  Current player's discard[%d]: %d, Expected: %d\n", i, g->discard[whoseTurn(g)][i], pre->discard[whoseTurn(g)][i]);
			failed = 1;
		}
	}
	if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1] != TEST_CARD){
		printf("FAIL valid buy\n");
		printf("  Gained card: %d, Expected: %d\n", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1], TEST_CARD);
		failed = 1;		
	}
	
	//Final check
	if (!failed){
		printf("PASS valid buy\n");
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
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
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
		printf("FAIL buy with embargo\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("FAIL buy with embargo\n");
		printf("  NumPlayers: %d, Expected: %d\n", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("FAIL buy with embargo\n");
		printf("  outpostPlayed: %d, Expected: %d\n", g->outpostPlayed, pre->outpostPlayed);
		printf("  outpostTurn: %d, Expected: %d\n", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("FAIL buy with embargo\n");
		printf("  whoseTurn: %d, Expected: %d\n", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkNumActions(pre, g) < 0){
		printf("FAIL buy with embargo\n");
		printf("  numActions: %d, Expected: %d\n", g->numActions, pre->numActions);
		failed = 1;
	}	
	//Check phase = 1
	if (g->phase != 1){
		printf("FAIL buy with embargo\n");
		printf("  phase: %d, Expected: %d\n", g->phase, 1);
		failed = 1;
	}	
	//Check coins = coins_before - cost of card
	if (g->coins != pre->coins - getCost(TEST_CARD)){
		printf("FAIL buy with embargo\n");
		printf("  coins: %d, Expected: %d\n", g->coins, pre->coins - getCost(TEST_CARD));
		failed = 1;
	}
	//Check numBuys decreased by 1
	if (g->numBuys != pre->numBuys - 1){
		printf("FAIL buy with embargo\n");
		printf("  numBuys: %d, Expected: %d\n", g->numBuys, pre->numBuys - 1);
		failed = 1;
	}
	//Check supply for bought card is decreased by 1
	if (g->supplyCount[TEST_CARD] != pre->supplyCount[TEST_CARD]-1){
		printf("FAIL buy with embargo\n");
		printf("  Supply count for card %d: %d, Expected: %d\n", TEST_CARD, g->supplyCount[TEST_CARD], pre->supplyCount[TEST_CARD]-1);
		failed = 1;
	}
	//Check supply for curse card is decreased by 1
	if (g->supplyCount[0] != pre->supplyCount[0]-1){
		printf("FAIL buy with embargo\n");
		printf("  Supply count for curse card: %d, Expected: %d\n", g->supplyCount[0], pre->supplyCount[0]-1);
		failed = 1;
	}
	//Check supply for other cards remains the same
	for (i = 1; i <= treasure_map; i++){
		//if test card, skip
		if (i == TEST_CARD){
			continue;
		}
		if (pre->supplyCount[i] != g->supplyCount[i]){
			printf("FAIL buy with embargo\n");
			printf("  Supply count for card %d: %d, Expected: %d\n", i, g->supplyCount[i], pre->supplyCount[i]);
			failed = 1;
		}
	}
	//Check embargo tokens for bought card is decreased by 1
	if (g->embargoTokens[TEST_CARD] != pre->embargoTokens[TEST_CARD]-1){
		printf("FAIL buy with embargo\n");
		printf("  Embargo tokens for card %d: %d, Expected: %d\n", TEST_CARD, g->embargoTokens[TEST_CARD], pre->embargoTokens[TEST_CARD]-1);
		failed = 1;
	}
	//Check embargo tokens for other cards remains the same
	for (i = 0; i <= treasure_map; i++){
		//if test card, skip
		if (i == TEST_CARD){
			continue;
		}
		if (pre->embargoTokens[i] != g->embargoTokens[i]){
			printf("FAIL buy with embargo\n");
			printf("  Embargo tokens for card %d: %d, Expected: %d\n", i, g->embargoTokens[i], pre->embargoTokens[i]);
			failed = 1;
		}
	}
	//Check all hand, deck and played cards unchanged
	if (checkHands(pre, g) < 0){
		printf("FAIL buy with embargo\n");
		printf("  Hands changed after buyCard\n");
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
				printf("\n");
			}
		}
		failed = 1;
	}
	if (checkDecks(pre, g) < 0){
		printf("FAIL buy with embargo\n");
		printf("  Decks changed after buyCard\n");
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
				printf("\n");
			}
		}
		failed = 1;
	}
	if (checkPlayed(pre, g) < 0){
		printf("FAIL buy with embargo\n");
		printf("  Played cards changed after buyCard\n");
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
			printf("\n");
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
			printf("FAIL buy with embargo\n");
			printf("  Player %d's discardCount: %d, Expected: %d\n", i, g->discardCount[i], pre->discardCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->discardCount[i]; j++){
				if (pre->discard[i][j] != g->discard[i][j]){
					printf("FAIL buy with embargo\n");
					printf("  Player %d's discard[%d]: %d, Expected: %d\n", i, j, g->discard[i][j], pre->discard[i][j]);
					failed = 1;
				}
			}
		}
	}	
	//Check current player's discardCount increased by 2
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)]+2){
			printf("FAIL buy with embargo\n");
			printf("  Current player's discardCount: %d, Expected: %d\n", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)]+2);
			failed = 1;
	}
	//Check current player's discard contains same cards plus new card and curse in last two positions
	for (i = 0; i < g->discardCount[whoseTurn(g)]-2; i++){
		if (pre->discard[whoseTurn(g)][i] != g->discard[whoseTurn(g)][i]){
			printf("FAIL buy with embargo\n");
			printf("  Current player's discard[%d]: %d, Expected: %d\n", i, g->discard[whoseTurn(g)][i], pre->discard[whoseTurn(g)][i]);
			failed = 1;
		}
	}
	if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1] == TEST_CARD){
		if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-2] != 0){
			printf("FAIL buy with embargo\n");
			printf("  Gained card: %d, Expected: %d\n", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1], 0);
			failed = 1;		
		}
	} else if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1] == 0){
		if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-2] != TEST_CARD){
			printf("FAIL buy with embargo\n");
			printf("  Gained card: %d, Expected: %d\n", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1], TEST_CARD);
			failed = 1;		
		}
	} else {
		printf("FAIL buy with embargo\n");
		printf("  Gained card: %d, Expected: %d or %d\n", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1], TEST_CARD, 0);
		failed = 1;			
	}
	
	//Final check
	if (!failed){
		printf("PASS buy with embargo\n");
	}

	
	return 0;
}
