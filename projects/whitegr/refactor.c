Refactored the below cards to each run from their own functions:
Inroduced bugs as noted below:

1. Adventure:
Added bug where int drawntreasure initialize to 1.
This will cause the card to only find one treasure instead of two.

2. Smithy:
4 cards are drawn instead of three.
For loop iterates too many times because of a problem equals.
for (i = 0; i <= 3; i++)

3. Council Room:
Removed conditional if statement that prevented current player from
not getting a draw. Effectively giving the player 5 cards.  
for (i = 0; i < state->numPlayers; i++)
{
      drawCard(i, state);
}

3. Steward:
Removed discard statement for steward card. 
Card is now not discarded when used. Could be played multiple times
if user has multiple action points.

4. Tribute:
No changes.
