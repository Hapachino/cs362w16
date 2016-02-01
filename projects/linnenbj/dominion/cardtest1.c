/* -----------------------------------------------------------------------
 *playCardSmithy() Unit Testing file
 *Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 *testCard1: cardtest1.c dominion.o rngs.o
 *	gcc -0 cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
 *
 *
 * playCardSmithy() is allows the player to draw three additional cards
 * into their hand.
 *
 * What needs testing:
 *   - Player draws three cards
 *        - final handCount increases by 2 (+3 new cards -1 smithy discard)
 *        - deckCount needs to decrease by 3
 *   - Smithy card is discarded
 *        - discardCount increases by 1
 *        - make sure the smithy card is actually the one played
 *
 *   - detect what happens when there are fewer than 3 cards left to draw
 *     (deck & discard contain less than 3 cards)
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




// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0
int main() {
    int i, j;
    int numcards, temp, numHand, numDeck, numDiscard;
    int testHandCounts = 0, testPlayedCounts = 0, testDeckCounts = 0;
    int testHandCards = 0, testPlayedCards = 0;
    int smithyLoc, currentTest;
    int tests = 100;  // number of times to run test
    int seed = 500;
    srand(seed);
    struct gameState game, test;
    int tempCards[20];
    int tempDeck[MAX_DECK];
    int tempHand[MAX_HAND];
    int tempDiscard[MAX_HAND];


    printf ("TESTING playCardSmithy():\n");
    for(j=0; j < tests; j++)
    {
        currentTest = 1;
        numHand = 0;
        numDeck = 0;
        numDiscard = -1;
        //determine how big the player's deck size should be 0 - 20
        //(technically, 0 is allowable for a deck size, but 1 has to be
        // in the hand to play smithy card 20 seems a reasonable upper limit)
        numcards = (int)(rand() % 17 + 4);

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
        while(numDeck == 0)
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
        smithyLoc = (int) (rand() % numHand);
        tempHand[smithyLoc] = smithy;
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
         for(i=0; i < MAX_DECK; i++){game.playedCards[i] = -1;}
         memcpy(&test, &game, sizeof(struct gameState));     //establish a cloned game state
         playCardSmithy(&game, 0, smithyLoc);


#if (NOISY_TEST == 1)
        printf("\nAFTER PLAYED SMITHY\n");
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
    //Check for proper card counts
    if(game.handCount[0] == numHand + 2)
        testHandCounts++;
    else if(numDeck + numDiscard < 3 && game.handCount[0] == numHand + numDeck + numDiscard -1)
        testHandCounts++;
    else
    {
        #if (NOISY_TEST == 1)
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nHAND COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        #endif
    }
    //Check for deck card counts
    if(numDeck < 3) //did we have to shuffle
    {
        if(game.deckCount[0] == numDeck + numDiscard - 3)
            testDeckCounts++;
        else if(numDeck + numDiscard < 3 && game.deckCount[0] == 0)
            testDeckCounts++;
        else
        {
           #if (NOISY_TEST == 1)
           printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nDECK COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
           #endif
        }
    }
    else if(game.deckCount[0] == numDeck -3)
            testDeckCounts++;
    else
        {
           #if (NOISY_TEST == 1)
           printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nDECK COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
           #endif
        }


    //Check for played card counts
    if(game.playedCardCount == 1)
            testPlayedCounts++;
    else
    {
        #if (NOISY_TEST == 1)
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nPLAYED COUNT FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        #endif
    }

    //check for played card accuracy
    if(game.playedCards[game.playedCardCount-1] == smithy)
        testPlayedCards++;
    else
    {
        #if (NOISY_TEST == 1)
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nPLAYED CARD LIST FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        #endif
    }

    //check for deck & hand card accuracy
    currentTest = 1;
    if(numDeck >= 3)  //no shuffle
    {

        for(i = 0; i < numDeck - 3; i++)
        {
            if(game.deck[0][i] != tempDeck[i])
                currentTest = 0;
        }


        if((game.hand[0][numHand-1] != tempDeck[numDeck-3]) &&
           (game.hand[0][numHand] != tempDeck[numDeck-1]) &&
           (game.hand[0][numHand+1] != tempDeck[numDeck-2]))
           {
               currentTest = 0;
           }


        if(currentTest == 1)
            testHandCards++;
        else
        {
            #if (NOISY_TEST == 1)
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=\nHAND & DECK CARD LIST FAILURE\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            #endif
        }
    }
    else
    {
        testHandCards++;

    }

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
    if(testPlayedCards == tests)
        printf("\tALL PLAYED CARDS LIST TESTS PASSED\n");
    else
        printf("\tThere were %d played cards list test failures.\n", tests - testPlayedCards);
    if(testHandCards == tests)
        printf("\tALL HAND & DECK LIST TESTS PASSED\n");
    else
        printf("\tThere were %d hand & deck  list test failures.\n", tests - testHandCards);

    return 0;
}
