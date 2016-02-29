/* Author: Kim McLeod
 * Assignment 4
 * randomhistory.c
 


I started with my tests from assignment 3 for the smithy and adventurer cards. For both cards, I knew that the game needed a realistic gameState, a realistic number of players, a random number of cards in the deck, and a random number of cards in the players hand.

I used betterTestDrawCard.c as a base for my added code. This helped me utilize the Random() function that's included in the dominion.c code. Once I had random inputs for the gameState and test initialization, I added some fuzzing with a seed of 2000. This can be easily changed to increase or decrease the number of tests run. 

I next added a counter to summarize the results at the end of the testing. The counters increase on failed tests and print once the testing is complete.

To increase my coverage, I added testing for gameState correctness. In particular, I added tests to see if cards were discarded properly or not. 

I had more trouble with this assignment, as I ran into a lot of seg faults as I was trying to establish random gameStates to send into my tests. I ended up randomizing only what could be randomized without going out of the limits of the cards. 

*/