/*********************************************************************
** Program Filename: unittest1.c
** Author: Kyle Johnson
** Date: 2/2/2016
** Description: implementation file for updateCoins() testing
*********************************************************************/ 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//set-up and initialization based on testUpdateCoins.c, CS362W16
int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
	struct gameState G;
    int maxHandCount = 5;
    
	// arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    
	for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("----------------- Testing updateCoins(): ----------------\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {

                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);

                memset(&G, 23, sizeof(struct gameState));   
                r = initializeGame(numPlayer, k, seed, &G); 
                G.handCount[p] = handCount;              			// set the number of cards on hand
				memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);

                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
				// check if the number of coins is correct
                if (G.coins == handCount * 1 + bonus)
					printf("PASSED - correct number of copper coins = %d\n", handCount * 1 + bonus );
				else 
					printf("FAILED - incorrect number of copper coins\n");
				
                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
				
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
				// check if the number of coins is correct
                if (G.coins == handCount * 2 + bonus)
					printf("PASSED - correct number of silver coins = %d\n", handCount * 2 + bonus );
				else 
					printf("FAILED - incorrect number silver of coins\n");

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);

                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
				// check if the number of coins is correct
                if (G.coins == handCount * 3 + bonus)
					printf("PASSED - correct number of gold coins = %d\n", handCount * 3 + bonus );
				else 
					printf("FAILED - incorrect number of gold coins\n");
            }
        }
    }

    printf("completed testing of updateCoins()\n");

    return 0;
}