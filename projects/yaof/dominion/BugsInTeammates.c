/*
Faye Yao
CS 362
Assignment 5 - Part 1

Shaun Stapleton
---------------
Village Card:
Bug 1: Did not add right amount of NumActions. We were expecting 2, but we ended up getting 5.
You can reproduce this with my cardtest4.c.

Bug 2: playedCards and playedCardsCount doesn't change after you play the Village Card, when it should.
You can reproduce this with my cardtest4.c.

Adventurer Card:
Bug 1: Player doesn't discard the Adventurer card successfully. It's still in position 0 in the player's hand.
That means that our expected handCount is also offset by 1 since we don't discard successfully.
You can reproduce this with my cardtest1.c.

Bug 2: numActions, playedCards, and playedCardsCount doesn't change after playing the adventurer card.
You can reproduce this with my cardtest1.c.

Feast Card:
Bug 1: Game will never terminate once we try and select a card that's too expensive. 
You can reproduce this with my cardtest2.c.

Smithy Card: 
Bug 1: Handcount is one greater than expected. We have one more card in the hand than expected
after playing Smithy.
You can reproduce this with cardtest3.c.
Note: This is a bug that you introduced.

drawCard:
No bugs found.

isGameOver: 
No bugs found.

scoreFor:
Bug 1: Estate never returns the correct value we expect. We expected a score of 1500 if our entire
deck/hand consisted of Estate Cards, but scoreFor returns 0.

Bug 2: Gardens card effect is not calculated correctly. The score expected is 0, which means that
the way we calculate Gardens' card effect is wrong.

updateCoins:
No bugs found.

Robyn Lin
---------------
Village Card:
No bugs.

Feast Card:
Bug 1: Game will never terminate once we try and select a card that's too expensive. 
You can reproduce this with my cardtest2.c.

Adventurer Card:
Bug 1: Player doesn't discard the Adventurer card successfully. It's still in position 0 in the player's hand.
That means that our expected handCount is also offset by 1 since we don't discard successfully.
You can reproduce this with my cardtest1.c.

Bug 2: numActions, playedCards, and playedCardsCount doesn't change after playing the adventurer card.
You can reproduce this with my cardtest1.c.

Smithy Card: 
Bug 1: Handcount is one greater than expected. We have one more card in the hand than expected
after playing Smithy.
You can reproduce this with cardtest3.c.
Note: This is a bug that you introduced.

updateCoins:
No bugs found.

scoreFor:
Bug 1: Estate never returns the correct value we expect. We expected a score of 1500 if our entire
deck/hand consisted of Estate Cards, but scoreFor returns 0.

Bug 2: Gardens card effect is not calculated correctly. The score expected is 0, which means that
the way we calculate Gardens' card effect is wrong.

drawCard:
No bugs found.

isGameOver: 
No bugs found.
 */