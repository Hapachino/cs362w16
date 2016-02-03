#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    struct gameState G;
    int seed = 1000;
    int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    
    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    G.handCount[1] = 5;
    int player0Hand = G.handCount[0];
    int player1Hand = G.handCount[1];
    int played = G.playedCardCount;
    
    printf ("\n\nTESTING discardCard():\n\n");
    
    printf ("Current player 0 Hand Count: %d\n", G.handCount[0]);
    assert(G.handCount[0] == player0Hand);
    printf ("Current player 1 Hand Count: %d\n", G.handCount[1]);
    assert(G.handCount[1] == player1Hand);
    printf ("Number of Cards in played pile: %d\n\n", G.playedCardCount);
    assert(G.playedCardCount == played);
    
    discardCard(3, 0, &G, 0);
    
    printf ("player 0 Hand Count after discard for player 0: %d\n", G.handCount[0]);
    assert(G.handCount[0] == player0Hand - 1);
    printf ("player 1 Hand Count after discard for player 0: %d\n", G.handCount[1]);
    assert(G.handCount[1] == player1Hand);
    printf ("Number of Cards in played pile: %d\n\n", G.playedCardCount);
    assert(G.playedCardCount == played + 1);
    
    printf ("\n\nTESTING discardCard() Completed Successfully!\n\n");
    return 0;
}
