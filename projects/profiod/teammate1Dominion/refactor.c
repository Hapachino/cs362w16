/*Chris Loomis
CS362 W16
Assignment 2
refactor.c

Adventurer:
In the else clause after a card is drawn, I removed the line where the player's hand is decremented, thus removing the drawn card from their hand when it is not a treasure.  After the while loop I added a line that sets the player's hand to the size of itself minus z.  z is a variable counting the number of non treasure cards drawn.  This will result in the wrong cards disappearing from the player's hand and deck, as they are not properly discarded.

Smithy:
I changed the for loop to decrement.  Previously it was incrementally done with the counter starting at 0 and looping until it was no longer less than 3.  Now the counter starts at 3 and continues while the counter is greater than equal to 0.  This results in Smithy drawing a 4th card.

Village:
I changed the number of actions added to 1, rather than 2.

Feast:
I removed the else if clause that checks the supply cost of the card selected.  The player can now select any card, no matter the cost.

Council Room:
I removed the if statement that prevents the current player from drawing in the loop that normally allows all other players to draw 1 card.  This means the active player will get a 5th card.

/*