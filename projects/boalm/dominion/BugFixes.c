A note:  I did not realize that we were not supposed to fix bugs in dominion.c
previously.  So the changes I made are in the version of dominion.c in my 
dominion_assn2 directory.  Sorry if that causes any inconvenience.


Fixes:

adventurer:  I added copper back to the list of cards that is checked to see if the drawn
card is treasure.  I also added in the discardCard() function to discard the
adventurer card.  This was missing previously.

smithy:  I changed the trash flag in the discardCard() function to 0.  This
means the card is put into the discard pile.  My bug would have trashed the card
and removed it from the game.

counci_room:  I set this back to allowing other people to draw cards.  My bug
made it only allow the individual player to draw a card.

remodel:  I set the getCost() check in remodel back to 2.  This was previously set to
3, which would have let you get a card costing 3 rather than 2 more than the original card.