/* -----------------------------------------------------------------------
 * Test is for updateCoins()
 * unittest2
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"



int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState test;
    int maxHandCount = 5;
    
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    int v =2;
    int w = 2;
    printf ("-------TESTING updateCoins()--------\n");
    for (p = 0; p < numPlayer; p++)
    {
                
                bonus = rand()% maxBonus;
                handCount = 5;
                printf("Player #%d with %d treasure cards and %d bonus.\n", p, handCount, bonus);

                memset(&test, 23, sizeof(struct gameState));   
                initializeGame(numPlayer, k, seed, &test); 
                test.handCount[p] = handCount;                 
                memcpy(test.hand[p], coppers, sizeof(int) * handCount); 
                updateCoins(p, &test, bonus);

                printf("All Copper Coins = %d, expected = %d\n", test.coins, handCount * 1 + bonus);

                if(test.coins == handCount * 1 + bonus){
                    printf(">>>SUCCESS: Coins are equal!!!\n");
                }
                else{
                    printf(">>>FAIL: Coins are not equal!!!\n");
                }

                memcpy(test.hand[p], silvers, sizeof(int) * handCount); 
                updateCoins(p, &test, bonus);

                printf("All Silver Coins = %d, expected = %d\n", test.coins, handCount * 2 + bonus);

                 if(test.coins == handCount * 2 + bonus){
                    printf(">>>SUCCESS: Coins are equal!!!\n");
                }
                else{
                    printf(">>>FAIL: Coins are not equal!!!\n");
                }
                

                memcpy(test.hand[p], golds, sizeof(int) * handCount); 
                updateCoins(p, &test, bonus);

                printf("All Gold Coins = %d, expected = %d\n", test.coins, handCount * 3 + bonus);

                 if(test.coins == handCount * 3 + bonus){
                    printf(">>>SUCCESS: Coins are equal!!!\n");
                }
                else{ 
                    printf(">>>FAIL: Coins are not equal!!!\n");
                }
                if(p==0){
                printf("----Now Testing 5 Treasured Card, Mixed Coins: %d gold, 1 silver and %d copper\n", v, w);
                bonus = rand()% maxBonus;
                memset(&test, 23, sizeof(struct gameState));   
                initializeGame(numPlayer, k, seed, &test);
                memcpy(test.hand[p], golds, sizeof(int) * v);
                memcpy(test.hand[p] + v, silvers, sizeof(int) * 1);
                memcpy(test.hand[p] + v + 1, coppers, sizeof(int) * w);

                updateCoins(p, &test, bonus);

                printf("All Coins = %d, expected = %d\n", test.coins, (v*3)+2+(w*1)+bonus);

                 if(test.coins == (v*3)+2+(w*1)+bonus){
                    printf(">>>SUCCESS: Coins are equal!!!\n");
                }
                else{ 
                    printf(">>>FAIL: Coins are not equal!!!\n");
                }

            }
             
            }
      

    return 0;
}