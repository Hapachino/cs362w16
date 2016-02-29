/*****************************************************************************************
* UNIT TEST
* By: Lynn Herrick
* Date: refactored for teammates code on 2/25/16
* card: sea_hag
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
	int testNum = 1;
	int pos, p1, p2;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    char cardTested[] = "Sea Hag";
	struct gameState Clean;		//state to compare
	struct gameState Test;		//state being tested
	signal(SIGSEGV, segfault); // keeps alive if func causes segfault

	printf("-------Beginning tests on the %s card.-------\n", cardTested);

	//initialize game
	initializeGame(2, kingdomCards, 1000, &Clean);
	memcpy(&Test, &Clean, sizeof(struct gameState));
	
	//set game vars
	pos = -1;							//similar to playdom.c
	p1 = 0;
	p2 = 1;

	//test chosen function
	//cardEffect(sea_hag, 0, 0, 0, &Test, 0, 0);
	playSeaHag(1, &Test);

	//print info from test case
	printf("\n%d. Did player 1's hand change:\n", testNum);
	if(Test.handCount[p1] == Clean.handCount[p1] + 1 - 1){ //acount for discard of village
		printf("Passed. Hand count is %d + 1 - 1 = %d\n", Clean.handCount[p1], Test.handCount[p1]);
	} 
	else{  //fail
		printf("Failed. Hand count is %d + 1 - 1 = %d\n", Clean.handCount[p1], Test.handCount[p1]);
	}
	testNum++;
	printf("\n%d. Did player 2's hand change:\n", testNum);
	if(Test.handCount[p2] == Clean.handCount[p2]){
		printf("Passed.  Hand count is %d - 0 = %d\n", Clean.handCount[p2], Test.handCount[p2]);
	}
	else{	//fail
		printf("Failed. Hand count is %d - 0 = %d\n", Clean.handCount[p2], Test.handCount[p2]);
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
	printf("\n%d. Did player 1's discard pile change - 1:\n", testNum);
	if(Test.discardCount[p1] == Clean.discardCount[p1]-1){
		printf("Passed. Discard count is %d - 1 = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
	}
	else{	//fail
		printf("Failed. Discard count is %d - 1 = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
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
	printf("\n%d. Did the number of actions change + 2':\n", testNum);
	if(Test.numActions == Clean.numActions){
		printf("Passed. Numbers of actions is %d + 2 = %d\n", Clean.numActions, Test.numActions);
	}
	else{	//fail
		printf("Failed. Phase is %d + 2 = %d\n", Clean.numActions, Test.numActions);
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
	if(Test.playedCardCount == Clean.playedCardCount){
		printf("Passed. Played card count is %d = %d\n", Clean.playedCardCount, Test.playedCardCount);
	}
	else{	//fail
		printf("Failed. Played card count is %d = %d\n", Clean.playedCardCount, Test.playedCardCount);
	}
	testNum++;
	printf("\n%d. Is next player's top card in their deck a curse:\n", testNum);
	if(Test.deck[p1][Test.deckCount[p2]--] == curse){
		printf("Passed. Top card is curse.\n");
	}
	else{	//fail
		printf("Failed. Top card is not curse.\n");
	}
	testNum++;
	printf("\n%d. Is current player's top card in their deck not a curse:\n", testNum);
	if(Test.deck[p2][Test.deckCount[p1]--] != curse){
		printf("Passed. Top card is curse.\n");
	}
	else{	//fail
		printf("Failed. Top card is not curse.\n");
	}
	testNum++;

	printf("\n-------Completed tests on the %s card.-------\n", cardTested);
	return 0;
} 



/****************************************************************************************
* Desc: ignores any sigal and continues with unit tests while showing what caused a
*		signal to occur.
* Parameters: int signal number
****************************************************************************************/
void segfault(int sig_num){
	//variables
	int testNum = 1;
	int pos, p1, p2;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    char cardTested[] = "Village";
	struct gameState Clean;		//state to compare
	struct gameState Test;		//state being tested
	signal(SIGSEGV, segfault); // keeps alive if func causes segfault

	printf("\n%d. %s card causes Seg Fault.\n", testNum, cardTested);
	testNum++;

	//initialize game
	initializeGame(2, kingdomCards, 1000, &Clean);
	memcpy(&Test, &Clean, sizeof(struct gameState));
	
	//set game vars
	pos = -1;							//similar to playdom.c
	p1 = 0;
	p2 = 1;

	//test chosen function
	cardEffect(village, 0, 0, 0, &Test, 0, 0);

	//print info from test case
	printf("\n%d. Did player 1's hand change:\n", testNum);
	if(Test.handCount[p1] == Clean.handCount[p1] + 1 - 1){ //acount for discard of village
		printf("Passed. Hand count is %d + 1 - 1 = %d\n", Clean.handCount[p1], Test.handCount[p1]);
	} 
	else{  //fail
		printf("Failed. Hand count is %d + 1 - 1 = %d\n", Clean.handCount[p1], Test.handCount[p1]);
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
	printf("\n%d. Did player 1's deck change - 3:\n", testNum);
	if(Test.deckCount[p1] == Clean.deckCount[p1]-3){
		printf("Passed. Deck count is %d - 3 = %d\n", Clean.deckCount[p1], Test.deckCount[p1]);
	}
	else{	//fail
		printf("Failed. Deck count is %d - 3 = %d\n", Clean.deckCount[p1], Test.deckCount[p1]);
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
	printf("\n%d. Did player 1's discard pile change - 1:\n", testNum);
	if(Test.discardCount[p1] == Clean.discardCount[p1]-1){
		printf("Passed. Discard count is %d - 1 = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
	}
	else{	//fail
		printf("Failed. Discard count is %d - 1 = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
	}
	testNum++;
	printf("\n%d. Did player 2's discard pile change - 0:\n", testNum);
	if(Test.discardCount[p2] == Clean.discardCount[p2]){
		printf("Passed. Discard count is %d - 1 = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
	}
	else{	//fail
		printf("Failed. Discard count is %d - 1 = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
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
	printf("\n%d. Did the number of actions change + 2':\n", testNum);
	if(Test.numActions == Clean.numActions){
		printf("Passed. Numbers of actions is %d + 2 = %d\n", Clean.numActions, Test.numActions);
	}
	else{	//fail
		printf("Failed. Phase is %d + 2 = %d\n", Clean.numActions, Test.numActions);
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
	if(Test.playedCardCount == Clean.playedCardCount){
		printf("Passed. Played card count is %d + 0 = %d\n", Clean.playedCardCount, Test.playedCardCount);
	}
	else{	//fail
		printf("Failed. Played card count is %d + 0 = %d\n", Clean.playedCardCount, Test.playedCardCount);
	}
	testNum++;


	printf("\n-------Completed tests on the %s card.-------\n", cardTested);
	exit(0);
}