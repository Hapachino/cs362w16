 /**
 * Unit test for card:
 *   Tribute card using CardEffect
 *   Using PlayCard would be more like the game but introduces an extra layer of checking
 *
 * Card Functions when played:
 * 	Tribute Card added to played cards,
 * 		- last card in played Cards is Tribute
 * 		- played cards count increases by 1,
 * 		- handCount decreases by 1
 * 		- last card in hand moved into Tribute position
 * 	Tribute card reads two top cards from deck of player to left
 * 	(1 higher or 0 if current player is highest player)
 * 		- if deck has 1 or no cards looks at cards in deck
 * 		- if two top cards contain Action cards add 2 to Actions
 * 		- if two top cards contain Treasure Cards add 2 to treasures
 * 		- if two top cards contain Victory Cards 2 cards added to hand
 * 		- if two top cards two different types two credits obtained
 * 		- if two top cards two of the same type credit occurs only once
 *
 * Tests:
 * 	Tribute played and 2 Actions on players deck
 * 	Tribute played and 2 Treasure cards on players deck
 * 	Tribute played and 2 Victory Cards on players deck
 * 	Tribute played and 1 Action and 1 Treasure on player's deck
 * 	Tribute played and 1 Action and 1 Victory on player's deck
 * 	Tribute played and 1 Treasure and 1 Victory on player's deck
 * 	Tribute played and only 1 card in player's deck
 * 	Tribute played and no cards in players deck.
 *
 * Preconditions:
 * 	player is a valid player
 * 	gameState has useable data that has reasonably expected values
 * 	deck is a mix of cards
 * 	deckCount represents a valid number of cards in the deck
 * 	handCount represents a valid number of cards in the hand
 * 	Tribute exists in the hand to be played (this is tested prior)
 * 	hand contains cards with at least 1 (Tribute)
 *
 * PostConditions:
 *  - Tribute is removed from hand and added to played pile
 *  - if cards revealed are both action and have the same name
 *  	- Actions increases by only 2
 *  - if cards revealed are both treasure cards and have the same name
 *  	- bonus increases by 2
 *  - if cards revealed are both Victory cards and have the same name
 *  	- 2 cards are added to hand
 *  - if cards revealed are both action and have different names
 *  	- Actions increase by 4
 *  - if cards revealed are both treasure cards and have different names
 *  	- bonus increases by 4
 *  - if cards revealed are both victory cards and have different names
 *  	- 4 cards added to hand
 *  - if cards revealed are 1 Action and one treasure
 *  	- Actions increase by 2
 *  	- bonus increases by 2
 *  - if cards revealed are 1 Action and one victory
 *  	- Actions increase by 2
 *  	- 2 cards are added to hand from deck
 *  - if cards revealed are 1 treasure and 1 Victory
 *  	- bonus increases by 2
 *  	- 2 cards are added to hand and deck decreases by 2
 *  - if one card is great hall (Action and Victory) and 1 card is action
 *  	- 2 Actions added for great hall, 2 Actions added for Action card
 *  	- 2 cards added to hand for great hall
 *  - if one card is great hall (Action and Victory) and 1 card is treasure
 *  	- 2 Actions added for great hall
 *		- 2 Coins added for treasure card
 *  	- 2 cards added to hand for great hall
 *  - if one card is great hall (Action and Victory) and 1 card is action
 *  	- 2 Actions added for great hall, 2 Actions added for Action card
 *  	- 2 cards added to hand for great hall
 *  - if only one card revealed from deck
 *  	- if card is action - actions increase by 2
 *  	- if card is treasure - bonus increases by 2
 *  	- if card is victory - cards in hand increase by 2
 *  - if no cards revealed
 *  	- no change to actions, bonus or cards.
 *  - if any victory cards are chosen and deck and discard combined equal 1
 *  	- only 1 card drawn
 *  - if any victory cards are chosen and deck and discard combined equal 0
 *  	- no cards added to hand
 *  - nothing else changes
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest.h"
#include "rngs.h"

#define PRINTPASS 0

#define GOLD_VALUE 3
#define SILVER_VALUE 2
#define COPPER_VALUE 1

#define HAND 0
#define DISCARD 1
#define DECK 2

struct cardResults
{
	int testsPassed;
	int testsFailed;
	int testNum;
	int cardUnderTest;
	int noCoinsInDeck;
	int seed;
	int players;
	int curPlayer;
	int handCount;
	int pdeckCount;
	int pdiscardCount;
	int ndeckCount;
	int ndiscardCount;
	int advPos;
	int coinFlag;
	int initFlag;
	int cardsToAdd;
	int buysToAdd;
	int coinsToAdd;
	int coinBonus;
	int choiceFlag;
};

 /**
  * Function: initCardResults
  * Inputs: struct cardResults
  * Outputs: None
  * Description:  Initialization of elements in struct cardResults
  */
void initCardResults(struct cardResults* result)
{
  result->testsPassed = 0;
  result->testsFailed = 0;
  result->testNum = 0;
  result->seed = 0;
  result->noCoinsInDeck = 0;
  result->players = 0;
  result->curPlayer = 0;
  result->pdeckCount = 0;
  result->pdiscardCount = 0;
  result->handCount = 0;
  result->ndeckCount = 0;
  result->ndiscardCount = 0;
  result->advPos = 0;
  result->coinFlag = 0;
  result->initFlag = 0;
  result->cardsToAdd = 0;
  result->buysToAdd = 0;
  result->cardUnderTest = 0;
  result->coinBonus = 0;
  result->choiceFlag = 0;
}

/**
 * Function: resetResults
 * Inputs: struct cardResults
 * Outputs: None
 * Description:  resets elements in card results for next test
 */
void resetResult(struct cardResults* result){
	  result->noCoinsInDeck = 0;
	  result->pdeckCount = 0;
	  result->pdiscardCount = 0;
	  result->ndeckCount = 0;
	  result->ndiscardCount = 0;
	  result->handCount = 0;
	  result->advPos = 0;
	  result->coinFlag = 0;
	  result->initFlag = 0;
	  result->coinBonus = 0;
	  result->choiceFlag = 0;
}

/**
 * Function: declCardResults
 * Inputs: None
 * Outputs: pointer to initialized cardResults object
 * Description:  declaration and initialization of cardResults Object
 */
struct cardResults* declCardResults() {
  struct cardResults* result = malloc(sizeof(struct cardResults));
  initCardResults(result);
  return result;
}

/**
 * Function: getCardType
 * Inputs: card
 * Outputs: type of card
 * Description:  converts a card to it's type: action, treasure, victory, dead
 */
char* getCardType(int card){
	char *cardType = (char*)malloc(20 * sizeof(char));

	// if cards is a treasure card
	if(card >= 4 && card <= 6)
		cardType = "Treasure";
	else if((card >= 1 && card <=3) || card == gardens)
		cardType = "Victory";
	else if((card >= 7 && card <=9) || (card >= 11))
		cardType = "Action";
	else if(card == great_hall)
		cardType = "Action Victory";
	else
		cardType = "Dead";

	return cardType;

}

/**
 * Function: updatePile
 * Inputs: player, count of elements to update, pile type to update, struct gameState
 * Outputs: None
 * Description:  updates a pile of cards to the number of elements requested in count
 */
int updatePile(int player, int count, int pile, struct gameState *state){

	int i;
	int *ptr;
	int oldCount;

	if(pile == HAND)
	{
		oldCount = state->handCount[player];
		state->handCount[player] = count;
		ptr = state->hand[player];
	}
	else if(pile == DECK)
	{
		oldCount = state->deckCount[player];
		state->deckCount[player] = count;
		ptr = state->deck[player];
	}
	else if(pile == DISCARD)
	{
		oldCount = state->discardCount[player];
		state->discardCount[player] = count;
		ptr = state->discard[player];
	}

	for(i = 0; i < count; i++){
		ptr[i] = random_number(0, treasure_map);
	}

	//clear values higher than count
	for(i = count; i < oldCount; i++){
		ptr[i] = 0;
	}

	return 0;
}

/**
 * Function: getDeckFrequencies
 * Inputs: array of cards, count of elements in array, array to hold frequencies,
 * 	count of elements in frequency array
 * Outputs: 0 on completion
 * Description:  counts the frequency of cards in a deck and stores the value in the
 * 	frequency array passed to the function.
 */
int getDeckFrequencies(int *card, int cardCount, int *cardFrequencies, int cardFreqCount){

	int i, j;
	for(i = 0; i < cardFreqCount; i++)
	{
		for(j = 0; j < cardCount; j++)
		{
			if(card[j] == i)
				cardFrequencies[i]++;
		}
	}

	return 0;
}

/**
 * Function: cardtest4
 * Inputs: printVal, seed, struct cardResults
 * Outputs: None
 * Description:  setup, running and verification of results obtained from
 * 	playing tribute in dominion.c
 */
void cardTest4(int printVal, int seed, struct cardResults *result){

	int r=0;
	int i = 0, j=0, m=0;

	int nextPlayer = 0;
	int dead = -1;
	int actions = 0, cards = 0, coins = 0;
	int curPlayer;
	int revealedCards[2] = {0,0};
	int conRevCards[2] = {0,0};

	// customizable values
	int revCardCount = 2;
	// initially set to 10 and 0
	int nPlayerDeck = result->ndeckCount;
	int nPlayerDiscard = result->ndiscardCount;
	int cPlayerDeck = result->pdeckCount;
	int cPlayerDiscard = result->pdiscardCount;

	// need some kingdom cards for initialization of game:
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};

	// setup the containers for the Game and Control Games
	struct gameState *controlGame = newGame();
	struct gameState *activeGame = newGame();

	// need a random number of players and to set current player
	// should be at least 2 to max players
	result->players = random_number(2, MAX_PLAYERS);
	result->curPlayer = random_number(0, result->players - 1);

	// iterate through all combinations of 2 cards
	for(i = 0; i < treasure_map; i++){
		for(j = i; j < treasure_map; j++){
			int nPreCardFreq[treasure_map] = {0};
			int nPostCardFreq[treasure_map] = {0};
			int cPreCardFreq[treasure_map] = {0};
			int cPostCardFreq[treasure_map] = {0};

			// rest coinBonus and hand
			result->coinBonus = 0;
			actions = 0;
			coins = 0;
			cards = 0;

			initializeGame(result->players, k, result->seed, controlGame);
			curPlayer = controlGame->whoseTurn;

			// set the next player
			if(controlGame->whoseTurn == controlGame->numPlayers - 1)
				nextPlayer = 0;
			else
				nextPlayer = controlGame->whoseTurn+1;

			// update the decks to the generated values
			updatePile(curPlayer, cPlayerDeck, DECK, controlGame);
			updatePile(curPlayer, cPlayerDiscard, DISCARD, controlGame);
			updatePile(nextPlayer, nPlayerDeck, DECK, controlGame);
			updatePile(nextPlayer, nPlayerDiscard, DISCARD, controlGame);

			// add tribute card to hand
			result->handCount = controlGame->handCount[curPlayer];
			result->advPos = random_number(0, result->handCount - 1);
			controlGame->hand[curPlayer][result->advPos] = tribute;


			// SETUP TESTS CALCULATED VALUES
			// from the wiki - if one card in hand take that card out BEFORE shuffling in discards
			// determine revealed cards from next player as if there is a shuffle with more
			// than on card this will need to be a calculated value based on missing cards
			if(nPlayerDeck >= 2)
			{
				// both cards revealed come from deck
				controlGame->deck[nextPlayer][controlGame->deckCount[nextPlayer] -1] = i;
				revealedCards[0] = i;
				controlGame->deck[nextPlayer][controlGame->deckCount[nextPlayer] -2] = j;
				revealedCards[1] = j;
			}
			else if(nPlayerDeck == 1)
			{
				controlGame->deck[nextPlayer][0] = i;
				revealedCards[0] = i;

				// if only card is in deck set the card value as 0
				if(nPlayerDiscard == 0)
				{
					// we have no second card to reveal
					revCardCount = 1;
					revealedCards[1] = dead;
					j = treasure_map;

				}
				if(nPlayerDiscard == 1)
				{
					// if only one card in discard we can set the value to j
					controlGame->discard[nextPlayer][0] = j;
					revealedCards[1] = j;
				}
				else
				{
					// cards need to be shuffled so we will need to get the frequencies
					// we can set all the cards in the discard pile to a single value
					for(m = 0; m < controlGame->discardCount[nextPlayer]; m++){
						controlGame->discard[nextPlayer][m] = j;
					}
					revealedCards[1] = j;
				}

			}
			else if(nPlayerDeck <= 0){

				// we have no cards in the deck to reveal
				// if no discard pile we have no cards to reveal
				if(nPlayerDiscard == 0)
				{
					revCardCount = 0;
					revealedCards[0] = dead;
					revealedCards[1] = dead;
					i = treasure_map;
					j = treasure_map;
				}
				if(nPlayerDiscard == 1){
					// we can set and pull the one card from the discard pile
					revCardCount = 1;
					controlGame->discard[nextPlayer][0] = i;
					revealedCards[0] = controlGame->discard[nextPlayer][0];
					revealedCards[1] = dead;
					j = treasure_map;
				}
				if(nPlayerDiscard > 1){
					// we have to shuffle and won't know the outcome nor will we be able to
					// 'set' the cards to the iteration values
					// this test will be random and values need to be tested after the game runs
					// Strategy:  get the card frequencies and determine either:
					// if cards properly put on discard pile - the 2 missing cards OR
					// if cards not properly put on discard pile - the last two cards in the deck
					getDeckFrequencies(controlGame->discard[nextPlayer], controlGame->discardCount[nextPlayer],
							nPreCardFreq, treasure_map);
				}
			}

			// copy the active Game into the control Game
			memcpy(activeGame, controlGame, sizeof(struct gameState));

			// play the card
			r = cardEffect(tribute, 0, 0, 0, activeGame, result->advPos, &result->coinBonus);
			assert(r == 0);

			// get the post frequencies for the next Players Card if deck needed shuffle
			// if revealed cards were actually never discarded as they should have been
			// we will need to use the top two cards on the deck for our calculated values
			if(nPlayerDeck == 0 && nPlayerDiscard > 2){
				// if we had to shuffle to get 2 cards we can attempt to calculate the values
				getDeckFrequencies(activeGame->deck[nextPlayer], activeGame->deckCount[nextPlayer],
											nPostCardFreq, treasure_map);

				if(activeGame->deck[nextPlayer] - controlGame->discard[nextPlayer] == 2){
					int idx = 0;
					for(m = 0; m < treasure_map; m++){
						if(nPreCardFreq[m] - nPostCardFreq[m] == 2){
							revealedCards[0] = m;
							revealedCards[1] = m;
							m = treasure_map;
						}
						if(nPreCardFreq[m] - nPostCardFreq[m] == 1){
							revealedCards[idx] = m;
							idx++;
						}
					}
				}

			}

			// put the calculated cards into the control containers
			conRevCards[0] = revealedCards[0];
			conRevCards[1] = revealedCards[1];
			// if the cards are equal set one to dead
			if(revealedCards[0] == revealedCards[1])
				revealedCards[1] = dead;

			// CALCULATE THE EXPECTED BONUSES
			for(m = 0; m < revCardCount; m++){

				// cards can be two types so use if instead of else if
				// if cards is a treasure card
				if(revealedCards[m] >= 4 && revealedCards[m] <= 6)
				{
					coins = coins + 2;
				}
				// if the card is a victory card
				if((revealedCards[m] >= 1 && revealedCards[m] <=3)
						|| revealedCards[m] == gardens || revealedCards[m] == great_hall)
				{
					cards = cards + 2;
				}
				// if the card is an action card
				if((revealedCards[m] >= 7 && revealedCards[m] <=9) || (revealedCards[m] >= 11))
				{
					actions = actions + 2;
				}

			}

			// TEST GAME VARIABLES
			printf("\nCard1: %d - %s, Card2: %d - %s (-1 indicates card not drawn)\n", conRevCards[0], getCardType(conRevCards[0]), conRevCards[1], getCardType(conRevCards[1]));
			printf("**Game State Checks Starting**\n");
			// check the calculated actions + original actions = new actions
			if(!(activeGame->numActions == controlGame->numActions + actions))
			{
				printf("TEST%d FAIL: Reported total Actions: %d, Expected total Actions: %d "
						"(Control: %d, Bonus Actions Calculated: %d)\n",
						result->testNum, activeGame->numActions, controlGame->numActions + actions,
						controlGame->numActions, actions);

			} else {

				if(PRINTPASS){
					printf("TEST%d PASS: Reported total Actions: %d, Expected total Actions: %d "
						"(Control: %d, Bonus Actions Calculated: %d)\n",
						result->testNum, activeGame->numActions, controlGame->numActions + actions,
						controlGame->numActions, actions);
				}

				assert(activeGame->numActions == controlGame->numActions + actions);
			}

			// check the coinBonus contains expected amount of coins
			if(!(result->coinBonus == coins))
			{
				printf("TEST%d FAIL: Reported Bonus Coins: %d, Expected: %d\n",
						result->testNum, result->coinBonus, coins);

			} else {
				assert(result->coinBonus == coins);
				if(PRINTPASS){
					printf("TEST%d PASS: Reported Bonus Coins: %d, Expected: %d\n",
							result->testNum, result->coinBonus, coins);
				}
			}

			// Tribute card is put on top of the played pile
			// played Count increases by 1
			if(!activeGame->playedCardCount == controlGame->playedCardCount + 1){
				printf("TEST%d FAIL: Reported playedCardCount: %d, Expected: %d "
						"(Control: %d, Cards Played: 1)\n", result->testNum,
						activeGame->playedCardCount, controlGame->playedCardCount + 1,
						controlGame->playedCardCount);
			} else {
				assert(activeGame->playedCardCount == controlGame->playedCardCount + 1);

				if(PRINTPASS){
					printf("TEST%d PASS: Reported playedCardCount: %d, Expected: %d "
							"(Control: %d, Cards Played: 1)\n", result->testNum,
							activeGame->playedCardCount, controlGame->playedCardCount + 1,
							controlGame->playedCardCount);
				}
			}

			// check playedCard made it onto the played pile
			if(!(activeGame->playedCards[activeGame->playedCardCount - 1]))
			{
				printf("TEST%d FAIL: Reported last playedCard: %d, Expected: %d\n",
						result->testNum, activeGame->playedCards[activeGame->playedCardCount - 1], tribute);
			} else {
				assert(activeGame->playedCards[activeGame->playedCardCount - 1]);

				if(PRINTPASS){
					printf("TEST%d PASS: Reported last playedCard: %d, Expected: %d\n",
							result->testNum, activeGame->playedCards[activeGame->playedCardCount - 1], tribute);
				}
			}

			// check all playedCards in control Game still in playedCards
			for(m = 0; m < controlGame->playedCardCount; i++)
			{
				assert(activeGame->playedCards[m] == controlGame->playedCards[m]);

				if(PRINTPASS){
					printf("TEST%d PASS: All Played cards in control Game still in played cards in ActiveGame\n",
							result->testNum);
				}
			}

			// NEXT PLAYER CHECKS
			// revealed card count added to discard Count
			printf("**Next Player Checks Starting**\n");
			if(!(activeGame->discardCount[nextPlayer] == controlGame->discardCount[nextPlayer] + revCardCount))
			{
				printf("TEST%d FAIL: Reported discardCount: %d, Expected: %d "
						"(Control: %d + Revealed Card(s): %d)\n", result->testNum,
						activeGame->discardCount[nextPlayer], controlGame->discardCount[nextPlayer] + revCardCount,
						controlGame->discardCount[curPlayer], revCardCount);

			} else{
				assert(activeGame->discardCount[nextPlayer] == controlGame->discardCount[nextPlayer] + revCardCount);

				if(PRINTPASS){
					printf("TEST%d PASS: Reported discardCount: %d, Expected: %d "
							"(Control: %d + Revealed Card(s): %d)\n", result->testNum,
							activeGame->discardCount[nextPlayer], controlGame->discardCount[nextPlayer] + revCardCount,
							controlGame->discardCount[curPlayer], revCardCount);
				}
			}

			// revealed card count removed from deck
			// if deckCount included a shuffle Deck + Discard - revealed cards
			int nextDeckCount = 0;
			if(nPlayerDeck < 2)
				nextDeckCount = nPlayerDeck + nPlayerDiscard - revCardCount;
			else
				nextDeckCount = controlGame->deckCount[nextPlayer] - revCardCount;

			if(!(activeGame->deckCount[nextPlayer] == nextDeckCount))
			{
				printf("TEST%d FAIL: Reported deckCount: %d, Expected: %d "
						"(Control: %d - Revealed Card(s): %d (Expected may include Discard: %d)\n",
						result->testNum, activeGame->deckCount[nextPlayer], nextDeckCount,
						controlGame->deckCount[nextPlayer], revCardCount, controlGame->discardCount[nextPlayer]);
			}
			else
			{
				assert(activeGame->deckCount[nextPlayer] == nextDeckCount);

				if(PRINTPASS){
					printf("TEST%d PASS: Reported deckCount: %d, Expected: %d "
							"(Control: %d - Revealed Card(s): %d (Expected may include Discard: %d)\n",
							result->testNum, activeGame->deckCount[nextPlayer], nextDeckCount,
							controlGame->deckCount[nextPlayer], revCardCount, controlGame->discardCount[nextPlayer]);
				}
			}

			// revealed cards physically added to discard pile
			// if no cards revealed nothing should have changed
			if(revCardCount == 0)
			{
				assert(memcmp(controlGame->discard[nextPlayer], activeGame->discard[nextPlayer], sizeof(controlGame->discard[nextPlayer])) == 0);
				assert(memcmp(controlGame->deck[nextPlayer], activeGame->deck[nextPlayer], sizeof(controlGame->deck[nextPlayer])) == 0);
			}
			else if(revCardCount == 1)
			{

				// if only one card revealed it will be the last card in the discard pile
				if(!(activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1] == conRevCards[0]))
				{
					printf("TEST%d FAIL: Reported Last Discard: %d, Expected: %d "
							"(Control: Second Revealed Card: %d)\n", result->testNum,
							activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1],
							conRevCards[0], conRevCards[0]);
				}
				else
				{
					assert(activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1] == conRevCards[0]);

					if(PRINTPASS){
						printf("TEST%d PASS: Reported Last Discard: %d, Expected: %d "
									"(Control: Second Revealed Card: %d)\n", result->testNum,
									activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1],
									conRevCards[0], conRevCards[0]);
					}
				}

				// check card removed
				// the deck will have no cards - check the elements are 0
				assert(activeGame->deckCount[nextPlayer] == 0);


			}
			else if(revCardCount == 2)
			{

				// if at least one of the cards came from the deck check the calculated values added to the discard
				if(nPlayerDeck > 0)
				{
					// check the first card
					if(!(activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1] == conRevCards[1]))
					{
						printf("TEST%d FAIL: Reported Last Discard: %d, Expected: %d "
								"(Control: Second Revealed Card: %d)\n", result->testNum,
								activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1],
								conRevCards[1], conRevCards[1]);
					}
					else
					{
						assert(activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1] == conRevCards[1]);

						if(PRINTPASS){
							printf("TEST%d PASS: Reported Last Discard: %d, Expected: %d "
									"(Control: Second Revealed Card: %d)\n", result->testNum,
									activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1],
									conRevCards[1], conRevCards[1]);
						}
					}

					// check the second card
					if(!((activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 2] == conRevCards[0])))
					{

						if(PRINTPASS){
							printf("TEST%d FAIL: Reported Second Last Discard: %d, Expected: %d "
									"(Control: First Revealed Card: %d)\n", result->testNum,
									activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 2],
									conRevCards[0], conRevCards[0]);
						}
					}
					else
					{
						assert(activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 2] == conRevCards[0]);

						if(PRINTPASS){
							printf("TEST%d PASS: Reported Second Last Discard: %d, Expected: %d "
									"(Control: First Revealed Card: %d)\n", result->testNum,
									activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 2],
									conRevCards[0], conRevCards[0]);
						}
					}

				}
				else
				{
					// both cards were randomly selected from the discard pile.
					// Since we calculated the cards we will need to test them in both configurations
					if((!(activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1] == conRevCards[1]) &&
							!(activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 2] == conRevCards[0])) ||
							(!(activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1] == conRevCards[0]) &&
							!(activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 2] == conRevCards[1])))
					{
						printf("TEST%d FAIL: Reported Last Cards on Discard: %d, %d, Expected: %d, %d "
								"(Expected cards are not respective positions)\n", result->testNum,
								activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1],
								activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 2],
								conRevCards[0], conRevCards[1]);
					}
					else
					{
						if(PRINTPASS){
							printf("TEST%d PASS: Reported Last Cards on Discard: %d, %d, Expected: %d, %d "
									"(Expected cards are not respective positions)\n", result->testNum,
									activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 1],
									activeGame->discard[nextPlayer][activeGame->discardCount[nextPlayer] - 2],
									conRevCards[0], conRevCards[1]);
						}
					}

				}
			}

			// check no other cards on the discard pile changed if they weren't shuffled
			if(nPlayerDeck > 0)
			{
				for(m = 0; m < activeGame->discardCount[nextPlayer] - revCardCount; m++)
				{
					assert(activeGame->discard[nextPlayer][m] == controlGame->discard[nextPlayer][m]);
				}
			}
			// check no other cards in the deck changed
			for(m = 0; m < (controlGame->deckCount[nextPlayer] - revCardCount); m++)
			{
				assert(activeGame->deck[nextPlayer][m] == controlGame->deck[nextPlayer][m]);
			}

			// PLAYER CARD CHECKS
			printf("**Current Player Checks Starting**\n");
			// check the card played came out of the hand
			// handCount - cardplayed + cards drawn

			// Set cards drawn to available cards to be drawn
			int cardsDrawn = cPlayerDeck + cPlayerDiscard;

			if(cardsDrawn > cards)
				cardsDrawn = cards;

			// verify the handCount
			if(!(activeGame->handCount[curPlayer] == controlGame->handCount[curPlayer] - 1 + cardsDrawn))
			{
				printf("TEST%d FAIL: Reported handCount: %d, Expected: %d "
						"(Control: %d - 1 + Bonus Cards: %d)\n",
						result->testNum, activeGame->handCount[curPlayer], controlGame->handCount[curPlayer] - 1 + cardsDrawn,
						controlGame->handCount[curPlayer], cards);

			} else {
				assert(activeGame->handCount[curPlayer] == controlGame->handCount[curPlayer] - 1 + cardsDrawn);

				if(PRINTPASS){
					printf("TEST%d PASS: Reported handCount: %d, Expected: %d "
							"(Control: %d - 1 + Bonus Cards: %d)\n",
							result->testNum, activeGame->handCount[curPlayer], controlGame->handCount[curPlayer] - 1 + cardsDrawn,
							controlGame->handCount[curPlayer], cards);
				}
			}

			// check the original cards are still in the hand
			// check the index where tribute was and check it now contains the last original card in the deck
			// if it was the last original card the last check already checks the count
			for(m = 0; m < controlGame->handCount[curPlayer] - 1; m++)
			{
				if(m == result->advPos){
					if(!(activeGame->hand[curPlayer][m] == controlGame->hand[curPlayer][controlGame->handCount[curPlayer] - 1]))
					{
						printf("TEST%d FAIL: Hand index where tribute was: %d, Expected: %d "
								"(last card from original hand)\n", result->testNum,
								activeGame->hand[curPlayer][m], controlGame->hand[curPlayer][controlGame->handCount[curPlayer] - 1]);

					} else {
						assert(activeGame->hand[curPlayer][m] == controlGame->hand[curPlayer][controlGame->handCount[curPlayer] - 1]);
					}
				}
				else
					assert(activeGame->hand[curPlayer][m] == controlGame->hand[curPlayer][m]);
			}

			// if cards were drawn
			// check the cards were added to he hand (count already verified above)
			if(cardsDrawn > 0)
			{
				// if there were no cards available to be drawn
				if(cPlayerDeck + cPlayerDiscard == 0)
				{
					// deck and discard piles should not change
					// hand already checked in last test
					assert(memcmp(controlGame->discard[curPlayer], activeGame->discard[curPlayer], sizeof(controlGame->discard[curPlayer])) == 0);
					assert(memcmp(controlGame->deck[curPlayer], activeGame->deck[curPlayer], sizeof(controlGame->deck[curPlayer])) == 0);
				}
				// if there were enough cards in the deck to draw or only cards in the deck to pull from
				else if(controlGame->deckCount[curPlayer] >= cardsDrawn || controlGame->discardCount[curPlayer] == 0)
				{
					// check the last X cards physically added to hand
					for(m=0; m < cardsDrawn; m++)
					{
						if(!(activeGame->hand[curPlayer][activeGame->handCount[curPlayer] - 1 - cardsDrawn + m] ==
								controlGame->deck[curPlayer][controlGame->deckCount[curPlayer] - 1 - m]))
						{
							printf("TEST%d FAIL: HandIndex to check for bonus card: %d card: %d, Expected: %d\n",
									result->testNum, activeGame->handCount[curPlayer] - 1 - cards + m,
									activeGame->hand[curPlayer][activeGame->handCount[curPlayer] - 1 - cards + m],
									controlGame->deck[curPlayer][controlGame->deckCount[curPlayer] - 1 - m]);

						} else {
							assert(activeGame->hand[curPlayer][activeGame->handCount[curPlayer] - 1 - cards + m] ==
									controlGame->deck[curPlayer][controlGame->deckCount[curPlayer] - 1 - m]);

							if(PRINTPASS){
								printf("TEST%d PASS: Value in hand Index where tribute was: %d card: %d, Expected: %d\n",
										result->testNum, activeGame->handCount[curPlayer] - 1 - cards + m,
										activeGame->hand[curPlayer][activeGame->handCount[curPlayer] - 1 - cards + m],
										controlGame->deck[curPlayer][controlGame->deckCount[curPlayer] - 1 - m]);
							}
						}

					}

					// check the rest of the deck hasn't been changed if there were cards left
					for(m = 0; m < controlGame->deckCount[curPlayer] - cardsDrawn; m++)
					{
						assert(controlGame->deck[curPlayer][m] == activeGame->deck[curPlayer][m]);
					}

					// discard pile should not have changed
					assert(memcmp(controlGame->discard[curPlayer], activeGame->discard[curPlayer], sizeof(controlGame->discard[curPlayer])) == 0);

				}
				// if some of the cards came from the discard pile
				else
				{
					// if there were not enough cards to draw in the deck but there were cards in the discard
					// check the deck was moved to the hand
					for(m=0; m < controlGame->deckCount[curPlayer]; m++)
					{
						if(!(activeGame->hand[curPlayer][activeGame->handCount[curPlayer] - 1 - cardsDrawn + m] ==
								controlGame->deck[curPlayer][controlGame->deckCount[curPlayer] - 1 - m]))
						{
							printf("TEST%d FAIL: HandCount Index: %d card: %d, Expected: %d\n",
									result->testNum, activeGame->handCount[curPlayer] - 1 - cards + m,
									activeGame->hand[curPlayer][activeGame->handCount[curPlayer] - 1 - cards + m],
									controlGame->deck[curPlayer][controlGame->deckCount[curPlayer] - 1 - m]);

						} else {
							assert(activeGame->hand[curPlayer][activeGame->handCount[curPlayer] - 1 - cards + m] ==
									controlGame->deck[curPlayer][controlGame->deckCount[curPlayer] - 1 - m]);

							if(PRINTPASS){
								printf("TEST%d PASS: HandCount Index: %d card: %d, Expected: %d\n",
										result->testNum, activeGame->handCount[curPlayer] - 1 - cards + m,
										activeGame->hand[curPlayer][activeGame->handCount[curPlayer] - 1 - cards + m],
										controlGame->deck[curPlayer][controlGame->deckCount[curPlayer] - 1 - m]);
							}
						}

					}

					// check the rest of the deck hasn't been changed if there were cards left
					for(m = 0; m < controlGame->deckCount[curPlayer] - cardsDrawn; m++)
					{
						assert(controlGame->deck[curPlayer][m] == activeGame->deck[curPlayer][m]);
					}

					//TODO:
					// check preDiscard deck frequency
					int freqDiff[treasure_map] = {0};
					getDeckFrequencies(controlGame->discard[curPlayer], controlGame->discardCount[curPlayer],
							cPreCardFreq, treasure_map);
					getDeckFrequencies(activeGame->discard[curPlayer], activeGame->discardCount[curPlayer],
							cPostCardFreq, treasure_map);

					// check missing cards went into hand
					for(m = 0; m < cardsDrawn - cPlayerDeck; m++)
					{
						freqDiff[activeGame->hand[curPlayer][activeGame->handCount[curPlayer] -1 -m]]++;
					}
					for(m = 0; m < treasure_map; m++)
					{
						if(!((cPreCardFreq[m] - cPostCardFreq[m]) == freqDiff[m]))
						{
							printf("TEST%d FAIL: FREQ failed for DRAWN CARD: %d card (Card in hand but not removed from discard)\n",
									result->testNum, m);
						}
						else
						{
							assert((cPreCardFreq[m] - cPostCardFreq[m]) == freqDiff[m]);
						}
					}
				}


			}

			// copy over checked values and verify no other values changed
			controlGame->numActions = activeGame->numActions;

			controlGame->playedCardCount = activeGame->playedCardCount;
			memcpy(controlGame->playedCards, activeGame->playedCards, sizeof(controlGame->playedCards));
			controlGame->handCount[curPlayer] = activeGame->handCount[curPlayer];
			memcpy(controlGame->hand[curPlayer], activeGame->hand[curPlayer], sizeof(controlGame->hand[curPlayer]));
			controlGame->deckCount[curPlayer] = activeGame->deckCount[curPlayer];
			memcpy(controlGame->deck[curPlayer], activeGame->deck[curPlayer], sizeof(controlGame->deck[curPlayer]));
			controlGame->discardCount[curPlayer] = activeGame->discardCount[curPlayer];
			memcpy(controlGame->discard[curPlayer], activeGame->discard[curPlayer], sizeof(controlGame->discard[curPlayer]));
			controlGame->deckCount[nextPlayer] = activeGame->deckCount[nextPlayer];
			memcpy(controlGame->deck[nextPlayer], activeGame->deck[nextPlayer], sizeof(controlGame->deck[nextPlayer]));
			controlGame->discardCount[nextPlayer] = activeGame->discardCount[nextPlayer];
			memcpy(controlGame->discard[nextPlayer], activeGame->discard[nextPlayer], sizeof(controlGame->discard[nextPlayer]));

			if(!(controlGame->coins == activeGame->coins)){
				printf("TEST%d FAIL: Changes not in scope:  gameState->coins changed\n", result->testNum);
				controlGame->coins = activeGame->coins;
			}
			if(!(controlGame->numBuys == activeGame->numBuys)){
				printf("TEST%d FAIL: Changes not in scope:  gameState->numBuys changed\n", result->testNum);
				controlGame->numBuys = activeGame->numBuys;
			}
			if(!(controlGame->numPlayers == activeGame->numPlayers)){
				printf("TEST%d FAIL: Changes not in scope:  gameState->Players changed\n", result->testNum);
				controlGame->numPlayers = activeGame->numPlayers;
			}
			if(!(controlGame->outpostPlayed == activeGame->outpostPlayed)){
				printf("TEST%d FAIL: Changes not in scope:  gameState->outpostPlayed changed\n", result->testNum);
				controlGame->outpostPlayed = activeGame->outpostPlayed;
			}
			if(!(controlGame->outpostTurn == activeGame->outpostTurn)){
				printf("TEST%d FAIL: Changes not in scope:  gameState->outpostTurn changed\n", result->testNum);
				controlGame->outpostTurn = activeGame->outpostTurn;
			}
			if(!(controlGame->phase == activeGame->phase)){
				printf("TEST%d FAIL: Changes not in scope:  gameState->phase changed\n", result->testNum);
				controlGame->phase = activeGame->phase;
			}
			if(!(memcmp(controlGame->supplyCount, activeGame->supplyCount, sizeof(controlGame->supplyCount)) == 0)){
				printf("TEST%d FAIL: Changes not in scope:  gameState->supplyCount changed\n", result->testNum);
				memcpy(controlGame->supplyCount, activeGame->supplyCount, sizeof(controlGame->supplyCount));
			}
			if(!(controlGame->handCount[nextPlayer] == activeGame->handCount[nextPlayer]))
			{
				printf("TEST%d FAIL: Changes not in scope:  gameState->handCount[nextPlayer] changed\n", result->testNum);
				controlGame->handCount[nextPlayer] = activeGame->handCount[nextPlayer];
			}
			if(!(memcmp(controlGame->hand[nextPlayer], activeGame->hand[nextPlayer], sizeof(controlGame->hand[nextPlayer])) == 0)){
				printf("TEST%d FAIL: Changes not in scope:  gameState->hand[nextPlayer] changed\n", result->testNum);
				memcpy(controlGame->hand[nextPlayer], activeGame->hand[nextPlayer], sizeof(controlGame->hand[nextPlayer]));
			}
			if(!(controlGame->whoseTurn == activeGame->whoseTurn))
			{
				printf("TEST%d FAIL: Changes not in scope:  gameState->whoseTurn changed\n", result->testNum);
				controlGame->whoseTurn = activeGame->whoseTurn;
			}

			//printf("MEMCMP VALUE: %d\n", memcmp(controlGame, activeGame, sizeof(struct gameState)));
			assert(memcmp(controlGame, activeGame, sizeof(struct gameState)) == 0);

		}
	}

	// clean up memory
	free(controlGame);
	free(activeGame);
}

int main(int argc, char *argv[]){

	int seed = 9987;
	int printVal = 1;

	srand(seed);

	// containers for results
	struct cardResults *result = declCardResults();
	result->seed = seed;
	result->cardUnderTest = tribute;
	result->testNum = 1;

	printf("\nSTARTING: Tribute (cardtest4)\n");

	// test under regular starting conditions
	printf("ROUND 1:  Current Player has enough cards in deck to draw bonuses\n");
	printf("TEST1: Test with next player has enough cards in deck to reveal 2 without shuffle\n");
	result->ndeckCount = 10;
	result->ndiscardCount = 0;
	result->pdeckCount = 5;
	result->pdiscardCount = 0;
	cardTest4(printVal, seed, result);

	result->testNum++;

	printf("\nTEST2: Test with next player must shuffle to reveal 2 cards\n");
	// test where shuffle required
	result->ndeckCount = 1;
	result->ndiscardCount = 10;
	result->pdeckCount = 5;
	result->pdiscardCount = 0;
	cardTest4(printVal, seed, result);

	result->testNum++;

	printf("\nTEST3: Test with next player only had 1 card to revealin deck\n");
	// test where no cards to be revealed
	result->ndeckCount = 1;
	result->ndiscardCount = 0;
	result->pdeckCount = 5;
	result->pdiscardCount = 0;
	cardTest4(printVal, seed, result);

	result->testNum++;

	printf("\nTEST4: Test with next player only had 1 card to reveal in discard\n");
	// test where no cards to be revealed
	result->ndeckCount = 0;
	result->ndiscardCount = 1;
	result->pdeckCount = 5;
	result->pdiscardCount = 0;
	cardTest4(printVal, seed, result);

	result->testNum++;

	printf("\nTEST5: Test with next player has no cards in deck but more than 2 in discard\n");
	// test where no cards to be revealed
	result->ndeckCount = 0;
	result->ndiscardCount = 10;
	result->pdeckCount = 5;
	result->pdiscardCount = 0;
	cardTest4(printVal, seed, result);

	result->testNum++;

	printf("\nTEST6: Test with next player has no cards to reveal\n");
	// test where no cards to be revealed
	result->ndeckCount = 0;
	result->ndiscardCount = 0;
	result->pdeckCount = 5;
	result->pdiscardCount = 0;
	cardTest4(printVal, seed, result);

	result->testNum++;

	// test under regular starting conditions
	printf("\nROUND 2:  Current Player does not have enough cards in deck to draw bonuses - shuffle required\n");
	printf("TEST7: Test with next player has enough cards in deck to reveal 2 without shuffle\n");
	result->ndeckCount = 10;
	result->ndiscardCount = 0;
	result->pdeckCount = 0;
	result->pdiscardCount = 5;
	cardTest4(printVal, seed, result);

	result->testNum++;

	printf("ROUND 3:  Current Player has cards in deck or discard to draw bonuses\n");
	printf("\nTEST8: Test with next player has enough cards in deck to reveal 2 without shuffle\n");
	result->ndeckCount = 10;
	result->ndiscardCount = 0;
	result->pdeckCount = 5;
	result->pdiscardCount = 0;
	result->pdeckCount = 0;
	result->pdiscardCount = 0;
	cardTest4(printVal, seed, result);

	free(result);
	printf("\nFINISHED: Tribute (cardtest4)\n");

	return 0;
}


