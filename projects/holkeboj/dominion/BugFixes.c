/*
Jack Holkeboer
Oregon State University
holkeboj@onid.oregonstate.edu
CS362
Assignment 5


****************************
****************************
BUGS FOUND BY TEAMMATES
****************************
****************************

************************************************
Bugs found by Teammate #1 Kyle Collins (ONID collikyl)
***********************************************

******************************
Bug #1: Adventurer does not correctly move itself to the played pile.
************************************************************
This happens because the adventurer card does not discard itself.  We can see by examining
the code for other cards that they all discard themselves by calling discardCard().  
And discardCard() is what moves it to the played pile.
However, the adventurer card is missing this function.  I added the following line:

      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      
We ensure that it will be added to the played pile by setting the fourth parameter (trash flag)
to be zero.  If you look at the following snipped from discardCard(), you can see why:

  //if card is not trashed, added to Played pile 
  if (trashFlag < 1)
    {
      //add card to played pile
      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
      state->playedCardCount++;
    }
	
If the trash flag is 1 or greater, the card will not be added to the played pile.

******************************
Bug #2: When Adventurer is played, there is only one card being drawn 
    and added to the players hand while in other cases no cards are 
    drawn at all despite treasure being in the fullDeck. The adventurer card 
    is also skipping some treasures in the deck despite having a treasureCount < 2.
*********************************************************************
This behavior is caused by the bug I introduced in the Adventurer card by adding 
the following unnecessary condition, immediately after drawCard() is called:

        if (drawntreasure == 1) {
            // BUG: draw two extra cards if drawntreasure == 1.  Could potentially result in drawing
            // more than two treasure cards.
            drawCard(currentPlayer, state);
            drawCard(currentPlayer, state);
        }
 
 This is contained within the while loop " while (drawntreasure < 2) ".  
 This means that the loop will run again when the first treasure card is found (drawntreasure=1).
 Due to the above condition, once the first card is drawn, the program will draw two cards, in
 addition to already have drawn another one at the beginning of the current while loop iteration.
 The result is that if a treasure card is not drawn on the second iteration of the while loop on the 
 initial draw, there will be three total cards drawn instead of the expected one.  
 
 On the following lines, the card checks whether the most recently drawn card was a treasure, and if so,
 increments the drawntreasure count.  

        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
            drawntreasure++;
        } else {
            temphand[z] = cardDrawn;
            state->handCount[currentPlayer]--;
            z++;
        }

The problem is that cardDrawn will only reflect the most recent card drawn.  Since two extra cards are drawn
when drawntreasure==1, the first card drawn in that condition will not be checked.  This is the cause of 
"skipping" treasure cards.

I fixed this bug by removing the "if (drawntreasure == 1)" condition entirely.  After this is done we can see
the correct behavior for a given number of treasure cards in the deck.




************************************************
Bugs found by Teammate #2 Shaine Afzal (ONID afzals)
***********************************************

Bug #1: The fullDeckCount may not be correct, the expected amount was 25 but the result was 0.
**********
Upon closer inspection this is actually not a bug but rather a problem with my teammate's test code.
Take a look at the file projects/azfals/unittest1.c:

    // from projects/azfals/unittest1.c
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing fullDeckCount\n");
	
	x = rand() % 10;
	y = rand() % 20;
	z = rand() % 10;
	
	G.handCount[0] = x;
	G.deckCount[0] = y;
	G.discardCount[0] = z;
	
	rtotal = x + y + z;
	ftotal = fullDeckCount(0, smithy, &G);
	
	if(rtotal != ftotal)
	{
		printf("Test failed. Result: %d, Expected: %d\n", rtotal, ftotal);
	}
	else
	{
		printf("Test passed\n");
	}

This test is initializing a game, and then assigning random values for the handCount, deckCount, and discardCount
for player 0.  Then he calls the fullDeckCount function for player zero and the smithy card.

The problem is that fullDeckCounts return value is not based on the counts of each pile, but rather 
how many occurences of the card in question are in the piles.  If we take a look at the code of 
fullDeckCount, we can see that the return count is only incremented if the card parameter is found in 
that pile.  So the return value in this case will be the total number of smithy cards in that pile.  The 
problem with this test is that it checks the total number of cards of any type, rather than the total number
of smithy cards.  His test is returning 0 because there are no smithy cards in the hand, deck, or discard piles. 


Bug #2: In the Smithy card, when the handPos passed to the function
is 2 there were only 4 cards in the players hand after running the function. However when there 
are other numbers passed in for handPos there are 7 cards in the players hand after running the function.
**********
This is a bug that I introduced.  If you take a look at my refactor.c file, youll see that I 
purposefully made the Smithy card behave incorrectly if the handPos passed is 2.  This 
is the code that causes the bug:
        
    for (i = 0; i < 3; i++) {
        if (handPos != 2) {}
            drawCard(currentPlayer, state);
        }
    }

I fixed the bug by removing the "if (handPos != 2)" condition, so drawCard() will be called
for any handPos.


****************************
****************************
BUGS THAT I INTRODUCED
****************************
****************************

Bug #1: Smithy card does not draw any cards if handPos is 2
****************************
This bug was fixed above in response to bug #2 reported by Shaine Afzal.  See above.


Bug #2: Adventurer card draws extra cards and doesnt check them
****************************
This bug was fixed above in response to bug #2 reported by Kyle Collins.  See above.


Bug #3: Outpost card increments the hand count for the current player (should not do this)
**************************
int outpost_card(handPos, currentPlayer, state) {
    // set outpost flag
    state->outpostPlayed++;
    
    // THIS LINE CAUSES THE BUG
    state->handCount[currentPlayer]++;
    
    // discard card
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}

In the above, you can see where I added the line "state->handCount[currentPlayer]++;".  This line 
is not in the original code.  The hand count should not be incremented because no card is being drawn.
I fixed this bug by removing that line, so the function looks like this:

    // Refactored outpost card
    int outpost_card(int handPos, int currentPlayer, struct gameState *state) {
        // set outpost flag
        state->outpostPlayed++;
        
        // discard card
        discardCard(handPos, currentPlayer, state, 0);
        return 0;
    }


Bug #4: Remodel card:  In the line that checks getCost for choices 1 and 2, the choices are swapped.
This will result in returning -1 at the wrong time and vice versa.
**************************
To introduce this bug, I reversed the position of the choice1 and choice2 parameters in the 
line with the condition "if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )".
This causes the function to return -1 in the incorrect scenario.

//  BUGGY VERSION
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

I fixed this bug by putting these two variables back in their original position, as seen below:

// FIXED VERSION
int remodel_card(handPos, currentPlayer, choice1, choice2, state) {
    // store card we will trash
    j = state->hand[currentPlayer][choice1];
    
        // THIS IS THE LINE WHERE THE FIX WAS MADE
        // BY REVERSING choice1 AND choice2
    if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) ) {
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


Bug #5: Village card only discards the card 
    if the player has more than three actions after drawing two actions
**************************
I introduced this bug by wrapping the discard in the condition "if (state->numActions > 3)".
This condition should not be there.  The card should be discarded any time it is played.

// BUGGY VERSION
int village_card(int handPos, int currentPlayer, struct gameState *state) {
    // +1 card
    drawCard(currentPlayer,state);

    // +2 actions
    state->numActions = state->numActions + 2;

    // discard played card from hand
    if (state->numActions > 3) {    // THIS CONDITION CAUSES THE BUG
        discardCard(handPos, currentPlayer, state, 0);
    }
    return 0;
}


I fixed this bug by removing that condition, as seen below:

// FIXED VERSION
int village_card(int handPos, int currentPlayer, struct gameState *state) {
    // +1 card
    drawCard(currentPlayer,state);

    // +2 actions
    state->numActions = state->numActions + 2;

    // discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}
*/