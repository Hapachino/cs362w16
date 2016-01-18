adventurer:
MOVE INITIALIZATION OF CARD DRAWN TO INSIDE IF STATEMENT 
The bug introduced in playAdventurer is in the check to see if the card drawn
is a treasure card. Instead of assigning the cardDrawn variable to the top
card of the hand and then checking to see if that card is a treasure card,
this function now looks at the uninitialized cardDrawn variable. If the value
of the cardDrawn variable happens to be equivalent to a copper, silver, or
gold, then the variable is assigned to the top card of the hand (which may or
may not actually be a treasure card) and the drawnTreasure variable is
incremented, regardless of the card that was drawn.

This may be a tricky bug to catch, because the cardDrawn variable may be
assigned a default value or a garbage value, depending on the platform.

The code appears as follows:

int playAdventurer (struct gameState *state)
{
    int drawntreasure = 0;
    int currentPlayer = whoseTurn(state);
    int cardDrawn;
    int temphand[MAX_HAND];
    int z = 0;			// this is the counter for the temp hand

    while (drawntreasure < 2)
    {
        if (state->deckCount[currentPlayer] < 1)
        {
            //if the deck is empty we need to shuffle discard and add to deck
            shuffle (currentPlayer, state);
        }
        drawCard (currentPlayer, state);

        /* Original version:
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];	//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
        {
            drawntreasure++;
        } */
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
        {
            cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];	//top card of hand is most recently drawn card.
            drawntreasure++;
        }
        else
        {
            temphand[z] = cardDrawn;
            state->handCount[currentPlayer]--;	//this should just remove the top card (the most recently drawn one).
            z++;
        }
    }

    while (z - 1 >= 0)
    {
        // discard all cards in play that have been drawn
        state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1];
        z = z - 1;
    }

    return 0;
}

/*****************************************************************************/

smithy:

