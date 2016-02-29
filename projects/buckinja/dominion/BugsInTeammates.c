Janel Buckingham
Assignment 5

Teammate 1 is Paul Zotz
Teammate 2 is Jeannine Amm

(using the Noverse Bug Reporting Template)
==============================

Title:    AdventureCardBug1 (for Paul Zotz)

Class:
	serious gameplay error 

Date:           2/22/2016
Reported By:    Janel Buckingham
Email:      	buckinja@oregonstate.edu


Product:      Dominion          
Platform:     Unix              Version: Flip


Is it reproducible: Yes

Description
===========
When Adventurer card is played, an extra card is added to the player's hand.



Steps to Produce/Reproduce
--------------------------
Initialize game with 2 players.
Loop through the player's deck to count all coin cards at the start of player's turn.
Store player's handcount.
Play the adventurer card.
Compare stored handcount with new handcount.
Loop through deck again to count coin cards to see how many coin cards were removed.

Expected Results
----------------
Handcount should be increased by 2.
Deck's coin count should be decremented by 2.


Actual Results
--------------
Handcount is increased by 3.
Deck's coin count is decremented by 3.


==============================



Title:    AdventureCardBug2 (for Jeannine Amm)

Class:
	minor gameplay error 

Date:           2/22/2016
Reported By:    Janel Buckingham
Email:      	buckinja@oregonstate.edu


Product:      Dominion          
Platform:     Unix              Version: Flip


Is it reproducible: Yes


Description
===========
If a player has cards in their deck when Adventurer is played, but there are not 
sufficient coin cards in the deck, the player will discard the remainder of the deck 
but not reshuffle to continue looking for coin cards.  This results in a deck of size
0 and an incorrect hand count, although the handcount is not in keeping with a bug that
only skips shuffling.  In that case, it should not change if there are no coins in the 
deck, but it can still increment by one.


Steps to Produce/Reproduce
--------------------------
Found in random testing.
Initialize a 2 player game.
Manipulate the first player's deck so that it has a few cards but none of them are coin cards.
Discard should have at least 2 coins in it. This would allow the game to shuffle correctly.
Store the player's handcount. 
Store the player's deckcount.

Play the adventurer card.

Deck count will be set to 0 indicating an empty deck but no reshuffling.
Compare handcount with previous handcount.


Expected Results
----------------
Expected handcount to increase by two if shuffling is working in the middle of adventurer
card play, or expected 0 handcount if shuffling is not working, but result is not in keeping with 
either.  


Actual Results
--------------
Handcount incremented by one.





