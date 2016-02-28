/*Chris Loomis
CS362 W16
Assignment 4
randomhistory.c

The first task I set out to do was create a semi-random iteration of the game.  Semi-random as this is to test specific cards, so not
all values of the gameState can/should be random.  What is random is the number of cards in each player's deck and hand.

The first thing I noticed was that I wanted to use MAX_HAND and MAX_DECK which are both set to 500.  The name of these global variables
is misleading.  Doing some quick math shows that the most cards in a game are 254 for 2 player games, or 266 for 3 and 4 player games.
These numbers don't count curse cards, but there are only 20 so 274 and 286 respectively.  This is much less than 500, and thus my initial
random game generator did not work.  When you consider a game starts with 10 cards per player and the odds of one player amassing
all the cards is very slim, I question if these globals should be set to 500 or if they should even exist.  I understand part of the reason
is padding, since they are used for arrays of player's hands and decks, so making sure they do not go out of bounds is a good thing.

Once I had my random game generator working properly I began implementing test Smithy and Adventurer from last week.  I kept my tests mostly
the same.  The only real changes I made were to have the game run the tests over and over on new random games every iteration.  I also made
adjustments as I made sure to have a random number of legal players (2, 3, or 4).

I started with command line arguments to allow the user to assign values to the number of tests and the seed for the random number generator.
I have commented these out, as you will be simply running these via the Makefile.  Both the number of iterations and seed is set to 1000 in
the code currently.  I believe in a real world situation having a random tester where these variables can be set would result in better debugging
results.  For example, once an average speed was determined, the random tester could be set to run a number of times that should equate to the time
alotted, whether that be 30min during lunch, or ~48hours over the weekend.  Also allowing the seed to be set will allow different sets of values
to be tested, and if an issue occurs you can recreate it with the same seed.  This is also useful for testing after a potential fix is in place.

I had to return my playAdventurer() to it's original state.  In assignment 2 (I think) I removed the line that would decrement the player's hand
after drawCard() was called.  This means that the cards being drawed are staying in his hand.  This was causing a seg fault when I would run the
test more than 4 consecutive times.  I am not exactly sure why this would cause a seg fault, but in the interest of this assignment I limited my
investigation.  Returning that line of code resolved the issue so my random tester may run more than 4 times.

The tests on Smithy are as expected, they are failing by the amount they were changed when I introduced a bug weeks ago.  Adventurer tests are
returning some very odd values.  This was not observed last assignment.  I am thinking this is the other bug I introduced to Adventurer.  My
original intention for these bugs was to have the incorrect cards disappear from a players hand after Adventurer was played.  Since I had to
return the piece of code that removes the freshly drawn card from the player's  hand, the other half of the bug, which removes cards from the
hand equal to the number drawn during Adventurer, is causing the player's hand count to be much smaller, possibly negative.

Coverage wise, I am doing good within the playSmithy() and playAdventurer() functions, covering all possibilities within those functions.

*/