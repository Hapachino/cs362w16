/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Unit test for: shuffle()
*/

#include "dominion.h"
#include "dominion_helpers.h"
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
	//Attempt to shuffle
	result = shuffle(whoseTurn(g), g);
	if (result == -1){
		printf("shuffle(): PASS when deckCount = 0\n");
	} else {
		printf("shuffle(): FAIL when deckCount = 0\n");
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
		printf("shuffle(): FAIL when deckCount = 1\n");
		printf("\tFailure: function returned error when expecting success\n");
		failed = 1;
	} 
	//Check game state is unchanged
	if (memcmp(pre, g, sizeof(struct gameState)) != 0){
		printf("shuffle(): FAIL when deckCount = 1\n");
		printf("\tFailure: gameState changed after shuffle\n");
		failed = 1;
	} 
	//Final check
	if (!failed){
		printf("shuffle(): PASS when deckCount = 1\n");
	}
	
	
	//---Test deckCount > 1
	/*---Expected results: 
	     - Game and turn settings are unchanged
		 - Other player's cards (hand, deck, discard, played) are unchanged
		 - Current player's hand, discard and played are unchanged
		 - Deck Count is unchanged
		 - Deck contains same cards as before shuffle
		 - Deck cards are in different order than before shuffle
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
	//Initialize cards arrays
	for (i = 0; i < treasure_map; i++){
		cardsAfter[i] = 0;
		cardsBefore[i] = 0;
	}
	//Save current hand card counts
	for (i = 0; i < g->handCount[(whoseTurn(g))]; i++){
		cardsBefore[g->hand[whoseTurn(g)][i]]++;
	}
	//Run shuffle and check results
	failed = 0;
	result = shuffle(whoseTurn(g), g);
	if (result == -1){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: function returned error when expecting success\n");
		failed = 1;
	}
	//Check game/turn settings
	if (pre->numPlayers != g->numPlayers){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: numPlayers changed after shuffle\n");
		failed = 1;
	}
	for (i = 0; i <= treasure_map; i++){
		if (pre->supplyCount[i] != g->supplyCount[i]){
			printf("shuffle(): FAIL when deckCount > 1\n");
			printf("\tFailure: supplyCount changed after shuffle\n");
			failed = 1;
			break;
		}
	}
	for (i = 0; i <= treasure_map; i++){
		if (pre->embargoTokens[i] != g->embargoTokens[i]){
			printf("shuffle(): FAIL when deckCount > 1\n");
			printf("\tFailure: embargoTokens changed after shuffle\n");
			failed = 1;
			break;
		}
	}
	if (pre->outpostPlayed != g->outpostPlayed){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: outpostPlayed changed after shuffle\n");
		failed = 1;
	}
	if (pre->outpostTurn != g->outpostTurn){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: outpostTurn changed after shuffle\n");
		failed = 1;
	}	
	if (pre->whoseTurn != g->whoseTurn){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: whoseTurn changed after shuffle\n");
		failed = 1;
	}
	if (pre->phase != g->phase){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: phase changed after shuffle\n");
		failed = 1;
	}	
	if (pre->numActions != g->numActions){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: numActions changed after shuffle\n");
		failed = 1;
	}	
	if (pre->coins != g->coins){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: coins changed after shuffle\n");
		failed = 1;
	}
	if (pre->numBuys != g->numBuys){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: numBuys changed after shuffle\n");
		failed = 1;
	}
	//Check all hand, discard, play cards unchanged
	//hand
	for (i = 0; i < g->numPlayers; i++){
		if (pre->handCount[i] != g->handCount[i]){
			printf("shuffle(): FAIL when deckCount > 1\n");
			printf("\tFailure: handCounts changed after shuffle\n");
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->handCount[i]; j++){
				if (pre->hand[i][j] != g->hand[i][j]){
					printf("shuffle(): FAIL when deckCount > 1\n");
					printf("\tFailure: hands changed after shuffle\n");
					failed = 1;
				}
			}
		}
	}
	//discard
	for (i = 0; i < g->numPlayers; i++){
		if (pre->discardCount[i] != g->discardCount[i]){
			printf("shuffle(): FAIL when deckCount > 1\n");
			printf("\tFailure: discardCounts changed after shuffle\n");
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->discardCount[i]; j++){
				if (pre->discard[i][j] != g->discard[i][j]){
					printf("shuffle(): FAIL when deckCount > 1\n");
					printf("\tFailure: discards changed after shuffle\n");
					failed = 1;
				}
			}
		}
	}
	//played
	if (pre->playedCardCount != g->playedCardCount){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: playedCardCounts changed after shuffle\n");
		failed = 1;
	} else {   //check each card
		for (i = 0; i < g->playedCardCount; i++){
			if (pre->playedCards[i] != g->playedCards[i]){
				printf("shuffle(): FAIL when deckCount > 1\n");
				printf("\tFailure: playedCards changed after shuffle\n");
				failed = 1;
			}
		}
	}
	//Check deck unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->deckCount[i] != g->deckCount[i]){
			printf("shuffle(): FAIL when deckCount > 1\n");
			printf("\tFailure: other's deckCounts changed after shuffle\n");
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->deckCount[i]; j++){
				if (pre->deck[i][j] != g->deck[i][j]){
					printf("shuffle(): FAIL when deckCount > 1\n");
					printf("\tFailure: other's decks changed after shuffle\n");
					failed = 1;
				}
			}
		}
	}
	//Check current player's deck is same size
	if (pre->deckCount[whoseTurn(g)] != g->deckCount[whoseTurn(g)]){
		printf("shuffle(): FAIL when deckCount > 1\n");
		printf("\tFailure: player's deckCount changed after shuffle\n");
		failed = 1;
	}
	//Check current player's deck contains same cards as before
	for (i = 0; i < g->handCount[(whoseTurn(g))]; i++){
		cardsAfter[g->hand[whoseTurn(g)][i]]++;
	}	
	for (i = 0; i < treasure_map; i++){
		if (cardsBefore[i] != cardsAfter[i]){
			printf("shuffle(): FAIL when deckCount > 1\n");
			printf("\tFailure: cards in player's deck changed after shuffle\n");
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
			printf("shuffle(): FAIL when deckCount > 1\n");
			printf("\tFailure: cards in player's deck not shuffled\n");
			failed = 1;
		}
	}
	//Final check
	if (!failed){
		printf("shuffle(): PASS when deckCount > 1\n");
	}
	
	return 0;
}
