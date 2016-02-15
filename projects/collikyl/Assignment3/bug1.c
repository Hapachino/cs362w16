Bugs found in Card Test 1 (Smithy): None
Description: The bug I originally introduced was designed to first discard Smithy and then draw three cards, as opposed to drawing three cards and then discarding smithy.
My line of thinking was that by discarding smithy first, if the drawCount(3) is greater than deckCount smithy could be shuffled back into the deck and drawn again.
However, because of the existance of the played pile, where cards go before being discarded at the end of the turn, this error would never occur. As such, no bugs were found
in the smithy program.

Bugs found in Card Test 2 (Adventurer): One
Description: The bug I introduced in refactor.c was the fact that Adventurer did not discard itself. Instead, it discarded the card to the left of it.
This could be diffiult to test for, as the playedCardCount still changes by 1, deckCount is correctly decremented, and essentially nothing else is changed. Additionally, in a situation where 
the card to the left of Adventurer is another Adventurer, testing the val of the card discarded would not produce an error. Having one card in the hand of the player and testing specifically Adventurer
would produce the error, as Adventurer would not be counted as played. 

Bugs found in Card Test 3 (council room): None
Description: No bugs were found. This card correctly implements what it was designed to and I introduced no errors to this card in refactor.c

Bugs found in Card Test 4 (village): One
Description: Essentially the same bug as Adventurer, village discards the wrong card. See adventurer bug for description.

Card Test Description:
All my card test functions test the state of the game. Everything from the counts of specific piles for both piles, to the order of the piles, to specific cards, and supply values are tested.
Writing a general test to properly examine these states is a lot of work. Additionally, had I not known about the errors in specific cards, or if the errors were different(say for instance Adventurer only produced
the error when handCount > 2 and would create another adventurer to be discarded while appropiately decremented handCount would be very hard to test for. Playing the game through however, this kind of error would
be noticed instantly. 

Bugs found in Unit Test 1 (draw): None
Description: No bugs were found in this function. Test were conducted when deckCount > drawCount (no need for shuffle) and deckCount < drawCount (shuffle). In both cases, the deckCount was decremented correctly,
handCount was incremented correctly, and the function correctly chose the top card from deck.

Bugs found in Unit Test 2 (gameOver): None
Description: No bugs found. Tests were conducted for following win conditions: provinceCount = 0, and three different supplyCounts (not province) = 0. Both of which produced expected results.

Bugs found in Unit Test 3 (updateCoins): None
Description: No bugs found.Tests were conducted for extremely high value of coins (through the use of bonus coins), coins specifically in a players deck, and negative values of coins. All of which passed testing.

Bugs found in Unit Test 4 (fullDeckCount): None.
Description: No bugs found. Tests were conducted for specific piles having specific cards, thus fullDeckCount should only return the pileCount of specific piles. Other tests conducted were for empty piles and for piles that
have maxCount.
 
