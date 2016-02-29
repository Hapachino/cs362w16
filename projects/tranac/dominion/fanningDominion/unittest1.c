/* -----------------------------------------------------------------------
 * Testing getCost()
 * Pre conditions
 *  1) Passes in the name of a card 
 * Post conditions
 *  1) correctly returns the cost of the card 
 *  
 * getCost: unittest1.c dominion.o rngs.o
 *      gcc -o unit1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------*/
 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY to 0 to remove printfs from output
#define NOISY 1


int main() {
    int result;
	
    printf ("TESTING getCost():\n");
	result = getCost(curse);
#if (NOISY==1)	
	if (result==0)
	{
		printf("curse card  PASS\n");
	}
	else{
		printf("curse card  FAIL\n");
	}
#endif
	result = getCost(estate);
#if (NOISY==1)
	if (result==2)
	{
		printf("estate card  PASS\n");
	}
	else{
		printf("estate card  FAIL\n");
	}
#endif
	result = getCost(duchy);
#if (NOISY==1)
	if (result==5)
	{
		printf("duchy card  PASS\n");
	}
	else{
		printf("duchy card  FAIL\n");
	}
#endif
	result = getCost(province);
#if (NOISY==1)	
	if (result==8)
	{
		printf("province card  PASS\n");
	}
	else{
		printf("province card  FAIL\n");
	}
#endif
	result = getCost(copper);
#if (NOISY==1)	
	if (result==0)
	{
		printf("copper card  PASS\n");
	}
	else{
		printf("copper card  FAIL\n");
	}
#endif
	result = getCost(silver);
#if (NOISY==1)	
	if (result==3)
	{
		printf("silver card  PASS\n");
	}
	else{
		printf("silver card  FAIL\n");
	}
#endif
	result = getCost(gold);
#if (NOISY==1)	
	if (result==6)
	{
		printf("gold card  PASS\n");
	}
	else{
		printf("gold card  FAIL\n");
	}
#endif
	result = getCost(adventurer);
#if (NOISY==1)	
	if (result==6)
	{
		printf("adventurer card  PASS\n");
	}
	else{
		printf("adventurer card  FAIL\n");
	}
#endif
	result = getCost(council_room);
#if (NOISY==1)	
	if (result==5)
	{
		printf("council_room card  PASS\n");
	}
	else{
		printf("council_room card  FAIL\n");
	}
#endif
	result = getCost(feast);
#if (NOISY==1)	
	if (result==4)
	{
		printf("feast card  PASS\n");
	}
	else{
		printf("feast card  FAIL\n");
	}
#endif
	result = getCost(gardens);
#if (NOISY==1)	
	if (result==4)
	{
		printf("gardens card  PASS\n");
	}
	else{
		printf("gardens card FAIL\n");
	}
#endif
	result = getCost(mine);
#if (NOISY==1)	
	if (result==5)
	{
		printf("mine card PASS\n");
	}
	else{
		printf("mine card FAIL\n");
	}
#endif
	result = getCost(remodel);
#if (NOISY==1)	
	if (result==4)
	{
		printf("remodel card PASS\n");
	}
	else{
		printf("remodel card FAIL\n");
	}
#endif
	result = getCost(smithy);
#if (NOISY==1)	
	if (result==4)
	{
		printf("smithy card PASS\n");
	}
	else{
		printf("smithy card FAIL\n");
	}
#endif
	result = getCost(village);
#if (NOISY==1)
	if (result==3)
	{
		printf("village card PASS\n");
	}
	else{
		printf("village card FAIL\n");
	}
#endif
	result = getCost(baron);
#if (NOISY==1)	
	if (result==4)
	{
		printf("baron card PASS\n");
	}
	else{
		printf("baron card FAIL\n");
	}
#endif
	result = getCost(great_hall);
#if (NOISY==1)	
	if (result==3)
	{
		printf("great_hall card PASS\n");
	}
	else{
		printf("great_hall card FAIL\n");
	}
#endif
	result = getCost(minion);
#if (NOISY==1)	
	if (result==5)
	{
		printf("minion card PASS\n");
	}
	else{
		printf("minion card FAIL\n");
	}
#endif
	result = getCost(steward);
#if (NOISY==1)	
	if (result==3)
	{
		printf("steward card PASS\n");
	}
	else{
		printf("steward card FAIL\n");
	}
#endif
	result = getCost(tribute);
#if (NOISY==1)	
	if (result==5)
	{
		printf("tribute card PASS\n");
	}
	else{
		printf("tribute card FAIL\n");
	}
#endif
	result = getCost(ambassador);
#if (NOISY==1)	
	if (result==3)
	{
		printf("ambassador card PASS\n");
	}
	else{
		printf("ambassador card FAIL\n");
	}
#endif
	result = getCost(cutpurse);
#if (NOISY==1)	
	if (result==4)
	{
		printf("cutpurse card PASS\n");
	}
	else{
		printf("cutpurse card FAIL\n");
	}
#endif
	result = getCost(embargo);
#if (NOISY==1)	
	if (result==2)
	{
		printf("embargo card PASS\n");
	}
	else{
		printf("embargo card FAIL\n");
	}
#endif
	result = getCost(outpost);
#if (NOISY==1)
	if (result==5)
	{
		printf("outpost card PASS\n");
	}
	else{
		printf("outpost card FAIL\n");
	}
#endif
	result = getCost(salvager);
#if (NOISY==1)	
	if (result==4)
	{
		printf("salvager card PASS\n");
	}
	else{
		printf("salvager card FAIL\n");
	}
#endif
	result = getCost(sea_hag);
#if (NOISY==1)	
	if (result==4)
	{
		printf("sea_hag card PASS\n");
	}
	else{
		printf("sea_hag card FAIL\n");
	}
#endif
	result = getCost(treasure_map);
#if (NOISY==1)	
	if (result==4)
	{
		printf("treasure_map card PASS\n");
	}
	else{
		printf("treasure_map card FAIL\n");
	}
#endif
	printf("Tests Completed!\n");
	
    return 0;
}