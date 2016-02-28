Adventure card fixes
#1 fixed drawn treasure Errors
Error :: while(drawntreasure<2){
            if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
              shuffle(currentPlayer, state);
              }
              drawCard(currentPlayer, state);
                cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
            //error
            drawntreasure++;
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
              drawntreasure++;
            else{
              temphand[z]=cardDrawn;
              state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
              z++;
              //error
              drawntreasure++;

            }
          }
Fixed :: while(drawntreasure<2){
            if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
              shuffle(currentPlayer, state);
              }
              drawCard(currentPlayer, state);
              cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
              drawntreasure++;
            else{
              temphand[z]=cardDrawn;
              state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
              z++;
            }
          }

scoreFor function
Error :: for (i = 0; i < state->discardCount[player]; i++
Fixed :: for (i = 0; i < state->deckCount[player]; i++)

Village Card
Error :: no error within card, but off by 1 in my test caused

Steward card
