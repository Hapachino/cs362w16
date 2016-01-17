/*
Robert Jackson
CS362
Documentation Asignment 2

Smithy:
Has a cost of 4 coins.When invoked this "card" allows the current player to draw an additional 3 cards from their deck, to be placed in hand.
The code runs a for loop  from 0 to < 3 (3 times) calling the drawCard() function using the current player and current state.


Adventurer:
Has a cost of 6 coin, It's purpose is to allow you to draw from the deck until you gain two treasure cards.

It tracks the treasure that you have obtained by incrementing drawntreasure. 
In a while loop so long as drawntreasure is < 2 
If the number of cards in the deck should be < 1 then it switches players
then it draws a card using drawCard()
The drawn card is set equal to the card on the top of the person's deck. 
if the card is equal to any of the 3 treasure types, drawntreasure is incremented.
Otherwise the card is added to a temporary array of cards , and then the handCount is decremented to remove the card that was drawn
the array is then incremented for the temporary array

A second while where z >=0 loop is used to clean up the temp hand by setting the discard of the current player equal to the temparrays last card, and then
decrementing z each time 


*/

 
