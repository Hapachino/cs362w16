/*

1. play_adventurer (garciaan):
Test failed. The player's hand count is not as expected.

When a treasure isn't drawn, the top card of the player's hand is
not discarded, so the player's hand count is not as expected.

To modify randomtestadventurer.c, I changed the method name to play_adventurer() and the parameters to include the state, current player, and hand position.

2. playGreat_Hall (murphann):
Test failed. The next player's hand count is not as expected.

In playGreat_Hall, the next player draws a card whenever the current player draws a card. When comparing the actual state to the expected state, we see that the next player's hand count is one more than expected.

To modify randomtestcard.c, I changed the method name to playGreat_Hall() (instead of playSmithy) and modified the expected state to increase the current player's hand by 1 card. The state and handPos remained the only two parameters passed in.

*/
