/*
Marco Zamora
CS362

Results after testing adverturer card:
File 'dominion.c'
Lines executed:35.51% of 566
Branches executed:44.36% of 417
Taken at least once:35.01% of 417
Calls executed:20.00% of 100
function playAdventurer called 1000 returned 100% blocks executed 100%

Previously, a unit test of 4 cards and 4 functions reported the folllowing:
Lines executed:28.27% of 566
Branches executed:22.06% of 417
Taken at least once:20.62% of 417
Calls executed:21.00% of 100
function playAdventurer called 500 returned 100% blocks executed 100%

This means I was able to execute more lines and branches, and take more branches while
testing one card then all 8 previous tests. I was able to increase my coverage by constantly
adding incorporating other functions in the creation of the test. For instance, instead of making
a gameState completely random, I randomize elements that go into initializing the game. I also stepped back
a few functions when playing the card. Previously, I tested playAdventurer() when playing the card. Now, 
I used playCard() which in turn calls cardEffect(), which finally calls playAdventurer(). This means other functions
in between are being called, like discardCard(), updateCoins(), etc. This gives more coverage and tests more of 
the game rather than isolating the card.

Results after testing adverturer card:
Lines executed:29.33% of 566
Branches executed:34.77% of 417
Taken at least once:24.94% of 417
Calls executed:17.00% of 100
function playSmithy called 1000 returned 100% blocks executed 100%

Again, I was able to cover much more with this test than I previously did with the unit tests. I played the smithy 
card with playCard() rather than using playSmithy and I manually made the changes that would happen when a 
smithy was played. These tests also went further in making sure that there were no changes made to other players'
cards, that supply counts did not change, that coins updated only when treasures were drawn, among many other
things. These tests went much further in tracking any unintended changes than the previous unit tests.



*/