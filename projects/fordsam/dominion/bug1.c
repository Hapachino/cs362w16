Samuel Ford
CS362-400, Winter 2016
Assignment 3

Bugs Found from Assignment 3 Unit Tests
=======================================

unittest1: shuffle()
--------------------
No bugs found.


unittest2: kingdomCards()
-------------------------
I'm not sure if this qualifies as a bug but kingdomCards() doesn't validate the provided arguments to make sure that they're actually cards.  Rather, kingdomCards() blindly assigns the arguments to a dynamically allocated int array and returns a pointer to it.  This is fine if kingdomCards() will *never* receive bad input but it may be preferable to have some error checking.


unittest3: buyCard()
--------------------
No bugs found.


unittest4: updateCoins()
------------------------
As mentioned in an earlier assignment, updateCoins() resets state.coins whenever it's executed, so you will lose any pre-existing coins once the function is executed.  The program relies on this behavior because updateCoins() *always* adds all the treasure cards from the player's hand upon execution, so it will need to negate that if it's is run more than once.  This becomes a problem when cards are played that add coins as an effect, since you'll lose those added coins as soon as updateCoins() is executed.


cardtest1: playAdventurer()
---------------------------
playAdventurer() cannot handle the case where there are no treasure cards available to the player (in the discard pile or deck).  In this scenario, the function can get into a bad state and cause the program to crash as a result.

playAdventurer() doesn't move the played card to the playedCards array.  Specifically, the card seems to be removed from the player's hand but it isn't added to the playedCards array.

Past that, the bug I introduced in a previous assignment is present and I wrote a unit test to demonstrate it.  Specifically, all of the drawn non-treasure cards are added to the discard pile except for one.


cardtest2: playCouncilRoom()
----------------------------
No bugs found.


cardtest3: playMine()
---------------------
playMine() contained three naturally-occuring bugs outside of the one that I previously introduced.  It's worth noting that only one of the first two bugs will show up in the unit tests because the first bug masks the second (i.e. it creates a false positive).  [NOTE: Each of the first two bugs has two associated tests.]

1) The conditional statement where we're supposed to make sure that the player can't buy a treasure card that costs greater than 3 coins more than the card-to-upgrade (choice1) fails.  Specifically, the greater-than should be a less-than (i.e. "(getCost(state->hand[player][choice1]) + 3) < getCost(choice2)") so that the function returns -1 when the card-to-buy is too expensive.

2) The function checks to make sure that the card-to-purchase (choice2) is one of the enumerated cards but it doesn't make sure that the card is a treasure card.  This is to say, you could conceivably purchase a non-treasure card when playing Mine (whereas you're only supposed to be able to purchase a treasure card).

3) playMine() discards the card-to-upgrade (choice1) rather than trashing it.  That is, the trashFlag argument of discardCard() is set to 0 (don't trash) when it should be set to 1 or greater to effectively trash the card.  As a result, the card-to-upgrade (choice1) gets added to the playedCards array, which eventually gets added to the discard pile (so the card has the potential to come into play again).

Besides those three natural bugs, there's the bug that I introduced which trashes every instance of the card-to-upgrade.  Knowing about the bug, I created a failing test to bring light to the issue.


cardtest4: playSmithy()
-----------------------
The only bug that I found in playSmithy() was the one that I previously introduced.  Namely, playSmithy will trash the played Smithy card rather than discarding it (due to the trashFlag being set to 1 rather than 0).
