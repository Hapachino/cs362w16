/*
Faye Yao
CS 362
Randomized Testing

Function 'compare'
Lines executed:100.00% of 6
Branches executed:100.00% of 4
Taken at least once:100.00% of 4
No calls

Function 'supplyCount'
Lines executed:100.00% of 2
No branches
No calls

Function 'fullDeckCount'
Lines executed:100.00% of 9
Branches executed:100.00% of 12
Taken at least once:75.00% of 12
No calls

Function 'whoseTurn'
Lines executed:100.00% of 2
No branches
No calls

Function 'handCard'
Lines executed:0.00% of 3
No branches
Calls executed:0.00% of 1

Function 'numHandCards'
Lines executed:0.00% of 2
No branches
Calls executed:0.00% of 1

Function 'isGameOver'
Lines executed:100.00% of 10
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

Function 'scoreFor'
Lines executed:100.00% of 24
Branches executed:100.00% of 42
Taken at least once:92.86% of 42
Calls executed:100.00% of 3

Function 'getWinners'
Lines executed:0.00% of 24
Branches executed:0.00% of 22
Taken at least once:0.00% of 22
Calls executed:0.00% of 2

Function 'getCost'
Lines executed:16.67% of 30
Branches executed:100.00% of 28
Taken at least once:10.71% of 28
No calls

Function 'discardCard'
Lines executed:92.31% of 13
Branches executed:100.00% of 6
Taken at least once:66.67% of 6
No calls

Function 'gainCard'
Lines executed:61.54% of 13
Branches executed:100.00% of 6
Taken at least once:50.00% of 6
Calls executed:100.00% of 1

Function 'buyCard'
Lines executed:0.00% of 18
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
Calls executed:0.00% of 4

Function 'updateCoins'
Lines executed:100.00% of 11
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

Function 'playFeast'
Lines executed:82.61% of 23
Branches executed:80.00% of 10
Taken at least once:70.00% of 10
Calls executed:100.00% of 6

Function 'shuffle'
Lines executed:100.00% of 16
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
Calls executed:100.00% of 2

Function 'drawCard'
Lines executed:100.00% of 25
Branches executed:100.00% of 6
Taken at least once:100.00% of 6
Calls executed:100.00% of 1

Function 'playCouncil_Room'
Lines executed:0.00% of 9
Branches executed:0.00% of 4
Taken at least once:0.00% of 4
Calls executed:0.00% of 4

Function 'playVillage'
Lines executed:100.00% of 6
No branches
Calls executed:100.00% of 3

Function 'playSmithy'
Lines executed:100.00% of 6
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 3

Function 'playAdventurer'
Lines executed:100.00% of 16
Branches executed:100.00% of 10
Taken at least once:100.00% of 10
Calls executed:100.00% of 2

Function 'endTurn'
Lines executed:0.00% of 20
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
Calls executed:0.00% of 3

Function 'cardEffect'
Lines executed:6.50% of 200
Branches executed:13.61% of 169
Taken at least once:3.55% of 169
Calls executed:9.09% of 55

Function 'playCard'
Lines executed:0.00% of 14
Branches executed:0.00% of 10
Taken at least once:0.00% of 10
Calls executed:0.00% of 3

Function 'initializeGame'
Lines executed:85.48% of 62
Branches executed:100.00% of 46
Taken at least once:82.61% of 46
Calls executed:100.00% of 5

Function 'kingdomCards'
Lines executed:0.00% of 13
No branches
No calls

Function 'newGame'
Lines executed:0.00% of 3
No branches
No calls

File 'dominion.c'
Lines executed:41.90% of 580
Branches executed:52.54% of 413
Taken at least once:37.53% of 413
Calls executed:31.31% of 99
dominion.c:creating 'dominion.c.gcov'

Overall, I wouldn't say my coverage improved, but that's because my original tests
decently covered all of the cases for testing adventurer and the smithy card. However,
I think that these randomized tests make testing the functionality of these cards even
more robust, because I'm not merely testing one scenario for how many cards may be 
played in a given turn. My randomized testing randomizes how many cards (and which cards)
are in the player's hand, discard, and deck, as well as what cards are in there.
I noticed that my "Taken at least once" statistic went up by around .20%, which can be
attributed to taking a few more paths that weren't recently taken before because
of the randomized game state. Otherwise my coverage hasn't changed much according to
gcov.

Even though my coverage hasn't technically changed, I think that randomizing the game state
more fully accounts for all the scenarios that might arise in normal play, which
means that my randomized testing confirms what my original unit tests tested for in
correctness. Being able to confirm the functionality of the cards at any deck/discard/hand
count covers more of the cases where the functionality might break.
*/