Janel Buckingham
Assignment 5

==============================

Bugs reported by Paul Zotz:

playSmithy bug (unnamed)

Previously reported: this bug corresponds with card_smithy1 bug in bugs1.c

Fix: found an off-by-one error in the function's for-loop which resulted in an extra card drawn
each time playSmithy was called.  


playAdventurer bug (unnamed)

Previously reported: this bug corresponds with card_adventurer1 bug in bugs1.c

Fix: found an off-by-one error in the function's while-loop which resulted in one less card being
moved from temp hand to discards.  

==============================

Bugs reported by Jeannine Amm:

(Since this team member reported 21 bugs total, I have selected 2 bugs to fix (as per the 
instructor's instructions).  I chose 2 bugs that did not overlap Paul's reported bugs and
that I did not introduce.

Tribute card bug:
Name: Bug16

Fix: I recognized that the tribute card code did not include putting the next player's revealed cards 
into their discard pile, so I added that functionality.


Tribute card bug:
Name: Bug17

Fix: I refactored the Tribute card into its own function (similar to refactorings of other card
effects in a previous assignment) and wrote a unit test for it. (cardtestTribute.c)  Since the 
logic of the original tribute card code did not seem in keeping with the how the game intended 
the card to be played, I rewrote some of the logic of the card, giving the separating the 3 possible
states (next player has 0 in deck, 1 in deck or more than 1 in deck) in a more logical fashion with 
if/else if/else blocks.  While the resulting code decrements nextplayer's deck, it was decrementing 
twice as many cards as expected.  on closer inspection, I found a bug where the next player's deck 
count was decremented (  state->deck[nextPlayer][state->deckCount[nextPlayer]--]  ) where it should be 
accessing a previous element in the array (  state->deck[nextPlayer][state->deckCount[nextPlayer-1]]  ).  
The correct number of cards are now being removed from nextplayer's deck.



==============================

Bugs that I introduced:

The bug I put in playAdventurer was caught by Paul Zotz and fixed above.

The first bug I put in playSmithy was caught by Paul Zotz and fixed above.

The second bug was in line 'discardCard(handPos, currentPlayer, state, 1);' which was causing a card to
be permanently trashed instead of discarded to discard pile due to incorrect flag.  Flag was changed to 
fix this bug.

The bug in playCutpurse had discardCard parameters entered out of order leading to highly unpredictable
behavior.  The parameters have been fixed to be in correct order.

The bug in playRemodel was not breaking from the loop after a single instance of a card was found, so 
instead all instances of that card were being discarded.  To fix, a break was inserted after the call to 
discardCard.

In playMine, a greater than symbol was used where a less than symbol was needed, which resulted in a valid 
input returning an error.  To fix, the symbol was changed.
