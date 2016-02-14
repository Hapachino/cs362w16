/* -----------------------------------------------------------------------
 * Test is for initializeGame()
 *
 * unittest1
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main() {

	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState test;

    int i;
  
    int seed = 1000;
    int totalPlayers;
    int result;
    int testNum = 3;

    printf("\n--------Testing for game initilization function----------");

   	printf("\n--------Testing #1 for only one player----------");

   	memset(&test, 23, sizeof(struct gameState));   // clear the game state

   	totalPlayers = 1;

   	result = initializeGame(totalPlayers, k, seed, &test); // initialize a new game

    if(result == -1){
    	printf("\n>>>>Success: one player is not enough to play the game!!!");
    }
    else{
    	printf("\n>>>>Fail: one player alone cant play the game!!!");
    }

    printf("\n--------Testing #2 for only five players----------");

   	memset(&test, 23, sizeof(struct gameState));   // clear the game state

   	totalPlayers = 5;

   	result = initializeGame(totalPlayers, k, seed, &test); // initialize a new game

    if(result == -1){
    	printf("\n>>>>Success: five players is too much for the game!!!");
    }
    else{
    	printf("\n>>>>Fail: five players cant play the game!!!");
    }

    for(totalPlayers = 2; totalPlayers <=4; totalPlayers++){
    	printf("\n--------Testing #%d for only five players----------", testNum);

    	testNum++;

	   	memset(&test, 23, sizeof(struct gameState));   // clear the game state

	   	result = initializeGame(totalPlayers, k, seed, &test); // initialize a new game

	    if(result == 0){
    	printf("\n>>>>Success: %d players is enough for the game!!!", totalPlayers);
	    }
	    else{
	    	printf("\n>>>>Fail: %d players are suppose to be able to play the game!!!", totalPlayers);
	    }
	    if(totalPlayers == 2){
	    	if(test.supplyCount[curse] == 10){
	    		printf("\n>>>>SUCCESS: supply count for curse is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for curse is incorrect!!!");
	    	}
	    	if(test.supplyCount[estate] == 8){
	    		printf("\n>>>>SUCCESS: supply count for estate is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for estate is incorrect!!!");
	    	}
	    	if(test.supplyCount[duchy] == 8){
	    		printf("\n>>>>SUCCESS: supply count for duchy is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for duchy is incorrect!!!");
	    	}
	    	if(test.supplyCount[province] == 8){
	    		printf("\n>>>>SUCCESS: supply count for province is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for province is incorrect!!!");
	    	}
	    	if(test.supplyCount[copper] == 60 - (7 * totalPlayers)){
	    		printf("\n>>>>SUCCESS: supply count for copper is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for copper is incorrect!!!");
	    	}
	    	if(test.supplyCount[silver] == 40){
	    		printf("\n>>>>SUCCESS: supply count for silver is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>Fail: supply count for silver is incorrect!!!");
	    	}
	    	if(test.supplyCount[gold] == 30){
	    		printf("\n>>>>SUCCESS: supply count for gold is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for gold is incorrect!!!");
	    	}
	    }
	    if(totalPlayers == 3){
	    	if(test.supplyCount[curse] == 20){
	    		printf("\n>>>>SUCCESS: supply count for curse is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for curse is incorrect!!!");
	    	}
	    	if(test.supplyCount[estate] == 12){
	    		printf("\n>>>>SUCCESS: supply count for estate is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for estate is incorrect!!!");
	    	}
	    	if(test.supplyCount[duchy] == 12){
	    		printf("\n>>>>SUCCESS: supply count for duchy is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for duchy is incorrect!!!");
	    	}
	    	if(test.supplyCount[province] == 12){
	    		printf("\n>>>>SUCCESS: supply count for province is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for province is incorrect!!!");
	    	}
	    	if(test.supplyCount[copper] == 60 - (7 * totalPlayers)){
	    		printf("\n>>>>SUCCESS: supply count for copper is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for copper is incorrect!!!");
	    	}
	    	if(test.supplyCount[silver] == 40){
	    		printf("\n>>>>SUCCESS: supply count for silver is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for silver is incorrect!!!");
	    	}
	    	if(test.supplyCount[gold] == 30){
	    		printf("\n>>>>SUCCESS: supply count for gold is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for gold is incorrect!!!");
	    	}
	    }
	    if(totalPlayers == 4){
	    	if(test.supplyCount[curse] == 30){
	    		printf("\n>>>>SUCCESS: supply count for curse is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for curse is incorrect!!!");
	    	}
	    	if(test.supplyCount[estate] == 12){
	    		printf("\n>>>>SUCCESS: supply count for estate is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for estate is incorrect!!!");
	    	}
	    	if(test.supplyCount[duchy] == 12){
	    		printf("\n>>>>SUCCESS: supply count for duchy is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for duchy is incorrect!!!");
	    	}
	    	if(test.supplyCount[province] == 12){
	    		printf("\n>>>>SUCCESS: supply count for province is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for province is incorrect!!!");
	    	}
	    	if(test.supplyCount[copper] == 60 - (7 * totalPlayers)){
	    		printf("\n>>>>SUCCESS: supply count for copper is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for copper is incorrect!!!");
	    	}
	    	if(test.supplyCount[silver] == 40){
	    		printf("\n>>>>SUCCESS: supply count for silver is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for silver is incorrect!!!");
	    	}
	    	if(test.supplyCount[gold] == 30){
	    		printf("\n>>>>SUCCESS: supply count for gold is correct!!!");
	    	}
	    	else{
	    		printf("\n>>>>Fail: supply count for gold is incorrect!!!");
	    	}
	    }

    }
    	totalPlayers = 2;
    	memset(&test, 23, sizeof(struct gameState));   // clear the game state

	   	result = initializeGame(totalPlayers, k, seed, &test); // initialize a new game

	   	printf("\n-------Test if kingdom cards are correct amount-----");

	   	if(test.supplyCount[adventurer] == 10){
	   		printf("\n>>>>SUCCESS: supply count for adventurer is correct!!!");
	   	}
	   	else{
	    	printf("\n>>>>Fail: supply count for adventurer is incorrect!!!");
	    	}
	    if(test.supplyCount[gardens] == 8){
	   		printf("\n>>>>SUCCESS: supply count for gardens is correct!!!");
	   	}
	   	else{
	    	printf("\n>>>>Fail: supply count for gardens is incorrect!!!");
	    	}

	    for(i =0; i < totalPlayers; i++){
			
			if(i==0){
				if(test.handCount[i] == 5){
					printf("\n>>>>SUCCESS: Player #%d hand count is 5!!!", i+1);
				}
				else{
					printf("\n>>>>Fail: Player #%d hand count is not 5!!!", i+1);
					}
			}
			else{
				if(test.handCount[i] == 0){
					printf("\n>>>>SUCCESS: Player #%d hand count is empty!!!", i+1);
				}
				else{
					printf("\n>>>>Fail: Player #%d hand count is not empty!!!", i+1);
					}
			}
		    if(test.discardCount[i] == 0){
		    	printf("\n>>>>SUCCESS: Player #%d discardCount is empty!!!", i+1);
		    }
		    else{
		    	printf("\n>>>>Fail: Player #%d discardCount is not empty!!!", i+1);
		    	}

	    }

	    if(test.numActions == 1){
	   		printf("\n>>>>SUCCESS: Number of actions is correct!!!");
	   	}
	   	else{
	    	printf("\n>>>>Fail: Number of actions is inrrect!!!");
	    	}

	    if(test.numBuys == 1){
	   		printf("\n>>>>SUCCESS: Number of buys is correct!!!\n\n");
	   	}
	   	else{
	    	printf("\n>>>>Fail: Number of buys is inrrect!!!");
	    	}
		/*
		if(test.handCount[0] == 5){
		    	printf("\n>>>>SUCCESS: Player #1 hand count contains 5 cards!!!");
		    }
		else{
		    printf("\n>>>>Fail: Player #1 hand count does contains 5 cards!!!");
		    	}
				
		if(test.handCount[1] == 0){
		    	printf("\n>>>>SUCCESS: Player #2 hand count is empty!!!");
		    }
		else{
		    printf("\n>>>>Fail: Player #2 hand count is not empty to start!!!");
		    	}
		*/




    return 0;
}