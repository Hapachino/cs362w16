#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// card test salvager
int main(int argc, char** argv) 
{
    int retValue; 
    struct gameState game; 
    int trashedCard;
    int trashedCardVal;  
    int trashedCardPos; 
    int player = 0; 
    int i; 
    int cardPos; 
    int errorPresent = 0;
    int bonus;  
    
    game.numPlayers = 2; 
    game.numActions = 0; 
    game.numBuys = 0; 
    game.coins = 0; 
    
    trashedCard = silver; 
    trashedCardVal = 3; 
    trashedCardPos = 1;
    cardPos = 0; 
 
    for(i = 0; i < 5; i++)
    {
        game.hand[player][i] = estate; 
    }
    
    game.handCount[player] = 5; 
    game.hand[player][trashedCardPos] = trashedCard;
    game.hand[player][cardPos] = salvager;  
    bonus = 0; 
    game.playedCardCount = 0; 
    
    
    retValue = cardEffect(salvager, trashedCardPos, 0, 0, &game, cardPos, &bonus); 
    
    if(retValue != 0)
    {
        printf("\nError in salvager card, returned an error incorrectly.\n");
        errorPresent = 1; 
    }
    
    if(game.numBuys != 1)
    {
        printf("\nError in salvager card, did not increase number of buys by 1.\n");
        errorPresent = 1;
    }
    
    if(game.handCount[player] != 3)
    {
        printf("\nError in salvager card, did not remove two cards from hand.\n");
        errorPresent = 1;
    }
    
    if(game.playedCardCount == 0)
    {
        printf("\nError in salvager card, did not discard played salvager card.\n");
        errorPresent = 1;
    }
    else if(game.playedCardCount == 2)
    {
        printf("\nError in salvager card, did not trash selected card.\n");
        errorPresent = 1;
    }
    else if(game.playedCardCount != 1)
    {
        printf("\nError in salvager card, did not discard proper amount of cards.\n");
        errorPresent = 1;
    }
    
    if(game.coins != trashedCardVal)
    {
        printf("\nError in salvager card, did not update coins with value of trashed card.\n");
        errorPresent = 1;
    }
    
    // reset hand for test of non card 
    for(i = 0; i < 5; i++)
    {
        game.hand[player][i] = estate; 
    }
    
    game.handCount[player] = 5; 
    game.hand[player][trashedCardPos] = trashedCard;
    game.hand[player][cardPos] = salvager;  
    bonus = 0; 
    game.playedCardCount = 0; 
    game.numBuys = 0; 
    game.coins = 0; 
    
    retValue = cardEffect(salvager, 0, 0, 0, &game, cardPos, &bonus); 
    
    if(retValue != 0)
    {
        printf("\nError in salvager card, returned an error incorrectly.\n");
        errorPresent = 1; 
    }
    
    if(game.numBuys != 1)
    {
        printf("\nError in salvager card, did not increase number of buys by 1 when called with no selection.\n");
        errorPresent = 1;
    }
    
    if(game.handCount[player] != 4)
    {
        printf("\nError in salvager card, did not remove one card from hand when played with no selection.\n");
        errorPresent = 1;
    }
    
    if(game.playedCardCount != 1)
    {
        printf("\nError in salvager card, did not discard proper amount of cards.\n");
        errorPresent = 1;
    }
    
    if(game.coins != 0)
    {
        printf("\nError in salvager card, added coins with no card selected.\n");
        errorPresent = 1;
    }
    
    if(errorPresent == 0)
    {
        printf("\nNo error found in salvager tests.\n");
    }
    
    return 0; 
}