Stephen Heng
CS 362, Winter 2016
Assignment 5
BugsInTeamates.c

Teammate1 Brandon Gipson: 

Bug #1: smithy card

While testing smithycard for teammate 1, I found the handcount of player 2 to be incorrect.
My tests show that an extra card was added to player 2's hand. The deck count was also
incorrect. Teammate 1 smithy function added another card to the deck count. When
running the tests at the initial state of the game before player 2 was dealt, Player 2's 
deck count and hand count incremented to 1 each. For player 1, the discard count is also
at 0, this may be due to the bug in the program instead of the bug introduced by the teammate.
This bug was also in my original dominion code when I ran the tests.

Bug Code:
//Each other player draws a card
	for (i = 0; i < state->numPlayers; i++)
	{
	  if ( i != currentPlayer )
	    {
	      drawCard(i, state);
	    }
	}
	
Fix: remove that code portion on top


Bug#2: adventurer card

While testing the adventurer card, the handcount of current player is incorrect. The tests revealed
an enormous hand count. Also the deck count and coin count are incorrect.

Bug Code:

if (cardDrawn == silver || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		
Fix: The cardDrawn is only addressing silver or gold and not copper. Replace one of the silver
with copper.

if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;

Bug#3: village card

The number of actions is increased to 3 instead of by 2 and the handcount of player 2 is decreased
by 1 as soon as the game is initialized.

Bug Code:
 for (i = 0; i < state->numPlayers; i++)
	{
	  if ( i != currentPlayer )
	    {
	      discardCard(handPos, i, state, 0);
	    }
	}
	
Fix: remove the above code as to not decrease the discard count of the opposing players.


Bug #4: council_room card

When the council card is played, there should be 1 additional card for every other player.
My tests showed that this was not done as the hand count of the opposing player is increased
by 2 instead of by 1. This also affected the deck count as two cards were pulled instead of 1.

Bug Code:

//Each other player draws a card
	for (i = 0; i < state->numPlayers; i++)
	{
	  if ( i != currentPlayer )
	    {
	      drawCard(i, state);
	    }
	}
	
	for (i = 0; i < state->numPlayers; i++)
	{
	  if ( i != currentPlayer )
	    {
	      drawCard(i, state);
	    }
	}
	
Fix: The code is repeated twice and should be only done once so as not to draw two cards.
Erase one of the repeats.

	for (i = 0; i < state->numPlayers; i++)
	{
	  if ( i != currentPlayer )
	    {
	      drawCard(i, state);
	    }
	}



Teammate 2: Joshua Homann

Bugs #1: smithy card

The smithy card does not return the correct discard count of player 1. In fact,
no card is added to the discard count when smithy is played. 

Bug Code:

discardCard(handPos, currentPlayer, state, 1);

Fix: change the trashflag from 1 to 0

Bugs #2: adventurer card

The hand count of player 1 is incorrect. It is increased by 1, which indicated that
the adventurer card is still in the hand and probably has not be discarded.

Bug Code:

temphand[z]=cardDrawn;
            z++;
			
Fix: decrement the hand count of the current player

temphand[z]=cardDrawn;
	  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	  z++;
	  
Bug #3: village card

The hand count is increased by one and the deck count is decreased by 1. This means that
two extra cards were added to the current players hand and not that just 1 card.

Bug Code:

drawCard(currentPlayer, state);
drawCard(currentPlayer, state);

Fix: the drawCard is repeated twice. One drawCard needs to be deleted

drawCard(currentPlayer, state);


