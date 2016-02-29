/* -----------------------------------------------------------------------
 * Test is for isGameOver()
 *
 * unittest3
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

    int reset;
  
    int seed = 1000;
    int totalPlayers = 2;
   

    int result;

   
    printf("\n--------Testing #1 for isGameOver function for no state change----------");

    memset(&test, 23, sizeof(struct gameState));   // clear the game state

    reset = initializeGame(totalPlayers, k, seed, &test); // initialize a new game

    result = isGameOver(&test);

    if(result == 0){
    	printf("\n>>>>>>SUCCESS: No change in game state: game continues");
    }
    else{
    	printf("\n>>>>>>Fail: Game was not suppose to end!!!");
    }

    printf("\n--------Testing #2 for isGameOver function for province = 0----------");

    memset(&test, 23, sizeof(struct gameState));   // clear the game state

    reset = initializeGame(totalPlayers, k, seed, &test); // initialize a new game
    test.supplyCount[province] = 0;
    result = isGameOver(&test);

    if(result == 1){
    	printf("\n>>>>>>SUCCESS: Province is out of supply: game ends");
    }
    else{
    	printf("\n>>>>>>Fail: Game was suppose to end!!!");
    }
    printf("\n--------Testing #3 for isGameOver function for province = 1----------");

    memset(&test, 23, sizeof(struct gameState));   // clear the game state

    reset = initializeGame(totalPlayers, k, seed, &test); // initialize a new game
    test.supplyCount[province] = 1;

    result = isGameOver(&test);

    if(result == 0){
    	printf("\n>>>>>>SUCCESS: Province has only 1 card left: game continues");
    }
    else{
    	printf("\n>>>>>>Fail: Game was not suppose to end!!!");
    }

    printf("\n--------Testing #4 for isGameOver function for province = 1, one supply count is 0----------");
    test.supplyCount[adventurer] = 0;
    result = isGameOver(&test);

    if(result == 0){
    	printf("\n>>>>>>SUCCESS: Game must continue!!!");
    }
    else{
    	printf("\n>>>>>>Fail: Game was not suppose to end!!!");
    }
    printf("\n--------Testing #5 for isGameOver function for province = 1, two supply count is 0----------");
    test.supplyCount[smithy] = 0;
    result = isGameOver(&test);

    if(result == 0){
    	printf("\n>>>>>>SUCCESS: Game must continue!!!");
    }
    else{
    	printf("\n>>>>>>Fail: Game was not suppose to end!!!");
    }
    printf("\n--------Testing #6 for isGameOver function for province = 1, three supply count is 0----------");
    test.supplyCount[feast] = 0;
    result = isGameOver(&test);

    if(result == 1){
    	printf("\n>>>>>>SUCCESS: Game must end!!!");
    }
    else{
    	printf("\n>>>>>>Fail: Game was suppose to end!!!");
    }


	return 0;
    
    
}