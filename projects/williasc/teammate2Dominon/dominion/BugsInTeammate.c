/*
Assignment 5 - Bugs In Teammates
Gerald Gale


Teammate1 - Matthew Boal:
NOTE: 	This was hard to test as there were a number of changing commits. Sometimes there were seperate card functions 
		in dominion.c sometimes there weren't. The latest update to dominion.c didn't have separate card for things like
		playAdventurere(), I had to modify tests a bit more than normal. 

LOCATION: 
	council_room card

BUG1:
	In this bug it's very sutble and it took some time to find it. In essence ONLY the current player will get to discard 
	a card. This messes up the rest of the players if it is played. 

CODE:
	if ( i == currentPlayer )

LOCATION:
	great_hall card

BUG2:
	This was a simple mistake, but you can get a card now if the cost is less. So it is inflating your hand. The cost 
	is supposed to be +2 but it was +3 in the code. 

CODE:
	if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
	


Teammate2 - Scott Williams:
LOCATION:
	playAdventurer()

BUG3:
	This bug was that player 1's card count	was incorrect a number of times during many tests. This looks like it was due 
	to the change in the conditional of whether or not we needed to draw another card. 

CODE:
	if (state->deckCount[currentPlayer] <=1)


BUG4: 
	Another bug that I noticed was that the current player was also getting too much treasure, there was an 
	increment of 2 instead of one. This was something that I acutally didn't noticed in my initial set of tests. 
	This caused errors not at the card level, but later on for seeds in other areas of the game. 

CODE:
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		drawntreasure+=2;

LOCATION:
	playMinion()

BUG5:
	I am just going to list BUG5 as an aggregate of bugs just because there were so many. I had to go through and 
	rewrite my tests on this a few times, because I kept getting surprises. Therre are at least 4 bugs listed. 
	ISSUES:
		- Number of actions were -- instead of ++ 
			state->numActions--;
		- Coins were being taken - 2 instead of + 2 
			state->coins = state->coins - 2;
		- DiscardCard While loop was commented out 
			//	      discardCard(handPos, currentPlayer, state, 0);
		- Three more cards are added without discarding cards 
			//  discardCard(handPos, i, state, 0);
	

*/