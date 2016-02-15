/* 
For randomtestadventurer I gave a random deck size and then pull a random hand 
size out of that given deck. I then randomly seeded copper, silver, and gold 
into the deck with random cards filling in the rest of the cards. The next step
is to run the adventurer.  After adventurer runs I check the amount of coins in 
the players hand now versus before the card was played and threw an error if a 
maximum of two coins were not added to the hand.  I then checked each of copper,
silver, and gold to see if any had been discarded with the other drawn cards.
This is significant because if a coin card made it into the discard pile then,
it was not properly source by the function.  

For randomtestcard I chose smithy.  For this card I gave random deck and hand sizes
again.  But this time I tested hand size before and after testing that after smithy is
discarded that the net gain for the hand should be +2 cards after the 3 cards are added 
to the hand.  There was an issue with this where it turned out smithy was not initially 
placed in the discard pile but playedcard pile.  A quick variable reassignment fixed that.
Lastly I tested to ensure that the deck has decreased by the appropriate amount.
*/


















