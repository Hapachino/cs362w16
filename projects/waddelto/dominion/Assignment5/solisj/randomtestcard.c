#include "dominion.h"
#include "test_helper.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <math.h>

#define TEST_PATHS 9

void rTestMinion(long seed);

int main(int argc, char **argv) {

    int res;
    long seed;
    res = 0;
    seed = atoi(argv[1]);

    SelectStream(3);
    PutSeed(seed);

	rTestMinion(seed);


    return 0;

}

/*****************************
 *  Random Minion Card Tester
 * 
 * As with the adventurer test for assignment 4, we had implemented
 *  random testing for all our tests in assignment 3.  
 *
 *  For assignment 3, we wrote for really good coverage. I want to say 
 *  that our tests for this were written to cover all of the 
 *  branches.  However, we didn't optimize the settings to deeply
 *  explore some of the branches.  Thus in execution, we weren't getting
 *  the penetration
 *
 *  In particular, we didn't fully explore choice2, where the current
 *  player discards his hand, forcing the other players to discard their
 *  hand if they have five or more cards.
 *
 *  We randomized the handsize and the choice selection.  I think our
 *  random range of hand size < MAX_HAND and together with the
 *  number of branches meant we weren't getting in there deeply
 *  to throw a lot of cases at it.
 *
 *  So, we've increased the number of cases from 1,000 to 10,000,
 *  and we've changed the handsize to random 1-10
 *
 *
 *  *  **************************************/

void rTestMinion(long seed)
{

    int i, j, m, n, res;
    int count, tests, fail, handPos;
    count = 10000;
    tests = 0;
    fail = 0;

	struct test_results {
		int test;
		int count;
	} results[9];

	for (i = 0; i < TEST_PATHS; i++){
		results[i].count = 0;
		results[i].test = 1;
	}

    for (i = 0; i < count; i++)
    {

		tests++;
        int k[10];
        randomizeKingdomCards(k);
        struct gameState Tester;
        struct gameState Control;

        int numPlayers = floor(Random() * (MAX_PLAYERS - 2) + 2);
        assert (numPlayers >= 2 && numPlayers <= 4);

        res = initializeGame(numPlayers, k, seed, &Tester);
        assert(res != -1); //initialization fail

        Tester.whoseTurn = Random() * Tester.numPlayers;

        //we're going to randomize everyone's hand
        //(j loop) before we call the card
        for (j = 0; j < Tester.numPlayers; j++)
        {
            Tester.phase = 0;
            Tester.numActions = 1;
            Tester.coins = 0;
            Tester.handCount[j] = round(Random() * (6-2) + 2);
            assert(Tester.handCount[j] >= 2 && Tester.handCount[j] <= 6);

            for (m = 0; m < Tester.handCount[j]; m++){
                Tester.hand[j][m] = floor(Random() * (treasure_map + 1));
                assert(Tester.hand[j][m] < treasure_map+1);
            }

            handPos = 0;
            assert (handPos < Tester.handCount[j]);

            Tester.hand[j][handPos] = minion;

            Tester.discardCount[j] = 0;
            Tester.playedCardCount = 0;

        }

       
        memcpy(&Control, &Tester, sizeof(Control));

        //randomize choice one or two
	    n = tests % 2;
        int choice1 = 0;
        int choice2 = 0;
		int choice3 = 0;

        (n == 0) ? (choice1 = 1) : (choice2 = 1);
        res = playCard(handPos, choice1, choice2, choice3, &Tester);
        if (res == -1){
			results[0].count++;
            continue;
        }
        int currentPlayer;
        currentPlayer = Tester.whoseTurn;
        //check the effects
        //check action increased
        if (Tester.numActions != 1){
            results[1].count++;
            //continue;
        }
        //Check effects of each path
        if (choice1){
            //check increased coins
            if (Tester.coins != 0){
				results[2].count++;
         //       continue;
            }
           //check discarded minion
            if (Tester.playedCardCount != 1){
				results[3].count++;
         //       continue;
            }
        }
        else{
            //current player effects
            if (Tester.discardCount[currentPlayer] != Control.handCount[currentPlayer]){
				results[4].count++;
         //       continue;
            }
            //check current handcount = 4 and that the deck is 4 less
            if (Tester.handCount[currentPlayer] != 4 && Tester.deckCount[currentPlayer] != Control.deckCount[currentPlayer] -4){
				results[5].count++;
           //     continue;
            }
            //Check other players
            for(j = 0; j < Tester.numPlayers; j++){
                if (j != currentPlayer){
                    //check to see if other player handsize >= 5
                    if (Control.handCount[j] >= 5) {
                       if(Tester.discardCount[j] != Control.handCount[j]){
							results[6].count++;
             //               continue;
                       }
                       if(Tester.handCount[j] != 4 && Tester.deckCount[j] != Control.deckCount[j] - 4){
						   results[7].count++;
               //             continue;
                       }
                    }
					else { //other player's hand <5 don't do anything
						if (Tester.discardCount[j] != 0){
							results[8].count++;
				//			continue;
						}

					}

                }
            }
        }

    }

	/*********************
	 * results
	 * ******************/

    printf("Minion Results: Tests:\t\t %d\n", tests);
	printf("Card Effect Returned -1:\t %d\n", results[0].count);
	printf("Path 1:\n");
	printf("Failed to add one action:\t\t %d\n", results[1].count);
	printf("Failed to record coins correctly: \t%d\n", results[2].count);
	printf("Failed to discard played card:\t%d\n", results[3].count);
	printf("Path 2\n");
	printf("Current player failed to discard current hand:\t%d\n", results[4].count);
	printf("Current player failed to draw four cards: \t%d\n", results[5].count);
	printf("Other player didn't discard hand >=5:\t%d\n", results[6].count);
	printf("Other player didn't draw new hand:\t%d\n", results[7].count);
	printf("Other player discard when hand < 5:\t%d\n", results[8].count);
	
	
	return;
}
