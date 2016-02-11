// File 'smithytest.c'
// Lines executed:79.63% of 108
// Branches executed:86.36% of 44
// Taken at least once:63.64% of 44
// Calls executed:73.17% of 41
// Creating 'smithytest.c.gcov'

// File 'unittest2.c'
// Lines executed:92.31% of 13
// Branches executed:100.00% of 6
// Taken at least once:66.67% of 6
// Calls executed:75.00% of 8
// Creating 'unittest2.c.gcov'

// File 'unittest1.c'
// Lines executed:90.48% of 63
// Branches executed:100.00% of 46
// Taken at least once:73.91% of 46
// Calls executed:62.50% of 32
// Creating 'unittest1.c.gcov'

// File 'unittest3.c'
// Lines executed:69.08% of 207
// Branches executed:38.24% of 68
// Taken at least once:30.88% of 68
// Calls executed:79.38% of 97
// Creating 'unittest3.c.gcov'

// File 'unittest4.c'
// Lines executed:100.00% of 20
// Branches executed:100.00% of 8
// Taken at least once:50.00% of 8
// Calls executed:55.56% of 9
// Creating 'unittest4.c.gcov'

// File 'villagetest.c'
// Lines executed:100.00% of 86
// Branches executed:100.00% of 24
// Taken at least once:62.50% of 24
// Calls executed:70.97% of 31
// Creating 'villagetest.c.gcov'

// File 'dominion.c'
// Lines executed:29.25% of 588
// Branches executed:21.58% of 417
// Taken at least once:19.42% of 417
// Calls executed:14.58% of 96
// Creating 'dominion.c.gcov'


// My unit tests were not as thorough as I expected, which leads to the low coverage in dominion.c. Unittests1 and unittsts2 seem to be okay, but unittest3, where initializeGame() was tested was missing a few things. I could not finish the test because I could not get it to compile with gcov properly and so I had to comment out some of the subtests. The reason for this I was not able to ascertain exactly but it was narrowed down to the part where I was testing the initialization of the supply count according the types of cards in the deck. 

// I left 2 tests remaining and this also gives rise to the coverage number. The smithycard seemed to be low because I some of the business cases were untested for. For example, the status of the victory card piles and the kingdom cards. The adventurer card would not compile with gcov for some reason although the tests runs fine initially.         -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10428:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10428:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      767:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      767:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9233:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9233:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10426:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10426:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10861:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10861:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2294687:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20308964:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19014277:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981214:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18786:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18786:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981214:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10382:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10382:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      833:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      833:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9167:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9167:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10397:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10397:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10842:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10842:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2294358:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20301109:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19006751:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981278:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18722:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18722:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981278:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10396:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10396:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      819:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      819:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9181:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9181:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10399:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10399:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10870:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10870:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2298388:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20347685:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19049297:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   980846:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    19154:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    19154:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   980846:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10409:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10409:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      830:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      830:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9170:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9170:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10419:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10419:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10896:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10896:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2293498:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20300812:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19007314:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981201:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18799:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18799:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981201:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10399:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10399:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      805:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      805:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9195:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9195:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10433:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10433:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10870:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10870:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2295182:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20314971:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19019789:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981184:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18816:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18816:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981184:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10432:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10432:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      756:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      756:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9244:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9244:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10392:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10392:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10857:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10857:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2296241:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20322123:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19025882:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981158:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18842:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18842:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981158:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10414:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10414:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      783:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      783:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9217:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9217:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10424:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10424:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10897:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10897:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2296500:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20329002:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19032502:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981235:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18765:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18765:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981235:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10408:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10408:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      824:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      824:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9176:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9176:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10433:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10433:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10840:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10840:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2298648:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20352702:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19054054:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981013:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18987:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18987:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981013:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10440:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10440:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      739:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      739:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9261:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9261:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10421:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10421:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10853:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10853:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2296733:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20330939:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19034206:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981072:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18928:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18928:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981072:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10468:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10468:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      761:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      761:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9239:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9239:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10402:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10402:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10886:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10886:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2298205:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20349142:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19050937:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981181:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18819:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18819:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981181:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 100%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 99% (fallthrough)
branch  5 taken 1%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
        1:  106:			ASSERT2(ret, 0, "FAIL");
call    0 returned 100%
        -:  107:		}
        -:  108:		else
        -:  109:		{
   999999:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10390:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10390:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      821:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      821:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9179:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9179:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10419:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10419:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10868:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10868:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2299226:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20358027:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19058801:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   980941:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    19059:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    19059:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   980941:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10448:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10448:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      775:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      775:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9225:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9225:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10381:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10381:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10875:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10875:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2296798:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20332525:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19035727:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981001:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18999:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18999:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981001:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10379:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10379:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      755:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      755:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9245:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9245:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10411:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10411:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10866:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10866:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2293894:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20297085:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19003191:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981138:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18862:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18862:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981138:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10432:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10432:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      766:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      766:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9234:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9234:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10446:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10446:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10860:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10860:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2294113:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20303439:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19009326:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981226:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18774:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18774:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981226:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10400:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10400:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      779:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      779:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9221:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9221:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10370:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10370:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10863:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10863:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2297192:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20336405:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19039213:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981198:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18802:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18802:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981198:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10430:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10430:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      816:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      816:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9184:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9184:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10431:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10431:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10885:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10885:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2299381:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20362406:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19063025:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981107:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18893:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18893:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981107:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10466:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10466:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      809:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      809:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9191:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9191:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10412:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10412:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10869:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10869:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2298946:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20356893:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19057947:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   980887:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    19113:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    19113:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   980887:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10420:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10420:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      816:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      816:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9184:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9184:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10433:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10433:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10843:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10843:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2299185:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20359170:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19059985:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   980920:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    19080:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    19080:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   980920:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10432:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10432:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      786:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      786:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9214:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9214:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10379:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10379:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10893:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10893:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2299390:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20360217:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19060827:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   980918:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    19082:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    19082:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   980918:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10454:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10454:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      802:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      802:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9198:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9198:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10443:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10443:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10831:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10831:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2294840:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20309100:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19014260:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   980970:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    19030:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    19030:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   980970:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10425:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10425:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      828:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      828:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9172:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9172:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10435:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10435:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10821:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10821:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2298461:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20350687:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19052226:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   980947:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    19053:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    19053:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   980947:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10430:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10430:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      804:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      804:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9196:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9196:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10434:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10434:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10854:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10854:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2294816:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20310980:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19016164:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981197:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18803:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18803:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981197:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10436:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10436:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      794:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      794:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9206:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9206:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10438:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10438:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10867:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10867:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2296343:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20326174:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19029831:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981133:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18867:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18867:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981133:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
        -:    0:Source:unittest2.c
        -:    0:Graph:unittest2.gcno
        -:    0:Data:unittest2.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:
function main called 1 returned 100% blocks executed 87%
        1:    9:int main() {
        -:   10:
        1:   11:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   12:	printf("START of the unittest2 - KingdomCards\n");
call    0 returned 100%
        1:   13:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   14:
        -:   15:	int i;
        1:   16:	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   17:	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
call    0 returned 100%
        -:   18:
       11:   19:	for(i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       10:   20:		int ret = compare(&k1[i], &	k2[i]);
call    0 returned 100%
       10:   21:		if(ret != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   22:			printf("FAIL: return val should be 0, got %d\n", ret);
call    0 never executed
       10:   23:		assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   24:	}
        1:   25:	printf("PASS: kingdom cards allocated correctly\n");
call    0 returned 100%
        -:   26:
        1:   27:	return 0;
        -:   28:}
        -:    0:Source:unittest1.c
        -:    0:Graph:unittest1.gcno
        -:    0:Data:unittest1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <stdlib.h>
        -:    6:#include <assert.h>
        -:    7:#include "rngs.h"
        -:    8:#include <time.h>
        -:    9:
function main called 1 returned 100% blocks executed 82%
        1:   10:int main() {
        -:   11:
        1:   12:	printf("-------------------------------------\n");
call    0 returned 100%
        1:   13:	printf("START of the unittest1\n");
call    0 returned 100%
        1:   14:	printf("-------------------------------------\n");
call    0 returned 100%
        -:   15:	struct gameState G;
        -:   16:	struct gameState G2;
        -:   17:	int i, j;
        1:   18:	int numPlayers = 2;
        -:   19:	// Initialize G.
        -:   20:	  //set number of Kingdom cards
       26:   21:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   22:		G.supplyCount[i] = 1;
        -:   23:	}
        -:   24:	
        1:   25:	G.supplyCount[province] = 10;
        -:   26:
        1:   27:	int ret = isGameOver(&G);
call    0 returned 100%
        1:   28:	if(ret == 0) 
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   29:	{
        1:   30:		printf("PASS when all supply count is 1\n");
call    0 returned 100%
        -:   31:	}
        -:   32:	else
        -:   33:	{
    #####:   34:		printf("FAIL when all supply count is 1\n");
call    0 never executed
        -:   35:	}
        1:   36:	assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   37:
        -:   38:
       26:   39:	for(i = 0; i < 25; i++) {
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
       25:   40:		G.supplyCount[i] = 0;
        -:   41:
       25:   42:		ret = isGameOver(&G);
call    0 returned 100%
        -:   43:		//assert(ret == 0);
       25:   44:		if(i == province)
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        -:   45:		{
        1:   46:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   47:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
        1:   48:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   49:		}
        -:   50:		else
        -:   51:		{
       24:   52:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   53:				printf("FAIL: isGameOver should return 0 when only 1 supply is 0; instead got %d\n", ret);
call    0 never executed
       24:   54:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   55:		}
       25:   56:		G.supplyCount[i] = 1;
        -:   57:	}
        1:   58:	printf("PASS when any one supply is set to 0\n");
call    0 returned 100%
        -:   59:
        -:   60:
        -:   61:	//random testing when any two supplies are 0
        1:   62:	SelectStream(1);
call    0 returned 100%
        1:   63:	PutSeed((long)time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   64:	
    10001:   65:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   66:	{
        -:   67:		int r1, r2;
    10000:   68:		r1 = floor(Random()*25);
call    0 returned 100%
        -:   69:		do
    10407:   70:			r2 = floor(Random()*25);
call    0 returned 100%
    10407:   71:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:   72:
    10000:   73:		G.supplyCount[r1] = 0;
    10000:   74:		G.supplyCount[r2] = 0;
    10000:   75:		ret = isGameOver(&G);
call    0 returned 100%
        -:   76:
    10000:   77:		if(r2 == province || r1 == province)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 4% (fallthrough)
branch  3 taken 96%
        -:   78:		{
        -:   79:			//if province is 0, game should be over
      843:   80:			if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   81:				printf("FAIL: isGameOver should return 1 when province supply is 0; instead got %d\n", ret);
call    0 never executed
      843:   82:			assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   83:		}
        -:   84:		else
        -:   85:		{
     9157:   86:			if(ret == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   87:				printf("FAIL: isGameOver should return 0 when only two supplies are 0; instead got %d\n", ret);
call    0 never executed
     9157:   88:			assert(ret == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   89:		}
    10000:   90:		G.supplyCount[r1] = 1;
    10000:   91:		G.supplyCount[r2] = 1;
        -:   92:	}
        1:   93:	printf("PASS when any two supplies are set to 0\n");
call    0 returned 100%
        -:   94:
        -:   95:	//random testing when any three supplies are 0
        -:   96:
    10001:   97:	for(i = 0; i < 10000; i++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   98:	{
        -:   99:		int r1, r2, r3;
    10000:  100:		r1 = floor(Random()*25);
call    0 returned 100%
        -:  101:		do
    10424:  102:			r2 = floor(Random()*25);
call    0 returned 100%
    10424:  103:		while(r2 == r1);
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
        -:  104:
        -:  105:		do
    10833:  106:			r3 = floor(Random()*25);
call    0 returned 100%
    10833:  107:		while(r3 == r1 || r3 == r2 );
branch  0 taken 4%
branch  1 taken 96% (fallthrough)
branch  2 taken 4%
branch  3 taken 96% (fallthrough)
        -:  108:
        -:  109:
    10000:  110:		G.supplyCount[r1] = 0;
    10000:  111:		G.supplyCount[r2] = 0;
    10000:  112:		G.supplyCount[r3] = 0;
    10000:  113:		ret = isGameOver(&G);
call    0 returned 100%
        -:  114:
        -:  115:		//if three supplies are 0 game should be over
    10000:  116:		if(ret == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  117:			printf("FAIL: isGameOver should return 1 when province three supplies are 0; instead got %d\n", ret);
call    0 never executed
    10000:  118:		assert(ret == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  119:		
    10000:  120:		G.supplyCount[r1] = 1;
    10000:  121:		G.supplyCount[r2] = 1;
    10000:  122:		G.supplyCount[r3] = 1;
        -:  123:	}
        -:  124:
        1:  125:	printf("PASS when any three supplies are set to 0\n");
call    0 returned 100%
        1:  126:	printf("-------------------------------------\n");
call    0 returned 100%
        1:  127:	return 0;
        -:  128:}
        -:    0:Source:unittest3.c
        -:    0:Graph:unittest3.gcno
        -:    0:Data:unittest3.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#define NUMCARDS 10
        -:   10:#define NUMTRIALS 1000000
        -:   11:
function getUniqueCards called 4 returned 100% blocks executed 100%
        4:   12:int* getUniqueCards() 
        -:   13:{
        4:   14:	return kingdomCards(5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
call    0 returned 100%
        -:   15:}
        -:   16:
function ASSERT2 called 2000021 returned 100% blocks executed 29%
  2000021:   17:void ASSERT2(int testVal, int assVal, char *s) 
        -:   18:{	
  2000021:   19:	if(assVal != testVal) 
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:   20:	{
    #####:   21:		printf("FAIL - %s\n", s);
call    0 never executed
    #####:   22:		printf("ASSERTED value is %d; got %d", assVal, testVal);
call    0 never executed
    #####:   23:		assert(assVal == testVal);
branch  0 never executed
branch  1 never executed
call    2 never executed
    #####:   24:		exit(1);
call    0 never executed
        -:   25:	}
  2000021:   26:}
        -:   27:
function cardsAreUnique called 1000000 returned 100% blocks executed 100%
  1000000:   28:int cardsAreUnique(int k[]) 
        -:   29:{
        -:   30:	int i, j;
        -:   31:	//check selected kingdom cards are different (from dominion.c)
  2298240:   32:	for (i = 0; i < NUMCARDS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   33:	{
 20347524:   34:		for (j = 0; j < NUMCARDS; j++)
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:   35:		{
 19049284:   36:			if (j != i && k[j] == k[i])
branch  0 taken 88% (fallthrough)
branch  1 taken 12%
branch  2 taken 6% (fallthrough)
branch  3 taken 94%
        -:   37:			{
   981108:   38:				return -1;
        -:   39:			}
        -:   40:		}
        -:   41:	}
    18892:   42:	return 0;
        -:   43:}
        -:   44:
function cardsAreCorrectVals called 0 returned 0% blocks executed 0%
    #####:   45:int cardsAreCorrectVals(int k[]) {
        -:   46:	int i;
    #####:   47:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:   48:	{
    #####:   49:		if(k[i] > treasure_map || k[i] < adventurer) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:   50:			return -1;
        -:   51:		}
        -:   52:	}
    #####:   53:	return 0;
        -:   54:}
        -:   55:
function test1 called 1 returned 100% blocks executed 100%
        1:   56:int test1(int seed) 
        -:   57:{
        -:   58:	int i, j;
        1:   59:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:   60:
        1:   61:	int numPlayers = (rand()% 3) + 2;
call    0 returned 100%
        1:   62:	int ret = -1;
        -:   63:
        1:   64:	struct gameState *G = newGame();
call    0 returned 100%
        -:   65://	struct gameState *Gcpy = newGame();
        -:   66:	//repeat until you get return val 0 in initializeGame, i.e. all kingdom cards are unique
        -:   67:
        1:   68:	printf("TEST #1: Kingdom cards random testing\n");
call    0 returned 100%
        1:   69:	printf("\t should return 0 if unique; -1 if non-unique\n");
call    0 returned 100%
  1000001:   70:	for(i = 0; i < NUMTRIALS; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   71:	{
 11000000:   72:		for(j = 0; j < NUMCARDS; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
 10000000:   73:			k[j] = (rand()%15);
call    0 returned 100%
        -:   74:		}
  1000000:   75:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:   76:		int cret = cardsAreUnique(k);
call    0 returned 100%
  1000000:   77:		if(cret == 0) {
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
    18892:   78:			ASSERT2(ret, 0, "FAIL when cards are unique");
call    0 returned 100%
        -:   79:		}
        -:   80:		else {
   981108:   81:			ASSERT2(ret, -1, "FAIL when cards are non-unique");
call    0 returned 100%
        -:   82:		}
        -:   83:	}
        -:   84:
        1:   85:	printf("PASS\n");
call    0 returned 100%
        1:   86:	printf("------------------\n");
call    0 returned 100%
        1:   87:	free(G);
        1:   88:	free(k);
        1:   89:}
        -:   90:
function test2 called 1 returned 100% blocks executed 94%
        1:   91:int test2(int seed) {
        1:   92:	struct gameState *G = newGame();
call    0 returned 100%
        -:   93:	//struct gameState *Gcpy = newGame();
        -:   94:	int i;
        -:   95:	int numPlayers;
        -:   96:	int ret;
        1:   97:	int *k = getUniqueCards();
call    0 returned 100%
        1:   98:	printf("TEST #2: Number of players random testing\n");
call    0 returned 100%
        1:   99:	printf("\t should return 0 if 2 - 4; -1 otherwise\n");
call    0 returned 100%
        -:  100:	//random testing for number of players
  1000001:  101:	for(i = 0; i < NUMTRIALS; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
  1000000:  102:		numPlayers = rand();
call    0 returned 100%
  1000000:  103:		ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
  1000000:  104:		if((numPlayers == 1) || (numPlayers == 2) || (numPlayers == 3) || (numPlayers == 4))
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 100% (fallthrough)
branch  5 taken 0%
branch  6 taken 0% (fallthrough)
branch  7 taken 100%
        -:  105:		{
    #####:  106:			ASSERT2(ret, 0, "FAIL");
call    0 never executed
        -:  107:		}
        -:  108:		else
        -:  109:		{
  1000000:  110:			ASSERT2(ret, -1, "FAIL");
call    0 returned 100%
        -:  111:		}
        -:  112:	}
        1:  113:	printf("PASS\n");
call    0 returned 100%
        1:  114:	printf("----------------------\n");
call    0 returned 100%
        1:  115:	free(G);
        1:  116:	free(k);
        1:  117:}
        -:  118:
function test3a called 1 returned 100% blocks executed 100%
        1:  119:int test3a(int seed) {
        -:  120:	int ret;
        -:  121:	int numPlayers;
        1:  122:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  123:	struct gameState *G = newGame();
call    0 returned 100%
        1:  124:	int *k = getUniqueCards();
call    0 returned 100%
        -:  125:
        -:  126:	//Test when players are 2
        1:  127:	numPlayers = 2;
        1:  128:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  129:	curseCount = G->supplyCount[curse];
        1:  130:	estateCount = G->supplyCount[estate];
        1:  131:	duchyCount = G->supplyCount[duchy];
        1:  132:	provinceCount = G->supplyCount[province];
        1:  133:	copperCount = G->supplyCount[copper];
        1:  134:	silverCount = G->supplyCount[silver];
        1:  135:	goldCount = G->supplyCount[gold];
        1:  136:	ASSERT2(curseCount, 10, "curseCount");
call    0 returned 100%
        1:  137:	ASSERT2(estateCount, 8, "estateCount");
call    0 returned 100%
        1:  138:	ASSERT2(duchyCount, 8, "duchyCount");
call    0 returned 100%
        1:  139:	ASSERT2(provinceCount, 8, "provinceCount");
call    0 returned 100%
        1:  140:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  141:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  142:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  143:
        1:  144:	free(G);
        1:  145:	free(k);
        1:  146:}
        -:  147:
function test3b called 1 returned 100% blocks executed 100%
        1:  148:int test3b(int seed) {
        -:  149:	int ret;
        -:  150:	int numPlayers;
        1:  151:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  152:	struct gameState *G = newGame();
call    0 returned 100%
        1:  153:	int *k = getUniqueCards();
call    0 returned 100%
        -:  154:	//Test when players are 3
        -:  155:
        1:  156:	numPlayers = 3;
        1:  157:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  158:	curseCount = G->supplyCount[curse];
        1:  159:	estateCount = G->supplyCount[estate];
        1:  160:	duchyCount = G->supplyCount[duchy];
        1:  161:	provinceCount = G->supplyCount[province];
        1:  162:	copperCount = G->supplyCount[copper];
        1:  163:	silverCount = G->supplyCount[silver];
        1:  164:	goldCount = G->supplyCount[gold];
        1:  165:	ASSERT2(curseCount, 20, "curseCount");
call    0 returned 100%
        1:  166:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  167:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  168:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  169:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  170:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  171:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        -:  172:
        1:  173:	free(G);
        1:  174:	free(k);
        1:  175:}
        -:  176:
function test3c called 1 returned 100% blocks executed 100%
        1:  177:int test3c(int seed) {
        -:  178:	int ret;
        -:  179:	int numPlayers;
        1:  180:	int curseCount, estateCount, duchyCount, provinceCount, copperCount, silverCount = 40, goldCount = 30;
        1:  181:	struct gameState *G = newGame();
call    0 returned 100%
        1:  182:	int *k = getUniqueCards();
call    0 returned 100%
        -:  183:
        -:  184:	//Test when players are 4
        1:  185:	numPlayers = 4;
        1:  186:	ret = initializeGame(numPlayers, k, seed, G);
call    0 returned 100%
        1:  187:	curseCount = G->supplyCount[curse];
        1:  188:	estateCount = G->supplyCount[estate];
        1:  189:	duchyCount = G->supplyCount[duchy];
        1:  190:	provinceCount = G->supplyCount[province];
        1:  191:	copperCount = G->supplyCount[copper];
        1:  192:	silverCount = G->supplyCount[silver];
        1:  193:	goldCount = G->supplyCount[gold];
        1:  194:	ASSERT2(curseCount, 30, "curseCount");
call    0 returned 100%
        1:  195:	ASSERT2(estateCount, 12, "estateCount");
call    0 returned 100%
        1:  196:	ASSERT2(duchyCount, 12, "duchyCount");
call    0 returned 100%
        1:  197:	ASSERT2(provinceCount, 12, "provinceCount");
call    0 returned 100%
        1:  198:	ASSERT2(copperCount, (60 - (7 * numPlayers)), "copperCount");
call    0 returned 100%
        1:  199:	ASSERT2(silverCount, 40, "silverCount");
call    0 returned 100%
        1:  200:	ASSERT2(goldCount, 30, "goldCount");
call    0 returned 100%
        1:  201:	free(G);
        1:  202:	free(k);
        1:  203:}
        -:  204:
function test4 called 0 returned 0% blocks executed 0%
    #####:  205:int test4(int seed) 
        -:  206:{
        -:  207:	int i, j, t, x;
    #####:  208:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  209:	int *supplyCount = (int*)malloc(sizeof(int)*NUMCARDS);
    #####:  210:	int trialCount = 100;
    #####:  211:	int numPlayers = (rand()% 3) + 2;
call    0 never executed
    #####:  212:	int ret = -1;
        -:  213:	int rand1;
    #####:  214:	struct gameState *G = newGame();
call    0 never executed
        -:  215:
        -:  216:	//initialize supplyCount 
    #####:  217:	for(i = 0; i < NUMCARDS; i++) 
branch  0 never executed
branch  1 never executed
        -:  218:	{
    #####:  219:		supplyCount[i] = -1;
        -:  220:	}
    #####:  221:	while(t < trialCount)
branch  0 never executed
branch  1 never executed
        -:  222:	{
    #####:  223:		for(j = 0; j < NUMCARDS; j++) {
branch  0 never executed
branch  1 never executed
    #####:  224:			rand1 = (rand()%15);
call    0 never executed
    #####:  225:			k[j] = rand1;
        -:  226:		}
        -:  227:
    #####:  228:		for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 never executed
branch  1 never executed
        -:  229:		{
    #####:  230:			for (j = 0; j < NUMCARDS; j++)           		//loop chosen cards
branch  0 never executed
branch  1 never executed
        -:  231:			{
    #####:  232:				if (k[j] == i)
branch  0 never executed
branch  1 never executed
        -:  233:				{
        -:  234:					//check if card is a 'Victory' Kingdom card
    #####:  235:					if (k[j] == great_hall || k[j] == gardens)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  236:					{
    #####:  237:						if (numPlayers == 2)
branch  0 never executed
branch  1 never executed
        -:  238:						{ 
    #####:  239:							supplyCount[i] = 8; 
        -:  240:						}
        -:  241:						else
        -:  242:						{
    #####:  243:							supplyCount[i] = 12;
        -:  244:						}
        -:  245:					}
        -:  246:					else
        -:  247:					{
    #####:  248:						supplyCount[i] = 10;
        -:  249:					}
    #####:  250:					break;
        -:  251:				}
        -:  252:			}
        -:  253:		}
    #####:  254:		ret = initializeGame(numPlayers, k, seed, G);
call    0 never executed
    #####:  255:		int cret = cardsAreUnique(k);
call    0 never executed
    #####:  256:		if(cret == 0) 
branch  0 never executed
branch  1 never executed
        -:  257:		{
    #####:  258:			t++;
    #####:  259:			for(x = 0; x < NUMCARDS; x++) 
branch  0 never executed
branch  1 never executed
        -:  260:			{
    #####:  261:				if(supplyCount[x] == -1) 
branch  0 never executed
branch  1 never executed
        -:  262:				{
    #####:  263:					ASSERT2(k[x], -1, "when initializing supplyCount (-1)");				
call    0 never executed
        -:  264:				}
        -:  265:				else 
        -:  266:				{
    #####:  267:					ASSERT2(k[x], supplyCount[x], "when initializing supplyCount");
call    0 never executed
        -:  268:				}
        -:  269:			}
        -:  270:		}
        -:  271:	}
        -:  272:
        -:  273:
    #####:  274:	printf("PASS\n");
call    0 never executed
    #####:  275:	printf("------------------\n");
call    0 never executed
    #####:  276:	free(G);
    #####:  277:	free(k);
    #####:  278:	return 0;
        -:  279:}
        -:  280:
function test5 called 0 returned 0% blocks executed 0%
    #####:  281:int test5(int seed) {
        -:  282:	int i,j;
    #####:  283:	int *k = getUniqueCards();
call    0 never executed
        -:  284:	int numPlayers ;
        -:  285:	struct gameState *G;
        -:  286:	struct gameState *Gcpy;
    #####:  287:	G = newGame();
call    0 never executed
    #####:  288:	Gcpy = newGame();
call    0 never executed
    #####:  289:	numPlayers = 2;
        -:  290:
    #####:  291:	initializeGame(numPlayers, k, seed, Gcpy);
call    0 never executed
        -:  292:	//set player decks
    #####:  293:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  294:	{
    #####:  295:		G->deckCount[i] = 0;
    #####:  296:		for (j = 0; j < 3; j++)
branch  0 never executed
branch  1 never executed
        -:  297:		{
    #####:  298:		  G->deck[i][j] = estate;
    #####:  299:		  G->deckCount[i]++;
        -:  300:		}
    #####:  301:		for (j = 3; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  302:		{
    #####:  303:		  G->deck[i][j] = copper;
    #####:  304:		  G->deckCount[i]++;		
        -:  305:		}
        -:  306:	}
        -:  307:
    #####:  308:	for (i = 0; i < numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  309:	{
    #####:  310:		for (j = 0; j < 10; j++)
branch  0 never executed
branch  1 never executed
        -:  311:		{
    #####:  312:			printf("G: %d, copy: %d\n", G->deck[i][j],Gcpy->deck[i][j]);
call    0 never executed
        -:  313:
    #####:  314:			ASSERT2(Gcpy->deck[i][j], G->deck[i][j], "when initializing player decks");
call    0 never executed
        -:  315:		}
        -:  316:	}
    #####:  317:	return 0;
        -:  318:}
        -:  319:
function main called 1 returned 100% blocks executed 100%
        1:  320:int main() {
        1:  321:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        1:  322:	int seed = rand() + 1;
call    0 returned 100%
        -:  323:		//declaring the reusable variables
        1:  324:	int *k = (int*)malloc(sizeof(int)*NUMCARDS);
        -:  325:
        1:  326:	printf("-------------------------------------------------------\n");
call    0 returned 100%
        1:  327:	printf("START OF UNIT TEST 3 - INITIALIZEGAME\n\n");
call    0 returned 100%
        -:  328:
        -:  329:	//testing for unique kingdom cards
        1:  330:	test1(seed);
call    0 returned 100%
        -:  331:
        -:  332:	//testing for number of players
        1:  333:	test2(seed);
call    0 returned 100%
        -:  334:
        -:  335:	//testing for supply count
        -:  336:	//when 2 players
        1:  337:	printf("TEST #3a: Supply cards: 3 players\n");
call    0 returned 100%
        1:  338:	printf("\t curse = 10, estate|province|duchy = 8\n");
call    0 returned 100%
        1:  339:	test3a(seed);
call    0 returned 100%
        1:  340:	printf("PASS\n");
call    0 returned 100%
        1:  341:	printf("------------------\n");
call    0 returned 100%
        -:  342:
        -:  343:	//when 3 players
        1:  344:	printf("TEST #3b: Supply cards: 3 players\n");
call    0 returned 100%
        1:  345:	printf("\t curse = 20, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  346:	test3b(seed);
call    0 returned 100%
        1:  347:	printf("PASS\n");
call    0 returned 100%
        1:  348:	printf("------------------\n");
call    0 returned 100%
        -:  349:
        -:  350:	//when 4 players
        1:  351:	printf("TEST #3c: Supply cards: 4 players\n");
call    0 returned 100%
        1:  352:	printf("\t curse = 30, estate|province|duchy = 12\n");
call    0 returned 100%
        1:  353:	test3c(seed);
call    0 returned 100%
        1:  354:	printf("PASS\n");
call    0 returned 100%
        1:  355:	printf("------------------\n");
call    0 returned 100%
        -:  356:
        -:  357:	//testing for correct kingdom card values
        1:  358:	printf("TEST #4: Kingdom cards correct values\n");
call    0 returned 100%
        1:  359:	printf("\t should return 8, 10, 12 depending on number of players; -1 for unselected card\n");
call    0 returned 100%
        -:  360:	//test4(seed);
        -:  361:	//test5(seed);
        -:  362:
        1:  363:	printf("\nEND OF UNIT TEST 3 - INITIALIZEGAME\n");
call    0 returned 100%
        1:  364:	printf("---------------------------------------------------\n");
call    0 returned 100%
        1:  365:	return 0;
        -:  366:}
        -:    0:Source:unittest4.c
        -:    0:Graph:unittest4.gcno
        -:    0:Data:unittest4.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include <string.h>
        -:    4:#include <stdio.h>
        -:    5:#include <assert.h>
        -:    6:#include "rngs.h"
        -:    7:#include <time.h>
        -:    8:#include <stdlib.h>
        -:    9:#include <assert.h>
        -:   10:#define NUMCARDS 10
        -:   11:
function main called 1 returned 100% blocks executed 73%
        1:   12:int main() {
        -:   13:
        -:   14:	struct gameState G;
        -:   15:
        1:   16:	int seed = 1000;
        -:   17:	int t1;
        1:   18:	int numPlayers = 4;
        1:   19:	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        1:   20:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   21:	G.whoseTurn = 0;
        1:   22:	t1 = G.whoseTurn;
        -:   23:
        1:   24:	endTurn(&G);
call    0 returned 100%
        1:   25:	t1 = G.whoseTurn;
        1:   26:	assert(t1 == 1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   27:
        1:   28:	endTurn(&G);
call    0 returned 100%
        1:   29:	t1 = G.whoseTurn;
        1:   30:	assert(t1 == 2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   31:
        1:   32:	endTurn(&G);
call    0 returned 100%
        1:   33:	t1 = G.whoseTurn;
        1:   34:	assert(t1 == 3);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:   35:
        1:   36:	endTurn(&G);
call    0 returned 100%
        1:   37:	t1 = G.whoseTurn;
        1:   38:	assert(t1 == 0);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:   39:	return 0;
        -:   40:}
        -:   41:
        -:   42:
        -:   43:// int endTurn(struct gameState *state) {
        -:   44://   int k;
        -:   45://   int i;
        -:   46://   int currentPlayer = whoseTurn(state);
        -:   47:  
        -:   48://   //Discard hand
        -:   49://   for (i = 0; i < state->handCount[currentPlayer]; i++){
        -:   50://     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
        -:   51://     state->hand[currentPlayer][i] = -1;//Set card to -1
        -:   52://   }
        -:   53://   state->handCount[currentPlayer] = 0;//Reset hand count
        -:   54:    
        -:   55://   //Code for determining the player
        -:   56://   if (currentPlayer < (state->numPlayers - 1)){ 
        -:   57://     state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:   58://   }
        -:   59://   else{
        -:   60://     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:   61://   }
        -:   62:
        -:   63://   state->outpostPlayed = 0;
        -:   64://   state->phase = 0;
        -:   65://   state->numActions = 1;
        -:   66://   state->coins = 0;
        -:   67://   state->numBuys = 1;
        -:   68://   state->playedCardCount = 0;
        -:   69://   state->handCount[state->whoseTurn] = 0;
        -:   70:
        -:   71://   //int k; move to top
        -:   72://   //Next player draws hand
        -:   73://   for (k = 0; k < 5; k++){
        -:   74://     drawCard(state->whoseTurn, state);//Draw a card
        -:   75://   }
        -:   76:
        -:   77://   //Update money
        -:   78://   updateCoins(state->whoseTurn, state , 0);
        -:   79:
        -:   80://   return 0;
        -:   81:// }
        -:    0:Source:villagetest.c
        -:    0:Graph:villagetest.gcno
        -:    0:Data:villagetest.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include "cardFunctions.h"
        -:    5:#include <stdio.h>
        -:    6:#include <math.h>
        -:    7:#include <stdlib.h>
        -:    8:#include <assert.h>
        -:    9:
        -:   10:
        -:   11://random hand with smithy at the end
function createRandomHand called 4 returned 100% blocks executed 100%
        4:   12:int createRandomHand(int *k, int max) 
        -:   13:{
        -:   14:	int j;
       20:   15:	for(j = 0; j < max-1; j++) 
branch  0 taken 80%
branch  1 taken 20% (fallthrough)
        -:   16:	{
       16:   17:		k[j] = (rand()%15);
call    0 returned 100%
        -:   18:	}
        4:   19:	k[j] = smithy;
        4:   20:}
        -:   21:
        -:   22://random hand with smithy at the end
function createRandomDeck called 4 returned 100% blocks executed 100%
        4:   23:int createRandomDeck(int *k, int max) 
        -:   24:{
        -:   25:	int j;
     1984:   26:	for(j = 0; j < max; j++) 
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   27:	{
     1980:   28:		k[j] = (rand()%15);
call    0 returned 100%
        -:   29:	}
        4:   30:}
        -:   31:
function setDiscardDeck called 4 returned 100% blocks executed 100%
        4:   32:int setDiscardDeck(int *k, int max) {
        -:   33:	int i;
     2004:   34:	for(i = 0; i < max; i++)
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
        -:   35:	{
     2000:   36:		k[i] = -1;
        -:   37:	}
        4:   38:}
        -:   39:
function main called 1 returned 100% blocks executed 78%
        1:   40:int main() {
        1:   41:	srand(time(NULL));
call    0 returned 100%
call    1 returned 100%
        -:   42:	struct gameState G;
        -:   43:	struct infosStruct infos;
        1:   44:	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
        1:   45:	int numPlayers = 4;
        -:   46:	int handCountBefore, handCountAfter;
        -:   47:	int deckCountBefore, deckCountAfter;
        1:   48:	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
        -:   49:	int i;
        1:   50:	int seed = 1000;
        1:   51:	initializeGame(numPlayers, k, seed, &G);
call    0 returned 100%
        1:   52:	G.numPlayers = numPlayers;
        1:   53:	G.whoseTurn = 0;
        1:   54:	infos.currentPlayer = 0;
        1:   55:	infos.handPos = 4;
        -:   56:	int numActions1, numActions2;
        -:   57:	int numCards1, numCards2;
        -:   58:	int numDeck1, numDeck2;
        -:   59:	int numHand1, numHand2;
        -:   60:
        1:   61:	int handCount = 5;
        1:   62:	int deckCount = MAX_DECK - handCount;
        1:   63:	createRandomHand(G.hand[p1], handCount);
call    0 returned 100%
        1:   64:	createRandomHand(G.hand[p2], handCount);
call    0 returned 100%
        1:   65:	createRandomHand(G.hand[p3], handCount);
call    0 returned 100%
        1:   66:	createRandomHand(G.hand[p4], handCount);
call    0 returned 100%
        -:   67:
        1:   68:	G.handCount[p1] = handCount;
        1:   69:	G.handCount[p2] = handCount;	
        1:   70:	G.handCount[p3] = handCount;	
        1:   71:	G.handCount[p4] = handCount;
        -:   72:
        1:   73:	createRandomDeck(G.deck[p1], deckCount);
call    0 returned 100%
        1:   74:	createRandomDeck(G.deck[p2], deckCount);
call    0 returned 100%
        1:   75:	createRandomDeck(G.deck[p3], deckCount);
call    0 returned 100%
        1:   76:	createRandomDeck(G.deck[p4], deckCount);
call    0 returned 100%
        -:   77:
        1:   78:	G.deckCount[p1] = deckCount;
        1:   79:	G.deckCount[p2] = deckCount;	
        1:   80:	G.deckCount[p3] = deckCount;	
        1:   81:	G.deckCount[p4] = deckCount;
        -:   82:
        1:   83:	setDiscardDeck(G.discard[p1], MAX_DECK);
call    0 returned 100%
        1:   84:	setDiscardDeck(G.discard[p2], MAX_DECK);
call    0 returned 100%
        1:   85:	setDiscardDeck(G.discard[p3], MAX_DECK);
call    0 returned 100%
        1:   86:	setDiscardDeck(G.discard[p4], MAX_DECK);
call    0 returned 100%
        -:   87:
        1:   88:	G.discardCount[p1] = 0;
        1:   89:	G.discardCount[p2] = 0;	
        1:   90:	G.discardCount[p3] = 0;	
        1:   91:	G.discardCount[p4] = 0;
        -:   92:
        -:   93:
        -:   94://testing current player
        1:   95:	numActions1 = G.numActions;
        1:   96:	numHand1 = G.handCount[p1];
        1:   97:	numDeck1 = G.deckCount[p1];
        1:   98:	effectVillage(&G, &infos);
call    0 returned 100%
        -:   99:
        1:  100:	numHand2 = G.handCount[p1];
        1:  101:	numDeck2 = G.deckCount[p1];
        1:  102:	numActions2 = G.numActions;	
        1:  103:	assert(numActions1 +2 == numActions2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  104:	assert(numDeck1 -1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  105:	//assert(numHand1 +1 == numHand2);
        -:  106:	
        1:  107:	endTurn(&G);
call    0 returned 100%
        1:  108:	assert(G.numActions == numActions1);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  109:
        -:  110:	//testing for player 2
        1:  111:	infos.currentPlayer = 0;
        1:  112:	numHand1 = G.handCount[p2];
        1:  113:	numDeck1 = G.deckCount[p2];
        1:  114:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  115:
        1:  116:	numHand2 = G.handCount[p2];
        1:  117:	numDeck2 = G.deckCount[p2];
        1:  118:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  119:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  120:
        -:  121://testing for player 3
        1:  122:	infos.currentPlayer = 0;
        1:  123:	numHand1 = G.handCount[p3];
        1:  124:	numDeck1 = G.deckCount[p3];
        1:  125:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  126:
        1:  127:	numHand2 = G.handCount[p3];
        1:  128:	numDeck2 = G.deckCount[p3];
        1:  129:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  130:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  131:
        -:  132://testing for player 4
        1:  133:	infos.currentPlayer = 0;
        1:  134:	numHand1 = G.handCount[p4];
        1:  135:	numDeck1 = G.deckCount[p4];
        1:  136:	effectVillage(&G, &infos);
call    0 returned 100%
        -:  137:
        1:  138:	numHand2 = G.handCount[p4];
        1:  139:	numDeck2 = G.deckCount[p4];
        1:  140:	assert(numDeck1 == numDeck2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        1:  141:	assert(numHand1 == numHand2);
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
call    2 never executed
        -:  142:
        -:  143:
        1:  144:	return 0;
        -:  145:}
        -:  146:
        -:  147:
        -:  148:
        -:  149:// int effectVillage(struct gameState *state, struct infosStruct *infos)
        -:  150:// {
        -:  151:
        -:  152://   int currentPlayer= infos->currentPlayer;
        -:  153:
        -:  154://   int handPos = infos->handPos;
        -:  155://   //+1 Card
        -:  156://   drawCard(currentPlayer, state);
        -:  157:
        -:  158://   //+2 Actions
        -:  159://   state->numActions = state->numActions + 2;
        -:  160:
        -:  161://   //discard played card from hand
        -:  162://   discardCard(handPos, currentPlayer, state, 0);
        -:  163://   return 0;
        -:  164:// }
        -:  165:
