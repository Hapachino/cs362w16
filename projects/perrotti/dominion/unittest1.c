/*
 * unittest1.c
 * This test is for the function "isGameOver()"
 * This test ensures that this procedure works given a random game state
 * with default values provided for critical items.
 *
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int main () {
    struct gameState g;
    int player, 
    
    
    int i;
    for (i = 0; i < sizeof(struct gameState); i++) {
        ((char*)&g)[i] = floor(random() * 256);
    }
    
    
    
    

}