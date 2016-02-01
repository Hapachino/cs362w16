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

#define MODULUS    2147483647 /* DON'T CHANGE THIS VALUE                  */
#define MULTIPLIER 48271      /* DON'T CHANGE THIS VALUE                  */
#define CHECK      399268537  /* DON'T CHANGE THIS VALUE                  */
#define STREAMS    256        /* # of streams, DON'T CHANGE THIS VALUE    */
#define A256       22925      /* jump multiplier, DON'T CHANGE THIS VALUE */
#define DEFAULT    123456789  /* initial seed, use 0 < DEFAULT < MODULUS  */
#define MAX_DECK 500
static long seed[STREAMS] = {DEFAULT};  /* current state of each stream   */
static int  stream        = 0;          /* stream index, 0 is the default */
static int  initialized   = 0;          /* test for stream initialization */


   double Random(void)
/* ----------------------------------------------------------------
 * Random returns a pseudo-random real number uniformly distributed
 * between 0.0 and 1.0.
 * ----------------------------------------------------------------
 */
{
  const long Q = MODULUS / MULTIPLIER;
  const long R = MODULUS % MULTIPLIER;
        long t;

  t = MULTIPLIER * (seed[stream] % Q) - R * (seed[stream] / Q);
  if (t > 0)
    seed[stream] = t;
  else
    seed[stream] = t + MODULUS;
  return ((double) seed[stream] / MODULUS);
}


   void PlantSeeds(long x)
/* ---------------------------------------------------------------------
 * Use this function to set the state of all the random number generator
 * streams by "planting" a sequence of states (seeds), one per stream,
 * with all states dictated by the state of the default stream.
 * The sequence of planted states is separated one from the next by
 * 8,367,782 calls to Random().
 * ---------------------------------------------------------------------
 */
{
  const long Q = MODULUS / A256;
  const long R = MODULUS % A256;
        int  j;
        int  s;

  initialized = 1;
  s = stream;                            /* remember the current stream */
  SelectStream(0);                       /* change to stream 0          */
  PutSeed(x);                            /* set seed[0]                 */
  stream = s;                            /* reset the current stream    */
  for (j = 1; j < STREAMS; j++) {
    x = A256 * (seed[j - 1] % Q) - R * (seed[j - 1] / Q);
    if (x > 0)
      seed[j] = x;
    else
      seed[j] = x + MODULUS;
   }
}


   void PutSeed(long x)
/* ---------------------------------------------------------------
 * Use this function to set the state of the current random number
 * generator stream according to the following conventions:
 *    if x > 0 then x is the state (unless too large)
 *    if x < 0 then the state is obtained from the system clock
 *    if x = 0 then the state is to be supplied interactively
 * ---------------------------------------------------------------
 */
{
  char ok = 0;

  if (x > 0)
    x = x % MODULUS;                       /* correct if x is too large  */
  if (x < 0)
    x = ((unsigned long) time((time_t *) NULL)) % MODULUS;
  if (x == 0)
    while (!ok) {
      printf("\nEnter a positive integer seed (9 digits or less) >> ");
      scanf("%ld", &x);
      ok = (0 < x) && (x < MODULUS);
      if (!ok)
        printf("\nInput out of range ... try again\n");
    }
  seed[stream] = x;
}


   void GetSeed(long *x)
/* ---------------------------------------------------------------
 * Use this function to get the state of the current random number
 * generator stream.
 * ---------------------------------------------------------------
 */
{
  *x = seed[stream];
}


   void SelectStream(int index)
/* ------------------------------------------------------------------
 * Use this function to set the current random number generator
 * stream -- that stream from which the next random number will come.
 * ------------------------------------------------------------------
 */
{
  stream = ((unsigned int) index) % STREAMS;
  if ((initialized == 0) && (stream != 0))   /* protect against        */
    PlantSeeds(DEFAULT);                     /* un-initialized streams */
}


   void TestRandom(void)
/* ------------------------------------------------------------------
 * Use this (optional) function to test for a correct implementation.
 * ------------------------------------------------------------------
 */
{
  long   i;
  long   x;
  double u;
  char   ok = 0;

  SelectStream(0);                  /* select the default stream */
  PutSeed(1);                       /* and set the state to 1    */
  for(i = 0; i < 10000; i++)
    u = Random();
  GetSeed(&x);                      /* get the new state value   */
  ok = (x == CHECK);                /* and check for correctness */

  SelectStream(1);                  /* select stream 1                 */
  PlantSeeds(1);                    /* set the state of all streams    */
  GetSeed(&x);                      /* get the state of stream 1       */
  ok = ok && (x == A256);           /* x should be the jump multiplier */
  if (ok)
    printf("\n The implementation of rngs.c is correct.\n\n");
  else
    printf("\n\a ERROR -- the implementation of rngs.c is not correct.\n\n");
}

int compare(const void* a, const void* b)
{
    if (*(int*)a > *(int*)b)
        return 1;
    if (*(int*)a < *(int*)b)
        return -1;
    return 0;
}

int shuffle(int player, struct gameState *state)
{


    int newDeck[MAX_DECK];
    int newDeckPos = 0;
    int card;
    int i;

    if (state->deckCount[player] < 1)
        return -1;
    qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare);
    /* SORT CARDS IN DECK TO ENSURE DETERMINISM! */

    while (state->deckCount[player] > 0)
    {
        card = floor(Random() * state->deckCount[player]);
        newDeck[newDeckPos] = state->deck[player][card];
        newDeckPos++;
        for (i = card; i < state->deckCount[player]-1; i++)
        {
            state->deck[player][i] = state->deck[player][i+1];
        }
        state->deckCount[player]--;
    }
    for (i = 0; i < newDeckPos; i++)
    {
        state->deck[player][i] = newDeck[i];
        state->deckCount[player]++;
    }

    return 0;
}


int drawCard(int player, struct gameState *state)
{
    int count;
    int deckCounter;
    if (state->deckCount[player] <= 0) //Deck is empty
    {

        //Step 1 Shuffle the discard pile back into a deck
        int i;
        //Move discard to deck
        for (i = 0; i < state->discardCount[player]; i++)
        {
            state->deck[player][i] = state->discard[player][i];
            state->discard[player][i] = -1;
        }

        state->deckCount[player] = state->discardCount[player];
        state->discardCount[player] = 0;//Reset discard

        //Shufffle the deck
        shuffle(player, state);//Shuffle the deck up and make it so that we can draw

        if (DEBUG) //Debug statements
        {
            printf("Deck count now: %d\n", state->deckCount[player]);
        }

        state->discardCount[player] = 0;

        //Step 2 Draw Card
        count = state->handCount[player];//Get current player's hand count

        if (DEBUG) //Debug statements
        {
            printf("Current hand count: %d\n", count);
        }

        deckCounter = state->deckCount[player];//Create a holder for the deck count

        if (deckCounter == 0)
            return -1;

        state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
        state->deckCount[player]--;
        state->handCount[player]++;//Increment hand count
    }

    else
    {
        int count = state->handCount[player];//Get current hand count for player
        int deckCounter;
        if (DEBUG) //Debug statements
        {
            printf("Current hand count: %d\n", count);
        }

        deckCounter = state->deckCount[player];//Create holder for the deck count
        state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
        state->deckCount[player]--;
        state->handCount[player]++;//Increment hand count
    }

    return 0;
}

int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{

    //if card is not trashed, added to Played pile
    if (trashFlag < 1)
    {
        //add card to played pile
        state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
        state->playedCardCount++;
    }

    //set played card to -1
    state->hand[currentPlayer][handPos] = -1;

    //remove card from player's hand
    if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
    {
        //reduce number of cards in hand
        state->handCount[currentPlayer]--;
    }
    else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
    {
        //reduce number of cards in hand
        state->handCount[currentPlayer]--;
    }
    else
    {
        //replace discarded card with last card in hand
        state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
        //set last card to -1
        state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
        //reduce number of cards in hand
        state->handCount[currentPlayer]--;
    }

    return 0;
}


int playCardAdventurer(struct gameState *state, int currentPlayer, int handPos)
{
    //decare variables
    int temphand[MAX_HAND];     //establish a temporary hand for non-treasure cards
    int tempCount = 0;          //How many cards are currently in the temporary hand
    int drawntreasure = 0;          //how many treasure cards have been drawn
    int cardDrawn;              //the card that was just drawn

    discardCard(handPos, currentPlayer, state, 0);  //Discard the adventurer card

    //while(drawntreasure<=2)                         //As long as 2 treasures have not been drawn
    while(drawntreasure < 2)    //correct version
    {

        if (state->deckCount[currentPlayer] <1)     //if the deck is empty we need to shuffle
        {
            shuffle(currentPlayer, state);            //discard and add to deck
        }

        drawCard(currentPlayer, state);
        //cardDrawn = state->hand[currentPlayer][0]; //top card of hand is most recently drawn card.
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //correct version.

        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else
        {
            temphand[tempCount]=cardDrawn;
            state->handCount[currentPlayer]--;  //this should just remove the top card (the most recently drawn one).
            tempCount++;
            //printf("%d\t%d\n",tempCount, drawntreasure);
        }
    }

    while(tempCount-1>=0)
    {
        //state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[tempCount-1]; // discard all cards in play that have been drawn
         state->playedCards[tempCount]=temphand[tempCount-1];
        tempCount -= 1;
    }
    return 0;
}
//-----------------------------------------------------------------------------------------------






// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0
int main() {
    int i, j;
    int numcards, temp, numHand, numDeck, numDiscard;
    int testHandCounts = 0, testPlayedCounts = 0, testDeckCounts = 0;
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
    int tempDiscard[MAX_HAND];


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
         for(i=0; i < MAX_DECK; i++){game.playedCards[i] = -1;}
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

/*    //Check for deck card counts
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
*/
}
    printf("CardCountTests (%d total tests):\n", tests);
    if(testHandCounts == tests)
        printf("\tALL HAND COUNT TESTS PASSED\n");
    else
        printf("\tThere were %d hand count test failures.\n", tests - testHandCounts);
/*
    if(testDeckCounts == tests)
        printf("\tALL DECK COUNT TESTS PASSED\n");
    else
        printf("\tThere were %d deck count test failures.\n", tests - testDeckCounts);
    if(testPlayedCounts == tests)
        printf("\tALL PLAYED COUNT TESTS PASSED\n");
    else
        printf("\tThere were %d played count test failures.\n", tests - testPlayedCounts);
*/
    printf("ListAccuracyTests (%d total tests):\n", tests);
    if(testHandCards == tests)
        printf("\tALL HAND LIST TESTS PASSED\n");
    else
        printf("\tThere were %d hand list test failures.\n", tests - testHandCards);
 /*
    if(testPlayedCards == tests)
        printf("\tALL PLAYED CARDS LIST TESTS PASSED\n");
    else
        printf("\tThere were %d played cards list test failures.\n", tests - testPlayedCards);

*/

    return 0;
}
