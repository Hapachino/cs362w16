/* Author: Kim McLeod
 * Assignment: 4
 * File: randomtestadventurer.c
 * 
 * 
 * adventurer - make sure deck doesn't need to be shuffled
 *		see if card drawn is treasure card, 
 *		increment until 2 treasure cards or deck is empty
 *		discard all drawn cards that aren't treasure cards
 *	- stops when 2 treasure cards are revealed
 * 	- all revealed non-treasure cards are discarded
 *	- no treasure cards in deck (end of deck)
 *	- deck is shuffled when needed (at beginning and middle) **
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#define TESTCARD "adventurer"

int main() {

    int i, n, deckCount = 0, error1 = 0, error2 = 0, error3 = 0, error4 = 0, error5 = 0;
    int handPos = 0;
    int seed = 2000;
    int numPlayers = floor(Random() * MAX_PLAYERS);
    int player;
    int numBefore;
    int numAfter;
    int coinsBefore;
    int coinsAfter;

    int card = 0;
    int bonus = 0;

	struct gameState G, testG, oldG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, gardens, smithy, council_room};

	printf("----------------- Random Testing for %s Begin----------------\n", TESTCARD);
for(n = 0; n < seed; n++){
	player = floor(Random() * 2);
	G.deckCount[player] = floor(Random() * MAX_DECK);
	G.discardCount[player] = floor(Random() * MAX_DECK);
	G.handCount[player] = floor(Random() * MAX_HAND);	
	numPlayers = floor(Random() * MAX_PLAYERS);

	// initialize a game state and player cards
	initTestGame(numPlayers, k, seed, &G);



	

	/*************** TEST 1: Two treasure cards are revealed ***********/
	

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// make sure the player has treasure cards
	gainCard(copper,&testG,1,player);
	gainCard(silver,&testG,1,player);
	gainCard(gold,&testG,1,player);

	// record coin amount before card is played
	updateCoins(player, &testG, 0);
	coinsBefore = testG.coins;


	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
        	gainCard(k[rand() % 9 + 1],&testG,1,player);
      	}

	// give player an adventurer card and play it
	gainCard(adventurer,&testG,2,player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);


	// this will fail due to the altered dominion.c code
	if(coinsAfter != 5)
	{	printf("Error 1 'Two treasure cards in deck' Expected: 5, Actual: %d\n", coinsAfter);
		error1++;
	}
	if(numHandCards(&testG) != (numHandCards(&G) + 1))
	{ 	printf("Error 5 'Number of cards in hand updated' Expected: %d, Actual: %d\n", (numHandCards(&G) + 1), numHandCards(&testG));
		error5++; 
	}




	/*************** TEST 2: No treasure cards in deck ***********/
	

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// record coin amount before card is played
	updateCoins(player, &testG, 0);
	coinsBefore = testG.coins;

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
        	gainCard(k[rand() % 9 + 1],&testG,1,player);
      	}

	// give player an adventurer card and play it
	gainCard(adventurer,&testG,2,player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);

	// test fails if player gains coins from playing the adventurer card	
	if(coinsAfter != 0)
	{	printf("Error 2 'No treasure cards in deck' Expected: 0, Actual: %d\n", coinsAfter);
		error2++;//printf("PASS: No treasure cards in deck\n\n\n");
		
	}
	if(numHandCards(&testG) != numHandCards(&G))
	{	printf("Error 5 'Number of cards in hand updated' Expected: %d, Actual: %d\n", numHandCards(&G), numHandCards(&testG));
		 error5++; 
	}



	/*************** TEST 3: One treasure card in deck ***********/
	

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// record coin amount before card is played
	gainCard(copper,&testG,1,player);
	
	updateCoins(player, &testG, 0);
	coinsBefore = testG.coins;

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
        	gainCard(k[rand() % 9 + 1],&testG,1,player);
      	}

	// give player an adventurer card and play it
	gainCard(adventurer,&testG,2,player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);

	// test fails if player gains no coins from playing the adventurer card
	// will fail due to altered dominion.c code
	if(coinsAfter == 0)
	{	printf("Error 3 'One treasure card in deck' Expected: 1, Actual: %d\n", coinsAfter);
		error3++;//printf("PASS: One treasure card in deck\n\n\n");
		
	}
	if(numHandCards(&testG) != numHandCards(&G))
	{ 	printf("Error 5 'Number of cards in hand updated' Expected: %d, Actual: %d\n", numHandCards(&G), numHandCards(&testG));
		error5++; 
	}



	/*************** TEST 4: All revealed non-treasure cards are discarded ***********/
	

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give player treasure cards and record card amounts before card is played
	gainCard(silver,&testG,1,player);
	gainCard(silver,&testG,1,player);
	gainCard(silver,&testG,1,player);
	numBefore = numHandCards(&testG);

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
        	gainCard(k[rand() % 9 + 1],&testG,1,player);
      	}

	// give player an adventurer card and play it
	gainCard(adventurer,&testG,2,player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get card amounts after card is played
	oldG = testG;	
	endTurn(&testG);
	numAfter = numHandCards(&oldG);


	// test passes if player's hand cointains only the adventurer card 
	if(numAfter != (numBefore + 1))
	{	printf("Error 4 'All revealed non-treasure cards discarded' failed. Expected: %d, actual: %d\n", (numBefore+1), numAfter);
		error4++;	
	}
	

    }

	


	printf("\n >>>>> SUCCESS: Random Testing Complete for %s <<<<<\n\n", TESTCARD);
	printf("Error 1 'Two treasure cards in deck' failed %d of %d times\n", error1, seed);
	printf("Error 2 'No treasure cards in deck' failed %d of %d times\n", error2, seed);
	printf("Error 3 'One treasure card in deck' failed %d of %d times\n", error3, seed);
	printf("Error 4 'All revealed non-treasure cards discarded' failed %d of %d times\n", error4, seed);
	printf("Error 5 'Number of cards in hand updated' failed %d of %d times\n\n\n\n", error5, (seed * 3));

	return 0;
}

