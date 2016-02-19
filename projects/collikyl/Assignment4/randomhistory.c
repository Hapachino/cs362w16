Bug Report: 
Adventurer: Found additional bugs in adventurer code. Originally, the bug I thought I introduced was to ensure that adventurer did not discard itself. However, it turns out it that it won't discard all cards drawn as well.
Adventurer also doesn't go into the play pile (not because of the change I introduced). Interestingly, if there are two treasures on the top of the deck when adventurer is played, then the discard error does not occur, although
the played error still occurs. Tbe final error detected was in the event of there being no treasures in the deck/discard piles, the card discards a random portion of the players hand and the deck/discard piles are altered. This
was a fairly significant error as it could often discard large portions of the player's hand with cards randomly ending up in the discard pile and some cards moving from the discard pile to the deck.

Village: No additional errors were found apart from the error I introduced.

Program Description:
Adventurer: Creates a random game state without using initialize where almost all variables are randomized (Kingdom cards, cards in deck, card counts, supply counts, etc...). Some variables aren't randomized include whoseTurn, phase, 
and other control variables. There weren't randomized as they needed to be constant in order to gurantee that the program could play the card (can't play a card in buy phase or for someone elses turn). Creating a random test was
fairly challening as I tried to create accurate error statements whenever possible. As an example, if adventurer is played and cards in the deck pile are changed that weren't affected by card count, the error report will print
out a message indicating the cards position, expected card, and the actual card that showed up. Having the possibility of a shuffle occuring with no way of knowing before the test was conducted greatly complicated correct
error message handling. If there was a shuffle detected, the order of the discard/deck piles would not be examined. Instead, the discard pile will be examined for any treasures and report if it found one as it should be guranteed to
have none. If no treasures were found, the program checks both deck and discard for treasures (it has to check both because somehow cards end up in the deck even though there shouldn't be) and reports if any error is found. Additionally,
there may be error statements for deckCount, handCount, and handDiscard although because it seems cards are moved randomly, there may not be an error detected.
Village: Village follows the same general format as Adventurer (randomize almost everything, test everything) with the exception that no special test cases will be done as there is no shuffle required. This was significantly easier to 
write as I could reuse old cold from the Adventurer function and I didn't have examine situations where the postState could be significantly different than the preState.

Coverage Description:
randomtestadventurer.c'
Lines executed:82.96% of 270
Branches executed:98.61% of 144
Taken at least once:77.08% of 144
Calls executed:68.13% of 91
randomtestadventurer.c:creating 'randomtestadventurer.c.gcov'

File 'randomtestcard.c'
Lines executed:92.12% of 203
Branches executed:95.12% of 82
Taken at least once:85.37% of 82
Calls executed:90.00% of 80
randomtestcard.c:creating 'randomtestcard.c.gcov'

File 'dominion.c'
Lines executed:17.18% of 582
Branches executed:15.59% of 417
Taken at least once:8.63% of 417
Calls executed:11.70% of 94
dominion.c:creating 'dominion.c.gcov'

Coverage of dominion is lower than it was in my previous test. This was to be expected as I did not use initialize game which makes up a good portion of the dominion.c code. Coverage of my testing function is fairly high, with some low
categories such as the Calls Executed for randomtestadventurer.c. Some of the code in the randomtestadventurer.c is conditional and only occurs if specific errors occur. These types of errors would never occur in the current version
of adventurer and as such these calls would never be executed. The same concept holds true for randomtestcard.c as well. 
