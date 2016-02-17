/* Name: Thomas "Adam" Pippert
   Due Date: 14-February-2016
   File: randomhistory.c
   Purpose: Write-up of development and validation of random testers
*/

/* randomtestadventurer.c:

        I started out with a few random values for each loop: number of players, deck count, discard count, hand count, choices, hand position, current player, and seed.  This immediately tested the correctness of my specification: the code gave a seg fault when the number of players wasn't in the 2-4 range, when the deck/discard count went over the max deck amount, and when the hand count went over the max hand amount.  I discovered this using printf statements before the seg fault.  I gave the correct % constraints to all of the variables and made sure the number of players would never be 0 or 1. Coverage was 22.12%.

	I used what we learned in class about checking for an empty deck and gave the seed a 1 in 3 chance of making the current player's deck empty.  Coverage improved to 25.33%, and all lines in the adventurer portion of the cardEffect code were covered.

	In an effort to check the correctness of my code, I asserted that the return value from cardEffect wasn't an error (-1).  After running cardEffect with adventurer, I checked that it did its job: the current player should have at least 2 treasure cards added to their hand.  I checked for this by making sure the player had at least 2 coppers in their hand before the cardEffect call.  A treasure counter for the hand checked for at least 2 treasures and that the hand count was a positive number.  I also put in logic checks for the case where a player got a new deck or hand, in which case all of their cards would be 0 or their hand count would be 0.  This improved coverage to 27.41%. 

	By increasing my MAX_TESTS value, I found a bug: the hand count occasionally returns a negative number when the saved hand count is 0. There was also a bug in that sometimes 0 or 1 treasure cards were in a player's hand. My check for the deck count does not reveal any bugs.
*/

/* randomtestcard.c:

        The random test for the Great Hall card was much quicker to implement, because I had already finished the first random tester and used it as a framework for this test. I started out with random values in the loop as I did before: number of players, deck count, discard count, hand count, choices, hand position, current player, and seed. I made sure to set % with the correct restraints to ensure my code wouldn't break. I also included the 1 in 3 empty deck feature. My coverage started out at 25.90%.

	I decided to try increasing the chance of an empty deck to half of the occurences. This made coverage actually improve to 26.28%. I chose to keep this improvement in the code and then stop improvements, as that was an acceptable level of coverage for the small great_hall portion of code (The Great Hall card code in its function was, in fact, completely covered).

	In an effort to check the correctness of my code, I asserted that the return value from cardEffect was 0. After running cardEffect with great_hall, I checked that it did its job: the current player should have the same hand count as before, a discard count increment, and a number of actions increment. To check for these, I saved the values of hand count, discard count, and number of actions for the current player before the function call. After the call, I checked that the hand count was equal to the saved hand count, the discard count was incremented or was 0 (to account for an empty deck/hand), and the number of actions was incremented.

	By increasing my MAX_TESTS value, I found a bug: the discard count doesn't always increment as it should when a great hall is played. In fact, most of the time it fails with the discard count being the same as it was before. I ended up implementing a counter and using a printf statement outside of the loop to tell how many times it failed; this was easier to understand than when the current and saved discard counts printed to the screen for every failure, as it fails roughly 80% of the time. In addition, another bug was found when the hand count decremented instead of incremented as it should. Sometimes, the hand count is actually negative after the cardEffect call. My check for the number of actions does not reveal any bugs.
 */
