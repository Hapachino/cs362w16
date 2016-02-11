/* -----------------------------------------------------------------------
 * Testing Adventuerer card
 Basic requirements of smithy card

 * -----------------------------------------------------------------------
 */
 
 /*
 -random amount of players
 -random main player
 
 -deck has random amount & random cards
 
 -fill hand with one adventuerer
 -allow deck to possiably have 0 treasure cards

 -discard has random amount & random cards
 


-checking hand supply count 

-had a problem with deck because it wasn't max hand

BUG
-Deck has to be 500 cards intially or causes segmentation fault
TEST START---------------------------------
TEST NUM: 17 Deck: 10 Hand: 48 Discard: 84 Player 3
make: *** [randomtestadventurer.out] Segmentation fault (core dumped)
make: *** Deleting file `randomtestadventurer.out'




BUG
-5 cards are taken out instead of just 2
-Actually hand count is always wrong

-Added situation where deck could me empty 25% of the time
BUG
-Empty deck causes segmentation fault every time.

-discard pile should be updated.


Added ablity to count how many cards should be discarded.
BUG found, sometimes discard is correct, sometimes not.

TEST START---------------------------------
TEST NUM: 99998 Deck: 500 Hand: 49 Discard: 36 Player: 3 DiscardCount: 25
ADVENTURER CARD---
Hand Supply Count = 77 ,expected 51
TEST FAIL
Discard Supply Count = 62,expected 62
Coins = 16 ,expected 16
Number of buys = 10,expected 10

TEST START---------------------------------
TEST NUM: 99999 Deck: 500 Hand: 67 Discard: 85 Player: 2 DiscardCount: 10
ADVENTURER CARD---
Hand Supply Count = 80 ,expected 69
TEST FAIL
Discard Supply Count = 96,expected 96
Coins = 0 ,expected 0
Number of buys = 16,expected 16


 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <limits.h>

#define DEBUG2 1

int main() {
    int i;
    int j;
    int l;
    //Used to print out correct name of card being tested in printf statement.
    const char* cardNames[] =
    {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
      "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
     "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map" };
    int countNum = 0;
    int coinRandom;
    int coinCounter;
    int allCardsCounter;
    int supplyRandomEstate;
    int randomNum;
    int deckRandom;
    int handRandom;
    int discardRandom;
    int numBuysRandom;
    int locOfBaron;
    int nameCards[MAX_HAND][MAX_HAND];
    int testAllCards;
    int deckCards;
    int handCards;
    int discardCards;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, t;
    int countCopper = 0;
    int whoseTurnIsIt = 0;
    int smithyFound = 0;
    int supplyCountCheck = 0;
    int treasure[3] = {4,5,6};
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int pointCards[6] = {0,1,2,3,16,10}; //Used to orginize point cards used
    int pointValue[6] = {-1,1,3,6,1,0}; //Used to orginize the point values that go with pointcards
    int score; //keeps return number for fullDeckCount(p, allCards, &G)
     int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG, sizeS;
    int totalCards = 5;
    //Make Array called nameCards, that holds decks full of same card name
    for (i = 0; i < MAX_HAND; i++) {
       for (j = 0; j < MAX_HAND; j++) {
      nameCards[i][j] = i;
       }
    }


     SelectStream(2);
     PutSeed(3);
    
    

    
   
    
    while(countNum < 100000){ //Stops testing after a certain number of attemtps
    if(DEBUG2)
      printf("\nTEST START---------------------------------\n");

          //Setup game, number of players, whose turn is it-----------------------------
          seed = floor(Random()*2147483646); //Random see for initializeGame state
          numPlayer = floor(Random()*3) + 2;
          memset(&G, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
          G.whoseTurn = floor(Random()*numPlayer); //set current player
          
          
 
               
          
          
          
          //Cards in DECK SETUP------------------------------------------------
          deckRandom = MAX_DECK;//(Random()*MAX_DECK);
          for (i = 0; i < deckRandom; i++) {
            G.deck[G.whoseTurn][i] = floor(Random()*27); 
          }
          G.deckCount[G.whoseTurn] = deckRandom;
          // if(floor(Random()*4) > 0)
               // G.deckCount[G.whoseTurn] = 0;
            
            
            
            
            
            
            
            
          //COINS & CARD COUNTER------------------------------------------------
          //(Determines how many cards to be discarded.)
          coinCounter = 0;
          allCardsCounter = 0;
          i = deckRandom-1;
          while(coinCounter < 2 && i >= 0) {
            allCardsCounter++;
            //printf("Counter: %d  %d\n",allCardsCounter, G.deck[G.whoseTurn][i]);
            if(G.deck[G.whoseTurn][i] == copper || G.deck[G.whoseTurn][i] == silver || G.deck[G.whoseTurn][i] == gold){
               coinCounter++;
            }
            i--;
          }
          allCardsCounter = allCardsCounter - 2;
          


            
          
          
          
          
          
          
          //Cards in HAND SETUP------------------------------------------------
          //Fill hand with 1 adventurer and other cards random
          handRandom = floor((Random()*100)+2);
          for (i = 0; i < handRandom; i++) {
            randomNum = floor(Random()*27);
            G.hand[G.whoseTurn][i] = randomNum;
          }
          //Make sure 1 adventurer is in hand
          G.hand[G.whoseTurn][0] = adventurer;
          //G.hand[G.whoseTurn][1] = floor(Random()*2); //Does player have estate card in hand. 
          G.handCount[G.whoseTurn] = handRandom;
          
          
          
          
          
          
          //Cards in DISCARD SETUP------------------------------------------------
          //Cards in discard deck
          discardRandom = floor(Random()*100);
          for (i = 0; i < discardRandom; i++) {
            G.deck[G.whoseTurn][i] = floor(Random()*27); 
          }
          G.discardCount[G.whoseTurn] = discardRandom;
          
          

          
          //SETUP COINS------------------------------------------------
          coinRandom = floor(Random()*27);
          G.coins = coinRandom;
          
          //SETUP SUPPLY COUNT------------------------------------------------
          supplyRandomEstate = floor(Random()*100);
          G.supplyCount[estate] = supplyRandomEstate;
          
          //SETUP NUMBER OF BUYS COUNT------------------------------------------------
          numBuysRandom = floor(Random()*20);//set intial buys
          G.numBuys = numBuysRandom; 
           
          //COUNT HOW MANY CARDS BEFORE FINDING GOLD------------------------------------------------
          
          
          //RUN CARD FUNCTION------------------------------------------------
          handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
          cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

          

          printf("TEST NUM: %d Deck: %d Hand: %d Discard: %d Player: %d DiscardCount: %d\n",countNum, deckRandom, handRandom, discardRandom, G.whoseTurn+1, allCardsCounter);
 
             if(DEBUG2) {
                printf("ADVENTURER CARD---\n");
                
                printf("Hand Supply Count = %d ,expected %d\n", G.handCount[G.whoseTurn], handRandom+2);
                //assert(G.handCount[G.whoseTurn] == handRandom);
                if(G.handCount[G.whoseTurn] != handRandom)
                   printf("TEST FAIL\n");
                
                
                printf("Discard Supply Count = %d,expected %d\n",G.discardCount[G.whoseTurn], discardRandom+allCardsCounter+1);
                //assert( G.discardCount[G.whoseTurn] == discardRandom+allCardsCounter+1);
                if( G.discardCount[G.whoseTurn] != discardRandom+allCardsCounter+1)
                  printf("TEST FAIL\n");
                
                printf("Coins = %d ,expected %d\n",G.coins, coinRandom);
                assert( G.coins == coinRandom);
                
                printf("Number of buys = %d,expected %d\n",G.numBuys, (numBuysRandom));
                assert( G.numBuys == (numBuysRandom));
                
                

             }
         
          
          

          countNum++;
       }
     

       
       
 
    
    
    

    return 0;
}