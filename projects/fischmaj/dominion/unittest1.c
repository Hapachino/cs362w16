/***************************************************************************
 ** unittest1.c ( test of shuffle() function) 
 ** Jeremy Fischman
 ** 
 ** This program is a unit test of the shuffle function.  It tests that the
 ** shuffle function complies with the following business rules: 
 **
 ** 1. The function accepts 1 player and a game state, and the discard deck
 ** of the chosen player is permuted. 
 **
 ** 2. Should result in the same number of total cards in the player's deck
 **    following shuffling.
 ** 
 ** 3. Should result in the same number of each type of card in the player's
 **    deck following shuffling as existed in the deck before shuffling
 ** 
 ** 4. The permutation after shuffling should look relatively random (i.e.
 **    the order of cards should be varied somewhat randomly).
 ** 
 ** 5. The other features of the state of the game should all be unchanged. 
 **
 **************************************************************************/

#include "dominion_helpers.h"
#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MEMBERS 19     /* Number of member variables in a gameState */
#define CARDTYPES treasure_map+1  /* Number of different card types in game */
#define NUMTESTS 10   /* Number of times to run the tests */


/* function prototypes */
int compareGameState(struct gameState *old, struct gameState *new, 
		     int *diffArray, int length);

int countCards(struct gameState *state, int *deck, int decklength); 
int checkShuffle(int player, struct gameState *pre); 
double Random(); 



int main(){

  int n, i, p; 
  int diffArray[MEMBERS];  /* array to record changed members of gamestate*/
 
  struct gameState pre;

  int k[10]= {adventurer, council_room, feast, gardens, mine, remodel, 
	      smithy, village, baron, great_hall}; 

  printf("\n Running tests of shuffle():\n");

  for (n = 0; n < NUMTESTS; n ++){
    /* generate a random gamestate*/
    for (i=0; i <sizeof(struct gameState); i++){
      ((char*)&pre)[i]= floor(Random() * 256);
    }
    p=floor(Random()*2);
    pre.deckCount[p]= floor(Random() * MAX_DECK);
    pre.discardCount[p] = floor(Random() * MAX_DECK);
    pre.handCount[p] = floor(Random() * MAX_HAND); 
    checkShuffle(p, &pre);

    printf("\n\n\nTest #%d:\n", n); 
    unsigned char* charPtr= (unsigned char*) &pre;
    for ( i =0; i < sizeof(struct gameState); i++){
      printf("%02x ", charPtr[i]);
    } 
  
 }

 
  printf("\nTesting shuffle() complete.  \n");

  return 0;
}



/* This function compares 2 struct gameStates, and returns 0 if they are  */
/* identical, and 1 otherwise.  Also, it fills an Array with a 1 for each */
/* member of gameState 'new' that differs from gameState 'old' */
int compareGameState(struct gameState *old, struct gameState *new, 
		     int *diffArray, int length){


  return 0; 
}




/* This function counts the cards in a card deck and records number of each */
/* type of card in an array */
int countCards(struct gameState *state, int *deck, int decklength){

  return 0;
} 

int checkShuffle(int player, struct gameState *pre){
  struct gameState *post = malloc(sizeof(struct gameState));

  memcpy(post, pre, sizeof(struct gameState)); 

  shuffle(player, post); 

  free(post); 
  return 0;
} 

double Random(){
  return (rand()/(double)RAND_MAX);
}
