Refactored programs:

smithy - playSmithy()
BUG - the loop for drawing cards will run 4 times instead of three
(loop condition changed from i < 3 to i <= 3)

adventurer - playAdventurer()
BUG - the temporary hand will not be created properly, and as a result, not all of the non-treasure cards drawn and added to the temp hand will be properly discarded.
This bug was introduced by removing the increment for z in the else condition of the first while loop.

village - playVillage()
BUG - when the village card is discarded, it is sent to the trash rather than to the players discard pile.
This occurs because the trash flag was changed from 0 to 1 in the call to discardHand()

feast - playFeast()
BUG - Playing the card will only result in having four coins with which to purchase a new card.
The parameter passed to updateCoins() was changed from 4 to 5.

councilRoom - playCouncilRoom()
BUG - The loop for all other players to draw a card will not operate correctly.
The condition for drawCard() was changed from if j != currentPlayer to if i != currentPlayer.
The value of i comes from the previous loop and should be set at four when this runs,
so every player will draw except for player 4, regardless of whether they are the currentPlayer. 