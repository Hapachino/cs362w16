/**************************************************************************
* CS 362-400 Assignment 4 
* By:  Lynn Herrick
* Date: 2/9/16
* Description: Write a random testers for two Dominion cards, one of which 
*       has to be the adventurer card. Check these random testers in.
* NOTE: Structure of code taken from class lecture titled "Radome Testing 1"
***************************************************************************/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>  //for floor()
#include <signal.h>
#include <setjmp.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


//look at testdrawcard for example of test structure
int checkAdventurer(struct gameState Clean, int player);	//test oracle
void segfault(int sig_num);  								//keep testing alive if signal

//global vars
jmp_buf skipPoint;	//used for keeping randomizing alive if signal


int main(){  //test generator
	char testName[] = "Adventurer";
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	int i, j, currentPlayer, deckcount, discardcount, handcount, tpos, tcoin;
	struct gameState testState;
	srand(time(NULL));

	printf("---------------- Testing %s card. ----------------\n", testName);
	//amount of random tests -- similar to lecture
	for(i=0; i<2000; i++){	
		//set up proper preconditions and random input
		initializeGame(2, kingdomCards, 1000, &testState);
		currentPlayer = rand()%2;
		deckcount = floor(Random()*MAX_DECK);		//from lecture
		testState.deckCount[currentPlayer] = deckcount;
		for(j=0; j<2; j++){  //two mandatory treasure cards
			tpos = floor(Random()*deckcount); //randomize position in deck
			tcoin = floor(Random()*2);	//randomize type added
			if(tcoin == 0){
				testState.deck[currentPlayer][tpos] = gold;
			}
			else if(tcoin == 1){
				testState.deck[currentPlayer][tpos] = silver;
			}
			else{
				testState.deck[currentPlayer][tpos] = copper;
			}
		}
		discardcount = floor(Random()*MAX_DECK);   //from lecture
		testState.discardCount[currentPlayer] = discardcount;
		handcount = floor(Random()*MAX_HAND + 1);		//from lecture
		testState.handCount[currentPlayer] = handcount;
		printf("Random Variables: Test number = %d Current Player = %d; Deck Count = %d; Discard Count = %d; Hand Count = %d\n", i+1, currentPlayer, deckcount, discardcount, handcount);
		
		//test card - send through oracle
		checkAdventurer(testState, currentPlayer);
	}
	printf ("---------- Random Testing Complete -------------\n");

	return 0;
}



int checkAdventurer(struct gameState Clean, int player){
	int i;
	int testNum = 1;
	int pos, p1, p2, result;
	int testTreasureCount = 0;
	int cleanTreasureCount = 0;
    char cardTested[] = "Adventurer";
	struct gameState Test;		//state to compare
	signal(SIGSEGV, segfault); // keeps alive if func causes segfault

	//set the correct player as random current player (p1)
	pos = -1;
	if(player == 0){
		p1 = player;
		p2 = 1;
	}
	else{
		p1 = player;
		p2 = 0;
	}

	memcpy (&Test, &Clean, sizeof(struct gameState));
	//keeps test alive if signal, jmp in signal handler
	if(setjmp(skipPoint) == 0){  
		//test chosen function
		result = cardEffect(village, 0, 0, 0, &Test, 0, 0);
	}else{
		printf("----cardEffect() DID NOT RETURN PROPERLY FOR THIS TEST-----");
		goto tests;
	}

tests:
	//print info from test case
	printf("\n%d. Did player 1's hand change:\n", testNum);
	if(Test.handCount[p1] > Clean.handCount[p1]){ //acount for discard of adventurer
		printf("Passed. Hand count is %d > %d\n", Clean.handCount[p1], Test.handCount[p1]);
	} 
	else{  //fail
		printf("Failed. Hand count is %d > %d\n", Clean.handCount[p1], Test.handCount[p1]);
	}
	testNum++;
	printf("\n%d. Did player 2's hand change:\n", testNum);
	if(Test.handCount[p2] == Clean.handCount[p2]){
		printf("Passed.  Hand count is %d - 0 = %d", Clean.handCount[p2], Test.handCount[p2]);
	}
	else{	//fail
		printf("Failed. Hand count is %d - 0 = %d", Clean.handCount[p2], Test.handCount[p2]);
	}
	testNum++;
	printf("\n%d. Did player 1's deck change:\n", testNum);
	if(Test.deckCount[p1] == Clean.deckCount[p1] - (Test.discardCount[p1]+2)){	//discards plus two treasure cards
		printf("Passed. Deck count is %d - (%d + 2) = %d\n", Clean.deckCount[p1], Test.discardCount[p1],Test.deckCount[p1]);
	}
	else{	//fail
		printf("Failed. Deck count is %d - (%d + 2) = %d\n", Clean.deckCount[p1], Test.discardCount[p1],Test.deckCount[p1]);
	}
	testNum++;
	printf("\n%d. Did player 2's deck change - 0:\n", testNum);
	if(Test.deckCount[p2] == Clean.deckCount[p2]){
		printf("Passed. Deck count is %d - 0 = %d\n", Clean.deckCount[p2], Test.deckCount[p2]);
	}
	else{	//fail
		printf("Passed. Deck count is %d - 0 = %d\n", Clean.deckCount[p2], Test.deckCount[p2]);
	}
	testNum++;
	printf("\n%d. Did player 1's discard pile change:\n", testNum);
	if(Test.discardCount[p1] >= Clean.discardCount[p1]-1){
		printf("Passed. Discard count is %d - 1 <= %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
	}
	else{	//fail
		printf("Failed. Discard count is %d - 1 <= %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
	}
	testNum++;
	printf("\n%d. Did player 2's discard pile change - 0:\n", testNum);
	if(Test.discardCount[p2] == Clean.discardCount[p2]){
		printf("Passed. Discard count is %d - 0 = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
	}
	else{	//fail
		printf("Failed. Discard count is %d - 0 = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
	}
	testNum++;
	printf("\n%d. Did the number of players change - 0:\n", testNum);
	if(Test.numPlayers == Clean.numPlayers){
		printf("Passed. Player count is %d - 0 = %d\n", Clean.numPlayers, Test.numPlayers);
	}
	else{	//fail
		printf("Failed. Player count is %d - 0 = %d\n", Clean.numPlayers, Test.numPlayers);
	}
	testNum++;
	printf("\n%d. Did the outpost played change - 0:\n", testNum);
	if(Test.outpostPlayed == Clean.outpostPlayed){
		printf("Passed. Outpost played is %d - 0 = %d\n", Clean.outpostPlayed, Test.outpostPlayed);
	}
	else{	//fail
		printf("Failed. Outpost played is %d - 0 = %d\n", Clean.outpostPlayed, Test.outpostPlayed);
	}
	testNum++;
	printf("\n%d. Did the outpost turn change - 0:\n", testNum);
	if(Test.outpostTurn == Clean.outpostTurn){
		printf("Passed. Outpost turn is %d = %d\n", Clean.outpostTurn, Test.outpostTurn);
	}
	else{	//fail
		printf("Failed. Outpost turn is %d = %d\n", Clean.outpostTurn, Test.outpostTurn);
	}
	testNum++;
	printf("\n%d. Did whose turn it is not chage:\n", testNum);
	if(Test.whoseTurn == Clean.whoseTurn){
		printf("Passed. Player's turn is %d = %d\n", Clean.whoseTurn, Test.whoseTurn);
	}
	else{	//fail
		printf("Failed. Player turn is %d = %d\n", Clean.whoseTurn, Test.whoseTurn);
	}
	testNum++;
	printf("\n%d. Did the phase change + 0':\n", testNum);
	if(Test.phase == Clean.phase){
		printf("Passed. Phase is %d + 0 = %d\n", Clean.phase, Test.phase);
	}
	else{	//fail
		printf("Failed. Phase is %d + 0 = %d\n", Clean.phase, Test.phase);
	}
	testNum++;
	printf("\n%d. Did the number of actions change + 0':\n", testNum);
	if(Test.numActions == Clean.numActions){
		printf("Passed. Numbers of actions is %d + 0 = %d\n", Clean.numActions, Test.numActions);
	}
	else{	//fail
		printf("Failed. Phase is %d + 0 = %d\n", Clean.numActions, Test.numActions);
	}
	testNum++;
	printf("\n%d. Did the coins change + 0':\n", testNum);
	if(Test.coins == Clean.coins){
		printf("Passed. Coins are %d + 0 = %d\n", Clean.coins, Test.coins);
	}
	else{	//fail
		printf("Failed. Coins are %d + 0 = %d\n", Clean.coins, Test.coins);
	}
	testNum++;
	printf("\n%d. Did the number of buys change + 0':\n", testNum);
	if(Test.numBuys == Clean.numBuys){
		printf("Passed. Number of buys is %d + 0 = %d\n", Clean.numBuys, Test.numBuys);
	}
	else{	//fail
		printf("Failed. Number of buys is %d + 0 = %d\n", Clean.numBuys, Test.numBuys);
	}
	testNum++;
	printf("\n%d. Did the played card count change + 1':\n", testNum);
	if(Test.playedCardCount == Clean.playedCardCount + 1){
		printf("Passed. Played card count is %d + 1 = %d\n", Clean.playedCardCount, Test.playedCardCount);
	}
	else{	//fail
		printf("Failed. Played card count is %d + 1 = %d\n", Clean.playedCardCount, Test.playedCardCount);
	}
	testNum++;
	printf("\n%d. Did the played 1 draw 2 treasure cards':\n", testNum);
	for(i = 0; i < sizeof(Test.hand); i++){
		if(Test.hand[p1][i] == gold || Test.hand[p1][i] == silver || Test.hand[p1][i] == copper){
			testTreasureCount++;
		}
	}
	for(i = 0; i < sizeof(Clean.hand); i++){
		if(Clean.hand[p1][i] == gold || Clean.hand[p1][i] == silver || Clean.hand[p1][i] == copper){
			cleanTreasureCount++;
		}
	}
	if(testTreasureCount == cleanTreasureCount + 2){
		printf("Passed. Player 1 treasure count is %d + 2 = %d\n", cleanTreasureCount, testTreasureCount);
	}
	else{	//fail
		printf("Failed. Played card count is %d + 2 = %d\n", cleanTreasureCount, testTreasureCount);
	}
	testNum++;
	
	printf("\n-------Completed tests on the %s card.-------\n", cardTested);

	//assert(result == 0); //function ran
	//assert(memcmp(&Clean, &Test, sizeof(struct gameState)) == 0); //no mismatch
	return 0;
}




/****************************************************************************************
* Desc: ignores any sigal and continues with unit tests while showing what caused a
*		signal to occur.
* Parameters: int signal number
****************************************************************************************/
void segfault(int sig_num){
	printf("----cardEffect() DID NOT RETURN PROPERLY FOR THIS TEST-----");
	longjmp(skipPoint, 0);  //since seg fault, this exits infinite handler
}
