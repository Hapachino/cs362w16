/********************************************************************
 * Assignment 5
 * Author: Isaiah Fentress
 * Date: 2/28/16
 * Description: Fix all the bugs that are found in your code. First 
 * fix the bugs that your teammate found then fix the bugs that you 
 * introduced. For each bug I've included the original code, and the 
 * newly updated code. I've inserted comments where I've made changes
 * to fix the errors.
 ********************************************************************/

Bug 1.0: Great Hall always draws a card from player 2's deck.
Reported by: Will Thomas

Result: This caused a mismatch in the expected hand and deck counts
for both players. Player 2 will always gain a card from their deck
into their hand, even though we expect this to happen for the current
player.

Pre-fix code for playGreatHall
/*-------------------------------------------------------------------*/
int playGreatHall(struct gameState *state, int handPos) {
    int currentPlayer = whoseTurn(state); // Determine current player
    
    //+1 Card
    drawCard(currentPlayer = 1, state);
			
    //+1 Actions
    state->numActions++;
			
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    
    return 0;
}

Post-fix code for playGreatHall
/*-------------------------------------------------------------------*/
int playGreatHall(struct gameState *state, int handPos) {
    int currentPlayer = whoseTurn(state); // Determine current player
    
    //+1 Card
    drawCard(currentPlayer, state);
	/*Needed to remove the =1 from the "drawCard" function)*/
    
    //+1 Actions
    state->numActions++;
			
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    
    return 0;
}

I identified that the bug was caused by the call to drawCard. When calling
drawCard the current player was being arbitrarily set to 1 (player 2). This 
was making it so that the player playing the card had no impact on who 
actually got cards. By removing the =1 the function should work as expected.
This covers all of the bugs that I introduced myself.

/*********************************************************************/

Bug 2.0: Playing the adventurer card causes the current player to drawCard
an additional treasure card.
Reported by: Tim Robinson

Result: This caused a mismatch in the expected hand and deck counts
for the active player. The player will continue to search his deck after
two treasures are selected. 

Pre-fix code for playAdventurer
/*-------------------------------------------------------------------*/
int playAdventurer(struct gameState *state) {
    int z = 0; // Temp hand counter
    int drawntreasure = 0; // Counts treasure cards drawn
    int temphand[MAX_HAND]; // Create temp hand for cards
    int currentPlayer = whoseTurn(state); // Determine current player
    int cardDrawn; // Stores info on card drawn
    
    while(drawntreasure <= 2) {
        //if the deck is empty we need to shuffle discard and add to deck
        if (state->deckCount[currentPlayer] <1){
          shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        //top card of hand is most recently drawn card.
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
        if (cardDrawn == copper || cardDrawn == silver) {
            drawntreasure++;
        }
        else {
            temphand[z]=cardDrawn;
            // this should just remove the top card (the most recently drawn one).
            state->handCount[currentPlayer]--;
            z++;
        }
    }
    
    // Loop through all cards in temphand
    while(z-1>0) {
        // discard all cards in play that have been drawn
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; 
        z=z-1;
    }
    return 0;
}

Post-fix code for playAdventurer
/*-------------------------------------------------------------------*/
int playAdventurer(struct gameState *state) {
    int z = 0; // Temp hand counter
    int drawntreasure = 0; // Counts treasure cards drawn
    int temphand[MAX_HAND]; // Create temp hand for cards
    int currentPlayer = whoseTurn(state); // Determine current player
    int cardDrawn; // Stores info on card drawn
    
    /* Modified the while loop logical from <= to < */
    while(drawntreasure < 2) {
        //if the deck is empty we need to shuffle discard and add to deck
        if (state->deckCount[currentPlayer] <1){
          shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        //top card of hand is most recently drawn card.
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
        if (cardDrawn == copper || cardDrawn == silver) {
            drawntreasure++;
        }
        else {
            temphand[z]=cardDrawn;
            // this should just remove the top card (the most recently drawn one).
            state->handCount[currentPlayer]--;
            z++;
        }
    }
    
    // Loop through all cards in temphand
    while(z-1>0) {
        // discard all cards in play that have been drawn
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; 
        z=z-1;
    }
    return 0;
}

I identified that the bug was caused by the while loop impacted by the 
drawntreasure variable. It continues when the drawntreasure variable 
is equal to two. It should stop at this point because the max number
of treasures has been returned. To fix this I changed the <= to a <.

It seems that Tim's test failed to find other errors that my test found. 
My test notices that gold is not being counted to the treasures for drawing
which will cause issues because those won't be added to the player's hand.
This error will be fixed in my future rollback of self-introduced bugs. 

/*********************************************************************/

Bug 3.0: Playing the adventurer card does not add gold cards to the 
player's hand. The user also doesn't recover all cards from their 
temp hand, causing 1 card to be lost (no longer in players deck).
Reported by: Isaiah Fentress

Result: This causes a mismatch in the player's deck count (one less 
than expected), and also causes them to skip over gold cards, giving
them a tactical disadvantaged (fewer treasures potentially added to 
hand). 

Pre-fix code for playAdventurer
/*-------------------------------------------------------------------*/

int playAdventurer(struct gameState *state) {
    int z = 0; // Temp hand counter
    int drawntreasure = 0; // Counts treasure cards drawn
    int temphand[MAX_HAND]; // Create temp hand for cards
    int currentPlayer = whoseTurn(state); // Determine current player
    int cardDrawn; // Stores info on card drawn
    
    while(drawntreasure < 2) {
        //if the deck is empty we need to shuffle discard and add to deck
        if (state->deckCount[currentPlayer] <1){
          shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        //top card of hand is most recently drawn card.
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
        if (cardDrawn == copper || cardDrawn == silver) {
            drawntreasure++;
        }
        else {
            temphand[z]=cardDrawn;
            // this should just remove the top card (the most recently drawn one).
            state->handCount[currentPlayer]--;
            z++;
        }
    }
    
    // Loop through all cards in temphand
    while(z-1>0) {
        // discard all cards in play that have been drawn
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; 
        z=z-1;
    }
    return 0;
}

Post-fix code for playAdventurer
/*-------------------------------------------------------------------*/
int playAdventurer(struct gameState *state) {
    int z = 0; // Temp hand counter
    int drawntreasure = 0; // Counts treasure cards drawn
    int temphand[MAX_HAND]; // Create temp hand for cards
    int currentPlayer = whoseTurn(state); // Determine current player
    int cardDrawn; // Stores info on card drawn
    
    while(drawntreasure < 2) {
        //if the deck is empty we need to shuffle discard and add to deck
        if (state->deckCount[currentPlayer] <1){
          shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        //top card of hand is most recently drawn card.
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
        /* Added || cardDraw == gold to the code */
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
            drawntreasure++;
        }
        else {
            temphand[z]=cardDrawn;
            // this should just remove the top card (the most recently drawn one).
            state->handCount[currentPlayer]--;
            z++;
        }
    }
    
    // Loop through all cards in temphand
    /* Fixed the whle loop. Changed from > to >= */
    while(z-1>=0) {
        // discard all cards in play that have been drawn
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; 
        z=z-1;
    }
    return 0;
}

These were the documented bugs I already had. They were easy to find with tests that pointed
out that the player's deck was not ending with the number of expected cards. This led to
investigation of the final while loop which doesn't return all of the cards that are stored in it.

The other issue was with gold never being returned as a treasure. This was spotted by ensuring that
gold would appear in the user's deck, and would sometime causes fewer than 2 treasures to be returned.

/*********************************************************************/

Bug 4.0: Playing the smithy card results in 4 cards being drawn for the 
active player instead of 3. Also found a bug that always gives player 2
to drawCards in addition to the active player.
Reported by: Isaiah Fentress

Result: This causes a mismatch in the general game state because players
have more cards than expected in their hand after playing the smithy card.

Pre-fix code for playSmithy
/*-------------------------------------------------------------------*/

int playSmithy(struct gameState *state, int handPos) {
    int currentPlayer = whoseTurn(state); // Determine current player
    
    // +3 Cards
    int i;
    for (i = 0; i <= 3; i++) {
        drawCard(currentPlayer, state);
        drawCard(2, state);
	}
			
    // discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    
    return 0;
}

Post-fix code for playSmithy
/*-------------------------------------------------------------------*/
int playSmithy(struct gameState *state, int handPos) {
    int currentPlayer = whoseTurn(state); // Determine current player
    
    // +3 Cards
    int i;
    for (i = 0; i < 3; i++) {
        /* Removed second draw card function, and fixed the for loop */
        drawCard(currentPlayer, state);
	}
			
    // discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    
    return 0;
}

These were the documented bugs I already had. They were easy to find by just looking at the code.
Testing the for loop quickly showed that it was iterated through 4 times instead of 3. The issue
with the duplicate draw was located by the test script, but also easily identifiable by viewing
the code. 

/*********************************************************************/

Bug 5.0: Playing the village card results in 5 additional actions 
for the current player, and one additional card for player 2. Expected
that the additional card would be for the currentPlayer and that there
would just be two actions for the current player.
Reported by: Isaiah Fentress

Result: This causes a mismatch in the general game state because an
unexpected player has too many cards, and the current player has too 
many actions and one fewer cards than expected.

Pre-fix code for playVillage
/*-------------------------------------------------------------------*/

int playVillage(struct gameState *state, int handPos) {
    int currentPlayer = whoseTurn(state); // Determine current player
    
    //+1 Card
    drawCard(1, state);
            
    //+2 Actions
    state->numActions = state->numActions + 5;
            
    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);
    
    return 0;
}

Post-fix code for playVillage
/*-------------------------------------------------------------------*/
int playVillage(struct gameState *state, int handPos) {
    int currentPlayer = whoseTurn(state); // Determine current player
    
    //+1 Card
    drawCard(currentPlayer, state);
    /* Changed 1 to currentPlayer */        
    
    //+2 Actions
    state->numActions = state->numActions + 2;
    /* Changed +5 to +2 */
            
    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);
    
    return 0;
}

My test scripts easily caught both of these errors. You could easily see
that the number of actions returned was higher than the expected, which
leads to investigation of that portion of the code. Finally, you could
see that the correct players were not getting a card, which leads to 
investigation of the draw card function, which you can visually see 
that it is not getting the required inputs.

/*********************************************************************/

Bug 6.0: Playing the council room card results in only the current player 
getting an extra card (on top of their 4), instead of all other players
getting a card. Additionally, the discardCard function is trashing
the council room card, removing it from the game causing a mismatch
in expected deck size for the current player. 
Reported by: Isaiah Fentress

Result: This causes a mismatch in the general game state because all
other players have too few cards, and the primary player has too many.

Pre-fix code for playCouncilRoom
/*-------------------------------------------------------------------*/

int playCouncilRoom(struct gameState *state, int handPos) {
    int currentPlayer = whoseTurn(state); // Determine current player
    
    // +4 Cards
    int i;
    for (i = 0; i < 4; i++) {
	  drawCard(currentPlayer, state);
	}		
    
    // +1 Buy
    state->numBuys++;
			
    // Each other player draws a card
    for (i = 0; i < state->numPlayers; i++) {
	    if ( i == currentPlayer ) {
            drawCard(i, state);
	    }
	}
			
    // Put played card in played card pile
    discardCard(handPos, currentPlayer, state, 1);
			
    return 0;
}

Post-fix code for playCouncilRoom
/*-------------------------------------------------------------------*/
int playCouncilRoom(struct gameState *state, int handPos) {
    int currentPlayer = whoseTurn(state); // Determine current player
    
    // +4 Cards
    int i;
    for (i = 0; i < 4; i++) {
	  drawCard(currentPlayer, state);
	}		
    
    // +1 Buy
    state->numBuys++;
			
    // Each other player draws a card
    for (i = 0; i < state->numPlayers; i++) {
	    /* Fixed if statement by changing == to != */
        if ( i != currentPlayer ) {
            drawCard(i, state);
	    }
	}
			
    // Put played card in played card pile
    discardCard(handPos, currentPlayer, state, 1);
			
    return 0;
}

Test script caught this error because it checked that the hand states 
were the same as expected for all players. Using debugging I was able
to step through the code and see the number of cards in each players
hand, which made it easy to spot when cars were inaccurately being added.