updateCoins(): none\
\
gainCard(): none\
\
discardCard(): When you give discardCard a bad input for handPos, there is no error checking. When handpos is larger than the current handCount, you would expect discarCard() to return a -1 and exit the procedure immediately. Instead, there is no indication of error. Return value is 0 as usual. playedCardCount is incremented as if a valid card was played. Played card value is set to whatever integer was at handpos instead of -1.\
\
isGameOver(): none\
\
smithy: The correct card is not discarded. This shows in the test of the individual cards held in hand at the end of the play. This is verified by the playedCards card being not the card that was supposed to be discarded. This is the bug that was introduced in my refactoredSmithy. It discards the card and handpos + 1.\
\
village: The village is not discarded properly. The playedCardCount is not incremented. This is the bug introduced by my refactoredVillage. The card is trashed by setting the trash flag in discard() instead of being discarded normally.\
\
adventurer: There are 2 bugs:\
1.) The appropriate number of cards are not discarded. This is the bug introduced in my refactoredAdventurer. The temp hand counter is manipulated so that stops discarding one card short of the appropriate number of discards.\
2.) The adventurer card is also never discarded. It remains in the hand after being played. This bug was NOT introduced by me in  refactoredAdventurer. This is a native bug.\
\
council_room: none}
