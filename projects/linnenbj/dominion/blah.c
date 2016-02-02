
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main(){

int numcards, numDeck = 0;

int i;
srand(500);
for(i = 0; i < 100; i++)
{


  numcards = (int)(rand() % 17 + 4);
 numDeck = 0;
        while(numDeck == 0)
            numDeck = (int)(rand() % (numcards - 1));

    printf("Test %d:\t%d\t%d\n", i, numcards, numDeck);
}




 return 0;
}

