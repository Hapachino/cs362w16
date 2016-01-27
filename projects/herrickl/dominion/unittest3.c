/*****************************************************************************************
* UNIT TEST
* By: Lynn Herrick
* Date: 1/26/16
* function: updateCoins
* NOTE: print statements are used here to show details of both pass and fail situations
*****************************************************************************************/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//looks for potential signals that would disrupt test
void (*signal(int signum, void (*sighandler)(int)))(int);
void segfault(int sig_num);


int main(){
	//variables
	int i, j;
	int testNum = 1;
	int pos, p1, p2;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    char funcTested[] = "Update Coins";
	struct gameState Clean;		//state to compare
	struct gameState Test;		//state being tested
	signal(SIGSEGV, segfault); // keeps alive if func causes segfault

	printf("-------Beginning tests on the %s card.-------\n", funcTested);

	for(i=0; i<2; i++){	//test both players
		//initialize game
		initializeGame(2, kingdomCards, 1000, &Clean);
		memcpy(&Test, &Clean, sizeof(struct gameState));
		
		//set game vars
		pos = -1;							//similar to playdom.c
		p1 = 0;
		p2 = 1;

		//test chosen function
		updateCoins(i, &Test, 0);


		//check coins in hand, were they counted correctly
		printf("\n%d. Did the coins change + 0':\n", testNum);
		j = 0;	//temp variable used for coin count
		for(i=0; i < Clean.handCount[p1]; i++){
			if(Clean.hand[p1][i] == copper){
				j+=1;
			}
			else if(Clean.hand[p1][i] == silver){
				j+=2;
			}
			else if(Clean.hand[p1][i] == gold){
				j+=3;
			}
		}
		if(Test.coins == j){
			printf("Passed. Coins are %d = %d\n", j, Test.coins);
		}
		else{	//fail
			printf("Failed. Coins are %d = %d\n", j, Test.coins);
		}
		testNum++;
		//print info from test case
		printf("\n%d. Did player 1's hand change:\n", testNum);
		if(Test.handCount[p1] == Clean.handCount[p1]){ 
			printf("Passed. Hand count is %d = %d\n", Clean.handCount[p1], Test.handCount[p1]);
		} 
		else{  //fail
			printf("Failed. Hand count is %d = %d\n", Clean.handCount[p1], Test.handCount[p1]);
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
		if(Test.deckCount[p1] == Clean.deckCount[p1]){
			printf("Passed. Deck count is %d = %d\n", Clean.deckCount[p1], Test.deckCount[p1]);
		}
		else{	//fail
			printf("Failed. Deck count is %d = %d\n", Clean.deckCount[p1], Test.deckCount[p1]);
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
		if(Test.discardCount[p1] == Clean.discardCount[p1]){
			printf("Passed. Discard count is %d = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
		}
		else{	//fail
			printf("Failed. Discard count is %d = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
		}
		testNum++;
		printf("\n%d. Did player 2's discard pile change - 0:\n", testNum);
		if(Test.discardCount[p2] == Clean.discardCount[p2]){
			printf("Passed. Discard count is %d = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
		}
		else{	//fail
			printf("Failed. Discard count is %d = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
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
		printf("\n%d. Did the number of actions change':\n", testNum);
		if(Test.numActions == Clean.numActions){
			printf("Passed. Numbers of actions is %d = %d\n", Clean.numActions, Test.numActions);
		}
		else{	//fail
			printf("Failed. Phase is %d = %d\n", Clean.numActions, Test.numActions);
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
		printf("\n%d. Did the played card count change':\n", testNum);
		if(Test.playedCardCount == Clean.playedCardCount){
			printf("Passed. Played card count is %d + 0 = %d\n", Clean.playedCardCount, Test.playedCardCount);
		}
		else{	//fail
			printf("Failed. Played card count is %d + 0 = %d\n", Clean.playedCardCount, Test.playedCardCount);
		}
		testNum++;
	}

	printf("\n-------Completed tests on the %s card.-------\n", funcTested);
	return 0;
} 



/****************************************************************************************
* Desc: ignores any sigal and continues with unit tests while showing what caused a
*		signal to occur.
* Parameters: int signal number
****************************************************************************************/
void segfault(int sig_num){
	//variables
	int i, j;
	int testNum = 1;
	int pos, p1, p2;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    char funcTested[] = "Update Coins";
	struct gameState Clean;		//state to compare
	struct gameState Test;		//state being tested

	printf("%d. %s function causes seg fault.\n", testNum, funcTested);
	testNum++;

	for(i=0; i<2; i++){	//test both players
		//initialize game
		initializeGame(2, kingdomCards, 1000, &Clean);
		memcpy(&Test, &Clean, sizeof(struct gameState));
		
		//set game vars
		pos = -1;							//similar to playdom.c
		p1 = 0;
		p2 = 1;

		//check coins in hand, were they counted correctly
		printf("\n%d. Did the coins change + 0':\n", testNum);
		j = 0;	//temp variable used for coin count
		for(i=0; i < Clean.handCount[p1]; i++){
			if(Clean.hand[p1][i] == copper){
				j+=1;
			}
			else if(Clean.hand[p1][i] == silver){
				j+=2;
			}
			else if(Clean.hand[p1][i] == gold){
				j+=3;
			}
		}
		if(Test.coins == j){
			printf("Passed. Coins are %d = %d\n", j, Test.coins);
		}
		else{	//fail
			printf("Failed. Coins are %d = %d\n", j, Test.coins);
		}
		testNum++;
		//print info from test case
		printf("\n%d. Did player 1's hand change:\n", testNum);
		if(Test.handCount[p1] == Clean.handCount[p1]){ 
			printf("Passed. Hand count is %d = %d\n", Clean.handCount[p1], Test.handCount[p1]);
		} 
		else{  //fail
			printf("Failed. Hand count is %d = %d\n", Clean.handCount[p1], Test.handCount[p1]);
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
		if(Test.deckCount[p1] == Clean.deckCount[p1]){
			printf("Passed. Deck count is %d = %d\n", Clean.deckCount[p1], Test.deckCount[p1]);
		}
		else{	//fail
			printf("Failed. Deck count is %d = %d\n", Clean.deckCount[p1], Test.deckCount[p1]);
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
		if(Test.discardCount[p1] == Clean.discardCount[p1]-1){
			printf("Passed. Discard count is %d = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
		}
		else{	//fail
			printf("Failed. Discard count is %d = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
		}
		testNum++;
		printf("\n%d. Did player 2's discard pile change - 0:\n", testNum);
		if(Test.discardCount[p2] == Clean.discardCount[p2]){
			printf("Passed. Discard count is %d = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
		}
		else{	//fail
			printf("Failed. Discard count is %d = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
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
		printf("\n%d. Did the number of actions change':\n", testNum);
		if(Test.numActions == Clean.numActions){
			printf("Passed. Numbers of actions is %d = %d\n", Clean.numActions, Test.numActions);
		}
		else{	//fail
			printf("Failed. Phase is %d = %d\n", Clean.numActions, Test.numActions);
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
		printf("\n%d. Did the played card count change':\n", testNum);
		if(Test.playedCardCount == Clean.playedCardCount){
			printf("Passed. Played card count is %d + 0 = %d\n", Clean.playedCardCount, Test.playedCardCount);
		}
		else{	//fail
			printf("Failed. Played card count is %d + 0 = %d\n", Clean.playedCardCount, Test.playedCardCount);
		}
		testNum++;
	}

	printf("\n-------Completed tests on the %s card.-------\n", funcTested);
	exit(0);
}