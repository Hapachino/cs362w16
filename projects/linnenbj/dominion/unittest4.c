/* -----------------------------------------------------------------------
 *fullDeckCount() Unit Testing file
 *Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 *testUnit4: unittest4.c dominion.o rngs.o
 *	gcc -0 unittest4 dominion.o rngs.o unittest1.c $(CFLAGS)
 *
 *
 * fullDeckCount() is supposed to return the number of a specified type
 * of card a player currently has in their hand, deck and discard combined.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

//Determine if two gameStates are identical or not: Return 1 if identical, 0 if not
int statesAreEqual(struct gameState *g1, struct gameState *g2)
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
    if(g1->numActions != g2->numActions) return 01;
    if(g1->coins != g2->coins) return 0;
    if(g1->numBuys != g2->numBuys) return 0;
    for(i = 0; i < MAX_PLAYERS; i++)
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

    return 1;
}

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0
int main() {
    int i, j, cardCount, card, numDeck, numHand, numDiscard, temp, result;
    int pass = 0, fail = 0;
    int tests = 1000;  // number of times to run test
    int seed = 500;

    srand(seed);
    struct gameState game, test;
    int tempCards[20];
    int tempDeck[MAX_DECK];
    int tempHand[MAX_HAND];
    int tempDiscard[MAX_HAND];
    printf ("TESTING fullDeckCount():\n");
    for(j=0; j < tests; j++)
    {

        //pick a random card to search for
        card = rand() % 27;

        //pick a random # of those cards to be in player's possession and decide how many in each location
        cardCount = (int)(rand() % 8);

        //build a randomized deck of 20 cards with the correct # of cards to search for
        for(i = 0; i < 20; i++)
        {
            tempCards[i] = -1;
        }

        for(i = 0; i < cardCount; i++)
        {
            do{
                temp = rand() % 20;
            }while (tempCards[temp] != -1);
            tempCards[temp] = card;
        }


        for(i = 0; i < 20; i++)
        {
            do{
                temp = rand() % 27;
            }while(temp == card);
            if(tempCards[i] == - 1)
                tempCards[i] = temp;
        }


        //decide how many cards to have in hand/deck/discard
        numDeck = (int)(rand() % 20);
        numHand = (int)(rand() % (20 - numDeck));
        numDiscard = (int)(20 - (numDeck + numHand));


        //create temporary deck, hand, discard
        for(i=0; i < numDeck; i++)
            tempDeck[i] = tempCards[i];
        for(i=numDeck; i < numDeck + numHand; i++)
            tempHand[i-numDeck] = tempCards[i];
        for(i=numHand+numDeck; i < 20; i++)
            tempDiscard[i-(numHand+numDeck)] = tempCards[i];

         //populate the gamestate with the player's relevant deck, hand, and discard information
         memset(&game, 0, sizeof(struct gameState));          // clear the game state
         memcpy(game.hand[0], tempHand, sizeof(int) * numHand);
         memcpy(game.deck[0], tempDeck, sizeof(int) * numDeck);
         memcpy(game.discard[0], tempDiscard, sizeof(int) * numDiscard);
         game.handCount[0] = numHand;
         game.deckCount[0] = numDeck;
         game.discardCount[0] = numDiscard;
         memcpy(&test, &game, sizeof(struct gameState));     //establish a cloned game state

         result = fullDeckCount(0, card, &game);
         #if (NOISY_TEST == 1)
         printf("Searching for card#%d: [fullDeckCount(): %d]\t[Expected: %d]\n", card, result, cardCount);
         #endif
         if(result == cardCount)
         {
             if(statesAreEqual(&game, &test) == 1)
                pass++;
             else{
                fail++;
                printf("states not equal failure.\n");
             }
         }
         else
         {
             fail++;
         }
    }
    if(pass == tests)
        printf("FullDeckCount() --- ALL TESTS PASSED\n");
    else
        printf("FullDeckCount() --- %d of %d tests failed.\n", fail, tests);

    return 0;
}

