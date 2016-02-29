File 'dominion.c'
Lines executed:28.60% of 584
This at first seemed much lower than I expected, but I think it's actually because I wrote a lot of my own helper functions in testhelper.c. For example, I wrote my own initializeState function (instead of using the initializeGame function) to tests the functions in dominion.c. When I use dominion.c's initializeGame function, coverage improves dramatically.

File 'unittest1.c'
Lines executed:71.43% of 42
The shuffle() coverage was better than I expected, but I think it's because this function is actually fairly straightfoward. Use of qsort reduces the edge cases.

File 'unittest2.c'
Lines executed:60.00% of 45
The discardCard() coverage was a little worse than I expected, but I think it's because this was a case where I defined strict boundaries in the state comparing function, so usually the branch coverage was fairly restricted.

File 'unittest3.c'
Lines executed:73.81% of 42
The gainCard() unit test coverage could have been improved by giving it a variety of flag combinations using the compareStates function in testhelper.c, but after running into a very strange bug where the card count is off by 10, I spent (too much) time combing over what might be going wrong in the original gainCard() code. To improve on this in the future, I would probably draw a better dependency diagram from the dominion.c file to better understand what this function relies upon.

File 'unittest4.c'
Lines executed:71.43% of 21
For a fairly straightforward function, the isGameOver() unit test performed a little lower than I expected. I think this is because the main function is split into two branches which cannot be explored simultaneously, since the game states must be manually re-initialized.

File 'cardtest1.c'
Lines executed:90.32% of 93
The playAdventurer() unit test was alright. When on its own, the branch coverage is decent, again because of the checkDiff() function. However, the bug I introduced where the drawn card assignment doesn't happen until the if statement makes it difficult to know how well this unit test actually performs.

File 'cardtest2.c'
Lines executed:89.58% of 48
The playSmithy() unit test also made use of a helper function, and I think by manually setting a sort-of oracle state, we manage to get decent boundary coverage. Again, the bug introduced - as outlined in refactor.c - makes it difficult to know how well we're really testing this function, since the player's deck, deck count, discard, discard count, hand, and hand count are all off from this bug (where the player effectively draws three cards, but only gets to keep 1).

File 'cardtest3.c'
Lines executed:80.00% of 15
While the playTribute() coverage looks decent, this is an unfinished unit test. I have rewritten this unit test a lot and am still stymied. I introduced a bug where the player should always get 2 actions no matter what (removing the else case from the original code), but I cannot seem to isolate this case to know if this is the bug that this unit test is catching. The first immediate thing to improve on would be to make an exhaustive expectedState case to be able to compare different player's decks and hands quite easily; I believe there are 2^4 cases to check, so this is a case where a more rigorous framework would help a lot re: coverage.

File 'cardtest4.c'
Lines executed:91.18% of 34
The playMine() unit test is shallow, so the boundary cases definitely need improvement: for instance, what happens when a player passes in a card that is not within a value of 3 of their desired card? This unit test at least catches the bug I introduced (also outlined in refactor.c) where the card the player chose to trash is added back to his/her hand. I also noticed a bug in the original implementation where choice1 should be trashed, but is instead discarded.
