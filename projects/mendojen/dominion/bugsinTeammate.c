Bug:
unittest 1: getCost
All tests pass.

unittest 2: updateCoins
All tests pass

unitTest 3: isGameOver
Bug found when setting random piles of 3 to 0. Some pass and some fail, meaning that there is a bug
with one or more of the cards. My test indicates that the bug is when treasure map and/or sea hag is
set to 0. These 2 cards are the source of the bug.

unitTest 4: buyCard
All tests pass.

cardtest1: village
Bug in incrementing if a card was played during the player's turn.

Card Test 2: salvager
Bug found when checking expected number of coins. Coin count stays at 0. Not incrementing.
Another bug. Other player's coin count is altered instead.

Card Test3: Smithy
Bug found when checking handCount. 

Card Test 4:adventurer
None found with this fixed test.

Random tests
Random test: Smithy
Bug found when checking handCount (same bug found from the fixed card test above).

Random test: Adventurer
Bug found when testing player who plays the adventurer card. deckCount is incremented when
it should remain unchanged. 
Another bug found when testing handCount. handCount of the player that played adventurer
card decreased instead of increased.