/* -----------------------------------------------------------------------
 *playCardAdventurer() Unit Testing file
 *Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 *testCard2: cardtest2.c dominion.o rngs.o
 *	gcc -0 cardtest2 dominion.o rngs.o cardtest2.c $(CFLAGS)
 *
 *
 * playCardAdventurer() is allows the player to draw three additional cards
 * into their hand.
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
int statesAreEqual(struct gameState *g1, struct gameState *g2)
{
    int i;

    if(g1->numPlayers != g2->numPlayers) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->supplyCount[i] != g2->supplyCount[i]) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->embargoTokens[i] != g2->embargoTokens[i]) return 0;
    if(g1->outpostPlayed != g2->outpostPlayed) return 0;
    if(g1->outpostTurn != g2->outpostTurn) return 0;
    if(g1->whoseTurn != g2->whoseTurn) return 0;
    if(g1->phase != g2->phase) return 0;
    if(g1->numActions != g2->numActions) return 01;
    if(g1->coins != g2->coins) return 0;
    if(g1->numBuys != g2->numBuys) return 0;
    /*   for(i = 0; i < MAX_PLAYERS; i++)
       {
           if(g1->handCount[i] != g2->handCount[i]) return 0;
           if(g1->deckCount[i] != g2->deckCount[i]) return 0;
           if(g1->discardCount[i] != g2->discardCount[i]) return 0;

           for(j = 0; j < MAX_HAND; j++)
               if(g1->hand[i][j] != g2->hand[i][j]) return 0;

           for(j = 0; j < MAX_DECK; j++)
               if(g1->deck[i][j] != g2->deck[i][j]) return 0;
       }

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
    int numcards, temp, numHand, numDeck, numDiscard;
    int testHandCounts = 0, testPlayedCounts = 0, testDeckCounts = 0, testStateCounts = 0;
    int testHandCards = 0, testPlayedCards = 0;
    int adventLoc, currentTest;
    int tLoc1, tLoc2, tType1, tType2, numDraws, tcount=0;
    int tests = 100;  // number of times to run test
    int seed = 500;
    srand(seed);
    struct gameState game, test;
    int tempCards[15];
    int tempDeck[MAX_DECK];
    int tempHand[MAX_HAND];


    printf ("TESTING playCardAdventurer():\n");
    for(j=0; j < tests; j++)
    {
        currentTest = 1;
        numHand = 0;
        numDeck = 0;
        numDiscard = -1;
        //set the deck to a random # of cards between 5 and 15
        numcards = (int)(rand() % 10 + 5);

        //load a temporary set of cards randomly picked
        for(i = 0; i < 15; i++)
        {
            tempCards[i] = -1;
        }

        for(i = 0; i < numcards; i++)
        {
            temp = rand() % 10;
            tempCards[i] = temp;
        }

        //decide how many cards to have in hand/deck/discard
        //make sure the hand has at least 1 card in it (for smithy)
        while(numDeck == 0)
            numDeck = rand() % numcards;
        //while(numDiscard < 0)
        //numDiscard = rand() % (numcards - (numDeck));
        while(numHand == 0)
            numHand = rand() % (numcards - numDeck +1);

        //create temporary deck, hand, discard
        for(i=0; i < numDeck; i++)
            tempDeck[i] = tempCards[i];
        for(i=numDeck; i < numDeck + numHand; i++)
            tempHand[i-numDeck] = tempCards[i];
        // for(i=numHand+numDeck; i < numcards; i++)
        //     tempDiscard[i-(numHand+numDeck)] = tempCards[i];

        //make sure adventurer card is in player's hand
        adventLoc = (int) (rand() % numHand);
        tempHand[adventLoc] = adventurer;


        //determine where 2 treasure cards are in deck
        tLoc1 = -1;
        tLoc2 = -1;
        tcount = 0;
        for(i = numDeck-1; i >= 0; i--)
        {
            if(tempDeck[i] == copper)
            {
                if(tLoc1 == -1)
                {
                    tLoc1 = i;
                    tType1 = copper;
                    tcount++;
                }
                else
                {
                    tLoc2 = i;
                    tType2 = copper;
                    i = -1;
                    tcount++;
                }
            }
            else if(tempDeck[i] == silver)
            {
                if(tLoc1 == -1)
                {
                    tLoc1 = i;
                    tType1 = silver;
                    tcount++;
                }
                else
                {
                    tLoc2 = i;
                    tType2 = silver;
                    i = -1;
                    tcount++;
                }
            }
            else if(tempDeck[i] == gold)
            {
                if(tLoc1 == -1)
                {
                    tLoc1 = i;
                    tcount++;
                    tType1 = gold;
                }
                else
                {
                    tLoc2 = i;
                    tType2 = gold;
                    i = -1;
                    tcount++;
                }
            }
        }

        //how many draws are going to be required:
        if(tLoc2 != -1)
        {
            numDraws = numDeck - tLoc2;
        }
        else
        {
            numDraws = numDeck;
        }


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
        /*
                printf("discard: [");
                for(i = 0; i < numDiscard; i++)
                    printf("%d, ", tempDiscard[i]);
                printf("\b\b]\n");
        */
        printf("tLoc1: %d\t\ttType: %d\n", tLoc1, tType1);
        printf("tLoc2: %d\t\ttType: %d\n", tLoc2, tType1);
        printf("draws needed: %d\n", numDraws);
#endif

        //populate the gamestate with the player's relevant deck, hand, and discard information
        memset(&game, 0, sizeof(struct gameState));          // clear the game state
        memcpy(game.hand[0], tempHand, sizeof(int) * numHand);
        memcpy(game.deck[0], tempDeck, sizeof(int) * numDeck);

        game.handCount[0] = numHand;
        game.deckCount[0] = numDeck;
        game.discardCount[0] = 0;
        game.playedCardCount = 0;
        for(i=0; i < MAX_DECK; i++)
        {
            game.playedCards[i] = -1;
        }
        memcpy(&test, &game, sizeof(struct gameState));     //establish a cloned game state


        playCardAdventurer(&game, 0, adventLoc);


#if (NOISY_TEST == 1)
        printf("\nAFTER PLAYED ADVENTURER\n");
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


        //Check for proper card counts
        printf("handcount: %d\ttcount: %d\tnumHand + tcount -1: %d\n",game.handCount[0], tcount,numHand + tcount - 1);
#endif
        if(game.handCount[0] == numHand + tcount - 1)
            testHandCounts++;
        else
        {
#if (NOISY_TEST == 1)
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nHAND COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif
        }

        //Check for proper cards in hand
        //take discard of adventurer into consideration
        tempHand[adventLoc] = tempHand[numHand-1];
        if(tcount == 0)
            tempHand[numHand-1]=-1;
        else
        {
            tempHand[numHand-1] = tType1;
            if(tcount == 2)
                tempHand[numHand] = tType2;
        }

        currentTest = 1;
        for(i=0; i <= numHand; i++)
        {
#if (NOISY_TEST == 1)
            printf("tempHand[i]: %d\tgame.hand[0][i]: %d\n", tempHand[i], game.hand[0][i]);
#endif
            if(tempHand[i] != game.hand[0][i])
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

        //Check for deck card counts
        if(tLoc2 > -1) //did we find 2 treasures
        {

            if(game.deckCount[0] == tLoc2)
                testDeckCounts++;
            else
            {
#if (NOISY_TEST == 1)
                printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nDECK COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif
            }
        }
        else if(game.deckCount[0] == 0)
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
        if(tLoc1 == -1 && game.playedCardCount == numDeck)
            testPlayedCounts++;
        else if(tLoc2 == -1 && game.playedCardCount == numDeck-1)
            testPlayedCounts++;
        else if(game.playedCardCount == (numDeck - tLoc2 - 1))
            testPlayedCounts++;
        else
        {
#if (NOISY_TEST == 1)
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nPLAYED COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif
        }

        //check for rest of game state to remain unchanged
        if(statesAreEqual(&game, &test) == 1)
            testStateCounts++;
        else
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nSTATE CHANGE FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

    }
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
