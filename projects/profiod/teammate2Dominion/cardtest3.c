#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// card test smithy
int main(int argc, char** argv) 
{
    int retValue; 
    struct gameState game; 
    int player = 0; 
    int i; 
    int cardPos; 
    int errorPresent = 0;
    int bonus;  
    
    // initialize game modeled from playdom.c
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    
    initializeGame(2, k, 1, &game);
   
    cardPos = 0; 
 
    for(i = 0; i < 5; i++)
    {
        game.hand[player][i] = estate; 
    }
    
    game.hand[player][0] = smithy; 
    
    game.handCount[player] = 5; 
    game.playedCardCount = 0; 
    
    retValue = cardEffect(smithy, 0, 0, 0, &game, cardPos, &bonus); 
    
    if(retValue != 0)
    {
        printf("\nError in smithy card, returned an error incorrectly.\n");
        errorPresent = 1; 
    }
    
    if(game.playedCardCount != 1)
    {
        printf("\nError in smithy card, did not discard played card properly.\n");
        errorPresent = 1;
    }
    
    if(game.handCount[player] != 7)
    {
        printf("\nError in smithy card, did not gain 3 cards.\n");
        errorPresent = 1;
    }
    
    if(errorPresent == 0)
    {
        printf("\nNo error found in smithy tests.\n");
    }
    
    return 0; 
}