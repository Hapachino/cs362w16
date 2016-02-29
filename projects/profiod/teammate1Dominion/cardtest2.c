#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// card test village
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
    game.numActions = 0; 
    
    retValue = cardEffect(village, 0, 0, 0, &game, cardPos, &bonus); 
    
    if(retValue != 0)
    {
        printf("\nError in village card, returned an error incorrectly.\n");
        errorPresent = 1; 
    }
    
    if(game.playedCardCount != 1)
    {
        printf("\nError in village card, did not discard played card properly.\n");
        errorPresent = 1;
    }
    
    if(game.handCount[player] != 5)
    {
        printf("\nError in village card, did not gain a card.\n");
        errorPresent = 1;
    }
    
    if(game.numActions != 2)
    {
        printf("\nError in village card, did not gain two actions.\n");
        errorPresent = 1;
    }
    
    if(errorPresent == 0)
    {
        printf("\nNo error found in village tests.\n");
    }
    
    return 0; 
}