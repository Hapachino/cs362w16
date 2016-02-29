Ava Petley
Bug fixes

Smithy: hand count incorrect because too many cards are drawn. 
the error is due to a bug I introduced .The for loop statment i<4 it should be i<3 this has been changed
	for (i = 0; i < 4; i++)
	{
	  drawCard(currentPlayer, state);
	}
Adventurer: The errors reported had to do with the hand count and deck count of the player and this error is because of one I introduced. I removed copper from the if 
	statment so coppers are always discarded when they should be added to the players hand. This causes incorrected numbers with the hand and deck counts. so I have
	fixed this bug by adding copper into the if statment.

Council: Error reported was an infinate loop due to this peace of code. Where I introduced the bug i=currentPlayer instead of i!=currentPlayer
I don't think the bug would cause and infinate loop rather the current player would draw a card instead of other players. But regardless the bug has been fixed.
 
    for (i = 0; i < state->numPlayers; i++)
	{
	  if ( i = currentPlayer )
	    {
	      drawCard(i, state);
	    }
	}

Village: The error is the players hand count is 1 too many and the other player looses a card. This is a bug I introduced. So I fixed the problem by removing
		 currentPlayer = currentPlayer + 1 which was put in before the discard function is called. The card will be removed from the correct player now.

Scorefor : Error reported in the Scorefor function.  The third for loop should have been this : for (i = 0; i < state->deckCount[player]; i++) but it was
				for (i = 0; i < state->discardCount[player]; i++) so I fixed it.

All my introduced bugs were found except the bug I introduced into the steward function where I switched the integers in the if and if else statements so I changed those
back.
