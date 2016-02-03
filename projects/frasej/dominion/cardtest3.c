//test gardens
//gardens does nothing and should not change the gamestate
//since gardens is a victory card but between adventurer and treasure_map should return -1
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

int main(){
    struct gameState G, pre;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int p, r;
    int bonus = 0;
    int pass = 1;

    r = initializeGame(MAX_PLAYERS, k, 1, &G); // initialize a new game
    assert(r == 0);

    memcpy(&pre, &G, sizeof(struct gameState));

    printf ("TESTING gardens card:\n");
    for(p = 0; p < MAX_PLAYERS; p++){
        pre.whoseTurn = p;
        G.whoseTurn = p;
        r = cardEffect(gardens, 0, 0, 0, &G, 0, &bonus);
        assert(r == -1);
        if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
            if(DEBUG)
                printf("TEST FAILED: gardens changed the gameState for player %d\n", p);
            pass = 0;
        }
    }
    if(pass)
        printf("gardens card tests passed!\n");
    else
        printf("gardens tests failed!\n");
    return 0;
}
