No bugs found in the 4 unit tests.

In adventurer, non-treasure cards that are drawn are not discarded. We know this because one of our asserts checks to make
sure that the discard count for testG is more than the discard count for G fails, even after we put a non-coin card into the
deck to be drawn.

In smithy, 1 card is distributed to both players instead of 3 cards going to the player who played the card. We know this
because both asserts to compare the number of cards to the original number for both players fail.

In village, too many actions are given to player 2. We know this because the assertion that the player has only gained 1 action
fails for player 2. Player 1 gets the correct amount, though.

In council room, it gives too many buys to the current player. Also, it does not give the enemy player a card.