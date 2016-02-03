/*
 * unittest2.c
 * This test is for the function "getCost()"
 * This test ensures that getCost returns the appropriate cost for each card.
 * The test also tests bounds outside of the cards provided (greater than, and also negative).
 * Requirement 1: Appropriate value should be returned for each card
 * Solution: Test all card inputs at least once, and create a new value list chart to ensure original code values were correct
 * Requirement 2: Appropriate value should be returned for negative numbers
 * Solution: If a negative value is provided, the program should return -1. Test with negative numbers
 * Requirement 3: If a card value is provided that is not in the enum, it should return -1
 * Solution: Provide card values higher than what the system is designed to handle with the switch statement
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
#include <time.h>

#define cardCount 27

int main () {
    srand(time(NULL));
    
    printf("Testing getCost().\n");
    
    /* Array created by looking up card values online, and putting 
    into a card array for comparison against switch statement */
    int cardValueArray[cardCount] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4,
                        4, 5, 4, 4, 3, 4, 3, 5, 3, 5,
                        3, 4, 2, 5, 4, 4, 4};
    
    /* Testing 2000 times becuase we have 30 different random inputs. 
    Should achieve */
    int i;
    for (i = 0; i < 2000; i++) {
        /* This will produce valid numbers for all cards, -3, 
        and 3 above the valid card range */
        int card = (rand() % (cardCount + 7)) - 3;
        
        // Run the function in question to determine the cost
        int cardCost = getCost(card);
        
        /* Check to see if it is an out of bounds card, in which case, 
        assign card value expected to -1. If it's a valid card number, 
        compare against control array in this program with the functions
        return value */
        if (card < 0 || card >= cardCount) { // Requirement 2 and 3
            card = -1;
            printf("Testing card number %d -- ", card);
            printf("Expecting: %d, Received: %d\n", cardValueArray[card], cardCost);
            assert(card == cardCost);
        } else { // Requirement 1
            printf("Testing card number %d\n", card);
            printf("Expecting: %d, Received: %d\n", cardValueArray[card], cardCost);
            assert(cardValueArray[card] == cardCost);
        }
    }
    
    printf("Finished all getCost() tests succesfully!\n");
    return 0;
}
