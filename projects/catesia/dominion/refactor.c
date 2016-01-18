smithy: The part that tells the program to discard the card is missing. This means that the smithy card will stay in the players hand.

adventurer: When checking how many cards to discard from temp hand. The z-1>0 in the for loop was changed to z>0 This will cause the cards to not be discarded propery.

village: The number of actions is increased by 0 instead of 2

Mine: The break statement in the discard trashed card loop was removed. Meaning that more cards then should be will be discarded.


