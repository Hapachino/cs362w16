There is a bug in the scoreFor() function which causes it to miscount the score of cards in the deck.

The loop that iterates over deck cards and adds their score to the total iterates from 0 to the size of
the discard pile rather than the size of the deck. 

In my tests, this causes the score of the deck to not be counted if the deck is larger than the discard 
pile, but if the discard pile is larger than the deck, then the function will iterate outside the bounds 
of the deck array, causing undefined behavior.