/*******************************************************************************
REPORTED BUG: After a player plays the Salvager card, the coin count is often
 incorrect.
FIX: The number of coins a player has after playing the Salvager card is 
 determined by the following code on line 1208 of dominion.c:
     state->coins = state->coins + getCost( handCard(choice1, state) );
 The bug is a result of an error in this line. The handCard() function takes as 
 parameters the handPos of the card in question and the game state. The choice1
 parameter being passed in the Salvager case represents the numerical value of
 the card, not it's position in the player's hand. This issue was fixed by 
 changing this line to read: 
     state->coins = state->coins + getCost( handCard(handPos, state) );
 
 
REPORTED BUG: Smithy card causes player to draw wrong number of cards
FIX: The loop for drawing three cards in my playSmithy had an error that was
 causing the wrong number of cards to be drawn: the loop ran from i = 0 -> i <= 3
 when it should run from i = 0 -> i < 3. 
 
 Original:
 void playSmithy (int currentPlayer, int handPos, struct gameState *state)
 {
 //draw three cards
 int i;
 for (i = 0; i <= 3; i++)
 drawCard(currentPlayer, state);
 
 //discard card from hand
 discardCard(handPos, currentPlayer, state, 0);
 }
 
 New:
 void playSmithy (int currentPlayer, int handPos, struct gameState *state)
 {
 //draw three cards
 int i;
 for (i = 0; i < 3; i++)
 drawCard(currentPlayer, state);
 
 //discard card from hand
 discardCard(handPos, currentPlayer, state, 0);
 }
 
 
REPORTED BUG: After playSmithy(), player loses a card
FIX: From examining the test results for Smithy and modifying them to display
 more detailed information, it is clear that playing the card correctly results
 in the player's deckCount correctly decreases by three, and the player's hand
 count correctly increases by two. The error is therefore coming from the 
 player's discard count not being properly incremented, which is actually a 
 result of the played card never being added to the player's dicard pile after
 the turn ends. I addressed this bug by adding a section to the endTurn() 
 function that moves all of the played cards from the turn into the player's 
 discard pile and properly increments the player's discardCount.
 
 New code in endTurn(): 
 //Move cards played during turn from playedCard pile to discard pile
 for (i = 0; i < state->playedCardCount; i++) {
 state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->playedCards[i]; //Discard
 state->discardCount[currentPlayer]++;
 }
 //All played cards have been moved to discard pile
 state->playedCardCount = 0;
 
 NOTE: Test must be ran through endTurn() in order to see results of modified code. 
  Otherwise the error will appear to still be present.
 
REPORTED BUG: When playing Adventurer, the player sometimes gains and/or loses
 cards
FIX: There was a bug introduced by me in the playAdventurer() function that 
 prevented the temporary hand from being created properly. As the cards in the 
 tempHand are later returned to the player's discard pile, an error here causes
 unexpected results for a player's cards after the Adventurer card is played. I 
 fixed this issue by adding an increment condition back to the function to ensure
 that the tempHand is created correctly. 
 
 Original code (inside first while loop in playAdventurer()):
 else {
 temphand[z] = cardDrawn;
 //remove the top (most recently drawn) card
 state->handCount[currentPlayer]--;
 }
 
 New:
 else {
 temphand[z] = cardDrawn;
 //remove the top (most recently drawn) card
 state->handCount[currentPlayer]--;
 z++;
 }
 
 OTHER BUG FIXES FROM REFACTOR.C
 In playVillage(), the flag passed in call do discardCard() was changed from 1
 back to the correct value of 0 (so that card is not trashed). 
 
 In playFeast(), the parameter passed in the call to update coins was changed
 from 4 back to the correct value of 5.
 
 In playCouncilRoom(), the index value used while causing all other players to 
 draw a card was changed back to correct value.
 
 //Each other player draws a card
 int j;
 for (j = 0; j < state->numPlayers; j++)
 {
 if (j != currentPlayer)            //This line was changed from i != to j !=
 drawCard(j, state);
 }


*******************************************************************************/