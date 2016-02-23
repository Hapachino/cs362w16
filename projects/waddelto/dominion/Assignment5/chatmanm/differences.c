*** dominion.c	2016-01-17 12:38:37.000000000 -0800
--- dominion.original	2016-02-21 09:56:43.000136000 -0800
*************** int getCost(int cardNumber)
*** 643,664 ****
    return -1;
  }
  
! // Refactored adventurer to be its own function
! int playAdventurer(struct gameState *state, int currentPlayer) {
    int drawntreasure = 0;
    int cardDrawn;
-   int temphand[MAX_HAND];// moved above the if statement
    int z = 0;// this is the counter for the temp hand
  
    while(drawntreasure < 2) {
      if (state->deckCount[currentPlayer] < 1) { //if the deck is empty we need to shuffle discard and add to deck
        shuffle(currentPlayer, state);
      }
      drawCard(currentPlayer, state);
      cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //top card of hand is most recently drawn card.
!     if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
!       drawntreasure+=2;
!     } else {
        temphand[z]=cardDrawn;
        state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
        z++;
--- 643,681 ----
    return -1;
  }
  
! int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
! {
!   int i;
!   int j;
!   int k;
!   int x;
!   int index;
!   int currentPlayer = whoseTurn(state);
!   int nextPlayer = currentPlayer + 1;
! 
!   int tributeRevealedCards[2] = {-1, -1};
!   int temphand[MAX_HAND];// moved above the if statement
    int drawntreasure=0;
    int cardDrawn;
    int z = 0;// this is the counter for the temp hand
+   if (nextPlayer > (state->numPlayers - 1)){
+     nextPlayer = 0;
+   }
    
+ 	
+   //uses switch to select card and perform actions
+   switch( card ) 
+     {
+     case adventurer:
        while(drawntreasure<2){
  	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
  	  shuffle(currentPlayer, state);
  	}
  	drawCard(currentPlayer, state);
  	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
! 	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
! 	  drawntreasure++;
! 	else{
  	  temphand[z]=cardDrawn;
  	  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
  	  z++;
*************** int playAdventurer(struct gameState *sta
*** 670,787 ****
      z = z - 1;
    }
    return 0;
- }
- 
- // Refactored smithy to be its own function
- int playSmithy(struct gameState *state, int currentPlayer, int handPos) {
-   //+3 Cards
-   int i;
- 
-   for (i = 1; i < 3; i++) {
-     drawCard(currentPlayer, state);
-   }
- 
-   //discard card from hand
-   discardCard(handPos, currentPlayer, state, 0);
-   return 0;
- }
- 
- // Refactored playSalvager to be its own function
- int playSalvager(struct gameState *state, int currentPlayer, int handPos, int choice1) {
-   //+1 buy
-   state->numBuys++;
- 
-   if (choice1) {
-     //gain coins equal to trashed card
-     state->coins = state->coins + getCost(handCard(choice1, state));
-     //trash card
-     discardCard(choice1, currentPlayer, state, 0);
-   }
-   //discard card
-   discardCard(handPos, currentPlayer, state, 0);
-   return 0;
- }
- 
- // Refactored playGreatHall to be its own function
- int playGreatHall(struct gameState *state, int currentPlayer, int handPos) {
-   //+1 Card
-   drawCard(currentPlayer, state);
- 
-   //+1 Actions
-   state->numActions += 2;
- 
-   //discard card from hand
-   discardCard(handPos, currentPlayer, state, 0);
-   return 0;
- }
- 
- // Refactored playMinion to be its own function
- int playMinion(struct gameState *state, int currentPlayer, int handPos, int choice1, int choice2) {
-   int i;
-   int j;
-   //+1 action
-   state->numActions++;
- 
-   //discard card from hand
-   discardCard(handPos, currentPlayer, state, 0);
- 
-   if (choice1) {		//+2 coins
-     state->coins = state->coins + 2;
-   } else if (choice2) {		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
-       //discard hand
-       while(numHandCards(state) > 0) {
-         discardCard(handPos, currentPlayer, state, 0);
-     }
-   }
- 
-   //draw 4
-   for (i = 0; i < 4; i++) {
-     drawCard(currentPlayer, state);
-   }
- 
- //other players discard hand and redraw if hand size > 4
-   for (i = 0; i < state->numPlayers; i++) {
-     if (i == currentPlayer) {
-       if ( state->handCount[i] > 4) {
-         //discard hand
-         while( state->handCount[i] > 0) {
-           discardCard(handPos, i, state, 0);
-         }
- 
-         //draw 4
-         for (j = 0; j < 4; j++) {
-           drawCard(i, state);
-         }
-       }
-     }
-   }
-   return 0;
- }
- 
- int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
- {
-   int i;
-   int j;
-   int k;
-   int x;
-   int index;
-   int currentPlayer = whoseTurn(state);
-   int nextPlayer = currentPlayer + 1;
-   int temphand[MAX_HAND];// moved above the if statement
-   int tributeRevealedCards[2] = {-1, -1};
- 
-   if (nextPlayer > (state->numPlayers - 1)) {
-     nextPlayer = 0;
-   }
- 
-   //uses switch to select card and perform actions
-   switch(card) {
-     case adventurer:
-       return playAdventurer(state, currentPlayer);
  
      case council_room:
        //+4 Cards
!       for (i = 0; i < 4; i++) {
  	       drawCard(currentPlayer, state);
  	    }
  
--- 686,696 ----
  	z=z-1;
        }
        return 0;
  			
      case council_room:
        //+4 Cards
!       for (i = 0; i < 4; i++)
! 	{
  	  drawCard(currentPlayer, state);
  	}
  			
*************** int cardEffect(int card, int choice1, in
*** 789,796 ****
        state->numBuys++;
  
        //Each other player draws a card
!       for (i = 0; i < state->numPlayers; i++) {
! 	       if (i != currentPlayer) {
  	          drawCard(i, state);
  	       }
         }
--- 698,707 ----
        state->numBuys++;
  			
        //Each other player draws a card
!       for (i = 0; i < state->numPlayers; i++)
! 	{
! 	  if ( i != currentPlayer )
! 	    {
  	      drawCard(i, state);
  	    }
  	}
*************** int cardEffect(int card, int choice1, in
*** 814,822 ****
        x = 1;//Condition to loop on
        while(x == 1) {//Buy one card
  	       if (supplyCount(choice1, state) <= 0) {
! 	          if (DEBUG) {
                printf("None of that card left, sorry!\n");
!             }
  	          if (DEBUG) {
  	             printf("Cards Left: %d\n", supplyCount(choice1, state));
  	          }
--- 725,733 ----
        x = 1;//Condition to loop on
        while( x == 1) {//Buy one card
  	if (supplyCount(choice1, state) <= 0){
! 	  if (DEBUG)
  	    printf("None of that card left, sorry!\n");
! 
  	  if (DEBUG){
  	    printf("Cards Left: %d\n", supplyCount(choice1, state));
  	  }
*************** int cardEffect(int card, int choice1, in
*** 914,920 ****
        return 0;
  
      case smithy:
!       return playSmithy(state, currentPlayer, handPos);
  
      case village:
        //+1 Card
--- 829,843 ----
        return 0;
  		
      case smithy:
!       //+3 Cards
!       for (i = 0; i < 3; i++)
! 	{
! 	  drawCard(currentPlayer, state);
! 	}
! 			
!       //discard card from hand
!       discardCard(handPos, currentPlayer, state, 0);
!       return 0;
  		
      case village:
        //+1 Card
*************** int cardEffect(int card, int choice1, in
*** 979,988 ****
        return 0;
  
      case great_hall:
!       return (state, currentPlayer, handPos);
  
      case minion:
!       return playMinion(state, currentPlayer, handPos, choice1, choice2);
  
      case steward:
        if (choice1 == 1)
--- 902,967 ----
        return 0;
  		
      case great_hall:
!       //+1 Card
!       drawCard(currentPlayer, state);
! 			
!       //+1 Actions
!       state->numActions++;
! 			
!       //discard card from hand
!       discardCard(handPos, currentPlayer, state, 0);
!       return 0;
  		
      case minion:
!       //+1 action
!       state->numActions++;
! 			
!       //discard card from hand
!       discardCard(handPos, currentPlayer, state, 0);
! 			
!       if (choice1)		//+2 coins
! 	{
! 	  state->coins = state->coins + 2;
! 	}
! 			
!       else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
! 	{
! 	  //discard hand
! 	  while(numHandCards(state) > 0)
! 	    {
! 	      discardCard(handPos, currentPlayer, state, 0);
! 	    }
! 				
! 	  //draw 4
! 	  for (i = 0; i < 4; i++)
! 	    {
! 	      drawCard(currentPlayer, state);
! 	    }
! 				
! 	  //other players discard hand and redraw if hand size > 4
! 	  for (i = 0; i < state->numPlayers; i++)
! 	    {
! 	      if (i != currentPlayer)
! 		{
! 		  if ( state->handCount[i] > 4 )
! 		    {
! 		      //discard hand
! 		      while( state->handCount[i] > 0 )
! 			{
! 			  discardCard(handPos, i, state, 0);
! 			}
! 							
! 		      //draw 4
! 		      for (j = 0; j < 4; j++)
! 			{
! 			  drawCard(i, state);
! 			}
! 		    }
! 		}
! 	    }
! 				
! 	}
!       return 0;
  		
      case steward:
        if (choice1 == 1)
*************** int cardEffect(int card, int choice1, in
*** 1185,1191 ****
        return 0;
  
      case salvager:
!       return playSalvager(state, currentPlayer, handPos, choice1);
  
      case sea_hag:
        for (i = 0; i < state->numPlayers; i++){
--- 1164,1183 ----
        return 0;
  		
      case salvager:
!       //+1 buy
!       state->numBuys++;
! 			
!       if (choice1)
! 	{
! 	  //gain coins equal to trashed card
! 	  state->coins = state->coins + getCost( handCard(choice1, state) );
! 	  //trash card
! 	  discardCard(choice1, currentPlayer, state, 1);	
! 	}
! 			
!       //discard card
!       discardCard(handPos, currentPlayer, state, 0);
!       return 0;
  		
      case sea_hag:
        for (i = 0; i < state->numPlayers; i++){
