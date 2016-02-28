#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0
#define NUM_KCARDS 20
#define TEST_CARD adventurer
#define NUM_TESTS 50


int getCoinCount(struct gameState *game, int player) {
	int i;
	int coinCount = 0;
	for (i = 0; i < game->deckCount[player]; i++) {
		if ((game->deck[player][i] == copper) || (game->deck[player][i] == silver) || (game->deck[player][i] == gold)) {
			coinCount++;
		}
	}
	for (i = 0; i < game->discardCount[player]; i++) {
		if ((game->discard[player][i] == copper) || (game->discard[player][i] == silver) || (game->discard[player][i] == gold)) {
			coinCount++;
		}
	}
	return coinCount;
}


int main() {
	int h, i, j, k, available;
	int numPlayers, handPos, randomSeed;
	int hand, deck, discard, playCard, gainedCard;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int error1 = 0, error2 = 0, error3 = 0, error4 = 0, error5 = 0, error6 = 0, error7 = 0;
	int e2array[NUM_TESTS], e4array[NUM_TESTS];
	int counter = 0, check = -1;
	int kCards[10], supply[17];
	struct gameState pre, post;

	//seed random number generator
	srand(time(NULL));
	
	//start testing loop
	for (h = 0; h < NUM_TESTS; h++) {
		//initialize variables
		counter = 0;
		check = -1;
		numPlayers = (rand() % 3) + 2;
		handPos = -1;
		randomSeed = (rand() % 100);

		//randomize kingdom cards chosen to initialize the game
		for (i = 0; i < 10; i++) {
			kCards[i] = -1;
		}
		while (counter < 10) {
			available = 0;
			k = (rand() % NUM_KCARDS) + 7;
			for (i = 0; i < counter; i++) {
				if (kCards[i] == k) {
					available = -1;
					i = 10;
				}
			}
			if (available == 0) {
				kCards[counter] = k;
				counter++;
			}
		}
		
		//check if TEST_CARD is in kingdom card array. If not in list, replace one entry with the TEST_CARD
		for (i = 0; i < 10; i++) {
			if (kCards[i] == TEST_CARD) {
				check = 1;
				i = 10;
			}
		}
		if (check != 1) {
			kCards[rand() % 10] = TEST_CARD;
		}
		
		
		for (i = 0; i < 10; i++) {
			supply[i] = kCards[i];
		}
		supply[10] = copper;
		supply[11] = silver;
		supply[12] = gold;
		supply[13] = curse;
		supply[14] = estate;
		supply[15] = duchy;
		supply[16] = province;
		
		//initialize game with random # of players and randomly generated kingdom card list
		initializeGame(numPlayers, kCards, randomSeed, &post);
		
		//randomize player hands, decks, and discard piles
		for (i = 0; i < numPlayers; i++) {
			//remove all cards from player's hand
			for (j = 0; j < post.handCount[i]; j++) {
				post.hand[i][j] = -1;
			}
			
			//create random hand, deck, and discard sizes for each player and fill up those piles with cards from the supply
			//made hand, deck, and discard piles a max of 24 cards so that the odds are higher we will test multiple cases where a player has a combined 0 or 1 coin in their deck and discard piles
			hand = rand() % 25 + 1; //ensure at least one card in hand since needs to play adventurer card
			deck = rand() % 25;
			discard = rand() % 25;

			post.handCount[i] = hand;
			post.deckCount[i] = deck;
			post.discardCount[i] = discard;
			
			//assign random cards to player's hand, deck, and discard
			for (j = 0; j < MAX_HAND; j++) {
				if (j < hand) {
					post.hand[i][j] = supply[rand() % 17];
				}
				else {
					post.hand[i][j] = -1;
				}
			}
			for (j = 0; j < MAX_DECK; j++) {
				if (j < deck) {
					post.deck[i][j] = supply[rand() % 17];
				}
				else {
					post.deck[i][j] = -1;
				}
			}
			for (j = 0; j < MAX_DECK; j++) {
				if (j < discard) {
					post.discard[i][j] = supply[rand() % 17];
				}
				else {
					post.discard[i][j] = -1;
				}
			}
		}
		
		//randomly generate the amount of supplies left
		//kingdom cards
		for (i = 0; i < 10; i++) {
			if (supply[i] == great_hall || supply[i] == gardens) {
				if (numPlayers == 2) {
					post.supplyCount[supply[i]] = rand() % 8;
				}
				else {
					post.supplyCount[supply[i]] = rand() % 12;
				}
			}
			else {
				post.supplyCount[supply[i]] = rand() % 10;
			}
		}
		//treasure cards
		post.supplyCount[supply[10]] = rand() % 60;
		post.supplyCount[supply[11]] = rand() % 40;
		post.supplyCount[supply[12]] = rand() % 30;
		//curse cards
		if (numPlayers == 2) {
			post.supplyCount[supply[13]] = rand() % 10;
		}
		else if (numPlayers == 3) {
			post.supplyCount[supply[13]] = rand() % 20;
		}
		else { //numPlayers == 4
			post.supplyCount[supply[13]] = rand() % 30;
		}
		//victory cards
		for (i = 14; i < 17; i++) {
			if (numPlayers == 2) {
				post.supplyCount[supply[i]] = rand() % 8;
			}
			else {
				post.supplyCount[supply[i]] = rand() % 12;
			}
		}
		
		//randomly determine which player's turn it is
		post.whoseTurn = rand() % numPlayers;	
			
		//ensure TEST_CARD is in player's hand (if not place it there) and set handPos
		for (i = 0; i < post.handCount[post.whoseTurn]; i++) {
			if (post.hand[post.whoseTurn][i] == TEST_CARD) {
				handPos = i;
				i = post.handCount[post.whoseTurn];
			}
		}
		if (handPos == -1) { //TEST_CARD not in current player's hand
			handPos = rand() % post.handCount[post.whoseTurn];
			post.hand[post.whoseTurn][handPos] = TEST_CARD;
		}
		
		//copy randomized game state to pre before testing card
		memcpy(&pre, &post, sizeof(struct gameState));
		
		//play card and check for error
		playCard = cardEffect(adventurer, choice1, choice2, choice3, &post, handPos, &bonus);
		if ((playCard < -1) || (playCard > 1)){
			error1++;
		}
		
		//Check that current player handCount increased by 1 (+2 for added coins, -1 for playing adventurer) when player has 2 or more coins combined in deck and discard
		if (getCoinCount(&pre, pre.whoseTurn) >= 2) {
			if (post.handCount[pre.whoseTurn] != pre.handCount[pre.whoseTurn]+1) {
				e2array[error2] = getCoinCount(&pre, pre.whoseTurn);
				error2++;
			}
		}
		//Check that current player handCount remained the same (+1 for added coin, -1 for playing adventurer) when player has 1 coin combined in deck and discard
		else if (getCoinCount(&pre, pre.whoseTurn) == 1) {
			if (post.handCount[pre.whoseTurn] != pre.handCount[pre.whoseTurn]) {
				e2array[error2] = getCoinCount(&pre, pre.whoseTurn);
				error2++;
			}
		}
		//Check that current player handCount decreased by 1 (+0 for added coin, -1 for playing adventurer) when player has 1 coin combined in deck and discard
		else {//getCoinCount == 0
			if (post.handCount[pre.whoseTurn] != pre.handCount[pre.whoseTurn]-1) {
				e2array[error2] = getCoinCount(&pre, pre.whoseTurn);
				error2++;
			}
		}
		
		//Check that adventurer card added to played pile and playedCardCount incremented by 1
		if  ((post.playedCards[pre.playedCardCount] != adventurer) && (post.playedCardCount != pre.playedCardCount + 1)) {
			error3++;
		}

		//Check that gained cards added to hand are coins
		gainedCard = post.hand[pre.whoseTurn][post.handCount[pre.whoseTurn]-2];
		if ((gainedCard != copper) && (gainedCard != silver) && (gainedCard != gold)) {
			//if failed check if had 2 or more coins in deck and discard piles combined
			if (getCoinCount(&pre, pre.whoseTurn) >= 2) { //if only 0 or 1 coin to draw, then not an error
				e4array[error4] = getCoinCount(&pre, pre.whoseTurn);
				error4++;
			}
		}
		else { //correctly drew a coin the first time, so check second card drawn
			gainedCard = post.hand[pre.whoseTurn][post.handCount[pre.whoseTurn]-1];
			if ((gainedCard != copper) && (gainedCard != silver) && (gainedCard != gold)) {
				//if failed check if had 2 or more coins in deck and discard piles combined
				if (getCoinCount(&pre, pre.whoseTurn) >= 1) { //if only 0 coins to draw, then not an error
					e4array[error4] = getCoinCount(&pre, pre.whoseTurn);
					error4++;
				}
			}
		}
		//Check that other player's deckCount, handCount, and discardCount were not changed
		for (i = 0; i < numPlayers; i++) {
			if (i != pre.whoseTurn) {
				if (post.deckCount[i] != pre.deckCount[i]) {
					error5++;
					i = numPlayers;
				}
			}
		}
		for (i = 0; i < numPlayers; i++) {
			if (i != pre.whoseTurn) {
				if (post.handCount[i] != pre.handCount[i]) {
					error6++;
					i = numPlayers;
				}
			}
		}
		for (i = 0; i < numPlayers; i++) {
			if (i != pre.whoseTurn) {
				if (post.discardCount[i] != pre.discardCount[i]) {
					error7++;
					i = numPlayers;
				}
			}
		}	
	
	}
		
	//print results of testing
	printf("\n\n------------------Random Testing Results for Adventurer card------------------\n\n");
	if (error1 > 0) {
		printf("Function returned an unexpected value in %d out of %d tests.\n", error1, NUM_TESTS);
	}
	
	if (error2 > 0) {
		printf("In %d out of the %d tests, the card player's hand size did not update correctly (+1 card if there were at least 2 coins combined in deck and discard piles to be drawn; no change if only 1 coin combined in deck and discard piles to be drawn; and -1 if there were no coins combined in deck and discard piles to be drawn).\n", error2, NUM_TESTS);
		printf("The number of coins combined in the player's deck and discard pile for these failures was: %d", e2array[0]);
		for (i = 1; i < error2; i++) {
			printf(", %d", e2array[i]);
		}
		printf(".\n\n");
	}
	else {
		printf("Successfully updated player's hand size correctly during all tests.\n\n");
	}
	
	if (error3 > 0) {
		printf("In %d out of the %d tests, the adventurer card was not added to the played card pile and/or the played card count did not increment.\n\n", error3, NUM_TESTS);
	}
	else {
		printf("Successfully added adventurer card to played card pile and incremented the played card count during all tests.\n\n");
	}
	
	if (error4 > 0) {
		printf("In %d of the %d tests, the cards added to the player's hand were not coins.\n", error4, NUM_TESTS);
		printf("The number of coins combined in the player's deck and discard pile for these failures was: %d", e4array[0]);
		for (i = 1; i < error4; i++) {
			printf(", %d", e4array[i]);
		}
		printf(".\n\n");
	}
	else {
		printf("Successfully added only coins to player's hand during all tests.\n\n");
	}
	
	if (error5 > 0) {
		printf("In %d out of the %d tests, another player's deck size changed.\n\n", error5, NUM_TESTS);
	}
	else {
		printf("Successfully maintained all other player's deck sizes during all tests.\n\n");
	}
	
	if (error6 > 0) {
		printf("In %d out of the %d tests, another player's hand size changed.\n\n", error6, NUM_TESTS);
	}
	else {
		printf("Successfully maintained all other player's hand sizes during all tests.\n\n");
	}
	
	if (error7 > 0) {
		printf("In %d out of the %d tests, another player's discard pile size changed.\n\n", error7, NUM_TESTS);
	}
	else {
		printf("Successfully maintained all other player's discard pile sizes during all tests.\n\n");
	}
	
	printf("------------------Testing Complete for Adventurer card------------------\n\n");
	
	return 0;
}



/*	Initial hand, deck, and discard size code. Revised this so that there was a higher liklihood of having a combined 0 or 1 coin in a player's deck and discard piles
		//handCount + deckCount + discardCount <= MAX_DECK
		hand = rand() % (MAX_HAND + 1);
		if (hand != MAX_DECK) {
			deck = rand() % (MAX_DECK - hand + 1);
			if (hand + deck < MAX_DECK) {
				discard = rand() % (MAX_DECK - hand - deck + 1);
			}
			else {
				discard = 0;
			}
		}
		else {
			deck = 0;
			discard = 0;
		}
*/



/*  Debugging code	
		//print out random game condition
		printf("Random Game statistics:\nNumber of players: %d\n", numPlayers);
		printf("Kingdom Cards and Supply:\n");
		for (i = 0; i < 17; i++) {
			printf("Card: %d; Supply: %d\n", supply[i], pre.supplyCount[supply[i]]);
		}
		printf("\n");
		for (i = 0; i < numPlayers; i++) {
			
			printf("Player %d: Hand Size: %d; Deck Size: %d; Discard Size: %d\n", i+1, pre.handCount[i], pre.deckCount[i], pre.discardCount[i]); 
			printf("\tCombined Coins in Deck and Discard: %d\n", getCoinCount(&pre, i));
			printf("Deck and Discard: [");
			for (j = 0; j < pre.deckCount[i]; j++) {
				printf("%d, ", pre.deck[i][j]);
			}
			for (j = 0; j < pre.discardCount[i] - 1; j++) {
				printf("%d, ", pre.discard[i][j]);
			}
			if (j < pre.discardCount[i]) {
				printf("%d]\n\n", pre.discard[i][j]);
			}
			else {
				printf(" ]\n\n");
			}
	*/