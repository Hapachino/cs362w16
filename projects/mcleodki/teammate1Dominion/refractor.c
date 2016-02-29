/********************************************************************
Assignment 3 - Part 3
Author: Lynn Herrick
Date: 1/16/16
Description:  Pick 5 cards implemented in dominion.c.  Choose 3 plus
the madatory smithy and adventurer.  Refractor the code so these
cards are implemented in their own functions, rather than as part of
the switch statements in cardEffect.  Your implementation of at 
least 4 of these 5 cards should be incorrect in some way (smithy and
adventuere are mandatory).  Document your changes (and bugs) here.
********************************************************************/

/* Refractor from 1/16/16
*******************************************************************
smithy: currentplayer draws three more cards to their hand, smithy 
card is discarded (bug - card is not disgarded properly with trash 
flag).
********************************************************************
int smithy(currentPlayer, state, handPos){
  int i;
  //for +3 cards
  for(i = 0; i <3; i++){
    drawCard(currentPlayer, state);
  }
  //discard card from hand
  discardCard(handPos,currentPlayer,state,1);  //trashfag should be 0

  return 0
}

********************************************************************
adventuer: Current player draws cards until two treassure cards are
drawn.  All other drawn cards are discarded.  (bug - looking for 
copper, silver, and gold together with single drawn card.  Should be 
"or" statements as a single card cannot represent all three types of
treasure.)
********************************************************************
int adventurer(drawntreasure, state, currentPlayer, cardDrawn, temphand, z, handpos){
  //draw until two treasure card draws
  while(drawntreasure<2){
    //if deck is empty
    if (state->deckCount[currentPlayer] <1){//we need to shuffle discard and add to deck
      shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    //if card is treassure
    if (cardDrawn == copper && cardDrawn == silver && cardDrawn == gold){  //bug here, should be or statements
      drawntreasure++;
    }
    //if card is not treassure
    else{
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  //discard all drawn cards
  while(z-1>=0){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  return 0;        
}


********************************************************************
village: Current player gets an extra card drawn to their hand.  
Current player is awarded two more actions.  (bug - card is sent to 
discardCard() as opponent's card)
********************************************************************
int village(currentPlayer, state, handPos, nextPlayer){
  //+1 Card
  drawCard(currentPlayer, state);
  //+2 Actions
  state->numActions = state->numActions + 2;
  //discard played card from hand
  discardCard(handPos, nextPlayer, state, 0); //second param should be currentPlayer

  return 0;
}


*******************************************************************
cutpurse: Current player is awarded 2 coins.  All other players must
discard 2 copper coins, if possible.  If discard is not possible, 
other player(s) must reveal their hand to the current player.  
(bug - for loop executes and first if statement doesn't
break at end and instead allows to go into second if statement)
*******************************************************************
int cutpurse(currentPlayer, state, handPos){
  int i;
  //card gives player 2 coins
  updateCoins(currentPlayer, state, 2);

  //consider all players
  for(i=0; i<state->numPlayers; i++){
    //each other player
    if(i != currentPlayer){
      //look at cards in hand
      for(j=0; j< state->handCount[i]; j++){
        //if has copper, discard it
        if(state->hand[i][j] == copper){
          discardCard(j, i, state, 0);
          //break should go here
        }
        //if no copper
        if( j == state->handCount[i]){
          //reveal hand
          for( k=0; k<state->handCount[i]; j++){
            if(DEBUG){
              printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
            }
            break;
          }
        }
      }
    }
  }
  //discard played card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}



*******************************************************************
council_room:  Current player gets to draw 4 more cards.  Current
player gets 1 more buy.  All other players get to draw one more 
card.  (bug - during time when other players draw one card, all 
draws go to current player)
*******************************************************************
int council_room(currentPlayer, state, handPos){
  //current player gets +4 drawn cards
  for (i = 0; i < 4; i++){
    drawCard(currentPlayer, state);
  }
  //current player gets +1 Buy
  state->numBuys++;      
  //Each other player draws a card
  for (i = 0; i < state->numPlayers; i++){
    if ( i == currentPlayer ){	//bug is here - other player do not get to draw cards
      drawCard(i, state);
    }
  }      
  //put played card in played card pile
  discardCard(handPos, currentPlayer, state, 0);
      
  return 0;
}