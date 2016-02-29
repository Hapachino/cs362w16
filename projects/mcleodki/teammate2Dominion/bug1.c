/*********************
Regina Imhoff
CS 362 
imhoffr@oregonstate.edu
Assignment 3 bug1.c
 
 
 No bugs found in isGameOver()
 No bugs found in gainCard()
 No bugs found in updateCoins()
 No bugs found in fullDeckCount()
 
 playAdventurer card:
 I found a bug in how playadventurer (and the original adventurer function) calls shuffle.
 It calls shuffle if the deck is empty, but shuffle (when the deck is empty) returns
 -1 without changing the deck.  
 Otherwise, the off-by-one was not noticed as it changes the state after the card is played.
 
 playSmithy card:
 I found my error where only 2 cards will be drawn instead of three.  Otherwise, no bugs found.
 
 village card:
 The village is not properly discarded properly due to the shuffle function, same as in playAdventurer.
 
 great_hall card:
 Card is not discardered properly due to the shuffle function issue, same as in playAdventurer.

 
 
*********************/