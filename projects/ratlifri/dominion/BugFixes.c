/*

Bug Fixes
--------------------------------

Smithy Card:

	Bug:  The bug reported from my two teammates are that the after state 
	of the handcount was lower than it should be, and hand has one too many
    and deck has one too few.

    Description:  It appears that instead of drawing three cards smithy is drawing two.

    Debug:

    This was debugged by putting a breakpoint in the smithy card draw loop 
	on the drawCard function call, and watching the iterator 'i'.  The value
	of i was 1 for the first call, 2 for the second call, then the loop ended.

	Fix:

    The loop iterator starting value was changed from 1 to 0 to draw three cards.

	dominion.c:

		Bug:
                      for (i = 1; i < 3; i++)

		Correction:
                      for (i = 0; i < 3; i++)


Adventurer Card:

	Bug:  The bug reported from my two teammates are that too many cards remain 
    in play at the end of the Adventurer card.

    Description:  Not all of the drawn cards end up being discarded; one remains.

    Debug:

    After general debugging of the adventurer function with breakpoints and 
    inspection of variables and game state, it became apparent a discard function
	was omitted, specifically, the discardCard() function.  This function needs
    the hand position of the card but it is not passed in.  So the correction 
    included adding the function call and refactoring parameters to add hand
	position for discardCard().

    A remaining discarding issue was debugged.  A breakpoint was put inside the 
	while loop on the function call, and watched the iterator 'z' and temphand
    array holding the cards adventurer found that were not treasures. The value 
    of z decremented down to 1 when the while loop stopped. This left a card in
    temphand array.

	Fixes:

	Toward adding discardCard()...

	dominion_helpers.h:

	Bugs:

        int cardEffectAdventurer(int currentPlayer, struct gameState *state);

	Corrections:

        int cardEffectAdventurer(int currentPlayer, struct gameState *state, int handPos);


	dominion.c:

	Bugs:

        int cardEffectAdventurer(int currentPlayer, struct gameState *state)

        case adventurer:
            return ( cardEffectAdventurer(currentPlayer, state) );

	Corrections:

        int cardEffectAdventurer(int currentPlayer, struct gameState *state, int handPos)

        discardCard(handPos, currentPlayer, state, 0);

        case adventurer:
            return ( cardEffectAdventurer(currentPlayer, state, handPos) );


    while loop iterator stop condition was changed and all temphand array cards
    now get discarded.

	dominion.c:

		Bug:
                      while( z - 1 > 0 ){

		Correction:
                      while( z > 0 ){

*/
