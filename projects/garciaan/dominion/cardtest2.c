/*
Testing card: Adventurer

Steps:
1. Draw Cards until 2 treasures are drawn
2. Discard all other card drawn
3. Set adventurer card to played (not discarded until end of turn)

Cases to check to ensure pass:
- Two more treasures in hand 
- If only 1 more treasure in deck, must stop //I don't think it will
- All other cards to discard
- Must check 5 different scenarios
  1. 3 Treasures at bottom of deck
  2. 2 Treasures scattered in deck with other cards in hand
  3. 2 Treasures at top of deck
  4. Only 1 treasure in deck
  5. No treasures in deck

Each case check:

*/

#include "dominion.h"
#include "dominion_helpers.h"
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
  int deck_count = 0;
  signal(SIGALRM,timeout);
  signal(SIGSEGV,handle_segfault);
  int pre_drawable_cards = 0;
  int drawable_cards = 0;
  test[player_hand] = 0;
  test[player_hand_count] = 0;
  test[player_deck] = 0; //will only be affected upon reshuffle
  test[player_deck_count] = 0;
  test[player_discard] = 0;
  test[player_discard_count] = 0;
  test[played_cards] = 0;
  test[played_card_count] = 0;

  printf("\n-------------------- Testing Adventurer --------------------\n\n");
  for (i = 1; i <= 1; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    

    if (whoseTurn(&G) == 0) {
      player = 0;
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
      play_adventurer(&G,player,0);
      printf("    TEST1.1: Hand Effects\n");
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
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
      play_adventurer(&G,player,0);
      printf("    TEST2.1: Hand Effects\n");
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
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
      play_adventurer(&G,player,0);
      printf("    TEST3.1: Hand Effects\n");
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
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
      play_adventurer(&G,player,0);
      printf("    TEST4.1: Hand Effects\n");
      checkError(previousG.handCount[player] + 0 == G.handCount[player]);
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
      play_adventurer(&G,player,0);
      printf("    TEST5.1: Hand Effects\n");
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



    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing Adventurer complete <<<<<<<<<<<\n\n");
  return 0;
}
