Refactored The Below Cards to each run from their own functions:

1. Adventure:
Introduced bug where int drawntreasure initialize to 1.
This will cause the card to only find one treasure instead of two.

2. Smithy:
4 cards are drawn instead of three.
For loop iterates too many times because of quals.
for (i = 0; i <= 3; i++)

3. Council Room:
Removed conditional if statement that prevented current player from
not  getting a draw. Effectively giving the player 5 cards.  
Bug -  for (i = 0; i < state->numPlayers; i++)
{
      drawCard(i, state);
}

3. Steward:
Removed discard statement for steward card. 
Card is now never discarded. Could be played multiple times
if user has multiple action points.

4. Tribute:
No changes.
