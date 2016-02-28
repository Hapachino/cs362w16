/*Chris Loomis
CS362 W16
Assignment 5
BugFixes.c
02/27/2016

My teammates both reported bugs I introduced to Smithy and Village.  Smithy would draw an extra card and Village grant one fewer actions.

Smithy:
	The cause of the 4th card drawing is because I had changed the loop to for (i = 3; i >= 0; i--).
	The solution was to revert back to a for loop that incremented, for (i = 0; i < 3; i++).
	Alternatively I could have just changed the comparison in the loop to simply > instead of >=, this would allow it to work decrementally.
	I prefer the incremental for loop, as it is used more often and is familiar to most.
	
Village:
	The cause of there being 1 too few actions being grated was state->numActions = state->numActions++; which grants only one action.
	There should be 2 granted actions so I reverted back to state->numActions = state->numActions + 2;.  
	
Feast:
	I added the else if clause I had removed back.  This checks to make sure the card selected is a legal choice, as Feast only allows a
	card that has cost up to 5.
	
Council Room:
	I returned the if statement in the loop that prevents the active player from drawing another (5th card).
	Another consideration I had was having the active player draw 3 cards, and then having all players draw a card in the loop.
	This means the active player would get the 4th card and the program wouldn't be running that if statement for every player everytime
	Council Room was played.
	
Adventurer:
	I removed the line I had added that sets the current players hand size to itself - z.  z is the counter of cards drawn while searching
	for the treasure cards.  This would mean that unless 2 treasure are drawn immediately, the 2nd treasure, at least, is guaranteed to be
	thrown out as it would always be the most recent card drawn.
	
I also fixed discardCard() as it bugged me and my tests would always report the wrong number of cards discarding.  This function previously
did not ever add the discarded card to the discard pile (int discard[MAX_PLAYERS][MAX_DECK]) nor increment the discard count 
(int discardCount[MAX_PLAYERS]).  Now it does both, provided the trash flag is not set.

I then added discardCard() calls to the card functions listed above so they may be properly discarded after they have resolved.  For some
this meant I needed to add another argument for where within the hand the played card is, but this was easy as the function cardEffect()
already takes that as an argument and is responsible for calling the card functions.

*/
