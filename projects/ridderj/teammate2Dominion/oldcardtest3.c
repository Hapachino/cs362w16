/* -----------------------------------------------------------------------
 *playCardVillage() Unit Testing file
 *Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 *testCard3: cardtest3.c dominion.o rngs.o
 *	gcc -0 cardtest3 dominion.o rngs.o cardtest3.c $(CFLAGS)
 *
 *
 * playCardVillage() allows the player to draw 1 additional card
 * into their hand and adds 2 more actions to their turn.
 *
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#include <stdio.h>
#include <time.h>
#include "rngs.h"

//Determine if two gameStates are identical or not: Return 1 if identical, 0 if not
int statesAreEqual(struct gameState *g1, struct gameState *g2, int shuffled)
{
    int i, j;

    if(g1->numPlayers != g2->numPlayers) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->supplyCount[i] != g2->supplyCount[i]) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->embargoTokens[i] != g2->embargoTokens[i]) return 0;
    if(g1->outpostPlayed != g2->outpostPlayed) return 0;
    if(g1->outpostTurn != g2->outpostTurn) return 0;
    if(g1->whoseTurn != g2->whoseTurn) return 0;
    if(g1->phase != g2->phase) return 0;
    //if(g1->numActions != g2->numActions) return 01;
    if(g1->coins != g2->coins) return 0;
    if(g1->numBuys != g2->numBuys) return 0;
//      for(i = 0; i < MAX_PLAYERS; i++)
    //     {
    //if(g1->handCount[i] != g2->handCount[i]) return 0;
    //if(g1->deckCount[i] != g2->deckCount[i]) return 0;
    if(shuffled == 0)
    {
        if(g1->discardCount[0] != g2->discardCount[0]) return 0;
        for(j = 0; j < MAX_HAND; j++)
            if(g1->discard[0][j] != g2->discard[0][j]) return 0;
    }
    //for(j = 0; j < MAX_HAND; j++)
    //if(g1->hand[i][j] != g2->hand[i][j]) return 0;

    //for(j = 0; j < MAX_DECK; j++)
    //if(g1->deck[i][j] != g2->deck[i][j]) return 0;
    //   }
    /*
           for(i = 0; i < MAX_DECK; i++)
               if(g1->playedCards[i] != g2->playedCards[i]) return 0;

           if(g1->playedCardCount != g2->playedCardCount) return 0;
        */
    return 1;
}



// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0
int main()
{
    int i, j;
    int numcards, temp, numHand, numDeck, numDiscard, numAction;
    int testHandCounts = 0, testPlayedCounts = 0, testDeckCounts = 0, testStateCounts = 0, testActionsCount = 0;
    int testHandCards = 0, testPlayedCards = 0;
    int villageLoc, currentTest;
    int tests = 1000;  // number of times to run test
    int seed = 500;
    srand(seed);
    struct gameState game, test;
    int tempCards[15];
    int tempDeck[MAX_DECK];
    int tempHand[MAX_HAND];
    int tempDiscard[MAX_HAND];

    printf ("TESTING playCardVillage():\n");
    for(j=0; j < tests; j++)
    {

        currentTest = 1;
        numHand = 0;
        numDeck = 0;
        numDiscard = -1;
        numAction = rand() % 5;    //initialize the number of actions remaining
        //determine how big the player's deck size should be 0 - 20
        //(technically, 0 is allowable for a deck size, but 1 has to be
        // in the hand to play smithy card 20 seems a reasonable upper limit)
        numcards = (int)(rand() % 20 + 2);

        //load a temporary set of cards randomly picked
        for(i = 0; i < 20; i++)
        {
            tempCards[i] = -1;
        }

        for(i = 0; i < numcards; i++)
        {
            temp = rand() % 27;
            tempCards[i] = temp;
        }

        //decide how many cards to have in hand/deck/discard
        //make sure the hand has at least 1 card in it (for smithy)
        numDeck = rand() % numcards;
        while(numDiscard < 0)
            numDiscard = rand() % (numcards - (numDeck));
        while(numHand == 0)
            numHand = rand() % (numcards - (numDeck + numDiscard))+1;

        //create temporary deck, hand, discard
        for(i=0; i < numDeck; i++)
            tempDeck[i] = tempCards[i];
        for(i=numDeck; i < numDeck + numHand; i++)
            tempHand[i-numDeck] = tempCards[i];
        for(i=numHand+numDeck; i < numcards; i++)
            tempDiscard[i-(numHand+numDeck)] = tempCards[i];

        //make sure smithy card is in player's hand
        villageLoc = (int) (rand() % numHand);
        tempHand[villageLoc] = village;


#if (NOISY_TEST == 1)
        printf("TEST# %d:   ", j);
        printf("%d\t%d\t%d\t%d\n", numcards, numDeck, numDiscard, numHand);
        printf("temp: %d [", numcards);
        for(i = 0; i < 20; i++)
            printf("%d, ", tempCards[i]);
        printf("\b\b]\n");

        printf("hand:  %d [", numHand);
        for(i = 0; i < numHand; i++)
            printf("%d, ", tempHand[i]);
        printf("\b\b]\n");

        printf("deck: %d [", numDeck);
        for(i = 0; i < numDeck; i++)
            printf("%d, ", tempDeck[i]);
        printf("\b\b]\n");

        printf("discard: [");
        for(i = 0; i < numDiscard; i++)
            printf("%d, ", tempDiscard[i]);
        printf("\b\b]\n");
#endif


        //populate the gamestate with the player's relevant deck, hand, and discard information
        memset(&game, 0, sizeof(struct gameState));          // clear the game state
        memcpy(game.hand[0], tempHand, sizeof(int) * numHand);
        memcpy(game.deck[0], tempDeck, sizeof(int) * numDeck);
        memcpy(game.discard[0], tempDiscard, sizeof(int) * numDiscard);
        game.handCount[0] = numHand;
        game.deckCount[0] = numDeck;
        game.discardCount[0] = numDiscard;
        game.playedCardCount = 0;
        game.numActions = numAction;
        for(i=0; i < MAX_DECK; i++)
        {
            game.playedCards[i] = -1;
        }
        memcpy(&test, &game, sizeof(struct gameState));     //establish a cloned game state


        playCardVillage(&game, 0);


#if (NOISY_TEST == 1)
        printf("\nAFTER PLAYED Village\n");
        printf("temp: %d [", numcards);
        for(i = 0; i < 20; i++)
            printf("%d, ", tempCards[i]);
        printf("\b\b]\n");

        printf("hand:  %d \t[", game.handCount[0]);
        for(i = 0; i < game.handCount[0]; i++)
            printf("%d, ", game.hand[0][i]);
        printf("\b\b]\n");

        printf("deck:  %d \t[", game.deckCount[0]);
        for(i = 0; i < game.deckCount[0]; i++)
            printf("%d, ", game.deck[0][i]);
        printf("\b\b]\n");

        printf("discard: [");
        for(i = 0; i < game.discardCount[0]; i++)
            printf("%d, ", game.discard[0][i]);
        printf("\b\b]\n");

#endif

        //Check for the number of actions has increased
        if(game.numActions == numAction + 2)
            testActionsCount++;
#if (NOISY_TEST == 1)
        else
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nACTION COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif


        if(game.handCount[0] == numHand && (numDeck > 0 || numDiscard > 0)) //discard village, draw 1 more
            testHandCounts++;
        else if(numDeck == 0 && numDiscard == 0 && game.handCount[0] == numHand -1)
            testHandCounts++;
        else
        {
#if (NOISY_TEST == 1)
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nHAND COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif
        }
        //Check for proper cards in hand
        //take discard of village into consideration
        for(i = 0; i < test.handCount[0]; i++)
        {
            if(test.hand[0][i] == village)
            {
                villageLoc = i;
                break;
            }
        }

        drawCard(0, &test);
        discardCard(villageLoc, 0, &test, 0);  //discard the card


        currentTest = 1;


        if(numDeck > 0 || numDiscard == 1)  //were able to draw
        {

            for(i=0; i < test.handCount[0]; i++)
            {
#if (NOISY_TEST == 1)
                printf("test.hand[0][i]: %d\tgame.hand[0][i]: %d\n", test.hand[0][i], game.hand[0][i]);
#endif
                if(test.hand[0][i] != game.hand[0][i])
                    currentTest = 0;
            }

            if(currentTest == 1)
                testHandCards++;
            else
            {
#if (NOISY_TEST == 1)
                printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nHAND CARD LIST FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif
            }
        }
        else if(numDiscard > 0)  //had to shuffle more than 1 discard to draw
        {
            currentTest = 0;
            //make sure last card in hand was from discard pile
            for(i = 0; i < numDiscard; i++)
                {
                    //printf("here: %d\t%d\n", game.hand[0][game.handCount[0]-1],tempDiscard[i]);
                    if(game.hand[0][villageLoc] == tempDiscard[i])
                    {
                        currentTest = 1;
                    }
                }
            if(currentTest == 1)
            {
                testHandCards++;

            }
            else
            {
#if (NOISY_TEST == 1)
                printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nHAND CARD LIST FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif
            }
        }
        else //no card to draw
        {
            for(i=0; i < test.handCount[0]-1; i++)
            {
#if (NOISY_TEST == 1)
                printf("test.hand[0][i]: %d\tgame.hand[0][i]: %d\n", test.hand[0][i], game.hand[0][i]);
#endif
                if(test.hand[0][i] != game.hand[0][i])
                    currentTest = 0;
            }

            if(currentTest == 1)
                testHandCards++;
            else
            {
#if (NOISY_TEST == 1)
                printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nHAND CARD LIST FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif
            }
        }

                //Check for deck card counts
                currentTest = 1;
                if(numDeck > 0 && game.deckCount[0] == numDeck - 1)
                    testDeckCounts++;
                else if(numDeck == 0 && numDiscard > 0 && game.deckCount[0] == numDiscard - 1)
                    testDeckCounts++;
                else if(numDeck == 0 && numDiscard == 0 && game.deckCount[0] == 0)
                    testDeckCounts++;
                else
                {
        #if (NOISY_TEST == 1)
                        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nDECK COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        #endif
                    }

        #if (NOISY_TEST == 1)
                //Check for played card counts
                printf("playedCardCount: %d \tnumDeck: %d\n", game.playedCardCount, numDeck);
        #endif
                if(game.playedCardCount == 1) //only 1 played card
                    testPlayedCounts++;
                else
                {
        #if (NOISY_TEST == 1)
                    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nPLAYED COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        #endif
                }



        //check for rest of game state to remain unchanged
        if(statesAreEqual(&game, &test, numDeck == 0) == 1)
            testStateCounts++;
#if (NOISY_TEST == 1)
        else
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nSTATE CHANGE FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif


    }
    printf("Random Action Count Tests (%d total tests):\n", tests);
    if(testActionsCount == tests)
        printf("\tALL ACTION COUNT TESTS PASSED\n");
    else
        printf("\tThere were %d action count test failures.\n", tests - testActionsCount);

    printf("CardCountTests (%d total tests):\n", tests);
    if(testHandCounts == tests)
        printf("\tALL HAND COUNT TESTS PASSED\n");
    else
        printf("\tThere were %d hand count test failures.\n", tests - testHandCounts);

            if(testDeckCounts == tests)
                printf("\tALL DECK COUNT TESTS PASSED\n");
            else
                printf("\tThere were %d deck count test failures.\n", tests - testDeckCounts);
            if(testPlayedCounts == tests)
                printf("\tALL PLAYED COUNT TESTS PASSED\n");
            else
                printf("\tThere were %d played count test failures.\n", tests - testPlayedCounts);

    printf("ListAccuracyTests (%d total tests):\n", tests);
    if(testHandCards == tests)
        printf("\tALL HAND LIST TESTS PASSED\n");
    else
        printf("\tThere were %d hand list test failures.\n", tests - testHandCards);

    printf("State Change Tests (%d total tests):\n", tests);
    if(testStateCounts == tests)
        printf("\tALL STATE CHANGE TESTS PASSED\n");
    else
        printf("\tThere were %d state change test failures.\n", tests - testPlayedCards);



    return 0;
}


