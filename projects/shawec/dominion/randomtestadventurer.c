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
	int ret;
	int coins;
	int shuffle;
	int discardPos;
	int deckPos;

	srand(100);
	
	system("clear"); 
	printf ("Testing myAdventurer()\n=======================================================\n");
#if (VERBOSE == 1)
	printf("Verbose mode.\n", seed);
#endif	
	for (j = 0; j < 100000; j++){
		
		shuffle = 0;
		discardPos = 0;	 
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
		//see if there are two treasure cards in deck
		//if there are not, then shuffle = 1 and then check to see if there are at least two cards in deck, if not, then deck
		coins = 0;
		deckPos = 0;
		for (i = Game.deckCount[player] -1; i >= 0 ; i--){
			//printf("%d, ", Game.deck[player][i]);
			if ((Game.deck[player][i] == copper || Game.deck[player][i] == silver || Game.deck[player][i] == gold)){
				coins++;
			}
			deckPos++;
			if (coins >= 2){
				break;
			}	
		}
		//printf("\n");
		//printf("Test: %d, deckPos: %d, deck Count: %d\n", j, deckPos, Game.deckCount[player]);
		if (deckPos == Game.deckCount[player]){
			shuffle = 1;
			for (i = Game.discardCount[player] - 1; i >= 0; i--){
				if ((Game.discard[player][i] == 4 || Game.discard[player][i] == 5 || Game.discard[player][i] == 6)){
					coins++;
				}
				discardPos++;	
				if (coins >= 2){
					break;
				}
			}
		}
		
		//play card
		ret = myAdventurer(&Game, player);
		   
		//check oldDeckSize - deckpos == new decksize if shuffle == 0 && handcount != 0
		if (shuffle != 1){
			if (Test.deckCount[player] - deckPos != Game.deckCount[player]){
				printf("Test: %d, deckPos: %d, Test count: %d, deck Count: %d, shuffle: %d\n", j, deckPos, Test.deckCount[player], Game.deckCount[player], shuffle);
				printf("Error - difference in deck size. Difference: %d\n", Test.deckCount[player] - Game.deckCount[player]);
			}
			//everything but two cards, + one card for discarding smithy
			if (Game.discardCount[player] != deckPos - 2 + Test.discardCount[player]){
				printf("Error - difference in discard size. Difference: %d\n", Test.discardCount[player] - Game.discardCount[player]);
			}
		}
		
		
		//testing shuffle consitions
		else if(shuffle == 1){
			//d
			if (Game.discardCount[player] != 0){
				//not yet implemented, hoewver not really needed to achieve full coverage :( 
			}
			
		}
		//printf("\n");
		//free(Game); // Did someone say, memory leaks? I love memory leaks! (sarcastic)
	}


	printf("\n=======================================================\nTesting finished for Adventurer\n\n");
	
	return 0;
}

/*int myAdventurer(struct gameState *state, int currentPlayer){
	
	int z = 0;
	int temphand[MAX_HAND];
	int drawntreasure = 0;
	int cardDrawn;
	
	while( drawntreasure < 2){
		if (state->deckCount[currentPlayer] <= 1){
			//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1]; //top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
			drawntreasure++;
		}
		else{
			temphand[z] = cardDrawn;
			state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		}
	}
	while(z - 1 >= 0){
		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z-1]; // discard all cards in play that have been drawn
		z = z - 1;
	}
	return 0;
}
*/




