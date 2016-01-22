/*
	adventurer_card
	refactored to increment by 2 for silver or gold card based on the drawn card
*/
int adventurer_card(int drawntreasure, int currentPlayer, int cardDrawn, struct gameState *state, int temphand[], int z) {
	while (drawntreasure < 2) {
		if (state->deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, state);
		
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //top card of hand is most recently drawn card.
		
		if (cardDrawn == copper)
			drawntreasure++;
		else if (cardDrawn == silver || cardDrawn == gold) // refactor to increment by 2 for silver or gold
			drawntreasure = drawntreasure + 2;
		else {
			temphand[z]=cardDrawn;
			state->handCount[currentPlayer]--;
			z++;
		}
	}
    
	while (z-1 >= 0) {
		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z-1]; // discard all cards in play that have been drawn
		--z;
    }
    
	return 0;
}


/*
	smithy_card
	refactored to draw card for the next player
*/
int smithy_card(int currentPlayer, struct gameState *state, int handPos) {
	int i;
	//+3 Cards
    for (i=0; i<3; ++i)
		drawCard(currentPlayer, state);
	
	drawCard(currentPlayer+1, state); // refactor to draw card for the next player
	
	//discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
	
	return 0;
}


/*
	village_card
	refactored to change number of actions depending on whether the last card was played
*/
int village_card(int currentPlayer, struct gameState *state, int handPos) { 
	//+1 Card
	drawCard(currentPlayer, state);
	
	// refactor to change number of actions depending on whether the last card was played
	// check if the last card in hand is played
	if (handPos == (state->handCount[currentPlayer] - 1)) //+3 Actions
		state->numActions = state->numActions + 3;
    else //+2 Actions
		state->numActions = state->numActions + 2;
	
	//discard played card from hand
	discardCard(handPos, currentPlayer, state, 0);

	return 0;
}


/*
	great_hall_card
	refactored to increase number of actions by two
*/
int great_hall_card(int currentPlayer, struct gameState *state, int handPos) { 
	//+1 Card
	drawCard(currentPlayer, state);
	
	// refactor to increase number of actions by two
	//+2 Actions
	state->numActions = state->numActions + 2;
	
	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	
	return 0;
}
