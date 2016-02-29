#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() {
    struct gameState G;
    int seed = 1000;
    int numPlayers = 2;
    int curPlayer = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};  
    int deckSize;
    int handSize;
    int handPos;
    int deckBefore;
    int deckAfter;
    int handBefore;
    int handAfter;
    int discardBefore;
    int discardAfter;
    int i;
    int deckFailure = 0;
    int handFailure = 0;
    int discardFailure = 0;
    int testPassed = 0;
    int passed;
    
    srand(time(NULL));
   
    for(i = 0; i < 100000; i++){
        initializeGame(numPlayers, k, seed, &G);
        deckSize = rand() % (MAX_DECK + 1);
   
        handSize = rand() % (deckSize + 1);
      
        
        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;
        
        handPos = G.hand[curPlayer][G.handCount[curPlayer] - 1];
        
        deckBefore = G.deckCount[0];
        //printf("deck before %d\n", deckBefore);
        handBefore = G.handCount[0];
        //printf("Hand before %d\n",handBefore);
        discardBefore = G.playedCardCount;
        //printf("Discard before %d\n", discardBefore);
        
        printf("Deck Before: %d\n\n",deckBefore);
        
        playSmithy(handPos, &G);
        int curPlayer = whoseTurn(&G);
        
        deckAfter = G.deckCount[0];
        //printf("deck after %d\n", deckAfter);
        handAfter = G.handCount[0];
        //printf("hand After %d\n", handAfter);
        discardAfter = G.playedCardCount;
        //printf("Discard After %d\n\n", discardAfter);
        
        passed = 1;
            
        if(handAfter != (handBefore + 2)){
            printf("Incorrect amount of cards drawn: Test Failed\n\n");
            handFailure++;
            passed = 0;
        }
        
        if(deckAfter != (deckBefore - 3)){
            printf("Deck After: %d\n\n",deckAfter);
            printf("Incorrect number of cards removed from deck: Test Failed\n\n");
            deckFailure++;
            passed = 0;
        }
        
        if(discardAfter != (discardBefore + 1)){
            printf("Smithy Not Discarded after use: Test Failed\n\n");
            discardFailure++;
            passed = 0;
        }
        
        
        
        if(passed == 1){
            printf("All Tests Passed\n\n");
            testPassed++;
        }
        
    }
        
   printf("\n\n");
   printf("Tests Passed: %d\n", testPassed);
   printf("Cards Drawn To Hand Failed %d\n", handFailure);
   printf("Smithy Discarded Failed: %d\n\n", discardFailure);        
   
   return 0;
}