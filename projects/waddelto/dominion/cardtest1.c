#include "dominion.h"
#include "test_helper.h"
#include <stdio.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <math.h>


/**************************
 * cardtest1.c
 * Smithy Card Test
 *
 * We're going to:
 *  create two game structs: control and test
 *
 *  We're going to randomize the state of the game
 *  We're going copy the game state to our control
 *  We're going to call smithyEffects
 *  Then we're going to check to see if the top 
 *  three cards from the draw deck are now in the hand
 *  and that the smithy card has been discarded.    
 *  *****************************/

void smithyTest(long seed)
{
    int i, j, m, res;
    int count = 1000;
    int tests = 0;
    int fail = 0;

    for (i = 0; i < count; i++)
    {
      int k[10];
      randomizeKingdomCards(k);

      struct gameState Tester;
      struct gameState Control;

      int numPlayers = floor(Random() * (MAX_PLAYERS - 2) + 2);
      assert(numPlayers >= 2 && numPlayers <= 4);
      initializeGame(numPlayers, k, seed, &Tester);


      //randomize handstates, deck, draw states for each player
        for (j = 0; j < Tester.numPlayers; j++)
        { 
            tests++;
            //randomize hand
            //Tester.handCount[j] = 100;
            Tester.handCount[j] = floor(Random() * MAX_HAND-3);
            assert (Tester.handCount[j] < (MAX_HAND-3));
            for (m = 0; m < Tester.handCount[j]; m++)
                Tester.hand[j][m] = floor(Random() * (treasure_map + 1));

            //If there are less than 3 cards in the deck when we play the
            //smithy, we have no way to tell if the draw correctly chose the
            //top three cards of the deck because of the shuffle.  We're not
            //testing the shuffle here, so we're going to pass any tests where
            //there are lesS THAN Three cards in the hand.
       
            //Tester.deckCount[j] = 200;
            Tester.deckCount[j] = floor(Random() * (MAX_DECK - 3) ) + 3;
            assert((Tester.deckCount[j] < MAX_DECK - 3) && (Tester.deckCount[j] >= 3));
            for (m = 0; m < Tester.deckCount[j]; m++){
                Tester.deck[j][m] = floor(Random() * (treasure_map + 1));
                //printf("Deck value[%d]: %d\n", m, Tester.hand[j][m]);
            }
            //in the real game, it seems impossible to have a hand of less
            //than three cards.  Even if one burns or trashes a lot of
            //cards, one would have three estates.
            //
            //But the code does not protect against an endless look where 
            //it's trying to play a smithy card, but the player has less
            //than three total cards in deck or discard. 
            //In order to protect against this known logic gap, we're going
            //to hard code the test so that there should always be at least
            //three cards in the discard that could be shuffled to enable
            //to smithy draw.
            
            Tester.discardCount[j] = floor((Random() * (MAX_DECK -3)) + 3);
            for (m = 0; m <Tester.discardCount[j]; m++)
                Tester.discard[j][m] = floor(Random() * (treasure_map + 1));

            //put smithy card in handPos 
            int handPos = 0; //floor(Random() * Tester.handCount[j]);
            Tester.hand[j][handPos] = smithy;
            Tester.phase = 0;
            Tester.numActions = 1;

            Tester.whoseTurn = j;

            //copy the tester state to the Control state.
            memcpy(&Control, &Tester, sizeof(Control));

            //For test purposes we select handPos 0 where we have inserted a
            //smithy.  Since smithy takes no choices, we set choice1, choice2
            //and choice3 = 0;
            res = playCard(handPos, 0, 0, 0, &Tester);
            //smithy does not return -1 on failure and has no failure state.
            //we assert (res != -1) to protect against faults in the playCard
            //function.
            if (res == -1){
                printf("Error returned from playCard function.  Smithy function has no\n");
                printf("error reporting.  So we know the error was in the playCard routine.\n");
                continue;
            }

            //check that the discardCount count is incremented by one
            if (Tester.discardCount[j] != Control.discardCount[j] + 1){
                printf("Smithy didn't discard properly.\n");
                fail++;
                continue;
            }

            //printHand(&Tester);
            //printDeck(&Control);
            //check effects
            //check 3 cards drawn from deck
            if (Tester.deckCount[j] != Control.deckCount[j] - 3){
                printf("Smithy draw count failure.\n");
                fail++;
                continue;
            }

            //check 3 cards added to hand, 1 discarded
            if (Tester.handCount[j] != Control.handCount[j] + 2){
                printf("Smithy hand count failure.\n");
                fail++;
                printf("Tester handCount: %d\tControl handCount: %d\n", Tester.handCount[j], Control.handCount[j]);
                continue;
            }

        
        //Check that the Tester draw deck no longer contains the cards
        //To fully test this function, we should write a function that counds
        //the number of occurances of a card X in the Control deck
        //
        //Then we should determine which cards were drawn into the hand 
        //and determine that the Tester deck contains 1 less of that card than
        //the control deck.
        //For the sake of time, we're not going to do that at this point.
        //Instead, we're simply going to check that the deck is three less than
        //it was before smithy
        if (Tester.deckCount[j] != Control.deckCount[j] - 3){
            printf("Smithy failed to decrement the Tester deck.\n");
            fail++;
            continue;
            }
        }
    }
   
    printf("Smithy test results: Tested: %d\tPassed: %d\t Failed: %d\n",
        tests, tests - fail, fail);
    return;
}
