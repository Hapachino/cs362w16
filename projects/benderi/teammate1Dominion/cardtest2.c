/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Unit test for Adventurer card.
 * Business Requirements
 *      - draw cards until at least 2 treasure cards are drawn
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() 
{
    int i, j;
    int outcome;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int cardDrawn1, cardDrawn2;
    int treasureCnt1 = 0, treasureCnt2 = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

    printf("TESTING - ADVENTURER CARD\n");
    //initialize game state
    outcome = initializeGame(numPlayers, k, seed, &G);
    if (outcome == -1)
        printf("ERROR - Game initialization failed.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    //give Adventurer card to player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = adventurer;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("SUCCESS - Adventurer card given to player.\n");
    else
        printf("ERROR - Adventurer card not given.\n");

    //play Adventurer card
    //code adjusted for use in teammate2 function
    playAdventurer(&testG, thisPlayer);
    //playAdventurer(thisPlayer, &testG);

    //verify that at least 2 new treasure cards were added to hand
    for (i = 0; i < testG.handCount[thisPlayer]; i++) 
    {
       cardDrawn1 = testG.hand[thisPlayer][i];
       if (cardDrawn1 == copper || cardDrawn1 == silver || cardDrawn1 == gold)
          treasureCnt1++;
    }
    for (i = 0; i < G.handCount[thisPlayer]; i++) 
    {
       cardDrawn2 = G.hand[thisPlayer][i];
       if (cardDrawn2 == copper || cardDrawn2 == silver || cardDrawn2 == gold)
          treasureCnt2++;
    }
    if ((treasureCnt1 - treasureCnt2) > 0 || (treasureCnt1 - treasureCnt2) < 3 )
       printf("SUCCESS - %d additional treasure cards drawn.\n", 
                  (treasureCnt1 - treasureCnt2));
    else
       printf("ERROR - Less than 1 or more than 3 treasure cards drawn.\n");


    //verify more cards in test state hand than original hand
    if (G.handCount[thisPlayer] < testG.handCount[thisPlayer])
       printf("SUCCESS - Additional cards added to test hand.\n");
    else
       printf("ERROR - No additional cards added to test hand.\n");

    printf("TEST COMPLETE\n\n");

    return 0;

}
