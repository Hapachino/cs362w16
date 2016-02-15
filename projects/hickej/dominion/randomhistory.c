File 'dominion.c'
Lines executed:23.30% of 588
dominion.c:creating 'dominion.c.gcov'


assignment 3
File 'dominion.c'
Lines executed:31.63% of 588
dominion.c:creating 'dominion.c.gcov'


combined
File 'dominion.c'
Lines executed:33.16% of 588
dominion.c:creating 'dominion.c.gcov'


There was a a 1.5% improvement with the addiation of the new random tests
This is most likely becuase the main bulk of the code is same. As cards are dealing
discard, draw, and effecting some basic variable like hand count. THis test is still
missing the bulk of code related to scoring as well as not touching a good amount of the cards.

Both of the random test have higher than 90% coverage. Which means the the test are running correctly.
Though this does not mean that the test give the right results.

I did find another bug in the program. In the council card it is miss drawing the amount of cards
for each player. Some are up and some are down. I return to the code and added a number at the start to show which player number
 is the current player. With this addiontional information it appears that the currentplayer is overdrawing
 and the other players are under drawing. Most likely the bug is within the code for the other players draw call.
