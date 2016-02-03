Functions not covered at all:
newGame
kingdomCards
playCard
numHandCards
handCard
endTurn
scoreFor
getWinners


Coverage for tested functions:

discardCard:
-The branch for if there is only one card in hand is never executed because that is always caught by the "is card last in hand" branch. This code section could be removed.
-The reset of the code is executed.

buyCard:
-100% coverage
-The test for if the player has enough buys is caught 80% of the time. This is probably not representative of how a game would be played and it might have been better to weight the testing the other way.

gainCard:
-100% coverage
-2/3 of the time, the supply pile choice is invalid. This is probably not representative of how a game would be played and it might have been better to weight the testing the other way.

isGameOver:
-100% coverage. The branch coverage was very easy to weight for this unit test.


Coverage for card effects:

Smithy:
-100% coverage

Adventurer:
-The if statement for if the deck is empty is never skipped. This is something that a second unit test should cover.
-Silver and Gold cards are never drawn because the deck is not intially set up to have them. This is another thing that a second unit test could cover.

Village:
-100% coverage

embargoEffect:
-100% coverage
