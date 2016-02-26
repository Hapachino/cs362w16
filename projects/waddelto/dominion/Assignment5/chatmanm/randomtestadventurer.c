#include "dominion.h"
#include "test_helper.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <math.h>

#define TEST_PATHS 5
typedef enum {
	play_test = 0,
	shuffle_test,
	treasure_test,
	discard_test,
	cards_test
} test_type;


char *returnTestType(int test_type) {

	switch (test_type){
		case 0:
			return "play_test";
			break;
		case 1:
			return "shuffle_test";
			break;
		case 2:
			return "shuffle_test";
			break;
		case 3:
			return "discard_test";
			break;
		case 4:
			return "cards_test";
			break;
	}

	return "?";

}



void rTestAdventurer(long seed);

int main(int argc, char **argv) {

    int res;
    long seed;
    res = 0;
    seed = atoi(argv[1]);

    SelectStream(3);
    PutSeed(seed);

	rTestAdventurer(seed);


    return 0;

}

/*****************************
 * Adventure card test
 * This card draws cards until it adds
 * 2 coins to the hand.  Other cards are discarded.
 *
 * We're going to:
 *  a. Randomize kingdom cards 
 *  b. randomize the number of players
 *  c. initialize a game
 *  d. we're not going to test the shuffle
 *  e. so we're going to set up a deck that has a random number of cards
 *  f. and we're going to randomly insert in that deck three coin cards 
 *      in the deck to ensure that there are coins in the deck
 *  g.  we're going to copy the tester into a control
 *  g.  we're going to call int playCard
 *  h.  we're going to ignore error messages from the playCard function
 *  i.  We're going to check that the tester hand has two additional coins
 *  j.  we're going to draw cards from the control deck until we get to the
 *  two additional coins
 *  k.  we're going to check that the cards in the hand are the same as the
 *  three coins we drew.
 *  l.  we're going to check that the discard piles for the control and
 *  tester are the same size. 
 **********************************/
void rTestAdventurer(long seed)
{

    int i, j, m, shuffle, res;
    int count, tests, fail, playFail;

    count = 10000;
    tests = 0;
    fail = 0;

	struct test_restults {
		int test;
		int count;
	} results[TEST_PATHS];

	results[0].test = play_test;
	results[1].test = shuffle_test;
	results[2].test = treasure_test;
	results[3].test = discard_test;
	results[4].test = cards_test;

    for (i = 0; i < count; i++)
    {
        int k[10];
        randomizeKingdomCards(k);
        struct gameState Tester;
        struct gameState Control;

        int numPlayers = floor(Random() * (MAX_PLAYERS -2) + 2);
        assert(numPlayers >= 2 && numPlayers <= 4);

        initializeGame(numPlayers, k, seed, &Tester);

        for (j = 0; j < Tester.numPlayers; j++)
        {
            tests++;
            Tester.whoseTurn = j;
            Tester.phase = 0;
            Tester.numActions = 1;
            Tester.handCount[j] = floor(Random() * (MAX_HAND -2));
            assert(Tester.handCount[j] <= MAX_HAND -2);
            
            for (m = 0; m < Tester.handCount[j]; m++){
                Tester.hand[j][m] = floor(Random() * (treasure_map + 1));
                assert(Tester.hand[j][m] <= treasure_map + 1);   
            }

            //we're going to set a minimum size of 30 cards so we can
            //insert three treasure cards, just to be sure they're in there
            Tester.deckCount[j] = floor(Random() * (MAX_HAND - 30) + 30);
            assert(Tester.handCount[j] <= MAX_HAND - 2);

            for (m = 0; m < Tester.deckCount[j]; m++){
                Tester.deck[j][m] = floor(Random() * (treasure_map + 1));
                assert(Tester.hand[j][m] <= treasure_map + 1);
            }

            int insertionPoint1 = floor(Random() * Tester.deckCount[j]);
            assert(insertionPoint1 < Tester.deckCount[j]);
            
            int insertionPoint2;
            while(1){
                insertionPoint2 = floor(Random() * Tester.deckCount[j]);
                assert(insertionPoint2 < Tester.deckCount[j]);
                if (insertionPoint2 != insertionPoint1) break;
            }

            int insertionPoint3;
            while(1){
                insertionPoint3 = floor(Random() * Tester.deckCount[j]);
                assert(insertionPoint3 < Tester.deckCount[j]);
                if (insertionPoint3 != insertionPoint1 && 
                        insertionPoint3 != insertionPoint2) break;
            }

            Tester.deck[j][insertionPoint1] = copper;
            Tester.deck[j][insertionPoint2] = silver;
            Tester.deck[j][insertionPoint3] = gold;

            Tester.discardCount[j] = 0;

            //insert adventure card into deck
            int handPos;
            handPos = floor(Random() * Tester.handCount[j]);
            Tester.hand[j][handPos] = adventurer;

			//sometimes we want to test the shuffle routine.
			//So we're going to insert a randomizer % 2 to force a shuffle
			m =  (Random() * 22);
			m = m % 3;
			(m == 0) ? (shuffle = 1) : (shuffle = 0);

			if (shuffle){
	            int tempDeckCount = Tester.deckCount[j];
		        for (m = 0; m < tempDeckCount; m++){
			        Tester.discard[j][Tester.discardCount[j]-1] = Tester.deck[j][m];
				    Tester.discardCount[j]++;
					Tester.deckCount[j]--;
				}
			}
			




            //copy tester into control
            memcpy(&Control, &Tester, sizeof(Control));

            res = playCard(handPos, 0, 0, 0, &Tester);
            if (res == -1){
                results[0].count++; 
                continue;
            }

            //check effects

			//shuffle checker
			if (shuffle) {
				int Tester_totalCards = 0;
				Tester_totalCards = Tester.handCount[j] + Tester.deckCount[j] + Tester.discardCount[j];
				int Control_totalCards = 0;
				Control_totalCards = Control.handCount[j] + Control.deckCount[j] + Control.discardCount[j];

				if (Tester_totalCards != Control_totalCards) {
					results[1].count++;
					continue;
				}
			}





           //Does the tester have two additional coins in the hand?
           //How many coins in the control hand?
           int testerCount = 0;
           for (m = 0; m < Tester.handCount[j]; m++){
                int card = Tester.hand[j][m];
                if (card == copper || card == silver || card == gold)
                    testerCount++;
           }

           int controlCount= 0;
           for (m = 0; m < Control.handCount[j]; m++){
               int card = Control.hand[j][m];
               if (card == copper || card == silver || card == gold)
                   controlCount++;
           }

           //printf("TesterCount: %d\tControlCount:%d\n", testerCount, controlCount);
           if (testerCount != controlCount + 2){
               results[2].count++;
               continue;
           }

           //check to see that the tester only has two additional cards
           if(Tester.handCount[j] != Control.handCount[j] + 2){
                results[3].count++;
                continue;
           }

           //check to see if adventurer drew the correct cards
           //& number of cards
           int drawnTreasure = 0;
           int counter = 0;
           while (drawnTreasure <= 2){
                int card = Control.deck[j][Control.deckCount[j] - (counter + 1)];
                counter++;
                if (card == copper || card == silver || card == gold)
                    drawnTreasure++;

            }
           //printf("Tester.discardCount: %d\tTest Counter:%d\n", Tester.discardCount[j], counter);
           if (Tester.discardCount[j] != counter - 3){
               results[4].count++;
               continue;
           }


        }

    }

	//***************************
	//Results
	//**************************
	for (i = 0; i < TEST_PATHS;  i++)
		fail += results[i].count;

	printf("\n\nAdventurer Test Results: \n");
    printf("Total Tests:\t\t\t\t %d\n", tests);

	//print test by test results
	printf("\nTest path results:\n"); 
	printf("Play Card Function Failure:\t\t %d\n", results[0].count);
	printf("Card count after shuffle incorrect:\t %d\n", results[1].count);
	printf("Drew wrong amount of treasure: \t\t %d\n", results[2].count);
	printf("Incorrect discard: \t\t\t%d\n", results[3].count);
	printf("Drew wrong cards: \t\t\t%d\n", results[4].count);

    return;

}

