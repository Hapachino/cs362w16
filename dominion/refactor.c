CS 362 Assignment 2
refactor.c
Emmalee Jones

runAdventurer() - For this card I refactored the function to remove the
"cardDrawn == copper" from the if statement testing for treasure cards.  
This will stop the selection of copper treasure cards in the game.
-------------------------------------------------------------------------------------------
	if (cardDrawn == silver || cardDrawn == gold) //refactor to remove cardDrawn == copper
-------------------------------------------------------------------------------------------


runCouncilRm() - For this card I refactored the function so that the buy 
statement was included in the for loop for the drawCard function. This 
will increase the number of buys to match the number of times the for 
loop is executed instead of being called only once.
-------------------------------------------------------------------------------------------
    //+4 Cards
      for (i = 0; i < 4; i++)
	{
	  drawCard(currentPlayer, state); 
				
      //+1 Buy
      state->numBuys++; //refactor so buy is included in for loop and occurs multiple times
	}		
--------------------------------------------------------------------------------------------


runSmithy() - For this card I refactored the function so that on iteration 3
the next player gets an extra card.
--------------------------------------------------------------------------------------------
    for (i = 0; i < 3; i++) //refactor to provide the next player an extra card on iteration 3
	{
	  if (i == 2)
	  {
		   drawCard(currentPlayer, state);
		   drawCard(nextPlayer, state);
	  }	
	  else	  
	  drawCard(currentPlayer, state);
	}
--------------------------------------------------------------------------------------------


runSteward() - For this card I refactored the function so cards are 
discarded to the discard pile instead of going to the trash. This is done by changing the
value for the trash flag from 1 to 0.
--------------------------------------------------------------------------------------------
	discardCard(choice2, currentPlayer, state, 0);//refactor so that cards are discarded to deck instead of trash
    discardCard(choice3, currentPlayer, state, 0);
--------------------------------------------------------------------------------------------