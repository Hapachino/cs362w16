/*
Gerald Gale 
CS 362 - Assignment 4

I had a lot of problems with the Adveturer Card, I had to go into dominion.c to make a few changes to it. The rest is below:

Both cards were tested individually, which meant that the rest of the game had to be created randomly. 

Adventurer:

- 2 Cards needed to be available for this to worm for each play
- Everything was randomly initialized. The main objective was to make sure that the decks and games states were OK at the end of it
- The hardest part of testing this card, was getting enough instances where the empty decks needed to be shuffled

RESULTS:

File 'dominion.c'
Lines executed:9.90% of 576
Branches executed:6.24% of 417
Taken at least once:5.04% of 417
Calls executed:4.26% of 94
dominion.c:creating 'dominion.c.gcov'

function callAdventurerCard called 1000 returned 100% blocks executed 100%
     1000:  648:int callAdventurerCard(struct gameState *state, int currentPlayer){
        -:  649:    int cardDrawn;
     1000:  650:    int drawntreasure = 0;
     1000:  651:    int z = 0;
        -:  652:    int temphand[MAX_HAND];
        -:  653:
    28452:  654:    while(drawntreasure<=2){
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
    26452:  655:        if (state->deckCount[currentPlayer] < 1){//if the deck is empty we need to shuffle discard and add to deck
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
      411:  656:          shuffle(currentPlayer, state);
call    0 returned 100%
        -:  657:        }
    26452:  658:        drawCard(currentPlayer, state);
call    0 returned 100%
    26452:  659:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    29452:  660:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 96% (fallthrough)
branch  3 taken 4%
branch  4 taken 4% (fallthrough)
branch  5 taken 96%
     3000:  661:          drawntreasure++;
        -:  662:        else{
    23452:  663:          temphand[z]=cardDrawn;
    23452:  664:          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
    23452:  665:          z++;
        -:  666:        }
        -:  667:    }
        -:  668:
    25452:  669:    while(z-1>=0){
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
    23452:  670:        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    23452:  671:        z=z-1;
        -:  672:    }
        -:  673:
     1000:  674:    return 0;
        -:  675:  }

Village:

- Village is already a pretty simple card, I don't think there would be a big differrence in having many tests or few tests. 
- Either the function just works or it doesn't. There aren't many branches or prumutations for things to change compared to adventurer.


RESULTS:
File 'dominion.c'
Lines executed:4.34% of 576
Branches executed:1.92% of 417
Taken at least once:1.20% of 417
Calls executed:1.06% of 94
dominion.c:creating 'dominion.c.gcov'

function callVillageCard called 1000 returned 100% blocks executed 100%
     1000:  691:int callVillageCard(int currentPlayer, struct gameState *state, int handPos){
        -:  692:     
        -:  693:      //+2 Actions
     1000:  694:      state->numActions = state->numActions + 2;
        -:  695:      
        -:  696:      //discard played card from hand
     1000:  697:      discardCard(handPos, currentPlayer, state, 0);
call    0 returned 100%
     1000:  698:      return 0;
        -:  699:}


*/