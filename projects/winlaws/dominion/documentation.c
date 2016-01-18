CS362 Assignment 2 - documentation.c - Spencer Winlaw

----------------------------------------------------------------------------
Smithy Card
----------------------------------------------------------------------------
When played, the smithy card enables a player to add 3 cards to their hand. 
This is implemented with a for loop that iterates 3 times executing the drawCard() 
function on each iteration. After the loop, the smithy card is removed from the 
player's hand with the discardCard().

----------------------------------------------------------------------------
Adventurer Card
----------------------------------------------------------------------------
When played, the adventurer card enables a player to add 2 treasure cards to 
their hand by continuously drawing cards from their deck, shuffling when necessary,
until 2 treasure cards have been drawn. This is implemented with a while loop
that iterates until 2 treasure cards are drawn. In each iteration, the loop first 
checks to see if there are cards in the deck to be drawn. If there are not, the 
shuffle() function is called so that the deck is replenished and can be drawn from.
Next, a card is drawn by calling the drawCard() function and the loop checks to
see whether it is a treasure card. If the card is a treasure card a counter is
incremented, otherwise the card is removed from the players hand and placed into 
temporary hand. Once 2 treasure cards have been drawn in this manner, as indicated
by the counter, the while loop exits and the temporary hand containing all cards drawn 
that were not treasure cards is discarded in another while loop.

----------------------------------------------------------------------------
discardCard()
----------------------------------------------------------------------------
Cards are discarded from a player's hand in 1 of 2 ways depending on what cards
the player has played during their turn. The 2 discard methods are as follows:
	1) The card is removed from the player's hand and trashed(removed from the 
	   game entirely) 
	2) The card is removed from the player's hand and placed into the player's 
	   played pile to later be reshuffled into the player's drawing deck once 
	   it has been depleted. 
This functionality is implemented in the discardCard() function by first performing 
a check to see whether the card to be discarded should be trashed or placed into 
the player's played pile, then placing the card in the appropriate place (nowhere
if being trashed), and finally removing the card from the player's hand. 

----------------------------------------------------------------------------
updateCoins()
----------------------------------------------------------------------------
The updateCoins() function calculates the number of coins a player currently has
by starting at 0 coins, then iterating over each card in a player's hand in a for 
loop, checking to see if the card is a treasure card, incrementing the number of 
coins appropriately (copper: +1, silver: +2, gold: +3), and finally adding on any 
bonus coins recieved from playing certain cards.