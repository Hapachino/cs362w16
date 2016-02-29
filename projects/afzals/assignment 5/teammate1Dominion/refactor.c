/*
Jack Holkeboer
CS362 Assignment 2 part 3
Documentation of refactoring

Refactor five cards out of case statements and into their own functions.
Mandatory: Smithy, Adventurer
Chosen by me: Outpost, Remodel, Village

*************************
Smithy
Bug: Does not draw any cards if hand position is 2
*************************
int smithy_card(int handPos, int currentPlayer, struct gameState *state) {
    int i;
    // +3 Cards
    for (i = 0; i < 3; i++) {
        if (handPos != 2) {}
            drawCard(currentPlayer, state);
        }
    }
    
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}

Called in case statement:
case smithy:
        return smithy_card(handPos, currentPlayer, state);

*************************
Adventurer
Bug: Once one adventurer card has been drawn, it draws two extra cards.
But the "cardDrawn" only checks the most recently drawn card.
This could potentiall result in a adventurer card giving the player more than two treasure cards.
*************************
int adventurer_card(int handPos, int z, int temphand[], int drawntreasure, int currentPlayer, int cardDrawn, struct gameState *state) {
    while (drawntreasure < 2) {
        if (state->deckCount[currentPlayer] < 1) {
            shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        if (drawntreasure == 1) {
            // draw two extra cards.  Could potentiall result in drawing
            // more than two treasure cards.
            drawCard(currentPlayer, state);
            drawCard(currentPlayer, state);
        }
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
            drawntreasure++;
        } else {
            temphand[z] = cardDrawn;
            state->handCount[currentPlayer]--;
            z++;
        }
        while (z-1>=0) {
            state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z-1];
            z = z -1;
        }
        return 0;
    }
}

Called in case statement:
case adventurer:
    return adventurer_card(handPos, z, temphand, drawntreasure, currentPlayer, cardDrawn, state);

*************************
Outpost
Bug: increments the hand count for the current player (should not do this)
*************************
int outpost_card(handPos, currentPlayer, state) {
    // set outpost flag
    state->outpostPlayed++;
    state->handCount[currentPlayer]++;
    
    // discard card
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}

Called in case statement:
case outpost:
    return outpost_card(handPos, currentPlayer, state);

*************************
Remodel
Bug: In the line that checks getCost for choices 1 and 2, the choices are swapped.
This will result in returning -1 at the wrong time and vice versa.
*************************
int remodel_card(handPos, currentPlayer, choice1, choice2, state) {
    // store card we will trash
    j = state->hand[currentPlayer][choice1];
    
    if ( (getCost(state->hand[currentPlayer][choice2]) + 2) > getCost(choice1) ) {
        return -1;
    }
    
    gainCard(choice2, state, 0, currentPlayer);
    
    // discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    
    //discard trashed card
    for (i = 0; i < state->handCount[currentPlayer]; i++) {
        if (state->hand[currentPlayer][i] == j) {
            discardCard(i, currentPlayer, state, 0);
            break;
        }
    }
    
    return 0;
}

Called in case statement:
case remodel:
    return remodel_card(handPos, currentPlayer, choice1, choice2, state);

*************************
Village
Bug: Only discards the card if the player has more than three actions after drawing two actions
*************************
int village_card(handPos, currentPlayer, state) {
    // +1 card
    drawCard(currentPlayer,state);

    // +2 actions
    state->numActions = state->numActions + 2;

    // discard played card from hand
    discardCard(handPos, currentPlayer, state, 0)
    return 0;
}

Called in case statement:
case village:
    return village_card(handPos, currentPlayer, state);


*/