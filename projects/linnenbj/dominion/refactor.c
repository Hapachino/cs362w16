/*
	refactor.c
	CS362 - Winter 2016
	Assignment #2 - refactoring 5 Dominion Cards
	James Linnenburger
	
	Adventurer Card:
	------------------------------------------------------------
	I added a playCardAdventurer() function into dominion.c with
	an appropriate declaration in the dominion.h file.  This 
	implements the adventurer card as a stand alone function.
	
	bugs added: 
	1. Changed while(drawntreasures < 2) to (drawntreasures <=2)
	   so that the card will draw up to 3 treasures.
	
	2. Changed the cardDrawn assignment so that it will always be
	   assigned the first card in the player's hand instead of the last
	   card.
	   
	3. Cards from the temporary hand go directly to the discard pile instead
	   of going to the played card pile.

	Smithy Card:
	------------------------------------------------------------
	I added a playCardSmithy() function into dominion.c with
	an appropriate declaration in the dominion.h file.  This 
	implements the smithy card as a stand alone function.	

	bugs added:
	1. added handPos++ inside the for loop to (incorrectly) account for 
	   the position of the smithy card in the hand when a new card is added.
	
	2. Changed the trashFlag on the discardCard() call to make the card go to the
	   trash instead of back into the player's played card pile.
	   
	
	Village Card:
	------------------------------------------------------------
	I added a playCardVillage() function into dominion.c with
	an appropriate declaration in the dominion.h file.  This 
	implements the village card as a stand alone function.
	
	
	bugs added:
	1. card is not removed from player's hand when played
	2. number of actions is set to 2 instead of adding 2
	
	
	Minion Card:
	------------------------------------------------------------
	I added a playCardMinion() function into dominion.c with
	an appropriate declaration in the dominion.h file.  This 
	implements the minion card as a stand alone function.	
	
	bugs added:
	1. will only check players with player numbers larger than
	   current player for having to discard and draw.
	2. draws cards before discarding, and then tries to discard
	   the cards at the beginning of the hand until there is 4 left
	   but discards in the wrong positions.
	
	Great Hall Card:
	------------------------------------------------------------
	I added a playCardGreatHall() function into dominion.c with
	an appropriate declaration in the dominion.h file.  This 
	implements the minion card as a stand alone function.		
	
	bugs added:
	1. implementation does not actually increase action count.
	
	
	Changes made:
	
		dominion.h:
			- Added appropriate function header declarations for
			the 5 cards being implemented along with commenting 
			descriptions for all of them.
			
			1. int playCardAdventurer(struct gameState *state, int currentPlayer);
			2. int playCardSmithy(struct gameState *state, int currentPlayer, int handPos);
			3. int playCardVillage(struct gameState *state, int currentPlayer);
			4. int playCardMinion(struct gameState *state, int currentPlayer, int handPos, int choice1);
		    5. 
		
		dominion.c:
			- Changed the cardEffect() function so that the switch cases
			  for the refactored card implementations call the appropriate
			  functions instead of being implemented within the switch.
			  
			- Added the implementation of each of the functions declared in dominion.h
*/
