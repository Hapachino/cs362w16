/* -----------------------------------------------------------------------
 * Test is for getCost()
 *
 * unittest4
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"



int main(){
	
	int i; 
	int value;
	int cardAmount = 27;
	char *availableCards[27]= {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", 
			"feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
			"tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

	int cardValue[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};

	for (i = 0; i < cardAmount; i++){
		value = getCost(i);
		if(value == cardValue[i]){
			printf(">>>>>Success:%s is the correct amount of %d\n", availableCards[i], cardValue[i]);
		}
			
		else
			printf(">>>>>ERROR: %s is the incorrect amount.\n", availableCards[i]);
	}

	return (0);
	
}