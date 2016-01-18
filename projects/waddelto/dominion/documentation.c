/********************************************************
Todd Waddell
CS362w16
Assignment //2

Submit a file called documentation.c (.c file because github thinks you are
using github for file storage if you use many .txt files) that contains
documentation of smithy, adventurer cards. Documentation should contain
your understanding of smithy and adventurer cards (code). It should also
contain documentation of your understanding of discardCard() and
updateCoins() method.  Keep your documentation short, though there is no
upper limit. Documentation.c file should contain at least 100 words.  

//Smithy Card
The smithy card costs five coins. The card allows the current player to
draw three additional cards.  from the top of the their deck and put the
cards into their hand.  The smithy card does not grant additional actions,
buys or coins and does not impact other players.
***********************************************************/
//Smithy Code
    case smithy:
      //+3 Cards: //loops three times and calls drawCard routine each time. 
      for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
      //discard card from hand //discards smithy card, now that it's been
      //played. 
      discardCard(handPos, currentPlayer, state, 0);

    return 0;  //code assumes that everything worked correctly and returns 0
		

/************************************************************
//Adenturer Card
The adventurer card costs 6 coins.  When played, the card enables the
current player to draw two treasure cards from their deck.  Cards are
drawen from the top of the deck.  Non-treasure cards are discarded.
Treasure cards are added to the current hand and are available for the play
treasures phase.  The adventurer card does not grant additional actions,
buys or coins (aside from the additional playable treasure cards).  Nor
does it impact other players.
***************************************************************/
//Adventurer Code
    case adventurer:
      while(drawntreasure<2){  //increments and tracks a counter 'drawntreasure' to
                               //track the number of treasure cards pulled. I've reformatted this to
                               //correct the code indentation

	    if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	        shuffle(currentPlayer, state);
	    }
	    
        drawCard(currentPlayer, state);    //draw a cardcheck to see if it
                                           //is copper, silver or gold, if
                                           //so, increment 
                                           //drawCard also puts the card in
                                           // hand, see dominion.c:562. 

	    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	    if (cardDrawn = copper || cardDrawn == silver || cardDrawn == gold)
	        drawntreasure++;
	    else{
	        temphand[z]=cardDrawn;  //if it's not treasure, don't co[MaLunt it
                                    //in the hand count.  Oddly, the card is actually discarded with
                                    //a while loop, below. 
	        state->handCount[currentPlayer]--; //this should just remov[MaLe the top card (the most recently drawn one).
	        z++;  //increment z for next time non-treasure card is drawn
	    }
      }

      while(z-1>=0){ //I have no idea why this isn't included in the else at
                     // line 63
	    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	    z=z-1;
      }
      
      return 0;

/****************************************************
 discardCard()
Discard Card takes the handPos of the card, the current player, the
gameState stuct and a trashFlag indicator.

If the card is not trashed, then it gets added to played cards array.

The code sets the cards value to -1 and decrements handPos to remove it
from the player's hand. 

If the handPos of the card is at the top of the player's hand or he's only
got one card in his/her hand, then decrement the count of the hand.
Otherwise, set the next card in his hand as the top card in his hand. Then
set the previous array value to -1 and decrement the array counter. 
********************************************************/

/***************************************************************
//updateCoins()
Update Coins takes the current player, gameState struct and bonus.  It
resets the number of coins in play to 0.  The the routine loops through the
cards in the player's hand and adds calculates the number of coins the
current player can play.  After reviewing the player's hand, the function
adds any bonus coins that the player may have earned during his action
phase.
****************************************************************/

