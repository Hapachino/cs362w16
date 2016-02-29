/* 
   Filename: randomtestadventurer.c
   Author: Lorena Nacoste
   Description: Random test for adventurer card
   Note: Format and skeleton of file based on "How to Write a Simple Random Tester" lecture provided by instructor
*/

 #include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

int checkAdventurerCard(int players, struct gameState *G, int *results);

int main(){

	int i, n, p, j;

	
    int treasure[3] = {copper, silver, gold};
    //initialize results array
    int results[6];
    for(j = 0; j <= 6; j++){
        results[j] = 0;
    }

	struct gameState G;
 
	printf("Testing adventurer card.\n");
    printf("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for(n = 0; n <= 1000; n++){
       
		for(i = 0; i < sizeof(struct gameState); i++){
		    //assign random bytes to the game state
			((char*)&G)[i] = floor(Random() * 256);
			
		}
        
        //randomly assign the number of players
		p = floor(Random() * 2);

         //randomly assign the decks, hands, and discards of player 1
         int index = 0;
         G.deckCount[0] = floor(Random() * MAX_DECK);
         for(i = 0; i <= MAX_DECK; i++){
                index = floor(Random() * 3);
                G.deck[0][i] = treasure[index];
        }
           
        index = 0;
        G.discardCount[0] = floor(Random() * MAX_DECK);
        for(i = 0; i <= MAX_DECK; i++){
                index = floor(Random() * 3);
           
        }

        index = 0;
        G.handCount[0] = floor(Random() * MAX_HAND);
        for(i = 0; i <= MAX_HAND; i++){
                index = floor(Random() * 3);
                G.hand[0][i] = treasure[index];
         }

        //if only one player, assign the turn to player 1
        if(p == 1){
            G.whoseTurn = 0;
           
        }

        else{
            //if more than one player, randomly assign the turn
            G.whoseTurn = floor(Random() * 2);

            //randomly assign the decks, hands, and discards of player 2
            index = 0;
            G.deckCount[1] = floor(Random() * MAX_DECK);
            for(i = 0; i <= MAX_DECK; i++){
                index = floor(Random() * 3);
                G.deck[1][i] = treasure[index];
            }
           
            index = 0;
            G.discardCount[1] = floor(Random() * MAX_DECK);
            for(i = 0; i <= MAX_DECK; i++){
                index = floor(Random() * 3);
           
            }

            index = 0;
            G.handCount[1] = floor(Random() * MAX_HAND);
            for(i = 0; i <= MAX_HAND; i++){
                index = floor(Random() * 3);
                G.hand[1][i] = treasure[index];
            }
        }
        

		
  
        

       
		checkAdventurerCard(p, &G, results);

	}


    printf("RESULTS:\n");
    printf("Test current player's hand count failed %d/1000 times\n", results[0]);
    printf("Test if adventurer card discarded failed %d/1000 times\n", results[1]);
    printf("Test current player's deck count failed %d/1000 times\n", results[2]);
    printf("Test if last two cards drawn were treasure cards failed %d/1000 times\n", results[3]);
    printf("Test if other player's deck changed failed %d/1000 times\n", results[4]);
    printf("Test if other player's hand changed failed %d/1000 times\n", results[5]);

	return 0;
}

int checkAdventurerCard(int players, struct gameState *G, int *results){

	
    //save game state
    struct gameState test;
    memcpy(&test, G, sizeof(struct gameState));

	int bonus = 0;
    int discardCheck;
    int treasureCounter = 0;
 
    //set expected hand and deck counts
  	int expecHand = G->handCount[0] + 2;
    int expecDeck = G->deckCount[0] - 2;
    G->hand[0][0] = adventurer;

	cardEffect(adventurer, 0, 0, 0, G, 0, &bonus);

	
    //check if the correct card was discarded
	if(G->hand[1][0] != adventurer)
        discardCheck = 0;

    else
        discardCheck = 1;


    printf("Testing hand count\n");
    if(G->handCount[0] == expecHand){
       assert(G->handCount[0] == expecHand); 
    }
    else{
        printf("Test FAILED: More than 2 cards added to current player's hand!\n");
        results[0]++;
    }

    
    printf("Testing if card discarded\n"); 
   
    if(discardCheck == 0){
        assert(discardCheck == 0);
    }

    else{
        printf("Test FAILED: Adventurer card not discarded!\n");
        results[1]++;
    }

    printf("Testing deck count\n");
    if(G->deckCount[0] == expecDeck){
        assert(G->deckCount[0] == expecDeck);
    }

    else{
         printf("Tests FAILED: More than 2 cards taken from current player's deck!\n");
         results[2]++;
    }
   

    printf("Testing if two cards drawn are treasure cards\n");
    int card1 = G->hand[0][G->handCount[0] - 1];
    int card2 = G->hand[0][G->handCount[0] - 2];
    
    if (card1 == copper || card1 == silver || card1 == gold){
        treasureCounter++;
    }

    if (card2 == copper || card2 == silver || card2 == gold){
        treasureCounter++;
    }

    if(treasureCounter == 2){
        assert(treasureCounter == 2);
    }

    else{
        printf("Test FAILED: Cards added to hand are not treasure cards!\n");
        results[3]++;
    }

    if(players > 1){
    	printf("Testing other player's deck count\n");
        if(G->deckCount[1] == test.deckCount[1]){
            assert(G->deckCount[1] == test.deckCount[1]);
        }

        else{
            printf("Test FAILED: Other player's deck changed!\n");
            results[4]++;
        }
        printf("Testing other player's hand count\n");
        if(G->handCount[1] == test.handCount[1]){
            assert(G->handCount[1] == test.handCount[1]);
        }

        else{
            printf("Test FAILED: Other player's hand count changed!\n");
            results[5]++;
        }
        
    }

    printf("\n");

    return 0;
}