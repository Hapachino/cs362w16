//test adventurer
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

int main(){
    struct gameState G, pre, test;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int i, p, r, v, s;
    int precards[MAX_DECK], cards[MAX_DECK];
    int bonus = 0;
    int cardCount;
    int pass = 1;

    r = initializeGame(MAX_PLAYERS, k, 1, &G); // initialize a new game
    assert(r == 0);

    for(i = 0; i < MAX_DECK; i++){
        precards[i] = estate;
    }

    printf ("TESTING adventurer card:\n");
    //set deck with 2 treasure at front
    //set deck with 2 treasure at back
    //set empty deck
    //check all players
    for(i = 0; i < MAX_PLAYERS; i++){
        G.whoseTurn = i;
        //check different cardCount sizes don't have a problem
        for(cardCount = 10; cardCount < MAX_DECK + 1; cardCount++){

            for(p = 0; p < MAX_PLAYERS; p++){
                G.handCount[p] = 1;
                G.hand[p][0] = adventurer;
                G.discardCount[p] = 0;
                G.deckCount[p] = cardCount - 1;
                memcpy(G.deck[p], cards, sizeof(int) * (cardCount - 1));
            }

            memcpy(&pre, &G, sizeof(struct gameState));

            for(v = copper; v <= gold; v++){
                memcpy(&G, &pre, sizeof(struct gameState));
                G.deck[i][G.deckCount[i] - 1] = v;
                G.deck[i][G.deckCount[i] - 2] = v;
                memcpy(&test, &G, sizeof(struct gameState));

                r = cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus);
                assert(r == 0);

                for(p = 0; p < MAX_PLAYERS; p++){
                    if(p == i){
                        if(G.deckCount[i] != test.deckCount[i] - 2){
                            if(DEBUG)
                                printf("A TEST FAILED: adventurer did not take exactly the top 2 cards from the deck which were %d cards for player %d\n", v, i);
                            pass = 0;
                        }
                        for(s = 0; s < G.deckCount[i]; s++){
                            if(G.deck[i][s] != pre.deck[i][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the deck besides taking the top two treasure cards\n", p);
                                pass = 0;
                            }
                        }

                        if(G.discardCount[i] != test.discardCount[i] + 1){
                            if(DEBUG)
                                printf("A TEST FAILED: adventurer did not discard a card from the hand for player %d\n", i);
                            pass = 0;
                        }
                        for(s = 0; s < test.discardCount[i]; s++){
                            if(G.discard[i][s] != test.discard[i][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the discard when only 2 cards were drawn\n", i);
                                pass = 0;
                            }
                        }
                        if(G.discard[i][G.discardCount[i] - 1] != smithy){
                            if(DEBUG)
                                printf("A TEST FAILED: adventurer did not discard adventurer card from the hand for player %d\n", i);
                            pass = 0;
                        }

                        if(G.handCount[i] != test.handCount[i] + 1){
                            if(DEBUG)
                                printf("A TEST FAILED: adventurer did not add 2 cards which were %d from the deck for player %d\n", v, i);
                            pass = 0;
                        }
                    }
                    else{
                        if(G.deckCount[p] != pre.deckCount[p]){
                            if(DEBUG)
                                printf("A TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.deckCount[p]; s++){
                            if(G.deck[p][s] != pre.deck[p][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                                pass = 0;
                            }
                        }


                        if(G.handCount[p] != pre.handCount[p]){
                            if(DEBUG)
                                printf("A TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.handCount[p]; s++){
                            if(G.hand[p][s] != pre.hand[p][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                                pass = 0;
                            }
                        }


                        if(G.discardCount[p] != pre.discardCount[p]){
                            if(DEBUG)
                                printf("A TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.discardCount[p] - 1; s++){
                            if(G.discard[p][s] != pre.discard[p][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                                pass = 0;
                            }
                        }
                    }
                }

                memcpy(&G, &pre, sizeof(struct gameState));
                G.deck[i][0] = v;
                G.deck[i][1] = v;
                memcpy(&test, &G, sizeof(struct gameState));

                r = cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus);
                assert(r == 0);

                for(p = 0; p < MAX_PLAYERS; p++){
                    if(p == i){
                        if(G.deckCount[i] != 0){
                            if(DEBUG)
                                printf("B TEST FAILED: adventurer did not take all the cards from the deck for player %d\n", i);
                            pass = 0;
                        }

                        if(G.discardCount[i] != test.discardCount[i] + test.deckCount[i] - 1){
                            if(DEBUG)
                                printf("B TEST FAILED: adventurer did not discard the right number of cards from the hand and deck for player %d\n", i);
                            pass = 0;
                        }
                        for(s = 0; s < test.discardCount[i]; s++){
                            if(G.discard[i][s] != test.discard[i][s]){
                                if(DEBUG)
                                    printf("B TEST FAILED: player %d's adventurer altered the discard when all cards were drawn\n", i);
                                pass = 0;
                            }
                        }
                        if(G.discard[i][G.discardCount[i] - 1] != smithy){
                            if(DEBUG)
                                printf("B TEST FAILED: adventurer did not discard adventurer card from the hand for player %d\n", i);
                            pass = 0;
                        }

                        if(G.handCount[i] != test.handCount[i] + 1){
                            if(DEBUG)
                                printf("B TEST FAILED: adventurer did not add 2 cards which were %d from the deck for player %d\n", v, i);
                            pass = 0;
                        }

                    }
                    else{
                        if(G.deckCount[p] != pre.deckCount[p]){
                            if(DEBUG)
                                printf("B TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.deckCount[p]; s++){
                            if(G.deck[p][s] != pre.deck[p][s]){
                                if(DEBUG)
                                    printf("B TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                                pass = 0;
                            }
                        }


                        if(G.handCount[p] != pre.handCount[p]){
                            if(DEBUG)
                                printf("B TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.handCount[p]; s++){
                            if(G.hand[p][s] != pre.hand[p][s]){
                                if(DEBUG)
                                    printf("B TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                                pass = 0;
                            }
                        }


                        if(G.discardCount[p] != pre.discardCount[p]){
                            if(DEBUG)
                                printf("B TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.discardCount[p] - 1; s++){
                            if(G.discard[p][s] != pre.discard[p][s]){
                                if(DEBUG)
                                    printf("B TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                                pass = 0;
                            }
                        }
                    }
                }


                memcpy(&G, &pre, sizeof(struct gameState));
                G.deckCount[i] = 0;
                G.discardCount[i] = cardCount - 1;
                memcpy(G.discard[i], cards, sizeof(int) * (cardCount - 1));
                G.discard[i][0] = v;
                G.discard[i][1] = v;
                memcpy(&test, &G, sizeof(struct gameState));

                r = cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus);
                assert(r == 0);

                for(p = 0; p < MAX_PLAYERS; p++){
                    if(p == i){
                        if(G.handCount[i] != test.handCount[i] + 1){
                            if(DEBUG)
                                printf("C TEST FAILED: adventurer did not add 2 cards which were %d from the deck for player %d\n", v, i);
                            pass = 0;
                        }

                    }
                    else{
                        if(G.deckCount[p] != pre.deckCount[p]){
                            if(DEBUG)
                                printf("C TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.deckCount[p]; s++){
                            if(G.deck[p][s] != pre.deck[p][s]){
                                printf("C TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                                pass = 0;
                            }
                        }


                        if(G.handCount[p] != pre.handCount[p]){
                            if(DEBUG)
                                printf("C TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.handCount[p]; s++){
                            if(G.hand[p][s] != pre.hand[p][s]){
                                if(DEBUG)
                                    printf("C TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                                pass = 0;
                            }
                        }


                        if(G.discardCount[p] != pre.discardCount[p]){
                            if(DEBUG)
                                printf("C TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.discardCount[p] - 1; s++){
                            if(G.discard[p][s] != pre.discard[p][s]){
                                if(DEBUG)
                                    printf("C TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                                pass = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    if(pass)
        printf("adventurer card tests passed!\n");
    else
        printf("adventurer tests failed!\n");
    return 0;
}
