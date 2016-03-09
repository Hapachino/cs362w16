/* unittest3.c

   SUMMARY:
   1. Check if Card is in Game and Supply pile not empty.
   2. Option 0 - Add to Discard; increase player discard count
   3. Option 1 - Add to players deck; increase players deck count
   4. Option 2- Add to players hand; increase hand count 
   5. Decrease Supply Count

   FUNCTION TO TEST: 

   int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
   {
     //Note: supplyPos is enum of choosen card
	
     //check if supply pile is empty (0) or card is not used in game (-1)
     if ( supplyCount(supplyPos, state) < 1 )
     {
       return -1;
     }
	
     //added card for [whoseTurn] current player:
     // toFlag = 0 : add to discard
     // toFlag = 1 : add to deck
     // toFlag = 2 : add to hand

     if (toFlag == 1)
     {
       state->deck[ player ][ state->deckCount[player] ] = supplyPos;
       state->deckCount[player]++;
     }
     else if (toFlag == 2)
     {
       state->hand[ player ][ state->handCount[player] ] = supplyPos;
       state->handCount[player]++;
     }
     else
     {
        state->discard[player][ state->discardCount[player] ] = supplyPos;
        state->discardCount[player]++;
     }
	
     //decrease number in supply pile
     state->supplyCount[supplyPos]--;
	 
     return 0;
   }

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(int argc, char *argv[]){
    
    printf("Testing gainCard() unittest3.c\n");

    struct gameState G;
    int kingdoms[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy};
    initializeGame(2, kingdoms,1000, &G);
    G.coins = 2;
    G.numActions = 10;
    G.whoseTurn = 0;
    int startDeckCount;
   
    // check if no change in hand with no supply card
    G.supplyCount[smithy] = 0;    
    gainCard(smithy, &G, 2, 1);  
    assert(G.handCount[1] == 0);

    // check if inc in hand count
    G.supplyCount[smithy] = 1;    
    gainCard(smithy, &G, 2, 1);  
    assert(G.handCount[1] == 1);
 
    //check if correct card
    assert(G.hand[1][0]== smithy);
 
    //Check if inc in deckcount
    startDeckCount = G.deckCount[1];    
    G.supplyCount[smithy] = 1;
    gainCard(smithy, &G, 1, 1);  
    assert(G.deckCount[1] == startDeckCount +1); 

    //Check if no decrease in coins
    if (G.coins != 2){
	printf("State Promblem: coins");
    }

     if (G.numActions != 10){
	printf("State Problem: numActions");
    }

    if (G.whoseTurn != 0){
	printf("State Problem: Turn");
    }
   
    printf("END Testing gainCard() unittest3.c\n");

    return 0;
}