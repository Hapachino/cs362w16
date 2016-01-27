/* -----------------------------------------------------------------------
 * Testing gainCard()
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>


int main() {
    int i;
    int j;
    int returnValue;
    //Used to print out correct name of card being tested in printf statement.
    const char* cardNames[] =
    {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
      "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
     "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map" };
    
    int nameCards[MAX_HAND][MAX_HAND];
    int testAllCards;
    int deckCards;
    int handCards;
    int discardCards;
    int seed = 1000;
    int numPlayer = 2;
    int p, r;
    int pointCards[6] = {0,1,2,3,16,10}; //Used to orginize point cards used
    int pointValue[6] = {-1,1,3,6,1,0}; //Used to orginize the point values that go with pointcards
    int score; //keeps return number for fullDeckCount(p, allCards, &G)
     int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int totalCards = 5;
    //Make Array called nameCards, that holds decks full of same card name
    for (i = 0; i < MAX_HAND; i++) {
       for (j = 0; j < MAX_HAND; j++) {
      nameCards[i][j] = i;
       }
    }
    
    
    
    
    
    printf ("\n\nTESTING gainCard():\n");
    
    
    printf("\nTest 1 - gainCard should return -1 if supplyCount is empty\n");
    
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    //Setting supplyCount for all cards to 0;
    for(i = 0; i < 27; i++) {
      G.supplyCount[i] = 0;
    }
    
    returnValue = gainCard(duchy, &G, 0, 0);
    printf("return value = %d, expected = -1\n", returnValue);
    assert(returnValue == -1);
    
    
    
    
    
    
    printf("\nTest 2 - Add card to player 1 discard deck - check if discard deck has been updated\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    G.supplyCount[curse] = 1;
    G.discardCount[0] = 0;
    G.discard[0][0] = 10; //put gardens card in initially
    
    returnValue = gainCard(curse, &G, 0, 0);
    printf("discard pile count = %d, expected discard pile count = 1\n",G.discardCount[0]);
    printf("card = %d, expected card = 0\n",G.discard[0][0]);
    
    assert(G.discardCount[0] == 1); // check discard pile for correct count of cards
    assert(G.discard[0][0] == 0); // check discard pile for card
    
    
    
    
    
    printf("\nTest 3 - Add card to player 1 deck - check if deck has been updated\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    G.supplyCount[curse] = 1;
    G.deckCount[0] = 0;
    G.deck[0][0] = 10; //put gardens card in initially
    
    returnValue = gainCard(curse, &G, 1, 0);
    printf("deck pile count = %d, expected deck pile count = 1\n",G.deckCount[0]);
    printf("card = %d, expected card = 0\n",G.deck[0][0]);
    
    assert(G.deckCount[0] == 1); // check deck pile for correct count of cards
    assert(G.deck[0][0] == 0); // check deck pile for card
    
    
    
    
    
    
    
    printf("\nTest 4 - Add card to player 1 hand - check if hand has been updated\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    G.supplyCount[curse] = 1;
    G.handCount[0] = 0;
    G.hand[0][0] = 10; //put gardens card in initially
    
    returnValue = gainCard(curse, &G, 2, 0);
    printf("hand pile count = %d, expected hand pile count = 1\n",G.handCount[0]);
    printf("card = %d, expected card = 0\n",G.hand[0][0]);
    
    assert(G.handCount[0] == 1); // check hand pile for correct count of cards
    assert(G.hand[0][0] == 0); // check hand pile for card
    
   
   
   
    
    printf("\nTest 5 - Testing supplyCount decressed in size after func completed.\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    G.supplyCount[curse] = 1;
    G.handCount[0] = 0;
    G.hand[0][0] = 10; //put gardens card in initially
    
    returnValue = gainCard(curse, &G, 2, 0);
    
    printf("supply count for curse = %d, expected supply count for curse = 0\n\n",G.supplyCount[curse]);
    
    assert(G.supplyCount[curse] == 0); // check hand pile for correct count of cards
    
    
    

    return 0;
}