/********************************************************************************************************************************************************
*** Filename: bug1.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Execute your unit tests and describe any bugs you find in a file named bug1.c.
***
*******************************************************************************************************************************************************

unittest1.c: updateCoins()
     No bugs encountered.

unittest2.c: fullDeckCount()
     When starting to write the unit test for this function, I first attempted to understand the function by reviewing its use in the dominion code.
     It seems to be only used for calculating the score from the gardens card which needs to sum up every card that a player contains in his/her deck, hand, and discard pile.
     However, this function accepts a int card parameter which then sums up the amount of the specified card only. 
     In terms of the latter functionality, no bugs were encountered.

unittest3.c: isGameOver()
     In terms of boundry cases, I tested the isGameOver() function for when at least 3 supply piles were empty. I discovered that the function only checks supply piles for cards 0-24.
     At first I thought this was intentional for the cards of sea hag and treasure map and adjusted the unit test. However, now having finished other unit tests, I realized this 
     is more likly a bug with isGameOver(). 

unittest4.c: gainCard()
     No bugs encountered.

cardtest1.c: playSmithy() 
     The card test found the deliberate bug where a for loop was starting at 1 and not 0 as intended and thus only adding two cards instead of 3. 


cardtest2.c: playAdventurer()
     The adventuerer card that is played is not discarded from the player's hand.
     Found the deliberate bug where the treasureCounter was intially set to 1 and not 0 as intended.

cardtest3.c: playVillage() 
     Found the deliberate bug that instead of adding 2 actions it was adding 3.


cardtest4.c: playSalvager()
     The handCard() call was not correctly returning the card that was specified in choice1 and after deeper investigation I beleive it might have been caused by
     me manually setting the hand and deck counts/cards. By refactoring the unit test to fill decks/hand automatically , it might be more evident if this was actually a bug with handCard().
     Testing the salvager code with a "clean" version for returning the handpos yielded no other bugs. 

*/