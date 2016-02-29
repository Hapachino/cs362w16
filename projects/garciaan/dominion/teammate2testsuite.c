/*
Testing Function: teammate2

Steps:

Cases to check to ensure pass:

Each case check:

*/

#include "teammate2dominion.h"
#include "teammate2dominion_helpers.h"
#include "testFunctions.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main (int argc, char** argv) {
  struct gameState G;
  struct gameState previousG;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  int seed = 2;
  int* test = malloc(last_tester * sizeof(int));
  createCompareStateArray(test,1);


  int i=0;
  int j;  
  int player = 0;
  int pre_drawable_cards = 0;
  int drawable_cards = 0;
  int deck_count = 0;
  int total_deck_count = 0;
  int money = 0;
  int hand_count = 0;
  int offset = 0;
  int limit = 0;
  int bonus = 0; 
  int discard = 0;
  int deck = 1;
  int hand = 2;

  int smithy_runs = 1;
  int adv_runs = 1;
  int draw_runs = 1;
  int update_coins_runs = 1;
  int gain_card_runs = 1;
  int buy_card_runs = 1;
  int great_hall_runs = 1;
  int village_runs = 1;

  signal(SIGALRM,timeout);
  signal(SIGSEGV,handle_segfault);

  printf("\n-------------------- Testing Teammate2 --------------------\n\n");
  printf("\n-------------------- Testing Smithy --------------------\n\n");
  for (i = 1; i <= smithy_runs; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    resetCards(&G,player);

    gainCard(adventurer,&G,1,player);
    gainCard(copper,&G,1,player);
    gainCard(silver,&G,1,player);
    gainCard(gold,&G,1,player);
    
    if (whoseTurn(&G) == 0) {
      player = 0;
    /***************************************************
            Smithy
      ***************************************************/
      test[player_deck] = 0;
      test[player_deck_count] = 0;
      test[player_hand] = 0;
      test[player_hand_count] = 0;
      test[played_cards] = 0;
      test[played_card_count] = 0;
      G.playedCardCount = 0;
      

      alarm(2);
      checkError(gainCard(smithy,&G,2,player) == 0); 
      previousG = G;
      playSmithy(&G,G.handCount[player] - 1);
      alarm(0);

      printf("TEST1: Nothing else affected\n");
      alarm(2);
      checkError(checkStates(&previousG,&G,test,0));
      alarm(0);
      printResults();
      resetError();

      printf("TEST2: Smithy Deck Effects\n");
      alarm(2);
      checkError(previousG.deckCount[player] - 3 == G.deckCount[player]);
      alarm(0);
      printResults();
      resetError();

      printf("TEST3: Smithy Hand Effects\n");
      alarm(2);
      checkError(previousG.handCount[player] + 2 == G.handCount[player]);
      checkError(contains(G.hand[player],G.handCount[player],copper) == 1);
      checkError(contains(G.hand[player],G.handCount[player],silver) == 1);
      checkError(contains(G.hand[player],G.handCount[player],gold) == 1);
      checkError(contains(G.hand[player],G.handCount[player],adventurer) == 0);
      alarm(0);
      printResults();
      resetError();

      printf("TEST4: Played Cards Effected\n");
      alarm(2);
      checkError(previousG.playedCardCount + 1 == G.playedCardCount);
      checkError(G.playedCards[G.playedCardCount - 1] == smithy);
      alarm(0);
      printResults();
      resetError();

    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing Smithy complete <<<<<<<<<<<\n\n");
  printf("\n-------------------- Testing Adventurer --------------------\n\n");
  for (i = 1; i <= adv_runs; i++){  
    resetError();
    initTestGame(2, k, seed, &G);

    if (whoseTurn(&G) == 0) {
      player = 0;
      
      createCompareStateArray(test,1);
      test[player_hand] = 0;
      test[player_hand_count] = 0;
      test[player_deck] = 0; //will only be affected upon reshuffle
      test[player_deck_count] = 0;
      test[player_discard] = 0;
      test[player_discard_count] = 0;
      test[played_cards] = 0;
      test[played_card_count] = 0;
    /***************************************************
    
      ***************************************************/
      printf("TEST1: Adventurer Hand Effects and 3 Treasures at bottom\n");
      resetCards(&G,player);

      //add 1 copper, 1 silver, and 1 gold to deck in that order
      gainCard(copper,&G,1,player);
      gainCard(silver,&G,1,player);
      gainCard(gold,&G,1,player);
      //put 5 estates in deck (non treasures)
      deck_count = G.deckCount[player];
      for (j = deck_count; j < (deck_count + 5); j++){
        gainCard(estate,&G,1,player);
      }
      //put the adventurer in hand
      gainCard(adventurer,&G,2,player);
      alarm(2);
      previousG = G;
      playAdventurer(&G);
      printf("    TEST1.1: Hand Effects\n");
      checkError(contains(G.hand[player], G.handCount[player], gold) == 1);
      checkError(contains(G.hand[player], G.handCount[player], silver) == 1);
      checkError(contains(G.hand[player], G.handCount[player], copper) == 0);
      printResults();
      resetError();

      //deck effects
      printf("    TEST1.2: Deck Effects\n");
      pre_drawable_cards = previousG.deckCount[player] + previousG.discardCount[player];
      drawable_cards = G.deckCount[player] + G.discardCount[player];
      checkError(pre_drawable_cards - 2 == drawable_cards);
      printResults();
      resetError();

      //playedcards
      printf("    TEST1.3: Played Card Effects\n");
      checkError(G.playedCardCount == 1);
      checkError(G.playedCards[G.playedCardCount - 1] == adventurer);
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
      printResults();
      resetError();

      //discard checker
      printf("    TEST1.4: Discard Effects\n");
      checkError(previousG.discardCount[player] + 5 == G.discardCount[player]);
      //make sure top five discards are the estates
      for (j = 0; j < G.discardCount[player]; j++){
        checkError(G.discard[player][G.discardCount[player] - (j+1)] == estate);
      }
      printResults();
      resetError();

      printf("    TEST1.5: Nothing else affected\n");
      checkError(checkStates(&previousG,&G,test,0));
      printResults();
      resetError();

      alarm(0);

      resetCards(&G,player);

      printf("TEST2: 2 Treasures scatterd in deck with other cards in hand\n");
      for (j = 0; j < 4; j++){
        gainCard(smithy,&G,1,player);
      }
      gainCard(silver,&G,1,player);
      for (j = 0; j < 2; j++){
        gainCard(minion,&G, 1, player);
      }
      gainCard(gold,&G,1,player);

      gainCard(adventurer,&G,2,player);
      gainCard(tribute,&G,2,player);

      previousG = G;
      alarm(2);
      playAdventurer(&G);
      printf("    TEST2.1: Hand Effects\n");
      checkError(contains(G.hand[player], G.handCount[player], gold) == 1);
      checkError(contains(G.hand[player], G.handCount[player], silver) == 1);
      checkError(contains(G.hand[player], G.handCount[player], tribute) == 1);
      printResults();
      resetError();

      //deck effects
      printf("    TEST2.2: Deck Effects\n");
      pre_drawable_cards = previousG.deckCount[player] + previousG.discardCount[player];
      drawable_cards = G.deckCount[player] + G.discardCount[player];
      checkError(pre_drawable_cards - 2 == drawable_cards);
      printResults();
      resetError();

      //playedcards
      printf("    TEST2.3: Played Card Effects\n");
      checkError(G.playedCardCount == 1);
      checkError(G.playedCards[G.playedCardCount - 1] == adventurer);
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
      printResults();
      resetError();

      //discard checker
      printf("    TEST2.4: Discard Effects\n");
      checkError(previousG.discardCount[player] + 2 == G.discardCount[player]);
      //make sure top two discards are minions
      for (j = 0; j < G.discardCount[player]; j++){
        checkError(G.discard[player][G.discardCount[player] - (j+1)] == minion);
      }
      printResults();
      resetError();

      printf("    TEST2.5: Nothing else affected\n");
      checkError(checkStates(&previousG,&G,test,0));
      printResults();
      resetError();

      alarm(0);

      resetCards(&G,player);

      printf("TEST3: 2 Treasures at top of deck\n");
      for (j = 0; j < 4; j++){
        gainCard(gardens,&G,1,player);
      }
      gainCard(silver,&G,1,player);
      gainCard(gold,&G,1,player);

      gainCard(adventurer,&G,2,player);
      gainCard(tribute,&G,2,player);

      previousG = G;
      alarm(2);
      playAdventurer(&G);
      printf("    TEST3.1: Hand Effects\n");
      checkError(contains(G.hand[player], G.handCount[player], gold) == 1);
      checkError(contains(G.hand[player], G.handCount[player], silver) == 1);
      checkError(contains(G.hand[player], G.handCount[player], tribute) == 1);
      printResults();
      resetError();

      //deck effects
      printf("    TEST3.2: Deck Effects\n");
      pre_drawable_cards = previousG.deckCount[player] + previousG.discardCount[player];
      drawable_cards = G.deckCount[player] + G.discardCount[player];
      checkError(pre_drawable_cards - 2 == drawable_cards);
      printResults();
      resetError();

      //playedcards
      printf("    TEST3.3: Played Card Effects\n");
      checkError(G.playedCardCount == 1);
      checkError(G.playedCards[G.playedCardCount - 1] == adventurer);
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
      printResults();
      resetError();

      //discard checker
      printf("    TEST3.4: Discard Effects\n");
      checkError(previousG.discardCount[player] == G.discardCount[player]);
      printResults();
      resetError();

      printf("    TEST3.5: Nothing else affected\n");
      checkError(checkStates(&previousG,&G,test,0));
      printResults();
      resetError();

      alarm(0);

      resetCards(&G,player);

      printf("TEST4: Only 1 treasure in deck\n");
      for (j = 0; j < 4; j++){
        gainCard(village,&G,1,player);
      }
      gainCard(copper,&G,1,player);
      for (j = 0; j < 4; j++){
        gainCard(mine,&G,1,player);
      }

      gainCard(adventurer,&G,2,player);
      gainCard(tribute,&G,2,player);

      previousG = G;
      alarm(2);
      playAdventurer(&G);
      printf("    TEST4.1: Hand Effects\n");
      checkError(contains(G.hand[player], G.handCount[player], copper) == 1);
      checkError(contains(G.hand[player], G.handCount[player], tribute) == 1);
      printResults();
      resetError();

      //deck effects
      printf("    TEST4.2: Deck Effects\n");
      pre_drawable_cards = previousG.deckCount[player] + previousG.discardCount[player];
      drawable_cards = G.deckCount[player] + G.discardCount[player];
      checkError(pre_drawable_cards - 1 == drawable_cards);
      printResults();
      resetError();

      //playedcards
      printf("    TEST4.3: Played Card Effects\n");
      checkError(G.playedCardCount == 1);
      checkError(G.playedCards[G.playedCardCount - 1] == adventurer);
      checkError(previousG.handCount[player] + 0 == G.handCount[player]);
      printResults();
      resetError();

      //discard checker
      printf("    TEST4.4: Discard Effects\n");
      checkError(previousG.discardCount[player] + 8 == G.discardCount[player]);
      printResults();
      resetError();

      printf("    TEST4.5: Nothing else affected\n");
      checkError(checkStates(&previousG,&G,test,0));
      printResults();
      resetError();

      alarm(0);

      resetCards(&G,player);

      printf("TEST5: No treasures in deck\n");
      for (j = 0; j < 4; j++){
        gainCard(sea_hag,&G,1,player);
      }
      for (j = 0; j < 4; j++){
        gainCard(cutpurse,&G,1,player);
      }

      gainCard(adventurer,&G,2,player);
      gainCard(village,&G,2,player);

      previousG = G;
      alarm(2);
      playAdventurer(&G);
      printf("    TEST5.1: Hand Effects\n");
      printf("Hand count: %d\n",G.handCount[player]);
      //checkError(previousG.handCount[player] - 1 == G.handCount[player]);
      checkError(contains(G.hand[player], G.handCount[player], village) == 1);
      printResults();
      resetError();

      //deck effects
      printf("    TEST5.2: Deck Effects\n");
      pre_drawable_cards = previousG.deckCount[player] + previousG.discardCount[player];
      drawable_cards = G.deckCount[player] + G.discardCount[player];
      checkError(pre_drawable_cards - 0 == drawable_cards);
      printResults();
      resetError();

      //playedcards
      printf("    TEST5.3: Played Card Effects\n");
      checkError(G.playedCardCount == 1);
      checkError(G.playedCards[G.playedCardCount - 1] == adventurer);
      printResults();
      resetError();

      //discard checker
      printf("    TEST5.4: Discard Effects\n");
      checkError(previousG.discardCount[player] + 8 == G.discardCount[player]);
      printResults();
      resetError();

      printf("    TEST5.5: Nothing else affected\n");
      checkError(checkStates(&previousG,&G,test,0));
      printResults();
      resetError();

      alarm(0);

      printf("TEST6: Adventurer Hand Effects and 3 Treasures in Discard Pile\n");
      resetCards(&G,player);

      //add 1 copper, 1 silver, and 1 estate to discard in that order
      gainCard(copper,&G,0,player);
      gainCard(silver,&G,0,player);
      gainCard(estate,&G,0,player);
      //put 5 estates in deck (non treasures)
      deck_count = G.deckCount[player];
      for (j = deck_count; j < (deck_count + 5); j++){
        gainCard(estate,&G,1,player);
      }
      //put the adventurer in hand
      gainCard(adventurer,&G,2,player);
      alarm(2);
      previousG = G;
      playAdventurer(&G);
      printf("    TEST6.1: Hand Effects\n");
      checkError(contains(G.hand[player], G.handCount[player], copper) == 1);
      checkError(contains(G.hand[player], G.handCount[player], silver) == 1);
      checkError(contains(G.hand[player], G.handCount[player], estate) == 0);
      printResults();
      resetError();

      //deck effects
      printf("    TEST6.2: Deck Effects\n");
      pre_drawable_cards = previousG.deckCount[player] + previousG.discardCount[player];
      drawable_cards = G.deckCount[player] + G.discardCount[player];
      checkError(pre_drawable_cards - 2 == drawable_cards);
      printResults();
      resetError();

      //playedcards
      printf("    TEST6.3: Played Card Effects\n");
      checkError(G.playedCardCount == 1);
      checkError(G.playedCards[G.playedCardCount - 1] == adventurer);
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
      printResults();
      resetError();

      printf("    TEST6.4: Nothing else affected\n");
      checkError(checkStates(&previousG,&G,test,0));
      printResults();
      resetError();

      alarm(0);

    }
  }
  printf(">>>>>>>>>>> SUCCESS: Testing Adventurer complete <<<<<<<<<<<\n\n");
  
  printf("\n-------------------- Testing Village --------------------\n\n");
  for (i = 1; i <= village_runs; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);
    createCompareStateArray(test,1);
    test[player_deck] = 0;
    test[player_deck_count] = 0;
    test[num_actions] = 0;
    test[played_cards] = 0;
    test[played_card_count] = 0;
    test[player_hand] = 0;
    test[player_hand_count] = 0;

    resetCards(&G,player);
    for (j = 0; j < 3; j++){ //put 3 smithys to deck
      gainCard(smithy,&G,1,player);
    }
    gainCard(gold,&G,1,player); //put a gold card on top

    //add the village card to hand
    gainCard(village,&G,2,player);

    if (whoseTurn(&G) == 0) {
      player = 0;
    /***************************************************
    
      ***************************************************/
      printf("TEST1: Play Village\n");
      alarm(2);
      previousG = G;
      playVillage(&G,G.handCount[player] - 1);
      printf("    TEST1.1: Hand Effects\n");
      checkError(previousG.handCount[player] == G.handCount[player] && G.handCount[player] == 1);
      checkError(G.hand[player][G.handCount[player] - 1] == gold);
      printResults();
      resetError();

      printf("    TEST1.2: Deck Effects\n");
      checkError(previousG.deckCount[player] - 1 == G.deckCount[player]);
      //smithy was underneath the gold, make sure it is now the top
      checkError(G.deck[player][G.deckCount[player] - 1] == smithy); 
      printResults();
      resetError();

      printf("    TEST1.3: Played Card Effects\n");
      checkError(previousG.playedCardCount + 1 == G.playedCardCount);
      checkError(G.playedCards[G.playedCardCount - 1] == village);
      printResults();
      resetError();

      printf("    TEST1.4: Num Actions Effect\n");
      checkError(previousG.numActions + 2 == G.numActions);
      printResults();
      resetError();

      printf("    TEST1.5: Nothing else affected\n");
      checkError(checkStates(&previousG,&G,test,0) == 1);
      printResults();
      resetError();

      alarm(0);

    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing Village complete <<<<<<<<<<<\n\n");

  printf("\n-------------------- Testing Great Hall --------------------\n\n");
  for (i = 1; i <= great_hall_runs; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    resetCards(&G,player);
    for (j = 0; j < 3; j++){ //put 3 smithys to deck
      gainCard(smithy,&G,1,player);
    }
    gainCard(gold,&G,1,player); //put a gold card on top

    //add the great hall card to hand
    gainCard(great_hall,&G,2,player);

    if (whoseTurn(&G) == 0) {
      player = 0;
    /***************************************************
    
      ***************************************************/
      printf("TEST1: Play Great Hall\n");
      alarm(2);
      previousG = G;
      playGreat_Hall(&G,G.handCount[player] - 1);
      printf("    TEST1.1: Hand Effects\n");
      checkError(previousG.handCount[player] == G.handCount[player] && G.handCount[player] == 1);
      checkError(G.hand[player][G.handCount[player] - 1] == gold);
      printResults();
      resetError();

      printf("    TEST1.2: Deck Effects\n");
      checkError(previousG.deckCount[player] - 1 == G.deckCount[player]);
      //smithy was underneath the gold, make sure it is now the top
      checkError(G.deck[player][G.deckCount[player] - 1] == smithy); 
      printResults();
      resetError();

      printf("    TEST1.3: Played Card Effects\n");
      checkError(previousG.playedCardCount + 1 == G.playedCardCount);
      checkError(G.playedCards[G.playedCardCount - 1] == great_hall);
      printResults();
      resetError();

      printf("    TEST1.4: Num Actions Effect\n");
      checkError(previousG.numActions + 1 == G.numActions);
      printResults();
      resetError();

      printf("    TEST1.5: Nothing else affected\n");
      checkError(checkStates(&previousG,&G,test,0) == 1);
      printResults();
      resetError();

      alarm(0);

    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing CARD_NAME complete <<<<<<<<<<<\n\n");
  printf("\n-------------------- Testing drawCard --------------------\n\n");
  for (i = 1; i <= draw_runs; i++){ //for some fuzzing, set seed to i
    createCompareStateArray(test,1);
    //draw card should only affect player hand, player hand count, and player deck count
    test[player_hand] = 0;
    test[player_hand_count] = 0;
    test[player_deck_count] = 0;
    resetError();
    initTestGame(2, k, seed, &G);

    limit = 0;
    total_deck_count = 0;
    money = 0;
    hand_count = 0;

    if (whoseTurn(&G) == 0) {

      total_deck_count = totalDeckCount(0,&G);
      /***************************************************
                draw card with empty hand
      ***************************************************/
      printf("TEST1: Draw card with empty hand\n");
      alarm(2);
      previousG = G;
      checkError(drawCard(0,&G) == 0); 
      checkError(checkStates(&previousG,&G,test,0) == 1); //check nothing else got affected
      offset = 1; //should be 1 card more
      checkError(checkDeck(0,&previousG,&G) == 0);
      checkError(checkHand(hand_count,offset,0,&G) == 0);
      alarm(0);
      printResults();
      resetError();


      /***************************************************
            tests drawing all the rest of cards in deck
      ***************************************************/
      printf("TEST2: Draw all cards in deck\n");
      alarm(2);
      //set limit for drawing all card in deck to hand
      if (MAX_HAND > total_deck_count){
        limit = total_deck_count - numHandCards(&G);
      }
      else {
        limit = MAX_HAND - numHandCards(&G);
      }

      hand_count = numHandCards(&G);
      for (j = 0; j < limit; j++) { //draw all rest of cards in deck
        previousG = G;
        checkError(drawCard(0,&G) == 0); 
        checkError(checkStates(&previousG,&G,test,0) == 1); 
      }
      checkError(checkHand(hand_count,limit, 0, &G) == 0); //should be offset by limit
      alarm(0);
      printResults();
      resetError();

      /***************************************************
      check that another card is not drawn when deck and 
      discard are empty
      ***************************************************/
      printf("TEST3: Draw card with all cards in hand\n");
      alarm(2);
      hand_count = numHandCards(&G);
      previousG = G;
      checkError(drawCard(0,&G)); //we want the -1 return value here
      checkError(checkStates(&previousG,&G,test,0) == 1);
      offset = 0; //hand count should not change, so no offset
      checkError(checkHand(hand_count,offset,0,&G) == 0);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
        check when all cards are in discard pile
      ***************************************************/
      printf("TEST4: Draw card when all cards in discard pile\n");
      alarm(2);
      test[player_deck] = 0; //deck should change due to reshuffle
      test[player_discard] = 0; //discard should change due to reshuffle
      test[player_discard_count] = 0; //discare count should change due to reshuffle
      discardAll(0,&G);
      offset = 1;
      hand_count = numHandCards(&G);
      previousG = G;
      checkError(drawCard(0,&G) == 0); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(checkDeck(0,&previousG,&G) == 0);
      checkError(checkHand(hand_count,offset,0,&G) == 0);
      alarm(0);
      printResults();
      resetError();
      
    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing drawCard complete <<<<<<<<<<<\n\n");

  printf("\n-------------------- Testing updateCoins --------------------\n\n");
  for (i = 1; i <= update_coins_runs; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);
    createCompareStateArray(test,1);
    //update coins should only affect coins
    test[num_coins] = 0;
    
    if (whoseTurn(&G) == 0) {
      player = 0;
    /***************************************************
    Play a single copper with another non treasure in hand
      ***************************************************/
      printf("TEST1: Play Copper\n");
      alarm(2);
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(smithy,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(numHandCards(&G) == 2);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 1);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
    Play a single silver with another non treasure in hand
      ***************************************************/
      printf("TEST2: Play Silver\n");
      alarm(2);
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(curse,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(numHandCards(&G) == 2);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 2);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
    Play a single gold with nothing else in hand
      ***************************************************/
      printf("TEST3: Play Gold\n");
      alarm(2);
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(numHandCards(&G) == 1);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 3);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
        Play 2 of each coin with another non treasure in hand
      ***************************************************/
      printf("TEST4: Play Two of Each Coin\n");
      alarm(2);
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(sea_hag,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(numHandCards(&G) == 7);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 12);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
        Play 2 of each coin with a bonus of (8) with another non treasure in hand
      ***************************************************/
      printf("TEST5: Play One of Each Coin with Bonus\n");
      alarm(2);
      bonus = 8;
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(numHandCards(&G) == 7);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 20);
      alarm(0);
      printResults();
      resetError();
      
      //reset
      discardAll(player,&G);

      /***************************************************
        Play no treasures with a non empty hand
      ***************************************************/
      printf("TEST6: Play No Treasures (Non-Empty Hand)\n");
      alarm(2);
      bonus = 0;
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(province,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(numHandCards(&G) > 0);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 0);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
        Play no treasures with a non empty hand with bonus of (8)
      ***************************************************/
      printf("TEST7: Play No Treasures (Non-Empty Hand) with Bonus\n");
      alarm(2);
      bonus = 8;
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(province,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(estate,&G,2,player) == 0);
      checkError(numHandCards(&G) > 0);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 8);
      alarm(0);
      printResults();
      resetError();
    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing updateCoins complete <<<<<<<<<<<\n\n");

  printf("\n-------------------- Testing gainCard --------------------\n\n");
  for (i = 1; i <= gain_card_runs; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    
    if (whoseTurn(&G) == 0) {
      player = 0;
    /***************************************************
            Gain a card to discard
      ***************************************************/
      printf("TEST1: Gain a card to discard\n");
      test[supply_count] = 0;
      test[player_discard] = 0;
      test[player_discard_count] = 0;
      alarm(2);
      previousG = G;
      checkError(gainCard(smithy, &G, discard, player) == 0);
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(previousG.discardCount[player] + 1 == G.discardCount[player]);
      checkError(fullDeckCount(player,smithy,&G) == 1); //make sure there is a smithy
      checkError((previousG.supplyCount[smithy] - 1) == G.supplyCount[smithy]);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

      /***************************************************
            Gain a card to deck
      ***************************************************/
      printf("TEST2: Gain a card to deck\n");
      test[player_deck] = 0; //player deck will change
      test[player_deck_count] = 0;  //deck count will change
      test[supply_count] = 0; //supply count will change
      alarm(2);
      previousG = G;
      checkError(gainCard(gold, &G, deck, player) == 0);
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError((previousG.deckCount[player] + 1) == G.deckCount[player]);
      checkError(fullDeckCount(player,gold,&G) == 1); //make sure 1 gold now in deck
      checkError((previousG.supplyCount[gold] - 1) == G.supplyCount[gold]);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

      /***************************************************
            Gain a card to hand
      ***************************************************/
      printf("TEST3: Gain a card to hand\n");
      test[player_hand] = 0;
      test[player_hand_count] = 0;
      test[supply_count] = 0;
      alarm(2);
      previousG = G;
      checkError(gainCard(gold, &G, hand, player) == 0);
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
      checkError(previousG.supplyCount[gold] - 1 == G.supplyCount[gold]);
      //make sure last card gained is a gold
      checkError(handCard(G.handCount[player] - 1,&G) == gold);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

      /***************************************************
            Gain a card with 0 supply. Nothing changes
      ***************************************************/
      printf("TEST4: Gain a card with 0 supply\n");
      alarm(2);
      G.supplyCount[great_hall] = 0; // set supply count to 0
      previousG = G;
      //we want an error returned
      checkError(gainCard(great_hall, &G, discard, player) == -1);
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

      /***************************************************
            Gain a card that is not in game. Nothing changes.
            Assumes salvager is not in game.
      ***************************************************/
      printf("TEST5: Gain a card that is not in game\n");
      alarm(2);
      previousG = G;
      checkError(gainCard(salvager, &G, discard, player) == -1);
      //we want an error returned
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing gainCard complete <<<<<<<<<<<\n\n");

  printf("\n-------------------- Testing buyCard --------------------\n\n");
  for (i = 1; i <= buy_card_runs; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    
    if (whoseTurn(&G) == 0) {
      player = 0;
      /***************************************************
            Buy a card (province)   
      ***************************************************/
      printf("TEST1: Buy a card (province) \n");
      test[player_discard] = 0;
      test[player_discard_count] = 0;
      test[num_phase] = 0; //don't check the phase change
      test[supply_count] = 0;
      test[num_buys] = 0;
      test[num_coins] = 0;
      G.numBuys = 1;
      G.coins = 100;
      alarm(2);
      previousG = G;
      checkError(buyCard(province,&G) == 0); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(G.discard[player][G.discardCount[player]-1] == province);
      checkError(previousG.discardCount[player] + 1 == G.discardCount[player]);
      checkError(previousG.supplyCount[province] - 1 == G.supplyCount[province]);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Buy 2 cards with 2 buys (smithy,village)  
      ***************************************************/
      printf("TEST2: Buy a 2 cards with 2 buys (smithy,village) \n");
      test[player_discard] = 0;
      test[player_discard_count] = 0;
      test[num_phase] = 0; //don't check the phase change
      test[supply_count] = 0;
      test[num_buys] = 0;
      test[num_coins] = 0;
      G.numBuys = 2;
      G.coins = 100;
      alarm(2);
      previousG = G;
      checkError(buyCard(smithy,&G) == 0); 
      checkError(buyCard(village,&G) == 0); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(G.discard[player][G.discardCount[player]-2] == smithy);
      checkError(G.discard[player][G.discardCount[player]-1] == village);
      checkError(previousG.discardCount[player] + 2 == G.discardCount[player]);
      checkError(previousG.supplyCount[smithy] - 1 == G.supplyCount[smithy]);
      checkError(previousG.supplyCount[village] - 1 == G.supplyCount[village]);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Attempt to buy 2 cards (2 adventurer) with only 1 buy 
      ***************************************************/
      printf("TEST3: Attempt to buy 2 cards (2 adventurer) with only 1 buy \n");
      test[player_discard] = 0;
      test[player_discard_count] = 0;
      test[num_phase] = 0; //don't check the phase change
      test[supply_count] = 0;
      test[num_buys] = 0;
      test[num_coins] = 0;
      G.numBuys = 1;
      G.coins = 100;
      alarm(2);
      previousG = G;
      checkError(buyCard(adventurer,&G) == 0); 
      checkError(buyCard(adventurer,&G) == -1); //second buy should fail
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(G.discard[player][G.discardCount[player]-1] == adventurer);
      checkError(previousG.discardCount[player] + 1 == G.discardCount[player]);
      checkError(previousG.supplyCount[adventurer] - 1 == G.supplyCount[adventurer]);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Attempt to buy a card that is too expensive
      ***************************************************/
      printf("TEST4: Attempt to buy a card that is too expensive \n");
      test[num_phase] = 0; //don't check the phase change
      G.numBuys = 1;
      G.coins = 1;
      alarm(2);
      previousG = G;
      checkError(buyCard(gardens,&G) == -1); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Attempt to buy a card with supply 0
      ***************************************************/
      printf("TEST5: Attempt to buy a card with supply 0 \n");
      test[num_phase] = 0; //don't check the phase change
      G.numBuys = 1;
      G.coins = 100;
      G.supplyCount[minion] = 0;
      alarm(2);
      previousG = G;
      checkError(buyCard(minion,&G) == -1); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Attempt to buy a card not in game (salvager)
      ***************************************************/
      printf("TEST6: Attempt to buy a card not in game (salvager)\n");
      test[num_phase] = 0; //don't check the phase change
      G.numBuys = 1;
      G.coins = 100;
      alarm(2);
      previousG = G;
      checkError(buyCard(salvager,&G) == -1); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();




    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing buyCard complete <<<<<<<<<<<\n\n");
  printf(">>>>>>>>>>> SUCCESS: Testing Teammate2 complete <<<<<<<<<<<\n\n");
  return 0;
}
