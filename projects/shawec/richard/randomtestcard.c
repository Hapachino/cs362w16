/* -----------------------------------------------------------------------
 * Cierra Shawe 
 * CS362 - W16
 * card test 1, random adventurer test
 * Reveal cards from your deck until you reveal 2 Treasure cards. 
 * Put those Treasure cards in your hand.
 * Discard the other revealed cards.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

// set VERBOSE to 0 to remove printfs from output
#define VERBOSE 0


//Used for assigning a random card to hand, deck, trash, and discard
int randomCard(){
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int var;
	int c = (int)(rand() % 3); // for Bool of card or coin
	
	//If card 
	if (c == 0) {
		var = (int)(rand() % 10); //should have own var, oh well
		return k[var];
	}
	// If coin
	else {
		var = (int)(rand() % 3); // gives rand coin
		if (var == 0){
			return copper;
		}
	
		if (var == 1){
			return silver;
		}
	
		if (var == 2){
			return gold;
		}
		printf("\nUh oh. Something is wrong.\n");
	}
	
	return -1; //should never execute
}

//creates random gamestate
struct gameState setup(int players){
	//Things needed to init game
	struct gameState Game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1234;
	int player;
	int i;
	
	/* Set Up */

	// clear the game state
	memset(&Game, 23, sizeof(struct gameState));
	// initialize a new game   
	initializeGame(players, k, seed, &Game);
	
	for (player = 0; player < players; player++){
		Game.deckCount[player] = (int)(rand() % MAX_DECK/10);
		Game.discardCount[player] = (int)(rand() % MAX_DECK/10);
		Game.handCount[player] = (int)(rand() % MAX_HAND/10);
		
		/* The point is  */
		//assign random hand
		for (i = 0; i < Game.handCount[player]; i++) {
			Game.hand[player][i] = randomCard();
		}
		//assign random deck
		for (i = 0; i < Game.deckCount[player]; i++) {
			Game.deck[player][i] = randomCard();
			//printf("%d, ", Game.deck[player][i]);
		}
		//assign random discard pile
		for (i = 0; i < Game.discardCount[player]; i++) {
			Game.discard[player][i] = randomCard();
		}
		
	}
	//printf("\n");
	return Game;
	
}

int main() {
	
	struct gameState Game;
	struct gameState Test;
	// Other Variables
	int i;
	int j;
	int player;
	int players;

	srand(100);
	
	system("clear"); 
	printf ("Testing mySmithy()\n=======================================================\n");
#if (VERBOSE == 1)
	printf("Verbose mode.\n", seed);
#endif	
	for (j = 0; j < 10; j++){
		 
		// rand num of players
		players = (int)(rand() % 3) + 2; //4 players 0 = 2, 1 = 3, 2 = 4
		Game = setup(players); //set up cards
		player = (int)(rand() % players); //selects rAndom player
		Game.whoseTurn = player;
		// clear the game state

		memcpy(&Test, &Game, sizeof(struct gameState));	
		assert(Game.deckCount[player] == Test.deckCount[player]);
		
#if (VERBOSE == 1)
		printf("Test: %d, Players: %d, Hand Count: %d\n", j, players, handCount);
#endif
		//using this to ensure smithy is always in the hand
		Game.hand[player][Game.handCount[player]-1] = smithy;
		playSmithy(player, &Game, Game.handCount[player]-1);
		
		
		//game deck is down three cards
		if (Test.deckCount[player]  >= 3 && Game.deckCount[player] != Test.deckCount[player] -3){
			printf("Error - Deck Count is not as expected. Test: %d, Actual: %d, Expected: %d\n", j, Game.deckCount[player], Test.deckCount[player] -3);
		}
		//check hand is up two cards
		if (Game.handCount[player] != Test.handCount[player] + 2){
			printf("Error - Deck Count is not as expected. Test: %d, Actual: %d, Expected: %d\n", j, Game.handCount[player], Test.handCount[player] + 2);
		}
		//check discard is up one card (based on original number)
		if (Test.deckCount[player] >= 3){
			if (Game.discard[player][Game.discardCount[player]] != smithy){
				printf("Error - We have a Smithy on the loose! (aka, it's not where it should be.)\n");
			}
		}
		//testing if the deck count is less than three
		if (Test.deckCount[player] < 3){
			if (Test.deckCount[player] + Test.discardCount != Game.deckCount[player] + Game.discardCount[player] + 2){
				printf("Error - Discard Count is not as expected. Test: %d, Actual: %d, Expected: %d\n", j, Game.discardCount[player], 1);
			}
		}
		
		
		//printf("\n");
		//free(Game); // Did someone say, memory leaks? I love memory leaks! (sarcastic)
	}


	printf("\n=======================================================\nTesting finished for Smithy\n\n");
	
	return 0;
}

//bug introduced 
/*int mySmithy(struct gameState *state, int currentPlayer){
	
	int i;
	
	//+3 Cards
	for (i = 0; i <= 3; i++){
		drawCard(currentPlayer, state);
	}
	
	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
	
}
*/



