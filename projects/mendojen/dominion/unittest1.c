/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * getCost: unittest1.c dominion.o rngs.o
 *      gcc -o unit1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1


int main() {
    int result;
    printf ("TESTING getCost():\n");
	result = getCost(curse);
#if (NOISY_TEST==1)	
	printf ("Testing curse card cost.\n");
	printf("Result: %d Expected: 0\n",result);
#endif
	assert(result==0);
	result = getCost(estate);
#if (NOISY_TEST==1)
	printf ("Testing estate card cost.\n");
	printf("Result: %d Expected: 2\n",result);
#endif	
	assert(result==2);
	result = getCost(duchy);
#if (NOISY_TEST==1)
	printf ("Testing duchy card cost.\n");
	printf("Result: %d Expected: 5\n",result);
#endif
	assert(result==5);
	result = getCost(province);
#if (NOISY_TEST==1)	
	printf ("Testing province card cost.\n");
	printf("Result: %d Expected: 8\n",result);
#endif
	assert(result==8);
	result = getCost(copper);
#if (NOISY_TEST==1)	
	printf ("Testing copper card cost.\n");
	printf("Result: %d Expected: 0\n",result);
#endif
	assert(result==0);
	result = getCost(silver);
#if (NOISY_TEST==1)	
	printf ("Testing silver card cost.\n");
	printf("Result: %d Expected: 3\n",result);
#endif
	assert(result==3);
	result = getCost(gold);
#if (NOISY_TEST==1)	
	printf ("Testing gold card cost.\n");
	printf("Result: %d Expected: 6\n",result);
#endif
	assert(result==6);
	result = getCost(adventurer);
#if (NOISY_TEST==1)	
	printf ("Testing adventurer card cost.\n");
	printf("Result: %d Expected: 6\n",result);
#endif
	assert(result==6);
	result = getCost(council_room);
#if (NOISY_TEST==1)	
	printf ("Testing council room card cost.\n");
	printf("Result: %d Expected: 5\n",result);
#endif
	assert(result==5);
	result = getCost(feast);
#if (NOISY_TEST==1)	
	printf ("Testing feast card cost.\n");
	printf("Result: %d Expected: 4\n",result);
#endif
	assert(result==4);
	result = getCost(gardens);
#if (NOISY_TEST==1)	
	printf ("Testing gardens card cost.\n");
	printf("Result: %d Expected: 4\n",result);
#endif
	assert(result==4);
	result = getCost(mine);
#if (NOISY_TEST==1)	
	printf ("Testing mine card cost.\n");
	printf("Result: %d Expected: 5\n",result);
#endif
	assert(result==5);
	result = getCost(remodel);
#if (NOISY_TEST==1)	
	printf ("Testing remodel card cost.\n");
	printf("Result: %d Expected: 4\n",result);
#endif
	assert(result==4);
	result = getCost(smithy);
#if (NOISY_TEST==1)	
	printf ("Testing smithy card cost.\n");
	printf("Result: %d Expected: 4\n",result);
#endif
	assert(result==4);
	result = getCost(village);
#if (NOISY_TEST==1)
	printf ("Testing village card cost.\n");
	printf("Result: %d Expected: 3\n",result);
#endif
	assert(result==3);
	result = getCost(baron);
#if (NOISY_TEST==1)	
	printf ("Testing baron card cost.\n");
	printf("Result: %d Expected: 4\n",result);
#endif
	assert(result==4);
	result = getCost(great_hall);
#if (NOISY_TEST==1)	
	printf ("Testing great hall card cost.\n");
	printf("Result: %d Expected: 3\n",result);
#endif
	assert(result==3);
	result = getCost(minion);
#if (NOISY_TEST==1)	
	printf ("Testing minion card cost.\n");
	printf("Result: %d Expected: 5\n",result);
#endif
	assert(result==5);
	result = getCost(steward);
#if (NOISY_TEST==1)	
	printf ("Testing steward card cost.\n");
	printf("Result: %d Expected: 3\n",result);
#endif
	assert(result==3);
	result = getCost(tribute);
#if (NOISY_TEST==1)	
	printf ("Testing tribute card cost.\n");
	printf("Result: %d Expected: 5\n",result);
#endif
	assert(result==5);
	result = getCost(ambassador);
#if (NOISY_TEST==1)	
	printf ("Testing ambassador card cost.\n");
	printf("Result: %d Expected: 3\n",result);
#endif
	assert(result==3);
	result = getCost(cutpurse);
#if (NOISY_TEST==1)	
	printf ("Testing cutpurse card cost.\n");
	printf("Result: %d Expected: 4\n",result);
#endif
	assert(result==4);
	result = getCost(embargo);
#if (NOISY_TEST==1)	
	printf ("Testing embargo card cost.\n");
	printf("Result: %d Expected: 2\n",result);
#endif
	assert(result==2);
	result = getCost(outpost);
#if (NOISY_TEST==1)
	printf ("Testing outpost card cost.\n");
	printf("Result: %d Expected: 5\n",result);
#endif
	result = getCost(salvager);
#if (NOISY_TEST==1)	
	printf ("Testing salvager card cost.\n");
	printf("Result: %d Expected: 4\n",result);
#endif
	assert(result==4);
	result = getCost(sea_hag);
#if (NOISY_TEST==1)	
	printf ("Testing sea_hag card cost.\n");
	printf("Result: %d Expected: 4\n",result);
#endif
	assert(result==4);
	result = getCost(treasure_map);
#if (NOISY_TEST==1)	
	printf ("Testing treasure_map card cost.\n");
	printf("Result: %d Expected: 4\n",result);
#endif
	assert(result==4);
	
	

    printf("All tests passed!\n");
	
    return 0;
}
