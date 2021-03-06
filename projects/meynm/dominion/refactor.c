#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
// code with BUGS DOCUMENTED

// bug on line 15
void playSmithy( int currentPlayer, struct gameState *state, int handPos )
{
	int i;
	for (i = 0; i < 3; i++)
	{
		drawCard( currentPlayer, state);
	}
	//discard card from hand
	discardCard( currentPlayer, handPos, state, 1 ); // should be (handPos, currentPlayer, state, 0)
	return;
}

// draw cards until 2 treasure cards have been drawn
// bugs in line 23, 43 (fixed), 44 (fixed)
void playAdventurer( int currentPlayer, struct gameState *state )
{
	int drawntreasure=0, cardDrawn, z = 0;	// should be initialized to 0
	int temphand[MAX_HAND];
	//keep drawing cards until 2 treasure cards are drawn
	while ( drawntreasure < 2 )
	{
		//if the deck is empty we need to shuffle discard and add to deck
		if (state->deckCount[currentPlayer] < 1)
		{
			shuffle( currentPlayer, state );
		}
		drawCard( currentPlayer, state );

		//top card of hand is most recently drawn card.
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else
		{
			temphand[z] = cardDrawn;
			//remove the top card
			state->handCount[currentPlayer]--;	// should be state->handCount[currentPlayer]--
			z++;//z needs to be incremented
		}
	}
	while ( z - 1 >= 0 )
	{
		//discard all cards in play that have been drawn
		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1];
		z = z - 1;
	}
	return;
}

// trash a treasure card, choose one costing up to 3 more
// bugs in line 68 and 78
int playMine( int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2 )
{
	int i, j;
	j = state->hand[currentPlayer][choice1];    //store card we will trash

	if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
	{
		return -1;
	}
	if (choice1 > treasure_map || choice1 < curse) // choice1 should be choice2
	//if (choice2 > treasure_map || choice2 < curse)
	{
		return -1;
	}

	if (( getCost( state->hand[currentPlayer][choice1] ) + 3 ) < getCost( choice2 )) // should be <
	{
		return -1;
	}

	gainCard( choice2, state, j, currentPlayer ); // j should be 2

	//discard card from hand
	discardCard( handPos, currentPlayer, state, 0 );

	//discard trashed card
	for (i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (state->hand[currentPlayer][i] == j)
		{
			discardCard( i, currentPlayer, state, 1 );
			break;
		}
	}

	return 0;
}

// bug on line 118--infinite loop!
void playBaron( int currentPlayer, struct gameState *state, int choice1 )
{
	state->numBuys++;    //Increase buys by 1!
	if (choice1 > 0)
	{    //Boolean true or going to discard an estate
		int p = 0;    //Iterator for hand!
		int card_not_discarded = 1;    //Flag for discard set!
		while ( card_not_discarded )
		{
			if (state->hand[currentPlayer][p] == estate)
			{    //Found an estate card!
				state->coins += 4;    //Add 4 coins to the amount of coins
				state->discard[currentPlayer][state->discardCount[currentPlayer]] =
						state->hand[currentPlayer][p];
				state->discardCount[currentPlayer]++;
				for (; p < state->handCount[currentPlayer]; p++)
				{
					state->hand[currentPlayer][p] = state->hand[currentPlayer][p + 1];
				}
				state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
				state->handCount[currentPlayer]--;
				//Need to exit the loop! set card_not_discarded to 0
			} else if (p > state->handCount[currentPlayer])
			{
				if (DEBUG)
				{
					printf( "No estate cards in your hand, invalid choice\n" );
					printf( "Must gain an estate if there are any\n" );
				}
				if (supplyCount( estate, state ) > 0)
				{
					gainCard( estate, state, 0, currentPlayer );
					state->supplyCount[estate]--;    //Decrement estates
					if (supplyCount( estate, state ) == 0)
					{
						isGameOver( state );
					}
				}
				card_not_discarded = 0;    //Exit the loop
			}

			else
			{
				p++;    //Next card
			}
		}
	}

	else
	{
		if (supplyCount( estate, state ) > 0)
		{
			gainCard( estate, state, 0, currentPlayer );    //Gain an estate
			state->supplyCount[estate]--;    //Decrement Estates
			if (supplyCount( estate, state ) == 0)
			{
				isGameOver( state );
			}
		}
	}
}

// bug on line 174
void playSteward(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2, int choice3)
{
	if (choice1 == 1)
	{
		//+2 cards
		drawCard( currentPlayer, state );
		drawCard( currentPlayer, state );
	} else if (choice1 == 2)
	{
		//+2 coins
		state->coins = state->coins + 2;
	} else
	{
		//trash 2 cards in hand
		//discardCard( choice1, currentPlayer, state, 1 ); // choice1 should be choice2
		discardCard( choice2, currentPlayer, state, 1 ); // choice1 should be choice2
		discardCard( choice3, currentPlayer, state, 1 );
	}

	//discard card from hand
	discardCard( handPos, currentPlayer, state, 0 );
}
