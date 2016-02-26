Robyn Lin
Assignment 5
BugFixes.c

Bug 1: Calling the cardEffect function fails. (Remodel card)
Reported by: Shaun Stapleton
Found in: cardtest1 test
Fix: In the original code for the remodel card, choice2 was passed in as a parameter to gainCard;
however, this should be changed to choice1 as this is the card the player wants to gain. Also, to get rid
of the trashed card the discardCard function must be called with the trash flag set to 1 instead of 0;
the line discardCard(i, currentPlayer, state, 0) should be changed to discardCard(i, currentPlayer, state, 1).

Bug 2: No cards appear to be discarded after cardEffect function call. (Council Room card)
Reported by: Shaun Stapleton
Found in: cardtest4 test
Fix: It appears there was a bug in the original discardCard() function code. Instead of adding the
card to be discarded to the discard pile and incrementing discardCount, the card was added to the
playedCards pile and the playedCardsCount was incremented. Fixing this error clears this bug.

Bug 3: Gold Treasure Cards not added to hand. (Adventurer card)
Reported by: Shaun Stapleton
Found in: randomtestadventurer test
Fix: This was the bug I introduced. I changed the function cardAdventurer() so Gold Treasure cards would be added to the hand.
I added if(cardDrawn == gold) back to the line (cardDrawn == copper || cardDrawn == silver, etc). Once I made this change
the bug was fixed.

Bug 4: Hand counts aren't incremented properly. (Smithy card)
Reported by: Shaun Stapleton
Found in: cardtest2 test
Fix: This was the bug I introduced. I changed the number of cards drawn for the cardSmithy function from 4 back to the
correct amount of 3, and this fixed the problem.


Bug 5: Game will never terminate once we try and select a card that's too expensive. (Feast card)
Reported by: Faye Yao
Found in: cardtest2 test
Fix: To fix this infinite loop, I added a "return -1" line to the cases where the player tries to buy
a card with an empty supply, or if the player tries to buy a card that is too expensive. Once I added
this same line to both cases, the bug was fixed.

Bug 6: Estate never returns the correct value we expect. We expected a score of 1500 if our entire
deck/hand consisted of Estate Cards, but scoreFor returns 0.
Reported by: Faye Yao
Found in: scoreFor() unit test
Fix: Looking through this function in the original dominion.c file, I saw that the code was counting
the score for the discard pile twice and never counting the points in the player's deck. Once I
changed the duplicate line for(i = 0; i < state->discardCount[player]; i++) to
for(i = 0; i < state->deckCount[player]; i++), this bug was fixed.

Bug 7: Player doesn't discard the Adventurer card successfully. It's still in position 0 in the player's hand.
That means that our expected handCount is also offset by 1 since we don't discard successfully. (Adventurer card)
Reported by: Faye Yao
Found in: cardtest1 test
Fix: The original code in dominion.c never called the discardCard() function to discard the Adventurer
card after it is played. Once the discardCard() function is called, this bug should be fixed.

Bug 8: numActions, playedCards, and playedCardsCount doesn't change after playing the adventurer card. (Adventurer card)
Reported by: Faye Yao
Found in: cardtest1 test
Fix: I believe these three values do not change because Faye called cardEffect() instead of playCard().
If the playCard() function was used instead, it would decrement the number of actions, update the
coins, and add the card to playedCards and increment the playedCardsCount.

Bug 9: Handcount is one greater than expected. We have one more card in the hand than expected
after playing Smithy. (Smithy card)
Reported by: Faye Yao
Found in: cardtest3 test
Fix: This was the bug I introduced. I changed the number of cards drawn for the cardSmithy function from 4 back to the
correct amount of 3, and this fixed the bug.


