/*
 * testGetWinnersOnly.c
 * Unit test for function:
 * int getWinners(int players[MAX_PLAYERS], struct gameState *state)
 *
 * Test For:
 * 		each player gets a point for every estate in their hand, deck and discard
 * 		each player gets 3 points for every duchy in their hand, deck and discard
 * 		each player gets 6 points for every province in their hand, deck and discard
 * 		each player gets 1 point for every great_hall in their hand, deck and discard
 * 		each player gets 1 point for every 10 cards in their hand, deck and discard combined
 * 		players greater than player but less than MAX_PLAYERS do not get scored
 *
 * 	3 scenarios:
 *    two players
 *    three players
 *    four players
 *
 * Preconditions:
 * player is a valid player
 * gameState has useable data that has reasonably expected values
 * deck is a mix of cards
 * deckCount represents a valid number of cards in the deck
 * discard is a mix of cards
 * discardCount represents a valid number of cards in the deck
 * hand is a mix of cards
 * handCount represents a valid number of cards in the deck
 *
 * PostConditions:
 *  the player with the highest total of the formula:
 *  cards mean cards in hand, deck and discard piles
 *  (-1 * curse cards) + (1 * estate cards) + (3 * duchy cards) + (6 * province cards)
 *  + (1 * great_hall cards) + (total cards / 10 * gardens cards)
 *
 *  // boundary tests:
 *  // when remainder from discard % 10, deck % 10 and hand % 10 = 10
 *  // score when all cards 0
 *  // score when many cards but no victory cards
 *  // score for all victory cards
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion_cards.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include "unittest.h"

#define PRINTPASS 1

#define HAND 0
#define DECK 1
#define DISCARD 2

#define CURSE_CT 0
#define ESTATE_CT 1
#define DUCHY_CT 2
#define PROVINCE_CT 3
#define GREATHALL_CT 4
#define GARDENS_CT 5

#define DECK_CT 0
#define DISCARD_CT 1
#define HAND_CT 2

#define MX_PLAYERS 4
#define MX_DECK 500
#define MX_HAND 500

static int DISPLAY = 0;

// taken from dominion renamed for test to avoid conflict
int tcompare(const void* a, const void* b) {
  if (*(int*)a > *(int*)b)
    return 1;
  if (*(int*)a < *(int*)b)
    return -1;
  return 0;
}

// taken from dominion refactored for test to avoid conflict
enum CARD2
  {testcurse = 0,
	testestate,
	testduchy,
	testprovince,

	testcopper,
	testsilver,
	testgold,

	testadventurer,
   /* If no/only 1 treasure found, stop when full deck seen */
	testcouncil_room,
	testfeast, /* choice1 is supply # of card gained) */
	testgardens,
	testmine, /* choice1 is hand# of money to trash, choice2 is supply# of
	    money to put in hand */
	testremodel, /* choice1 is hand# of card to remodel, choice2 is supply# */
	testsmithy,
	testvillage,

	testbaron, /* choice1: boolean for discard of estate */
   /* Discard is always of first (lowest index) estate */
	testgreat_hall,
	testminion, /* choice1:  1 = +2 coin, 2 = redraw */
	teststeward, /* choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) */
	testtribute,

	testambassador, /* choice1 = hand#, choice2 = number to return to supply */
	testcutpurse,
	testembargo, /* choice1 = supply# */
	testoutpost,
	testsalvager, /* choice1 = hand# to trash */
	testsea_hag,
	testtreasure_map
  };

// container for the player Value arrays
struct playerValues{
	int deckCounts[HAND_CT+1];
	int cardCounts[GARDENS_CT+1];
	int totalCards;
	int score;
	int winner;
};

// group of playerValue structs
struct playerGroup{
	int numPlayers;
	struct playerValues* playerValues[MX_PLAYERS];
};

// initialize create a gameStateobject
struct gameState* newTestGame() {
  struct gameState* g = malloc(sizeof(struct gameState));
  return g;
}

/**
 * Function: initPlayerValues
 * Inputs: playerValues as struct
 * Outputs: none
 * Description:  initializes a playerValues struct
 */
void initPlayerValues(struct playerValues *playerValues){

	int i;
	playerValues->score = 0;
	playerValues->winner = 0;
	playerValues->totalCards = 0;

	for(i=0; i <= HAND_CT; i++)
	{
		playerValues->deckCounts[i] = 0;
	}

	for(i=0; i <= GARDENS_CT; i++)
	{
		playerValues->cardCounts[i] = 0;
	}

}

/**
 * Function: setupPlayValues()
 * Inputs: none
 * Outputs: struct playerValues
 * Description:  declares and initializes a playerValues struct
 */
struct playerValues* newPlayerValues()
{
	struct playerValues* player = (struct playerValues*)malloc(sizeof(struct playerValues));
	initPlayerValues(player);
	return player;
}

/**
 * Function: initPlayerGroup()
 * Inputs: struct PlayerGroup
 * Outputs: None
 * Description:  initializes a group of playerValues
 */
void initPlayerGroup(struct playerGroup* playerGroup){
	int i;

	for(i=0; i < MX_PLAYERS; i++)
		playerGroup->playerValues[i] = newPlayerValues();
}

/**
 * Function: initPlayerGroup()
 * Inputs: None
 * Outputs: struct PlayerGroup ptr
 * Description:  Declares and initializes a group of playerValues
 */
struct playerGroup* newPlayerGroup() {

  struct playerGroup* playerGroup = (struct playerGroup*) malloc(sizeof(struct playerGroup));
  initPlayerGroup(playerGroup);
  return playerGroup;

}

// taken from dominion refactored for test to avoid conflict
int testShuffle(int player, struct gameState *state) {


  int newDeck[MX_DECK];
  int newDeckPos = 0;
  int card;
  int i;

  if (state->deckCount[player] < 1)
    return -1;
  qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), tcompare);
  /* SORT CARDS IN DECK TO ENSURE DETERMINISM! */

  while (state->deckCount[player] > 0) {
    card = floor(Random() * state->deckCount[player]);
    newDeck[newDeckPos] = state->deck[player][card];
    newDeckPos++;
    for (i = card; i < state->deckCount[player]-1; i++) {
      state->deck[player][i] = state->deck[player][i+1];
    }
    state->deckCount[player]--;
  }
  for (i = 0; i < newDeckPos; i++) {
    state->deck[player][i] = newDeck[i];
    state->deckCount[player]++;
  }

  return 0;
}

// taken from dominion refactored for test to avoid conflict
int testDrawCard(int player, struct gameState *state)
{	int count;
  int deckCounter;
  if (state->deckCount[player] <= 0){//Deck is empty

    //Step 1 Shuffle the discard pile back into a deck
    int i;
    //Move discard to deck
    for (i = 0; i < state->discardCount[player];i++){
      state->deck[player][i] = state->discard[player][i];
      state->discard[player][i] = -1;
    }

    state->deckCount[player] = state->discardCount[player];
    state->discardCount[player] = 0;//Reset discard

    //Shufffle the deck
    testShuffle(player, state);//Shuffle the deck up and make it so that we can draw

    state->discardCount[player] = 0;

    //Step 2 Draw Card
    count = state->handCount[player];//Get current player's hand count

    deckCounter = state->deckCount[player];//Create a holder for the deck count

    if (deckCounter == 0)
      return -1;

    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
    state->deckCount[player]--;
    state->handCount[player]++;//Increment hand count
  }

  else{
    int count = state->handCount[player];//Get current hand count for player
    int deckCounter;

    deckCounter = state->deckCount[player];//Create holder for the deck count
    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
    state->deckCount[player]--;
    state->handCount[player]++;//Increment hand count
  }

  return 0;
}

// taken from dominion refactored for test to avoid conflict
int testUpdateCoins(int player, struct gameState *state, int bonus)
{
  int i;

  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == testcopper)
	{
	  state->coins += 1;
	}
      else if (state->hand[player][i] == testsilver)
	{
	  state->coins += 2;
	}
      else if (state->hand[player][i] == testgold)
	{
	  state->coins += 3;
	}
    }

  //add bonus
  state->coins += bonus;

  return 0;
}

// taken from dominion refactored for test to avoid conflict
int initGameState(int numPlayers, int kingdomCards[10], int randomSeed,
	struct gameState *state) {

  int i;
  int j;
  int it;
  //set up random number generator
  SelectStream(1);
  PutSeed((long)randomSeed);

  //check number of players
  if (numPlayers > MX_PLAYERS || numPlayers < 2)
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
      state->supplyCount[testcurse] = 10;
    }
  else if (numPlayers == 3)
    {
      state->supplyCount[testcurse] = 20;
    }
  else
    {
      state->supplyCount[testcurse] = 30;
    }

  //set number of Victory cards
  if (numPlayers == 2)
    {
      state->supplyCount[testestate] = 8;
      state->supplyCount[testduchy] = 8;
      state->supplyCount[testprovince] = 8;
    }
  else
    {
      state->supplyCount[testestate] = 12;
      state->supplyCount[testduchy] = 12;
      state->supplyCount[testprovince] = 12;
    }

  //set number of Treasure cards
  state->supplyCount[testcopper] = 60 - (7 * numPlayers);
  state->supplyCount[testsilver] = 40;
  state->supplyCount[testgold] = 30;

  //set number of Kingdom cards
  for (i = testadventurer; i <= testtreasure_map; i++)       	//loop all cards
  {
  	for (j = 0; j < 10; j++)           		//loop chosen cards
  	{
  		if (kingdomCards[j] == i)
  		{
  			//check if card is a 'Victory' Kingdom card
  			if (kingdomCards[j] == testgreat_hall || kingdomCards[j] == testgardens)
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
				state->deck[i][j] = testestate;
				state->deckCount[i]++;
			}
			for (j = 3; j < 10; j++)
			{
				state->deck[i][j] = testcopper;
				state->deckCount[i]++;
			}
    }

  //shuffle player decks
  for (i = 0; i < numPlayers; i++)
    {
      if ( testShuffle(i, state) < 0 )
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
  for (i = 0; i <= testtreasure_map; i++)
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
  for (it = 0; it < 5; it++){
    testDrawCard(state->whoseTurn, state);
  }

  testUpdateCoins(state->whoseTurn, state, 0);

  return 0;
}

/**
 * Function: calculate_total()
 * Inputs: player, game
 * Outputs: 0 on successful completion
 * Description:  Calculates a players total victory points
 */
int calculate_total(int player, struct gameState *state)
{
	int total = -999;
	int frequencies[testtreasure_map] = {0};
	int totalCards = 0;

	if(player < MX_PLAYERS && player <= state->numPlayers)
	{
		// count the frequency of all the cards
		total = 0;
		totalCards = state->deckCount[player]+state->discardCount[player]+state->handCount[player];
		getDeckFrequencies(state->deck[player], state->deckCount[player], frequencies, testtreasure_map);
		getDeckFrequencies(state->discard[player], state->discardCount[player], frequencies, testtreasure_map);
		getDeckFrequencies(state->hand[player], state->handCount[player], frequencies, testtreasure_map);
		total = frequencies[testcurse] * (-1);
		total = total + (frequencies[testestate]);
		total = total + (frequencies[testduchy] * 3);
		total = total + (frequencies[testprovince] * 6);
		total = total + frequencies[testgreat_hall];
		total = total + (frequencies[gardens] * (totalCards/10));
	}

	return total;
}

/**
 * Function: shuffleCards
 * shuffles cards to be added to hands
 * Inputs: cards as array ptr, numCards as int
 * Outputs: 0 for successful completion
 * based on dominion.c shuffle()
 */
int updateCards(int player, struct playerValues *playValues, struct gameState *state){

	int i;

	initPlayerValues(playValues);


	playValues->deckCounts[HAND_CT] = random_number(1,10);
	playValues->deckCounts[DECK_CT] = random_number(1,200);
	playValues->deckCounts[DISCARD_CT] = random_number(1,200);

	state->handCount[player] = playValues->deckCounts[HAND_CT];
	state->deckCount[player] = playValues->deckCounts[DECK_CT];
	state->discardCount[player] = playValues->deckCounts[DISCARD_CT];

	playValues->totalCards = playValues->deckCounts[HAND_CT] + playValues->deckCounts[DECK_CT] + playValues->deckCounts[DISCARD_CT];

	for(i = 0; i < playValues->deckCounts[HAND_CT]; i++)
	{
		state->hand[player][i] = random_number(0, testtreasure_map);

		if(state->hand[player][i] == testcurse)
			playValues->cardCounts[CURSE_CT]++;
		else if(state->hand[player][i] == testestate)
			playValues->cardCounts[ESTATE_CT]++;
		else if(state->hand[player][i] == testduchy)
			playValues->cardCounts[DUCHY_CT]++;
		else if(state->hand[player][i] == testprovince)
			playValues->cardCounts[PROVINCE_CT]++;
		else if(state->hand[player][i] == testgreat_hall)
			playValues->cardCounts[GREATHALL_CT]++;
		else if(state->hand[player][i] == testgardens)
			playValues->cardCounts[GARDENS_CT]++;

	}

	for(i = 0; i < playValues->deckCounts[DECK_CT]; i++)
	{
		state->deck[player][i] = random_number(0, testtreasure_map);

		if(state->deck[player][i] == testcurse)
			playValues->cardCounts[CURSE_CT]++;
		else if(state->deck[player][i] == testestate)
			playValues->cardCounts[ESTATE_CT]++;
		else if(state->deck[player][i] == testduchy)
			playValues->cardCounts[DUCHY_CT]++;
		else if(state->deck[player][i] == testprovince)
			playValues->cardCounts[PROVINCE_CT]++;
		else if(state->deck[player][i] == testgreat_hall)
			playValues->cardCounts[GREATHALL_CT]++;
		else if(state->deck[player][i] == testgardens)
			playValues->cardCounts[GARDENS_CT]++;
	}

	for(i = 0; i < playValues->deckCounts[DISCARD_CT]; i++)
	{
		state->discard[player][i] = random_number(0, testtreasure_map);

		if(state->discard[player][i] == testcurse)
			playValues->cardCounts[CURSE_CT]++;
		else if(state->discard[player][i] == testestate)
			playValues->cardCounts[ESTATE_CT]++;
		else if(state->discard[player][i] == testduchy)
			playValues->cardCounts[DUCHY_CT]++;
		else if(state->discard[player][i] == testprovince)
			playValues->cardCounts[PROVINCE_CT]++;
		else if(state->discard[player][i] == testgreat_hall)
			playValues->cardCounts[GREATHALL_CT]++;
		else if(state->discard[player][i] == testgardens)
			playValues->cardCounts[GARDENS_CT]++;
	}

	return 0;
}

/**
 * Function:  unitTest4
 * Inputs:  printVal, seed, results
 * Outputs: none
 * Description: tests getWinners() function in dominion.c
 */
void unitTest4(int printVal, int seed, struct results *result){

	int i, r=0;
	int players[MX_PLAYERS] = {0};

	struct playerGroup *playGroup = newPlayerGroup();

	// setup the kingdom cards available
	int k[10] = {testadventurer, testgardens, testembargo, testvillage, testminion, testmine,
			testcutpurse, testsea_hag, testtribute, testsmithy};

	// setup the struct for the control and active Games
	struct gameState *controlGame = newTestGame();
	struct gameState *activeGame = newTestGame();

	playGroup->numPlayers = random_number(2, MX_PLAYERS);
	initGameState(playGroup->numPlayers, k, seed, controlGame);

	playGroup->playerValues[0]->cardCounts[0] = 23;
	playGroup->playerValues[1]->cardCounts[0] = 46;
	playGroup->playerValues[2]->cardCounts[0] = 75;
	playGroup->playerValues[3]->cardCounts[0] = 66;

	for(i = 0; i < playGroup->numPlayers; i++)
	{
		updateCards(i, playGroup->playerValues[i], controlGame);
	}

	//copy the values from the activeGame into the controlGame
	memcpy(activeGame, controlGame, sizeof(struct gameState));

	// calculate the scores for the players
	for(i = 0; i < MX_PLAYERS; i++)
	{
		playGroup->playerValues[i]->score = calculate_total(i, controlGame);
	}

	// run the getWinners function
	r = getWinners(players, activeGame);
	assert(r == 0);

	int winningScore = playGroup->playerValues[0]->score;
	int curWinner = 0;
	playGroup->playerValues[0]->winner = 1;

	for(i = 0; i < MX_PLAYERS; i++)
	{

		if(playGroup->playerValues[i]->score >= winningScore)
		{
			winningScore = playGroup->playerValues[i]->score;
			playGroup->playerValues[curWinner]->winner = 0;
			playGroup->playerValues[i]->winner = 1;
			curWinner = i;
		}

	}

	for(i=0; i < MX_PLAYERS; i++)
	{
		int j;
		int score = scoreFor(i, activeGame);

		if(playGroup->playerValues[i]->score == -999)
			playGroup->playerValues[i]->score = 0;

		if(!(playGroup->playerValues[i]->winner == players[i]) || !(score == playGroup->playerValues[i]->score))
		{
			if(DISPLAY == 1)
			{
				printf("TEST: %d, FAIL: Player: %d of %d players\nScore: %d, Expected: %d, Winner Val Returned: %d,"
						" Expected: %d\n",
						result->testNum, i, playGroup->numPlayers, score,
						playGroup->playerValues[i]->score, players[i], playGroup->playerValues[i]->winner);
			}
			result->testsFailed++;
		}
		else
		{
			assert(playGroup->playerValues[i]->winner == players[i]);

			if(PRINTPASS && DISPLAY == 1){
				printf("TEST: %d, PASS: Player: %d of %d players\nScore: %d, Expected: %d, Winner Val Returned: %d,"
						" Expected: %d\n",
						result->testNum, i, playGroup->numPlayers, score,
						playGroup->playerValues[i]->score, players[i], playGroup->playerValues[i]->winner);
			}
		}

		if(!(scoreFor(i, activeGame) == playGroup->playerValues[i]->score) && DISPLAY==1)
		{
			printf("HAND: ");
			for(j = 0; j < activeGame->handCount[i]; j++)
			{
				printf("%d,", activeGame->hand[i][j]);
			}
			printf("\n");
			printf("DECK: ");
			for(j = 0; j < activeGame->deckCount[i]; j++)
			{
				printf("%d,", activeGame->deck[i][j]);
			}
			printf("\n");
			printf("DISCARD: ");
			for(j = 0; j < activeGame->discardCount[i]; j++)
			{
				printf("%d,", activeGame->discard[i][j]);
			}
			printf("\n");
			printf("CURSE: %d, ESTATES: %d, DUCHY: %d, PROVINCE: %d, GREAT_HALL:%d, GARDENS: %d, totalCards: %d\n",
					playGroup->playerValues[i]->cardCounts[CURSE_CT], playGroup->playerValues[i]->cardCounts[ESTATE_CT],
					playGroup->playerValues[i]->cardCounts[DUCHY_CT], playGroup->playerValues[i]->cardCounts[PROVINCE_CT],
					playGroup->playerValues[i]->cardCounts[GREATHALL_CT], playGroup->playerValues[i]->cardCounts[GARDENS_CT],
					playGroup->playerValues[i]->totalCards);
		}
	}


	result->testsPassed++;

	// clean up memory
	for(i = 0; i < MX_PLAYERS; i++){
		free(playGroup->playerValues[i]);
	}
	free(playGroup);
	free(controlGame);
	free(activeGame);
}

int main(int argc, char *argv[]){

	int seed = 9987;
	int dispArg = 0;
	int printVal = 1;
	int passval = 0;
	char* endPtr = (char*)malloc(50 * sizeof(char));
	int base = 10;

	if(argc >= 2){

		if(argc >=3){

			// check seed is an integer
			dispArg = strtol(argv[2], &endPtr, base);
			errno = 0;

			if ((errno == ERANGE && (dispArg == LONG_MAX || dispArg == LONG_MIN))
					 || (errno != 0 && dispArg == 0)) {
				printf("Error converting display entry to integer.");
				return -1;
			}

			if (endPtr == argv[2]) {
				printf("display entry must be an integer: Exiting...\n");
				return -1;
			}

			if(dispArg >=0 && dispArg < 2)
				DISPLAY = dispArg;

		}

		// check seed is an integer
		seed = strtol(argv[1], &endPtr, base);
		errno = 0;

		if ((errno == ERANGE && (seed == LONG_MAX || seed == LONG_MIN))
				 || (errno != 0 && seed == 0)) {
			printf("Error converting seed to integer.");
			return -1;
		}

		if (endPtr == argv[1]) {
			printf("Seed must be an integer: Exiting...\n");
			return -1;
		}

	} else {
		seed = 9987;
	}

	srand(seed);

	// containers for results
	struct results *result = declResults();
	result->testNum = 1;

	// run randomtestadventurer
	unitTest4(printVal, seed, result);

	if(result->testsFailed == 0)
		passval = 1;
	else
		passval = 0;

	free(result);
	return passval;
}


