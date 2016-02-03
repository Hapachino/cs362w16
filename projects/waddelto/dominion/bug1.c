Todd Waddell
CS362W16_400
Assignment 3

Note: when writing this code, I specified run loops of 10,000-100,000 to ensure coverage.
However, for submission, I've lowered the run loops to 1,000 to save the TA
from having to scroll through endless error codes.

Bugs:

I developed tests for the following functions: shuffle, BuyCard,
  UpdateCoins, and fullDeckCount. 
I developed tests for the following cardEffects: Smithy, Adventurer,
  Minion, and Sea Hag.

I didn't discover any bugs for the shuffle, buyCard, updateCoins and
fullDeckCount. 

Smithy Effects: Smithy allows the player to draw three additional cards,
       then discards the played Smithy card.

Smithy bug: Smithy doesn't discard correctly. The function doesn't
increment the discardCount and add the card to the discarded pile.  There
are two reasons for this.  The first is that the bug I introduced in
Assignment 2 is to throw the trash flag, so the smithy card would be
trashed instead of added to the discard pile.  The second reason is that
there is an underlying bug in teh discardCard funnction.  Instead of adding
the card to the discard array and incrementing the discardCount, the
discard function puts the card in the cards played array and increments the
played cards index.  So, essentially the discard function always trashes
cards. 

Adventurer Effects:  The adventurer card gives allows the player to draw
from their deck and add two coins to their hand as they are revlealed.
Non-treasure cards drawn are added to the discard pile. The bug I
introduced in Assignment two was to change the drawntreasure loop from
drawntreasure < 2 to drawntreasure <= 3.  In effect, I changed to card play
to allow three treasures to be drawn. 

It is worth noting that the Adventurer function does not call the discard
function, so it is not subject to the bug in that function. Instead, the
adventurer function manually discards the played card and those
non-treasure cards drawn.


Minion Effects:  Minion gives +1 action.  Then choose 1: A) +2 coins or B)
discard your hand and draw four cards and other players with at least 5
cards also discard and draw four cards

Minion Bugs:
Minion calls discardCard() for discarding the cardPlayed and for discarding
the hand both for the current player and for other players.  DiscardCard
has a fatal problem.  Instead of putting the cards into the dicard pile and
incrementing the discard Count, discardCard puts the cards into communal
cards played routine and increments the communal cards played count.  In
effect, this error trashes the cards, removes them from play in the
players' deck

Minion also improperly credits the +2 coins.  Instead of adding them to the
bonus variable, Minion adds them to the gamestate coin variable.  However,
      when update coins runs, it first sets the game.coins variable to 0
      before analyzing the treasure in the player's hand.  Update coins
      expects any treasure gained from action cards to be credited to
      bonus. 

Sea Hag: Effects: Each other player discards teh top card of his deck, then
gains a curse card putting it on top of his deck.


Sea Hag Bugs:
Sea Hag decrements the deckCount three times.  Instead of putting the curse
card on the top of the players' decks, it puts it a couple of cards down. 

In addition, Sea Hag does not check the curse supply when giving curse
cards.  As a result, an infinite number of curse cards could be added to
play through the course of the game. 
