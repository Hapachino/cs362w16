Samuel Ford
CS362-400, Winter 2016
Assignment 5

Bugs Fixed in My Code
=====================

Bugs Found by Teammates
-----------------------
1. Joshua Curtis reported that playing the Adventurer card resulted in a hand count that was one greater than expected.  I knew from my previous experience with the Adventurer card that it was missing a call to discardCard(), so the played card (Adventurer) wasn't being removed from the hand.  This was a plausible explanation, so I tested the hypothesis and it turned out to be correct.  I added an appropriate call to discardCard() in playAdventurer() and this resolved the bug.  [I updated my cardtest1.c test after this modification because the original test relied on the knowledge that the Adventurer card did not discard the played card.  After updating cardtest1.c, the related test passes.]

2. Joseph Vidal reported that the "Smithy card is not discarded after use".  Based on the test code that he provided, what he specifically meant is that the Smithy card isn't present in the playedCards array after use (what the related call to discardCard() handles).  This reported issue dealt with the bug that I introduced into the Smithy card in Assignment 2 (switching the trashFlag in the call to discardCard() to 1 rather than 0), so that was a simple fix.  The specifics of the fix are detailed in the "Bugs Introduced in Assignment 2" section below.

3. Joseph Vidal reported another bug where "If there are fewer than 3 cards in the deck the Smithy card will draw the remaining amount but it will not call for a shuffle to get any remaining cards."  I created some tests to investigate the issue and found that Smithy's call to drawCard() *did* actually shuffle in cards from the discard pile (contrary to the bug report).  This "bug" only appeared when there were fewer than three cards available between both the player's hand *and* their discard pile; to my knowledge, this occurs with any card that draws cards (since they all use drawCard()).  After referring to the official Dominon rules, what the program is doing under these circumstances is proper behavior.  The rules state "...If [the player] still does not have enough cards left after forming a new Deck, he just draws as many as he can".  The way that drawCard() and shuffle() accomplish this isn't quite how I would like (shuffle() can end up being called more than once) but the resulting behavior is correct, so I would simply close this bug and mark it as "Behaves correctly".


Bugs Introduced in Assignment 2
-------------------------------
1. The code for the Adventurer card had been modified to contain an off-by-one bug.  The loop condition used when discarding the non-treasure cards that were drawn had been changed to "while (z - 1 > 0)", resulting in one of the drawn non-treasure cards not being discarded.  To fix this, I changed the condition to "while (z - 1 >= 0)" and the related failing test ("Should discard all other drawn cards") now passes.

2. The code for the Feast card had been modified to introduce a bug in an error-checking condition.  Specifically, the "else if (state->coins <= getCost(choice1))" condition would erroneously evaluate to true if the number of coins is equal to the cost of the card, leading to a "That card is too expensive!" error.  To fix this, I removed the "=" in the comparison, so the condition now reads "else if (state->coins < getCost(choice1))".

3. The code for the Mine card had been modified to introduce a bug in the "discard trashed card" for-loop (near the end of the function).  Specifically, the break statement had been removed from within the if-block, so the playMine() function would remove all instances of the choice1 card.  To fix this, I added a break statement after the discardCard() call in the aforementioned if-block, so only one instance of the choice1 card is discarded.  After fixing a bad test condition in cardtest3.c, the failing test ("Should only affect one instance of choice1 card") now passes.

4. The code for the Smithy card had been modified such that the trashFlag in the discardCard() call was set to 1 rather than 0.  This resulted in the Smithy card being trashed rather than discarded.  To fix this, I changed the trashFlag in the discardCard() call to 0, so the Smithy card is properly discarded (not trashed).  As such, the failing test ("Should move played card to playedCards") now passes.


Bugs Found by Tests in Earlier Assignments
------------------------------------------
Note: This isn't part of the assignment requirements but I decided to fix a few of the other bugs that my tests found in previous assignments.  To be clear, some other known bugs still exist.

1. The code for the Mine card attempts to ensure that the card to upgrade to (choice2) isn't greater than 3 coins more expensive than the card to upgrade (choice1), but it contains a bug which undermines this error-checking.  The related if condition reads "(getCost(state->hand[player][choice1]) + 3) > getCost(choice2)" but the comparison operator should be a less-than (<) rather than a greater than (>) to achieve the desired result.  With this fix in place, the related test now passes.

2. The code for the Mine card ensures that choice2 (the card to upgrade
to) is a valid card (i.e. within the range of values used by
dominion.h's CARD enum) but it doesn't do anything to ensure that
choice2 is a treasure card. As such, you could potentially upgrade
a treasure card to a non-treasure card, which goes against Dominion's
rules.  choice1 and choice2 should both be treasure cards, so I modified the code that makes sure choice2 is a valid card to bring it in line with the code that makes sure that choice1 is a treasure card.  With this fix in place, the related tests now pass.

3. The code for the Mine card ends up discarding the card to upgrade (choice1), rather than properly trashing it.  This occurs because the trashFlag argument of the related discardCard() call (in the for-loop near the end of the function) is less than 1 (0).  To properly trash the card, you need to supply a trashFlag value of 1 or greater, so I modified this discardCard() call to use a trashFlag value of 1.  With this fix in place, the related test now passes.
