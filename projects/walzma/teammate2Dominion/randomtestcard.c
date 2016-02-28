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
#define TEST_CARD mine
#define NUM_TESTS 100

int main() {
	int h, i, j, k, available;
	int numPlayers, handPos, randomSeed, choice1, choice2;
	int hand, deck, discard, playCard, goodTrade, difference, choice2Supply, choice1Coin, choice2Coin;
	int choice3 = 0, bonus = 0, counter = 0, check = -1;
	int case1, case2, case3, case4, case5, case6, case7, case8, case9, case10, case11, case12, case13, case14, case15, case16, case17, case18;
	int numCase1 = 0, numCase2 = 0, numCase3 = 0, numCase4 = 0, numCase5 = 0, numCase6 = 0, numCase7 = 0, numCase8 = 0, numCase9 = 0, numCase10 = 0, numCase11 = 0, numCase12 = 0, numCase13 = 0, numCase14 = 0, numCase15 = 0, numCase16 = 0, numCase17 = 0, numCase18 = 0;
	int error1 = 0, e1c1 = 0, e1c2 = 0, e2c1 = 0, e2c2 = 0, e3c3 = 0, e3c9 = 0, e3c12 = 0, e3c18 = 0, e4c4 = 0, e4c5 = 0, e4c6 = 0, e4c13 = 0, e4c14 = 0, e4c15 = 0, e5c7 = 0, e5c8 = 0, e5c9 = 0, e5c16 = 0, e5c17 = 0, e5c18 = 0, e6c10 = 0, e6c11 = 0, e6c12 = 0, e6c13 = 0, e6c14 = 0, e6c15 = 0, e6c16 = 0, e6c17 = 0, e6c18 = 0, error7 = 0, error8 = 0, error9 = 0;
	int kCards[10], supply[17];
	struct gameState pre, post;

	//seed random number generator
	srand(time(NULL));

	
//---------------------Game State Initialization Code----------------------------------------------
	
	//start testing loop
	for (h = 0; h < NUM_TESTS; h++) {
		//initialize variables
		counter = 0;
		check = -1;
		numPlayers = (rand() % 3) + 2;
		handPos = -1;
		choice1 = -1;
		choice2 = -1;
		goodTrade = -1;
		difference = -1;
		choice2Supply = -1;
		choice1Coin = -1;
		choice2Coin = -1;
		case1 = -1;
		case2 = -1;
		case3 = -1;
		case4 = -1;
		case5 = -1;
		case6 = -1;
		case7 = -1;
		case8 = -1;
		case9 = -1;
		case10 = -1;
		case11 = -1;
		case12 = -1;
		case13 = -1;
		case14 = -1;
		case15 = -1;
		case16 = -1;
		case17 = -1;
		case18 = -1;
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
			//made hand, deck, and discard piles a max of 24 cards so that the odds are higher we will test multiple cases where a player has no coin in their hand
			hand = rand() % 25 + 2; //ensure at least two cards in hand since needs to play mine card and have a card to trash
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
		//set supply of silver and gold to 0 every tenth test to test condition where supply is empty for mine card
		if (((h+1) % 10) == 0) {
			post.supplyCount[supply[11]] = 0;
			post.supplyCount[supply[12]] = 0;
		}
		
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

		//set choice1 to a coin from player's hand to be trashed with mine (every 25th test choose a non-coin card). Also select choice2 (the card to be gained) randomly. 25% of time choose copper, 25% silver, 25% gold, 25% any card in the supply
		if (((h+1) % 25) == 0) {
			for (i = 0; i < post.handCount[post.whoseTurn]; i++) {
				if ((post.hand[post.whoseTurn][i] != copper) && (post.hand[post.whoseTurn][i] != silver) && (post.hand[post.whoseTurn][i] != gold) && (post.hand[post.whoseTurn][i] != post.hand[post.whoseTurn][handPos])) {
					choice1 = i;
					i = post.handCount[post.whoseTurn];
				}
			}
			if (choice1 == -1) { //only coins in current player's hand
				choice1 = rand() % post.handCount[post.whoseTurn];
				while (choice1 == handPos) {
					choice1 = rand() % post.handCount[post.whoseTurn];
				}
				post.hand[post.whoseTurn][choice1] = supply[rand() % 10]; //a non coin card
			}
			choice2 = supply[rand() % 17];
		}
		else {
			for (i = 0; i < post.handCount[post.whoseTurn]; i++) {
				if ((post.hand[post.whoseTurn][i] == copper) || (post.hand[post.whoseTurn][i] == silver) || (post.hand[post.whoseTurn][i] == gold)) {
					choice1 = i;
					i = post.handCount[post.whoseTurn];
					
				}
			}
			if (choice1 == -1) { //no coins in current player's hand so put coin in hand
				choice1 = rand() % post.handCount[post.whoseTurn];
				while (choice1 == handPos) { //ensure choice1 and handPos are not the same
					choice1 = rand() % post.handCount[post.whoseTurn];
				}
				post.hand[post.whoseTurn][choice1] = supply[rand() % 3 + 10]; //a coin card
			}
			choice2 = rand() % 4;
			if (choice2 == 0) {
				choice2 = copper;
			}
			else if (choice2 == 1) {
				choice2 = silver;
			}
			else if (choice3 == 2) {
				choice2 = gold;
			}
			else { //choice2 == 3
/*				choice2 = supply[rand() % 17];
				while ((choice2 == copper) || (choice2 == silver) || (choice2 == gold)) {
					choice2 = supply[rand() % 17];
				}
*/				choice2 = supply[(rand() % 7) + 7];
			}
		}



//---------------------Testing Code Starts Here------------------------------------------------------


		
		//copy randomized game state to pre before testing card
		memcpy(&pre, &post, sizeof(struct gameState));
		
		//Categorize the gamestate into one of 18 cases
		
		//Check if choice2 is affordable
		difference = (getCost(pre.hand[pre.whoseTurn][choice1]) + 3) - getCost(choice2);

		//Check that choice1 was a coin
		if ((pre.hand[pre.whoseTurn][choice1] == copper) || (pre.hand[pre.whoseTurn][choice1] == silver) || (pre.hand[pre.whoseTurn][choice1] == gold)) {
			choice1Coin = 1;
		}
		
		//Check that choice2 is a coin
		if ((choice2 == copper) || (choice2 == silver) || (choice2 == gold)) {
			choice2Coin = 1;
		}
		
		//Check if supply of choice2 > 0
		if (pre.supplyCount[choice2] > 0) {
			choice2Supply = 1;
		}
		
		if ((difference > 0) && (choice2Supply == 1) && (choice1Coin == 1) && (choice2Coin == 1)) {
			case1 = 1;
			numCase1++;
		}
		else if ((difference == 0) && (choice2Supply == 1) && (choice1Coin == 1) && (choice2Coin == 1)) {
			case2 = 1;
			numCase2++;
		}
		else if ((difference < 0) && (choice2Supply == 1) && (choice1Coin == 1) && (choice2Coin == 1)){
			case3 = 1;
			numCase3++;
		}
		else if ((difference > 0) && (choice2Supply == -1) && (choice1Coin == 1) && (choice2Coin == 1)) {
			case4 = 1;
			numCase4++;			
		}
		else if ((difference == 0) && (choice2Supply == -1) && (choice1Coin == 1) && (choice2Coin == 1)) {
			case5 = 1;
			numCase5++;
		}
		else if ((difference < 0) && (choice2Supply == -1) && (choice1Coin == 1) && (choice2Coin == 1)){
			case6 = 1;
			numCase6++;
		}
		else if ((difference > 0) && (choice2Supply == 1) && (choice1Coin == -1) && (choice2Coin == 1)) {
			case7 = 1;
			numCase7++;			
		}
		else if ((difference == 0) && (choice2Supply == 1) && (choice1Coin == -1) && (choice2Coin == 1)) {
			case8 = 1;
			numCase8++;
		}
		else if ((difference < 0) && (choice2Supply == 1) && (choice1Coin == -1) && (choice2Coin == 1)){
			case9 = 1;
			numCase9++;
		}
		else if ((difference > 0) && (choice2Supply == 1) && (choice1Coin == 1) && (choice2Coin == -1)) {
			case10 = 1;
			numCase10++;			
		}
		else if ((difference == 0) && (choice2Supply == 1) && (choice1Coin == 1) && (choice2Coin == -1)) {
			case11 = 1;
			numCase11++;
		}
		else if ((difference < 0) && (choice2Supply == 1) && (choice1Coin == 1) && (choice2Coin == -1)){
			case12 = 1;
			numCase12++;
		}
		else if ((difference > 0) && (choice2Supply == -1) && (choice1Coin == 1) && (choice2Coin == -1)) {
			case13 = 1;
			numCase13++;			
		}
		else if ((difference == 0) && (choice2Supply == -1) && (choice1Coin == 1) && (choice2Coin == -1)) {
			case14 = 1;
			numCase14++;
		}
		else if ((difference < 0) && (choice2Supply == -1) && (choice1Coin == 1) && (choice2Coin == -1)){
			case15 = 1;
			numCase15++;
		}
		else if ((difference > 0) && (choice2Supply == 1) && (choice1Coin == -1) && (choice2Coin == -1)) {
			case16 = 1;
			numCase16++;			
		}
		else if ((difference == 0) && (choice2Supply == 1) && (choice1Coin == -1) && (choice2Coin == -1)) {
			case17 = 1;
			numCase17++;
		}
		else if ((difference < 0) && (choice2Supply == 1) && (choice1Coin == -1) && (choice2Coin == -1)) {
			case18 = 1;
			numCase18++;
		}
		
		
		
		
//-------------Test outcome of playing card based on initial game state test case
				
		
		//play card and check for error
		playCard = cardEffect(TEST_CARD, choice1, choice2, choice3, &post, handPos, &bonus);
		if ((playCard < -1) || (playCard > 1)){
			error1++;
		}

//Tests that should be successful		
//Test1
		//if case1 or case2, check that card from supply is added to player's hand
		if ((case1 == 1) || (case2 == 1)) {
			if (/*(post.hand[pre.whoseTurn][post.handCount[pre.whoseTurn]-1] != choice2) && */(post.supplyCount[choice2] != pre.supplyCount[choice2] - 1)) {
				if (case1 == 1) {
					e1c1++;
				}
				else { //case2 == 1
					e1c2++;
				}
			}
//Test2
			//check if current player's handCount was updated correctly (+1 for added coin, -1 for playing mine and -1 for trashed treasure)
			if (post.handCount[pre.whoseTurn] != pre.handCount[pre.whoseTurn]-1) {
				if (case1 == 1) {
					e2c1++;
				}
				else { //case2 == 1
					e2c2++;
				}
			}
		}
		
		
//Tests that should not be successful		
//Test3
		//when choice2 is too expensive check if added to player's hand
		if ((case3 == 1) || (case9 == 1) || (case12 == 1) || (case18 == 1)) {
			if (/*(post.hand[pre.whoseTurn][post.handCount[pre.whoseTurn]-1] == choice2) && */(post.supplyCount[choice2] == pre.supplyCount[choice2]-1)){
				if (case3 == 1) {
					e3c3++;
				}
				else if (case9 == 1) {
					e3c9++;
				}
				else if (case12 == 1) {
					e3c12++;
				}
				else { //(case18 == 1) {
					e3c18++;
				}
			}
		}
//Test4
		//when the supply of choice2 == 0
		if ((case4 == 1) || (case5 == 1) || (case6 == 1) || (case13 == 1) || (case14 == 1) || (case15 == 1)) {
			if ((post.hand[pre.whoseTurn][post.handCount[pre.whoseTurn]-1] == choice2) && (post.supplyCount[choice2] == pre.supplyCount[choice2]-1)) {
				if (case4 == 1) {
					e4c4++;
				}
				else if (case5 == 1) { 
					e4c5++;
				}
				else if (case6 == 1) {
					e4c6++;
				}
				else if (case13 == 1) {
					e4c13++;
				}
				else if (case14 == 1) { 
					e4c14++;
				}
				else { //if (case15 == 1) {
					e4c15++;
				}
			}
		}
//Test5
		//when choice1 is not a coin
		if ((case7 == 1) || (case8 == 1) || (case9 == 1) || (case16 == 1) || (case17 == 1) || (case18 == 1)) {
			if ((post.hand[pre.whoseTurn][post.handCount[pre.whoseTurn]-1] == choice2) && (post.supplyCount[choice2] == pre.supplyCount[choice2]-1)) {
				if (case7 == 1) {
					e5c7++;
				}
				else if (case8 == 1) { 
					e5c8++;
				}
				else if (case9 == 1) {
					e5c9++;
				}
				else if (case16 == 1) {
					e5c16++;
				}
				else if (case17 == 1) { 
					e5c17++;
				}
				else { //if (case18 == 1) {
					e5c18++;
				}
			}
		}
//Test6
		//when choice2 is not a coin
		if ((case10 == 1) || (case11 == 1) || (case12 == 1) || (case13 == 1) || (case14 == 1) || (case15 == 1) || (case16 == 1) || (case17 == 1) || (case18 == 1)) {
			if (/*(post.hand[pre.whoseTurn][post.handCount[pre.whoseTurn]-1] == choice2) && */(post.supplyCount[choice2] == pre.supplyCount[choice2]-1)) {
				if (case10 == 1) {
					e6c10++;
				}
				else if (case11 == 1) { 
					e6c11++;
				}
				else if (case12 == 1) {
					e6c12++;
				}
				else if (case13 == 1) { 
					e6c13++;
				}
				else if (case14 == 1) {
					e6c14++;
				}
				else if (case15 == 1) { 
					e6c15++;
				}
				else if (case16 == 1) {
					e6c16++;
				}
				else if (case17 == 1) { 
					e6c17++;
				}
				else { //if (case18 == 1) {
					e6c18++;
				}
			}
		}
	}
//Tests 7, 8, and 9
		//Check that other player's deckCount, handCount, and discardCount were not changed
		for (i = 0; i < numPlayers; i++) {
			if (i != pre.whoseTurn) {
				if (post.deckCount[i] != pre.deckCount[i]) {
					error7++;
					i = numPlayers;
				}
			}
		}
		for (i = 0; i < numPlayers; i++) {
			if (i != pre.whoseTurn) {
				if (post.handCount[i] != pre.handCount[i]) {
					error8++;
					i = numPlayers;
				}
			}
		}
		for (i = 0; i < numPlayers; i++) {
			if (i != pre.whoseTurn) {
				if (post.discardCount[i] != pre.discardCount[i]) {
					error9++;
					i = numPlayers;
				}
			}
		}
		
	//print results of testing
	printf("\n\n------------------Random Testing Results for Mine card------------------\n\n");
	
	printf("Of the %d randomly generated test conditions, %d tests fell in the category of proper usage of the 'Mine' card (choice1 was a treasure card, choice2 was a treasure card, choice2 cost no more than the cost of choice1 + 3, and there was a positive supply of choice2 available), whereas the other %d tests fell into the category of improper uses of the 'Mine' card (either choice1 was not a treasure, or choice2 was not a treasure, or choice2 cost more than the cost of choice1 + 3, or the supply of choice2 was empty).\n\n", NUM_TESTS, numCase1+numCase2, NUM_TESTS - numCase1 - numCase2);
	
	printf("Of the %d tests which should have been successful, %d of them failed and did not add the choice2 card to the player's hand.\n\t%d of these failures occurred when choice2 cost more than the cost of choice1 + 3 (%d occurrences of this test case).\n\t%d of these failures occurred when choice2 equaled the cost of choice1 + 3 (%d occurrences of this test case).\n\n", numCase1+numCase2, e1c1+e1c2, e1c1, numCase1, e1c2, numCase2);
	
	printf("Of the %d tests which should have been successful, %d of them failed to properly update the player's hand and discard pile.\n\t%d of these failures occurred when choice2 cost more than the cost of choice1 + 3 (%d occurrences of this test case).\n\t%d of these failures occurred when choice2 equaled the cost of choice1 + 3 (%d occurrences of this test case).\n\n", numCase1+numCase2, e2c1+e2c2, e2c1, numCase1, e2c2, numCase2);
	
	printf("Of the %d tests where choice2 had a supply but was too expensive, %d tests failed and incorrectly added choice2 to the player's hand.\n\t%d failures occurred when all other conditions were met (out of %d such test cases).\n\t%d failures occurred when choice1 was not a coin but other conditions were all met (out of %d such test cases).\n\t%d failures occurred when choice2 was not a coin but other conditions were all met (out of %d such test cases).\n\t%d failures occured when both choice1 and choice2 were not coins (out of %d such test cases).\n\n", numCase3+numCase9+numCase12+numCase18, e3c3+e3c9+e3c12+e3c18, e3c3, numCase3, e3c9, numCase9, e3c12, numCase12, e3c18, numCase18);
	
	if ((numCase4+numCase5+numCase6+numCase13+numCase14+numCase15 > 0) && (e4c4+e4c5+e4c6+e4c13+e4c14+e4c15 == 0)) {
		printf("Of the %d tests where the supply of choice2 was empty, all tests were successful in preventing choice2 from being added to the player's hand.\n\n", numCase4+numCase5+numCase6+numCase13+numCase14+numCase15);
	}
	else {
		printf("Of the %d tests where the supply of choice2 was empty, %d tests failed to prevent choice2 from being added to the player's hand.\n\n", numCase4+numCase5+numCase6+numCase13+numCase14+numCase15, e4c4+e4c5+e4c6+e4c13+e4c14+e4c15);
	}
	
	if ((numCase7+numCase8+numCase9+numCase16+numCase17+numCase18 > 0) && (e5c7+e5c8+e5c9+e5c16+e5c17+e5c18 == 0)) {
		printf("Of the %d tests where choice1 (the card to be trashed) was not a coin, all tests were successful in preventing choice2 from being added to the player's hand.\n\n", numCase7+numCase8+numCase9+numCase16+numCase17+numCase18);
	}
	else {
		printf("Of the %d tests where choice1 (the card to be trashed) was not a coin, %d tests failed and incorrectly added choice2 to the player's hand.\n\n", numCase7+numCase8+numCase9+numCase16+numCase17+numCase18, e5c7+e5c8+e5c9+e5c16+e5c17+e5c18);
	}
	
	if ((numCase10+numCase11+numCase12+numCase13+numCase14+numCase15+numCase16+numCase17+numCase18 > 0) && (e6c10+e6c11+e6c12+e6c13+e6c14+e6c15+e6c16+e6c17+e6c18 == 0)) {
		printf("Of the %d tests where choice2 (the card to be gained) was not a coin, all tests were successful in preventing choice2 from being added to the player's hand.\n\n", numCase10+numCase11+numCase12+numCase13+numCase14+numCase15+numCase16+numCase17+numCase18);
	}
	else {
		printf("Of the %d tests where choice2 (the card to be gained) was not a coin, %d tests failed and incorrectly added choice2 to the player's hand.\n\t%d failures occurred when all other conditions were met (out of %d such test cases).\n\t%d failures occurred when choice2 was too expensive but other conditions were all met (out of %d such test cases).\n\t%d failures occurred when choice2 supply was empty but other conditions were all met (out of %d such test cases).\n\t%d failures occurred when choice1 was not a coin but other conditions were all met (out of %d such test cases).\n\t%d failures occured when both choice2 was too expensive and choice2 supply was empty (out of %d such test cases).\n\t%d failures occured when both choice2 was too expensive and choice1 was not a coin (out of %d such test cases).\n\n", numCase10+numCase11+numCase12+numCase13+numCase14+numCase15+numCase16+numCase17+numCase18, e6c10+e6c11+e6c12+e6c13+e6c14+e6c15+e6c16+e6c17+e6c18, e6c10+e6c11, numCase10+numCase11, e6c12, numCase12, e6c13+e6c14, numCase13+numCase14, e6c16+e6c17, numCase16+numCase17, e6c15, numCase15, e6c18, numCase18);
	}
	
		if (error7 > 0) {
		printf("In %d out of the %d tests, another player's deck size changed.\n\n", error7, NUM_TESTS);
	}
	else {
		printf("Successfully maintained all other player's deck sizes during all tests.\n\n");
	}
	
	if (error8 > 0) {
		printf("In %d out of the %d tests, another player's hand size changed.\n\n", error8, NUM_TESTS);
	}
	else {
		printf("Successfully maintained all other player's hand sizes during all tests.\n\n");
	}
	
	if (error9 > 0) {
		printf("In %d out of the %d tests, another player's discard pile size changed.\n\n", error9, NUM_TESTS);
	}
	else {
		printf("Successfully maintained all other player's discard pile sizes during all tests.\n\n");
	}
	
	printf("------------------Testing Complete for Mine card------------------\n\n");
	
	return 0;
}
