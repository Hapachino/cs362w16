------
Smithy
------
Draws a card 3 times and then discards the smithy. Return 0.

----------
Adventurer
----------
This method repeats until 2 treasure cards have been reached.
First it checks to see if the deck is empty, and if it is, shuffle 
the discard pile and set as the deck (shuffle method). Draw a card
and then check to see if it is a treasure card. If it is, then 
increase the count of the drawn treasure cards by one. If it is 
not a treasure card, don't count that card as in hand and make 
sure it is marked as a temporary card. 
Finally, discard all cards drawn that are marked as temp cards and
return 0. 


-------------
discardCard()
-------------
This method first checks if the card will be going to the 
played cards pile or the trash pile after played. If it is
not going to be trashed, it adds that card to the played cards.
It then marks the card in the hand as played (-1) and begins to
remove the card from the player's hand by checking 2 special 
cases. The first is if the last card in the hand is played and
the second is if there is only 1 card in hand. For both of these
cases however, it will only reduce the number of cards in the hand.
For any other cases of cards (2 to last_card-1), the second to last
card will be set as the last card and the number of card in hand is 
reduced by one.
Then return 0. 

-------------
updateCoins()
-------------
This method begins by setting the coin count of the current state
of the game to 0 for each turn to make sure that this method can 
correctly count the total number of coins and does not count a coin
multiple times. 
It then moves to the for loop, which loops through each card in the 
players hand checking each for if it is specifically a copper, silver,
or gold and adding 1, 2, or 3 coins perspectively to the coin state
of the game. It finishes by adding the bonus coins (such as from the
woodcutter card) to the final coint of coins from treasure cards
in the players hand and then returning 0.