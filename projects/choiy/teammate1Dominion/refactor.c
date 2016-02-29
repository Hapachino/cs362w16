/**Jennifer Frase
  CS 362
  Assignment 2
  This file simply contains documentation for the changes made to dominion.c and dominion.
  For this assignment I chose to work with the village, mine, and remodel cards in addition
  to the adventurer and smithyy cards. In dominion.h, playAdventure, playSmithy, playVillage,
  playFeast, and playCouncil_Room were already present, so I removed playFeast and 
  playCouncil_Room, and added playMine and playRemodel.

  
  In dominion.c I removed the code from the switch statement in playCard for each of my choosen
  cards and implemented them in the functions named previously. For all but the village card I
  also added a bug to the code:
  
  playAdventure: doesn't shuffle the discard pile and add to the deck if the deck runs out of
				 cards
  playSmithy: tries to discard the card before it as well (if the smithy card is the first card
			  in the hand then it will segfault)
  playRemodel: trashes the remodel card
  playMine: instead of giving the player who uses the card the treasure card, it is always
            given to the first player (player with the value 0)
*/