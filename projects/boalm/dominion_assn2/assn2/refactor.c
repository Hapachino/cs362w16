Changes to the cards:
adventurer: Removed copper from the types of to look for.  It will now only grab silver or gold cards.
      if (cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    Notice how copper is not in this list anymore.

smithy: now a card is trashed after drawing three cards.
  Added this:   discardCard(handPos, currentPlayer, state, 1);


council_room: now the other players do not draw a card, and the original player draws a second card.
    for (i = 0; i < state->numPlayers; i++)
  {
    if ( i == currentPlayer )
  Notice how it is now i == currentPlayer instead of i != currentPlayer.


remodel: Now it will let you get a card costing up to 3 more instead of only 2 more.
  This was done by changing the following line to look like:   if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )  
  Notice the 3 instead of 2.