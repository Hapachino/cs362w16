/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Unit test for: shuffle()
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

 
int main () {
	int i, j;
	int result;				//return value for function calls
	int failed, changed;	//flags for tests
	int cardsBefore[treasure_map];	//cards in hand before shuffle
	int cardsAfter[treasure_map];	//cards in hand after shuffle
	
	struct gameState *g = malloc(sizeof(struct gameState));		//working game state
	struct gameState *pre = malloc(sizeof(struct gameState));	//reference game state; stored before functions run
	int selectedCards[10] = {adventurer, council_room, feast, gardens, mine, smithy, village, tribute, salvager, sea_hag};	
	int seed = 10;

	printf("---Testing shuffle()---\n");
	
	//---Test deckCount = 0
	//---Expected result: error
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Draw all cards in deck
	while (g->deckCount[whoseTurn(g)] > 0){
		drawCard(whoseTurn(g), g);
	}	
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to shuffle
	result = shuffle(whoseTurn(g), g);
	failed = 0;
	if (result != -1){
		printf("FAIL when deckCount = 0\n");
		printf("  Return value: %d, Expected: %d\n", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL when deckCount = 0\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Final check
	if (!failed){
		printf("PASS when deckCount = 0\n");
	}	
	

	//---Test deckCount = 1
	//---Expected result: gameState is unchanged
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Draw all cards but 1 in deck
	while (g->deckCount[whoseTurn(g)] > 1){
		drawCard(whoseTurn(g), g);
	}	
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Run shuffle and check results
	failed = 0;
	result = shuffle(whoseTurn(g), g);
	if (result == -1){
		printf("FAIL when deckCount = 1\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	} 
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL when deckCount = 1\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Final check
	if (!failed){
		printf("PASS when deckCount = 1\n");
	}
	
	
	//---Test deckCount > 1
	/*---Expected results: 
	     - Game and turn settings are unchanged
		 - Other player's cards (hand, deck, discard) are unchanged
		 - Current player's hand and discard are unchanged
		 - Played cards are unchanged
		 - Current player's deck Count is unchanged
		 - Current player's deck contains same cards as before shuffle
		 - Current player's deck cards are in different order than before shuffle
	*/
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	} 
	//Confirm deckCount > 1
	if (g->deckCount[whoseTurn(g)] <= 1){
		printf("Could not create suitable game. Testing aborted.\n");
		return -1;
	}		
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Initialize card count arrays
	for (i = 0; i < treasure_map; i++){
		cardsAfter[i] = 0;
		cardsBefore[i] = 0;
	}
	//Get before deck card counts
	for (i = 0; i < g->deckCount[(whoseTurn(g))]; i++){
		cardsBefore[g->deck[whoseTurn(g)][i]]++;
	}
	//Run shuffle and check results
	failed = 0;
	result = shuffle(whoseTurn(g), g);
	if (result == -1){
		printf("FAIL when deckCount > 1\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  NumPlayers: %d, Expected: %d\n", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkSupply(pre, g);
	if (result != 0){
		printf("FAIL when deckCount > 1\n");
		printf("  Supply count for card %d: %d, Expected: %d\n", result, g->supplyCount[result], pre->supplyCount[result]);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("FAIL when deckCount > 1\n");
		printf("  Embargo for card %d: %d, Expected: %d\n", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  outpostPlayed: %d, Expected: %d\n", g->outpostPlayed, pre->outpostPlayed);
		printf("  outpostTurn: %d, Expected: %d\n", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  whoseTurn: %d, Expected: %d\n", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkPhase(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  phase: %d, Expected: %d\n", g->phase, pre->phase);
		failed = 1;
	}	
	if (checkNumActions(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  numActions: %d, Expected: %d\n", g->numActions, pre->numActions);
		failed = 1;
	}	
	if (checkCoins(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  coins: %d, Expected: %d\n", g->coins, pre->coins);
		failed = 1;
	}
	if (checkNumBuys(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  numBuys: %d, Expected: %d\n", g->numBuys, pre->numBuys);
		failed = 1;
	}
	//Check all hand, discard, play cards unchanged
	if (checkHands(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  Hands changed after shuffle\n");
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
	if (checkDiscards(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  Discards changed after shuffle\n");
		//Print expected and actual discards for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Discard pile for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->discardCount[i], pre->discardCount[i]);
			if (g->discardCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->discardCount[i]; j++){
					printf("%d ", g->discard[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->discardCount[i]; j++){
					printf("%d ", pre->discard[i][j]);
				}
				printf("\n");
			}
		}
		failed = 1;
	}
	if (checkPlayed(pre, g) < 0){
		printf("FAIL when deckCount > 1\n");
		printf("  Played cards changed after shuffle\n");
		//Print expected and actual discards for each player
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
	//Check deck unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->deckCount[i] != g->deckCount[i]){
			printf("FAIL when deckCount > 1\n");
			printf("  Player %d's deckCount: %d, Expected: %d\n", i, g->deckCount[i], pre->deckCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->deckCount[i]; j++){
				if (pre->deck[i][j] != g->deck[i][j]){
					printf("FAIL when deckCount > 1\n");
					printf("  Player %d's deck[%d]: %d, Expected: %d\n", i, j, g->deck[i][j], pre->deck[i][j]);
					failed = 1;
				}
			}
		}
	}
	//Check current player's deck is same size
	if (pre->deckCount[whoseTurn(g)] != g->deckCount[whoseTurn(g)]){
		printf("FAIL when deckCount > 1\n");
		printf("  Current player's deckCount: %d, Expected: %d\n", g->deckCount[whoseTurn(g)], pre->deckCount[whoseTurn(g)]);
		failed = 1;
	}
	//Check current player's deck contains same cards as before
	for (i = 0; i < g->deckCount[(whoseTurn(g))]; i++){
		cardsAfter[g->deck[whoseTurn(g)][i]]++;
	}	
	for (i = 0; i < treasure_map; i++){
		if (cardsBefore[i] != cardsAfter[i]){
			printf("FAIL when deckCount > 1\n");
			printf("  Count for card %d in deck: %d, Expected: %d\n", i, cardsAfter[i], cardsBefore[i]);
			failed = 1;
			break;
		}
	}
	//Check current player's deck has cards in different order than before
	if (pre->deckCount[whoseTurn(g)] == g->deckCount[whoseTurn(g)]){
		changed = 0;
		for (i = 0; i < g->deckCount[whoseTurn(g)]; i++){
			if (pre->deck[whoseTurn(g)][i] != g->deck[whoseTurn(g)][i]){
				changed = 1;
				break;
			}
		}
		if (!changed){
			printf("FAIL when deckCount > 1\n");
			printf("  Cards in current player's deck not shuffled\n");
			failed = 1;
		}
	}
	//Final check
	if (!failed){
		printf("PASS when deckCount > 1\n");
	}
	
	return 0;
}
