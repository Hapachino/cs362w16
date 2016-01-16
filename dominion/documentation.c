/* smithy: */
This card places three cards from the player's deck into the player's hand. It
also moves the smithy card into the player's discard pile.

/* adventurer: */
This card draws cards from the player's deck until the player draws three
treasure cards total. All cards drawn from the player's deck that were not
treasure cards are moved into the player's discard pile.
    case adventurer:
      while(drawntreasure<2){
    if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
      }
      while(z-1>=0){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
      }
      return 0;

/* discardCard(): */
This function removes the card the player is currently holding from handPos and
moves it either into the trash pile (if the trashFlag is 1), thereby removing
the card from the game, OR into the player's discard pile. The side effects are
incrementing the count of played cards (if card was discarded) and decrementing
the count of cards still in the player's hand. Additionally, the card that the
player is currently holding (in handPos) is updated to be the next card in the
player's hand.

/* updateCoins(): */
This function effectively converts the copper, silver, and gold in the player's
hand into coins. It also adds any bonuses to the player's coin count (which may
come from cards like feast or cutpurse).
