/* Adventurer bug
Second while loop should be (z - 1 >= 0)

This bug was found by my test, because the hand, deck and discard counts never matched their intended number
*/

/* Smithy bug
should be:
for (i = 0; i < 3; i++)

This bug was found by my test, because the hand counts never matched their
intended state
*/

/*Council Room Bug

second for loop i is not initialized to 0
//Each other player draws a card
for ( i = 0; i < state->numPlayers; i++)
{

This resulted in some players not having drawn a card. This too was caught by my test.
*/

/*ScoreFor Bug
the Deck summation used the discard count instead of the deck count to loop
for (i = 0; i < state->discardCount[player]; i++)


This resulted in incorrect scores being calculated. In certain cases where there was a different discard count and deck card count
*/