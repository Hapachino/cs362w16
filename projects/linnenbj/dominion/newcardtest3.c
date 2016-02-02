/* -----------------------------------------------------------------------
 * getCost() Unit Testing file
 * Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 * This test calls the getCost method for all possible cards in the game
 * and check to make sure it returns the correct values.
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define MODULUS    2147483647 /* DON'T CHANGE THIS VALUE                  */
#define MULTIPLIER 48271      /* DON'T CHANGE THIS VALUE                  */
#define CHECK      399268537  /* DON'T CHANGE THIS VALUE                  */
#define STREAMS    256        /* # of streams, DON'T CHANGE THIS VALUE    */
#define A256       22925      /* jump multiplier, DON'T CHANGE THIS VALUE */
#define DEFAULT    123456789  /* initial seed, use 0 < DEFAULT < MODULUS  */

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

struct gameState* newGame()
{
    struct gameState* g = malloc(sizeof(struct gameState));
    return g;
}

int* kingdomCards(int k1, int k2, int k3, int k4, int k5, int k6, int k7,
                  int k8, int k9, int k10)
{
    int* k = malloc(10 * sizeof(int));
    k[0] = k1;
    k[1] = k2;
    k[2] = k3;
    k[3] = k4;
    k[4] = k5;
    k[5] = k6;
    k[6] = k7;
    k[7] = k8;
    k[8] = k9;
    k[9] = k10;
    return k;
}

int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
                   struct gameState *state)
{

    int i;
    int j;
    int it;
    //set up random number generator
    SelectStream(1);
    PutSeed((long)randomSeed);

    //check number of players
    if (numPlayers > MAX_PLAYERS || numPlayers < 2)
    {
        return -1;
    }

    //set number of players
    state->numPlayers = numPlayers;

    //check selected kingdom cards are different
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (j != i && kingdomCards[j] == kingdomCards[i])
            {
                return -1;
            }
        }
    }


    //initialize supply
    ///////////////////////////////

    //set number of Curse cards
    if (numPlayers == 2)
    {
        state->supplyCount[curse] = 10;
    }
    else if (numPlayers == 3)
    {
        state->supplyCount[curse] = 20;
    }
    else
    {
        state->supplyCount[curse] = 30;
    }

    //set number of Victory cards
    if (numPlayers == 2)
    {
        state->supplyCount[estate] = 8;
        state->supplyCount[duchy] = 8;
        state->supplyCount[province] = 8;
    }
    else
    {
        state->supplyCount[estate] = 12;
        state->supplyCount[duchy] = 12;
        state->supplyCount[province] = 12;
    }

    //set number of Treasure cards
    state->supplyCount[copper] = 60 - (7 * numPlayers);
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    //set number of Kingdom cards
    for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
        for (j = 0; j < 10; j++)           		//loop chosen cards
        {
            if (kingdomCards[j] == i)
            {
                //check if card is a 'Victory' Kingdom card
                if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
                {
                    if (numPlayers == 2)
                    {
                        state->supplyCount[i] = 8;
                    }
                    else
                    {
                        state->supplyCount[i] = 12;
                    }
                }
                else
                {
                    state->supplyCount[i] = 10;
                }
                break;
            }
            else    //card is not in the set choosen for the game
            {
                state->supplyCount[i] = -1;
            }
        }

    }

    ////////////////////////
    //supply intilization complete

    //set player decks
    for (i = 0; i < numPlayers; i++)
    {
        state->deckCount[i] = 0;
        for (j = 0; j < 3; j++)
        {
            state->deck[i][j] = estate;
            state->deckCount[i]++;
        }
        for (j = 3; j < 10; j++)
        {
            state->deck[i][j] = copper;
            state->deckCount[i]++;
        }
    }

    //shuffle player decks
    for (i = 0; i < numPlayers; i++)
    {
        if ( shuffle(i, state) < 0 )
        {
            return -1;
        }
    }

    //draw player hands
    for (i = 0; i < numPlayers; i++)
    {
        //initialize hand size to zero
        state->handCount[i] = 0;
        state->discardCount[i] = 0;
        //draw 5 cards
        // for (j = 0; j < 5; j++)
        //	{
        //	  drawCard(i, state);
        //	}
    }

    //set embargo tokens to 0 for all supply piles
    for (i = 0; i <= treasure_map; i++)
    {
        state->embargoTokens[i] = 0;
    }

    //initialize first player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = 0;
    state->handCount[state->whoseTurn] = 0;
    //int it; move to top

    //Moved draw cards to here, only drawing at the start of a turn
    for (it = 0; it < 5; it++)
    {
        drawCard(state->whoseTurn, state);
    }

    updateCoins(state->whoseTurn, state, 0);

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

int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
{
    int card;
    int coin_bonus = 0; 		//tracks coins gain from actions

    //check if it is the right phase
    if (state->phase != 0)
    {
        return -1;
    }

    //check if player has enough actions
    if ( state->numActions < 1 )
    {
        return -1;
    }

    //get card played
    card = handCard(handPos, state);

    //check if selected card is an action
    if ( card < adventurer || card > treasure_map )
    {
        return -1;
    }

    //play card
    if ( cardEffect(card, choice1, choice2, choice3, state, handPos, &coin_bonus) < 0 )
    {
        return -1;
    }

    //reduce number of actions
    state->numActions--;

    //update coins (Treasure cards may be added with card draws)
    updateCoins(state->whoseTurn, state, coin_bonus);

    return 0;
}

int buyCard(int supplyPos, struct gameState *state)
{
    int who;
    if (DEBUG)
    {
        printf("Entering buyCard...\n");
    }

    // I don't know what to do about the phase thing.

    who = state->whoseTurn;

    if (state->numBuys < 1)
    {
        if (DEBUG)
            printf("You do not have any buys left\n");
        return -1;
    }
    else if (supplyCount(supplyPos, state) <1)
    {
        if (DEBUG)
            printf("There are not any of that type of card left\n");
        return -1;
    }
    else if (state->coins < getCost(supplyPos))
    {
        if (DEBUG)
            printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
        return -1;
    }
    else
    {
        state->phase=1;
        //state->supplyCount[supplyPos]--;
        gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)

        state->coins = (state->coins) - (getCost(supplyPos));
        state->numBuys--;
        if (DEBUG)
            printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
    }

    //state->discard[who][state->discardCount[who]] = supplyPos;
    //state->discardCount[who]++;

    return 0;
}

int numHandCards(struct gameState *state)
{
    return state->handCount[ whoseTurn(state) ];
}

int handCard(int handPos, struct gameState *state)
{
    int currentPlayer = whoseTurn(state);
    return state->hand[currentPlayer][handPos];
}

int supplyCount(int card, struct gameState *state)
{
    return state->supplyCount[card];
}

int fullDeckCount(int player, int card, struct gameState *state)
{
    int i;
    int count = 0;

    for (i = 0; i < state->deckCount[player]; i++)
    {
        if (state->deck[player][i] == card) count++;
    }

    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == card) count++;
    }

    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->discard[player][i] == card) count++;
    }

    return count;
}

int whoseTurn(struct gameState *state)
{
    return state->whoseTurn;
}

int endTurn(struct gameState *state)
{
    int k;
    int i;
    int currentPlayer = whoseTurn(state);

    //Discard hand
    for (i = 0; i < state->handCount[currentPlayer]; i++)
    {
        state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        state->hand[currentPlayer][i] = -1;//Set card to -1
    }
    state->handCount[currentPlayer] = 0;//Reset hand count

    //Code for determining the player
    if (currentPlayer < (state->numPlayers - 1))
    {
        state->whoseTurn = currentPlayer + 1;//Still safe to increment
    }
    else
    {
        state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
    }

    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->coins = 0;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->handCount[state->whoseTurn] = 0;

    //int k; move to top
    //Next player draws hand
    for (k = 0; k < 5; k++)
    {
        drawCard(state->whoseTurn, state);//Draw a card
    }

    //Update money
    updateCoins(state->whoseTurn, state , 0);

    return 0;
}

int isGameOver(struct gameState *state)
{
    int i;
    int j;

    //if stack of Province cards is empty, the game ends
    if (state->supplyCount[province] == 0)
    {
        return 1;
    }

    //if three supply pile are at 0, the game ends
    j = 0;
    for (i = 0; i < 25; i++)
    {
        if (state->supplyCount[i] == 0)
        {
            j++;
        }
    }
    if ( j >= 3)
    {
        return 1;
    }

    return 0;
}

int scoreFor (int player, struct gameState *state)
{

    int i;
    int score = 0;
    //score from hand
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == curse)
        {
            score = score - 1;
        };
        if (state->hand[player][i] == estate)
        {
            score = score + 1;
        };
        if (state->hand[player][i] == duchy)
        {
            score = score + 3;
        };
        if (state->hand[player][i] == province)
        {
            score = score + 6;
        };
        if (state->hand[player][i] == great_hall)
        {
            score = score + 1;
        };
        if (state->hand[player][i] == gardens)
        {
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        };
    }

    //score from discard
    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->discard[player][i] == curse)
        {
            score = score - 1;
        };
        if (state->discard[player][i] == estate)
        {
            score = score + 1;
        };
        if (state->discard[player][i] == duchy)
        {
            score = score + 3;
        };
        if (state->discard[player][i] == province)
        {
            score = score + 6;
        };
        if (state->discard[player][i] == great_hall)
        {
            score = score + 1;
        };
        if (state->discard[player][i] == gardens)
        {
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        };
    }

    //score from deck
    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->deck[player][i] == curse)
        {
            score = score - 1;
        };
        if (state->deck[player][i] == estate)
        {
            score = score + 1;
        };
        if (state->deck[player][i] == duchy)
        {
            score = score + 3;
        };
        if (state->deck[player][i] == province)
        {
            score = score + 6;
        };
        if (state->deck[player][i] == great_hall)
        {
            score = score + 1;
        };
        if (state->deck[player][i] == gardens)
        {
            score = score + ( fullDeckCount(player, 0, state) / 10 );
        };
    }

    return score;
}

int getWinners(int players[MAX_PLAYERS], struct gameState *state)
{
    int i;
    int j;
    int highScore;
    int currentPlayer;

    //get score for each player
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        //set unused player scores to -9999
        if (i >= state->numPlayers)
        {
            players[i] = -9999;
        }
        else
        {
            players[i] = scoreFor (i, state);
        }
    }

    //find highest score
    j = 0;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (players[i] > players[j])
        {
            j = i;
        }
    }
    highScore = players[j];

    //add 1 to players who had less turns
    currentPlayer = whoseTurn(state);
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if ( players[i] == highScore && i > currentPlayer )
        {
            players[i]++;
        }
    }

    //find new highest score
    j = 0;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if ( players[i] > players[j] )
        {
            j = i;
        }
    }
    highScore = players[j];

    //set winners in array to 1 and rest to 0
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if ( players[i] == highScore )
        {
            players[i] = 1;
        }
        else
        {
            players[i] = 0;
        }
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

int getCost(int cardNumber)
{
    switch( cardNumber )
    {
    case curse:
        return 0;
    case estate:
        return 2;
    case duchy:
        return 5;
    case province:
        return 8;
    case copper:
        return 0;
    case silver:
        return 3;
    case gold:
        return 6;
    case adventurer:
        return 6;
    case council_room:
        return 5;
    case feast:
        return 4;
    case gardens:
        return 4;
    case mine:
        return 5;
    case remodel:
        return 4;
    case smithy:
        return 4;
    case village:
        return 3;
    case baron:
        return 4;
    case great_hall:
        return 3;
    case minion:
        return 5;
    case steward:
        return 3;
    case tribute:
        return 5;
    case ambassador:
        return 3;
    case cutpurse:
        return 4;
    case embargo:
        return 2;
    case outpost:
        return 5;
    case salvager:
        return 4;
    case sea_hag:
        return 4;
    case treasure_map:
        return 4;
    }

    return -1;
}

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
{
    int i;
    int j;
    int k;
    int x;
    int index;
    int currentPlayer = whoseTurn(state);
    int nextPlayer = currentPlayer + 1;

    int tributeRevealedCards[2] = {-1, -1};
    int temphand[MAX_HAND];// moved above the if statement
    int drawntreasure=0;
    int cardDrawn;
    int z = 0;// this is the counter for the temp hand
    if (nextPlayer > (state->numPlayers - 1))
    {
        nextPlayer = 0;
    }


    //uses switch to select card and perform actions
    switch( card )
    {
    case adventurer:
        return playCardAdventurer(state, currentPlayer, handPos);

    case council_room:
        //+4 Cards
        for (i = 0; i < 4; i++)
        {
            drawCard(currentPlayer, state);
        }

        //+1 Buy
        state->numBuys++;

        //Each other player draws a card
        for (i = 0; i < state->numPlayers; i++)
        {
            if ( i != currentPlayer )
            {
                drawCard(i, state);
            }
        }

        //put played card in played card pile
        discardCard(handPos, currentPlayer, state, 0);

        return 0;

    case feast:
        //gain card with cost up to 5
        //Backup hand
        for (i = 0; i <= state->handCount[currentPlayer]; i++)
        {
            temphand[i] = state->hand[currentPlayer][i];//Backup card
            state->hand[currentPlayer][i] = -1;//Set to nothing
        }
        //Backup hand

        //Update Coins for Buy
        updateCoins(currentPlayer, state, 5);
        x = 1;//Condition to loop on
        while( x == 1)  //Buy one card
        {
            if (supplyCount(choice1, state) <= 0)
            {
                if (DEBUG)
                    printf("None of that card left, sorry!\n");

                if (DEBUG)
                {
                    printf("Cards Left: %d\n", supplyCount(choice1, state));
                }
            }
            else if (state->coins < getCost(choice1))
            {
                printf("That card is too expensive!\n");

                if (DEBUG)
                {
                    printf("Coins: %d < %d\n", state->coins, getCost(choice1));
                }
            }
            else
            {

                if (DEBUG)
                {
                    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
                }

                gainCard(choice1, state, 0, currentPlayer);//Gain the card
                x = 0;//No more buying cards

                if (DEBUG)
                {
                    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
                }

            }
        }

        //Reset Hand
        for (i = 0; i <= state->handCount[currentPlayer]; i++)
        {
            state->hand[currentPlayer][i] = temphand[i];
            temphand[i] = -1;
        }
        //Reset Hand

        return 0;

    case gardens:
        return -1;

    case mine:
        j = state->hand[currentPlayer][choice1];  //store card we will trash

        if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
        {
            return -1;
        }

        if (choice2 > treasure_map || choice2 < curse)
        {
            return -1;
        }

        if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
        {
            return -1;
        }

        gainCard(choice2, state, 2, currentPlayer);

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);

        //discard trashed card
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == j)
            {
                discardCard(i, currentPlayer, state, 0);
                break;
            }
        }

        return 0;

    case remodel:
        j = state->hand[currentPlayer][choice1];  //store card we will trash

        if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
        {
            return -1;
        }

        gainCard(choice2, state, 0, currentPlayer);

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);

        //discard trashed card
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == j)
            {
                discardCard(i, currentPlayer, state, 0);
                break;
            }
        }


        return 0;

    case smithy:
        return playCardSmithy(state, currentPlayer, handPos);

    case village:
        return playCardVillage(state, currentPlayer);

    case baron:
        state->numBuys++;//Increase buys by 1!
        if (choice1 > 0) //Boolean true or going to discard an estate
        {
            int p = 0;//Iterator for hand!
            int card_not_discarded = 1;//Flag for discard set!
            while(card_not_discarded)
            {
                if (state->hand[currentPlayer][p] == estate) //Found an estate card!
                {
                    state->coins += 4;//Add 4 coins to the amount of coins
                    state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
                    state->discardCount[currentPlayer]++;
                    for (; p < state->handCount[currentPlayer]; p++)
                    {
                        state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
                    }
                    state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
                    state->handCount[currentPlayer]--;
                    card_not_discarded = 0;//Exit the loop
                }
                else if (p > state->handCount[currentPlayer])
                {
                    if(DEBUG)
                    {
                        printf("No estate cards in your hand, invalid choice\n");
                        printf("Must gain an estate if there are any\n");
                    }
                    if (supplyCount(estate, state) > 0)
                    {
                        gainCard(estate, state, 0, currentPlayer);
                        state->supplyCount[estate]--;//Decrement estates
                        if (supplyCount(estate, state) == 0)
                        {
                            isGameOver(state);
                        }
                    }
                    card_not_discarded = 0;//Exit the loop
                }

                else
                {
                    p++;//Next card
                }
            }
        }

        else
        {
            if (supplyCount(estate, state) > 0)
            {
                gainCard(estate, state, 0, currentPlayer);//Gain an estate
                state->supplyCount[estate]--;//Decrement Estates
                if (supplyCount(estate, state) == 0)
                {
                    isGameOver(state);
                }
            }
        }


        return 0;

    case great_hall:
        return playCardGreatHall(state, currentPlayer, handPos);

    case minion:
        return playCardMinion(state, currentPlayer, handPos, choice1);

    case steward:
        if (choice1 == 1)
        {
            //+2 cards
            drawCard(currentPlayer, state);
            drawCard(currentPlayer, state);
        }
        else if (choice1 == 2)
        {
            //+2 coins
            state->coins = state->coins + 2;
        }
        else
        {
            //trash 2 cards in hand
            discardCard(choice2, currentPlayer, state, 1);
            discardCard(choice3, currentPlayer, state, 1);
        }

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case tribute:
        if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1)
        {
            if (state->deckCount[nextPlayer] > 0)
            {
                tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
                state->deckCount[nextPlayer]--;
            }
            else if (state->discardCount[nextPlayer] > 0)
            {
                tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
                state->discardCount[nextPlayer]--;
            }
            else
            {
                //No Card to Reveal
                if (DEBUG)
                {
                    printf("No cards to reveal\n");
                }
            }
        }

        else
        {
            if (state->deckCount[nextPlayer] == 0)
            {
                for (i = 0; i < state->discardCount[nextPlayer]; i++)
                {
                    state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
                    state->deckCount[nextPlayer]++;
                    state->discard[nextPlayer][i] = -1;
                    state->discardCount[nextPlayer]--;
                }

                shuffle(nextPlayer,state);//Shuffle the deck
            }
            tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
            state->deckCount[nextPlayer]--;
            tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
            state->deckCount[nextPlayer]--;
        }

        if (tributeRevealedCards[0] == tributeRevealedCards[1]) //If we have a duplicate card, just drop one
        {
            state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
            state->playedCardCount++;
            tributeRevealedCards[1] = -1;
        }

        for (i = 0; i <= 2; i ++)
        {
            if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) //Treasure cards
            {
                state->coins += 2;
            }

            else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) //Victory Card Found
            {
                drawCard(currentPlayer, state);
                drawCard(currentPlayer, state);
            }
            else //Action Card
            {
                state->numActions = state->numActions + 2;
            }
        }

        return 0;

    case ambassador:
        j = 0;		//used to check if player has enough cards to discard

        if (choice2 > 2 || choice2 < 0)
        {
            return -1;
        }

        if (choice1 == handPos)
        {
            return -1;
        }

        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
            {
                j++;
            }
        }
        if (j < choice2)
        {
            return -1;
        }

        if (DEBUG)
            printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

        //increase supply count for choosen card by amount being discarded
        state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

        //each other player gains a copy of revealed card
        for (i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                gainCard(state->hand[currentPlayer][choice1], state, 0, i);
            }
        }

        //discard played card from hand
        discardCard(handPos, currentPlayer, state, 0);

        //trash copies of cards returned to supply
        for (j = 0; j < choice2; j++)
        {
            for (i = 0; i < state->handCount[currentPlayer]; i++)
            {
                if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
                {
                    discardCard(i, currentPlayer, state, 1);
                    break;
                }
            }
        }

        return 0;

    case cutpurse:

        updateCoins(currentPlayer, state, 2);
        for (i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                for (j = 0; j < state->handCount[i]; j++)
                {
                    if (state->hand[i][j] == copper)
                    {
                        discardCard(j, i, state, 0);
                        break;
                    }
                    if (j == state->handCount[i])
                    {
                        for (k = 0; k < state->handCount[i]; k++)
                        {
                            if (DEBUG)
                                printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
                        }
                        break;
                    }
                }

            }

        }

        //discard played card from hand
        discardCard(handPos, currentPlayer, state, 0);

        return 0;


    case embargo:
        //+2 Coins
        state->coins = state->coins + 2;

        //see if selected pile is in play
        if ( state->supplyCount[choice1] == -1 )
        {
            return -1;
        }

        //add embargo token to selected supply pile
        state->embargoTokens[choice1]++;

        //trash card
        discardCard(handPos, currentPlayer, state, 1);
        return 0;

    case outpost:
        //set outpost flag
        state->outpostPlayed++;

        //discard card
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case salvager:
        //+1 buy
        state->numBuys++;

        if (choice1)
        {
            //gain coins equal to trashed card
            state->coins = state->coins + getCost( handCard(choice1, state) );
            //trash card
            discardCard(choice1, currentPlayer, state, 1);
        }

        //discard card
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case sea_hag:
        for (i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];
                state->deckCount[i]--;
                state->discardCount[i]++;
                state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
            }
        }
        return 0;

    case treasure_map:
        //search hand for another treasure_map
        index = -1;
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == treasure_map && i != handPos)
            {
                index = i;
                break;
            }
        }
        if (index > -1)
        {
            //trash both treasure cards
            discardCard(handPos, currentPlayer, state, 1);
            discardCard(index, currentPlayer, state, 1);

            //gain 4 Gold cards
            for (i = 0; i < 4; i++)
            {
                gainCard(gold, state, 1, currentPlayer);
            }

            //return success
            return 1;
        }

        //no second treasure_map found in hand
        return -1;
    }

    return -1;
}

int playCardSmithy(struct gameState *state, int currentPlayer, int handPos)
{
    //+3 Cards
    int i;
    for (i = 0; i < 3; i++)
    {
        drawCard(currentPlayer, state);
        handPos++;    //adjust position of smithy card to allow for card just drawn.
    }

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 1);
    return 0;
}

int playCardVillage(struct gameState *state, int currentPlayer)
{
    //+1 Card
    drawCard(currentPlayer, state);

    //+2 Actions
    state->numActions = 2;
    return 0;
}

int playCardGreatHall(struct gameState *state, int currentPlayer, int handPos)
{
    //+1 Card
    drawCard(currentPlayer, state);

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 1);
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

    while(drawntreasure<2)                         //As long as 2 treasures have not been drawn
    {

        if (state->deckCount[currentPlayer] <1)     //if the deck is empty we need to shuffle
        {
            shuffle(currentPlayer, state);            //discard and add to deck
        }

        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //correct version.

        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else
        {
            temphand[tempCount]=cardDrawn;
            state->handCount[currentPlayer]--;  //this should just remove the top card (the most recently drawn one).
            tempCount++;
        }
    }

    while(tempCount-1>=0)
    {
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[tempCount-1]; // discard all cards in play that have been drawn
        tempCount -= 1;
    }
    return 0;
}

int playCardMinion(struct gameState *state, int currentPlayer, int handPos, int choice1)
{
//+1 action
    state->numActions++;

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    if (choice1)		//+2 coins
    {
        state->coins = state->coins + 2;
    }

    else	//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
    {
        int position = 0;
        int i;
        //discard hand and draw 4
        for (i = 0; i < 4; i++)
        {
            drawCard(currentPlayer, state);
        }

        while(numHandCards(state) > 4)
        {
            discardCard(position, currentPlayer, state, 0);
            position++;
        }

        //other players discard hand and redraw if hand size > 4
        for (i = currentPlayer; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                if ( state->handCount[i] > 4 )
                {
                    //discard hand
                    while( state->handCount[i] < 0 )
                    {
                        discardCard(handPos, i, state, 0);
                    }

                    //draw 4
                    int j;
                    for (j = 0; j < 4; j++)
                    {
                        drawCard(i, state);
                    }
                }
            }
        }

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

int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
    //Note: supplyPos is enum of choosen card

    //check if supply pile is empty (0) or card is not used in game (-1)
    if ( supplyCount(supplyPos, state) < 1 )
    {
        return -1;
    }

    //added card for [whoseTurn] current player:
    // toFlag = 0 : add to discard
    // toFlag = 1 : add to deck
    // toFlag = 2 : add to hand

    if (toFlag == 1)
    {
        state->deck[ player ][ state->deckCount[player] ] = supplyPos;
        state->deckCount[player]++;
    }
    else if (toFlag == 2)
    {
        state->hand[ player ][ state->handCount[player] ] = supplyPos;
        state->handCount[player]++;
    }
    else
    {
        state->discard[player][ state->discardCount[player] ] = supplyPos;
        state->discardCount[player]++;
    }

    //decrease number in supply pile
    state->supplyCount[supplyPos]--;

    return 0;
}

int updateCoins(int player, struct gameState *state, int bonus)
{
    int i;

    //reset coin count
    state->coins = 0;

    //add coins for each Treasure card in player's hand
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == copper)
        {
            state->coins += 1;
        }
        else if (state->hand[player][i] == silver)
        {
            state->coins += 2;
        }
        else if (state->hand[player][i] == gold)
        {
            state->coins += 3;
        }
    }

    //add bonus
    state->coins += bonus;

    return 0;
}







//-----------------------------------


#define TESTCARD "village"
/* qsort int comparison function */
int int_cmp(const void *a, const void *b)
{
    const int *ia = (const int *)a; // casting pointer types
    const int *ib = (const int *)b;
    return *ia  - *ib;
	/* integer comparison: returns negative if b > a
	and positive if a > b */
}

//Determine if two gameStates are identical or not: Return 1 if identical, 0 if not
int statesAreEqual(struct gameState *g1, struct gameState *g2, int arraychecks)
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
    if(g1->numActions != g2->numActions) return 0;
    if(g1->coins != g2->coins) return 0;
    if(g1->numBuys != g2->numBuys) return 0;
    if(g1->playedCardCount != g2->playedCardCount) return 0;

    qsort ((void*)(g1->deck[0]), g1->deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g1->hand[0]), g1->handCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g1->discard[0]), g1->discardCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g1->playedCards), g1->playedCardCount, sizeof(int), int_cmp);
    qsort ((void*)(g2->deck[0]), g2->deckCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g2->hand[0]), g2->handCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g2->discard[0]), g2->discardCount[0], sizeof(int), int_cmp);
    qsort ((void*)(g2->playedCards), g2->playedCardCount, sizeof(int), int_cmp);




    for(i = 0; i < g1->numPlayers; i++)
    {
        if(g1->handCount[i] != g2->handCount[i]) return 0;
        if(g1->deckCount[i] != g2->deckCount[i]) return 0;
        if(g1->discardCount[i] != g2->discardCount[i]) return 0;

        if(arraychecks == 1)
        {
            for(j = 0; j < g1->discardCount[i]; j++)
            {
                if(g1->discard[i][j] != g2->discard[i][j]) return 0;
            }

            for(j = 0; j < g1->handCount[i]; j++)
            {
                if(g1->hand[i][j] != g2->hand[i][j]) return 0;
            }

            for(j = 0; j < g1->deckCount[i]; j++)
            {
                if(g1->deck[i][j] != g2->deck[i][j]) return 0;
            }
            for(i = 0; i < g1->playedCardCount; i++)
            {
                if(g1->playedCards[i] != g2->playedCards[i]) return 0;
            }
        }
    }
        return 1;
}



int transform_ints_to_string(int const* data, int data_length,
                             char* output, int output_length)
{
  // if not enough space was available, returns -1
  // otherwise returns the number of characters written to
  // output, not counting the additional null character

  // precondition: non-null pointers
  assert(data);
  assert(output);
  // precondition: valid data length
  assert(data_length >= 0);
  // precondition: output has room for null
  assert(output_length >= 1);

  int written = 0;
  for (; data_length; data_length--) {
    int length = snprintf(output, output_length, "%d, ", *data++);
    if (length >= output_length) {
      // not enough space
      return -1;
    }
    written += length;
    output += length;
    output_length -= length;
  }
  return written;
}
void printArray(int const* d, int len, char* str)
{
    char buf[200] = "";
    printf("%s: ", str);
    if(len <= 0)
    {
        printf("[ ]\n");
        return;
    }
    else
    {
        transform_ints_to_string(d, len, buf, sizeof buf);
        printf("[%s\b\b]\n", buf);
    }
}

int handCoins(struct gameState *g, int player)
{
    int i;
    int coins = 0;
    for(i = 0; i < g->handCount[player]; i++)
    {
        if(g->hand[player][i] == copper || g->hand[player][i] == silver || g->hand[player][i] == gold)
        {
            coins++;
        }
    }
    return coins;
}




int main()
{
    char buffer[200] = "";
    int i, j, m;
    int tempCard, coinsInHand = 0, count;
    int handpos = 0, bonus = 0;
    int seed = 1800;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("*** Testing Card: %s \n", TESTCARD);

	// ----------- TEST 1: At least 1 cards in the deck --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 1: At least 1 cards in the player's deck\n");
    printf("-------------------------------------------------------------\n");
	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = village;           //assign the village card to the end of the hand

	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(village, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

	//determine if hand/deck is correct
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    drawCard(thisPlayer, &G);  //+1 card
    G.numActions += 2;        //+2 actions



    printf("After village card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);
	printf("\t  Player actions: %d [%d expected]\n", testG.numActions, G.numActions);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Expected deck");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Expected discard");


	printf("\tGamestates equal: %d\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 1) != 1)
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 1 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***\n");
        printf("-------------------------------------------------------------\n");
    }
    else
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 1 STATUS:  PASSED!\n");
        printf("-------------------------------------------------------------\n\n");
    }


// ----------- TEST 2: Force a shuffle (0 in deck, discard > 0) --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 2: Force a shuffle for the card\n");
    printf("-------------------------------------------------------------\n");

    memset(&G, 0, sizeof(struct gameState));              // clear the game state
    memset(&testG, 0, sizeof(struct gameState));          // clear the game state
    initializeGame(numPlayers, k, seed, &G);               //initialize a new game

	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = village;           //assign the village card to the end of the hand


	//move enough cards from the deck into discard so deckCount = 0
	count = 0;
	while(G.deckCount[thisPlayer] > 0)
    {
        G.discard[thisPlayer][count] = G.deck[thisPlayer][G.deckCount[thisPlayer]-1];
        G.deckCount[thisPlayer]--;
        G.discardCount[thisPlayer]++;
        count++;
    }

	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(village, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

    //determine if hand/deck is correct
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    drawCard(thisPlayer, &G);  //+1 card
    G.numActions += 2;        //+2 actions



    printf("After village card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);
	printf("\t  Player actions: %d [%d expected]\n", testG.numActions, G.numActions);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Expected deck");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Expected discard");


	printf("\tGamestates equal: %d\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 1) != 1)
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 2 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***\n");
        printf("-------------------------------------------------------------\n");
    }
    else
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 2 STATUS:  PASSED!\n");
        printf("-------------------------------------------------------------\n\n");
    }


// ----------- TEST 3: 0 Cards available for drawing --------------
	printf("-------------------------------------------------------------\n");
	printf("TEST 2: 0 cards in deck/discard piles\n");
    printf("-------------------------------------------------------------\n");

    memset(&G, 0, sizeof(struct gameState));              // clear the game state
    memset(&testG, 0, sizeof(struct gameState));          // clear the game state
    initializeGame(numPlayers, k, seed, &G);               //initialize a new game

	handpos= G.handCount[thisPlayer]-1;
	G.hand[thisPlayer][handpos] = village;           //assign the village card to the end of the hand


	//set deckCount to 0
	G.deckCount[thisPlayer] = 0;


	memcpy(&testG, &G, sizeof(struct gameState));      // copy the game state to a test case

	cardEffect(village, 0, 0, 0, &testG, handpos, &bonus);   //Play the card

    //determine if hand/deck is correct
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Starting hand");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Starting deck");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Starting discard");
	discardCard(G.handCount[thisPlayer]-1, thisPlayer, &G, 0);

    //mimic the act of the adventurer card on game G
    drawCard(thisPlayer, &G);  //+1 card
    G.numActions += 2;        //+2 actions



    printf("After village card has been played:\n");
	printf("\t   Cards in hand: %d [%d expected]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("\t   Cards in deck: %d [%d expected]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("\tCards in discard: %d [%d expected]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("\t    Played cards: %d [%d expected]\n", testG.playedCardCount, G.playedCardCount);
	printf("\t  Player actions: %d [%d expected]\n", testG.numActions, G.numActions);

    printArray(testG.hand[thisPlayer], testG.handCount[thisPlayer], "Player's hand");
	printArray(G.hand[thisPlayer], G.handCount[thisPlayer], "Expected hand");
	printArray(testG.deck[thisPlayer], testG.deckCount[thisPlayer], "Player's deck");
	printArray(G.deck[thisPlayer], G.deckCount[thisPlayer], "Expected deck");
	printArray(testG.discard[thisPlayer], testG.discardCount[thisPlayer], "Player's discard");
	printArray(G.discard[thisPlayer], G.discardCount[thisPlayer], "Expected discard");


	printf("\tGamestates equal: %d\n", statesAreEqual(&G, &testG, 1));
	if(statesAreEqual(&G, &testG, 1) != 1)
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 3 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***\n");
        printf("-------------------------------------------------------------\n");
    }
    else
    {
        printf("-------------------------------------------------------------\n");
        printf("TEST 3 STATUS:  PASSED!\n");
        printf("-------------------------------------------------------------\n\n");
    }

        printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);
    return 0;
}

