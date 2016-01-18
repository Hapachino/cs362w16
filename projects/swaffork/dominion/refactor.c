adventurer:
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
This function still draws three cards for the current player, but instead of
discarding only the smithy card after all three cards are drawn, it now
discards a card each time the player draws a card.

The code appears as follows:

int playSmithy(struct gameState *state, int handPos)
{
    int i;
    int currentPlayer = whoseTurn(state);

    //+3 Cards
    for (i = 0; i < 3; i++)
    {
        drawCard(currentPlayer, state);
        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
    }
    /* Original version:
    discardCard(handPos, currentPlayer, state, 0); */

    return 0;
}

/*****************************************************************************/
mine:
This function now passes in choice1 (the treasure card the player chose to
discard) into the gainCard function instead of choice2 (the card the player
wanted to exchange the treasure card for). All the logic in this function will
still check out, but the player will not receive the card they intended to.

The code appears as follows:

int playMine(struct gameState *state, int handPos, int choice1, int choice2)
{
    int i;
    int j;
    int currentPlayer = whoseTurn(state);

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

    /* Original version:
    gainCard(choice2, state, 2, currentPlayer); */
    gainCard(choice1, state, 2, currentPlayer);

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
}

/*****************************************************************************/

tribute:

