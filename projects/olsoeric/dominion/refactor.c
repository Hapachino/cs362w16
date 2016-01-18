/************
 * Eric Olson
 * Assignment #2 
 * Log of Errors Introduced to dominion.c
 ************/

Smithy:
  //In smithy_play() changed the final argument for discardCard from 0 to 1.  This is the
  //trashFlag and causes the smithy card to be trashed rather then put in play pile and
  //later in discard pile.

Adventurer:
  //Updated the adventurer() if statement that checks if drawn card is treasure to look for copper,
  //silver, and silver again (instead of gold).   This might simulate a copy/paste error.
  //The end result is a gold card drawn will be discarded and not added to hand.

Council Room:
  //In council_room_play() changed the +1 Buy action to increment state->numActions instead of
  //state->numBuys.  This causes actions to be increased instead of the intended buy.

Village:
  //In switch statement call to village_play() swapped the passed int arguments for currentPlayer
  //and handPos.  This will cause some undefined behavior, and possibly a seg fault if the card
  //position is larger then the # of players.  At the very least an incorrect card should be
  //discarded (the card in the position of the currentPlayer num).

Cutpurse:
  //Within updateCoins() in the 2nd embeded if statement removed an = from the conditional
  //statement.  The result of this is two fold, first of all the first card in an opponent hands
  //will be changed to copper instead of compared to copper, but then since the assignment will
  //always return true, will then discard that card.  The net result is that cutpurse should now
  //remove the 1st card from an opponents hand copper or not.