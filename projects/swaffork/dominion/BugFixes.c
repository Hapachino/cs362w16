/*
1. playSmithy():
garciann:
"The effects to the player’s hand are not as expected."

murphann:
"does not draw 3 cards"

Fixed version (line 1203):
    //+3 Cards
    for (i = 0; i < 3; i++)
    {
        drawCard(currentPlayer, state);
    }
     
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

*******************************************************************************

2. playAdventurer():
garciann:
"All tests failed concerning playing the card."
"When there are no treasures in the deck, the hand count gets set to -491 and discards everything, similar with when there is only 1 treasure in the deck"

murphann:
"segmentation fault"

Fixed version (line 1175):
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];	//top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
    {
        drawntreasure++;
    }

*******************************************************************************

3. playMine():
Player does not receive expected card.

Because this function passes choice1 as a parameter to gainCard(), the player's expected hand does not match the actual hand.

Fixed version (line 1237):
    gainCard(choice2, state, 2, currentPlayer);

*******************************************************************************

3. playTribute():
Player gains the wrong number of actions.

Because this function increments the current player's number of actions regardless of the cards which the player has drawn, the number of actions in the expected state are not the same as those in the actual state.

Fixed version (line 1335):
    else
    {
        //Action Card
        state->numActions = state->numActions + 2;
    }
*/
