Testing fullDeckCount()
   -No bugs found.


Testing scoreFor()
   -Bug found. If there were any cards in the deck card pile,
   sometimes the score returned would be incorrect.

   Example of failed test:
   
      Testing player 0 with 3 province card(s).
      Amount in location: Deckcards: 2  HandCards: 0 DiscardCards: 1. Point Value: 6
      Score = 12, expected = 18 TEST FAILED
   
   
   I did realize my oracle code didn't catch situations where discard
   piles equaled deck card piles. Example below. This shouldn't have
   passed.
   
   Examples of a test that shouldn't have been correct:

      Testing player 0 with 4 province card(s).
      Amount in location: Deckcards: 2  HandCards: 0 DiscardCards: 2. Point Value: 6
      Score = 24, expected = 24  