#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include "test_helper.h"
#include <string.h>
#include <math.h>
#include "unittest1.c"
#include "unittest2.c"
#include "unittest3.c"
#include "unittest4.c"
#include "cardtest1.c"
#include "cardtest2.c"
#include "cardtest3.c"
#include "cardtest4.c"

int main(int argc, char **argv) {

    int res;
    long seed;
    res = 0;
    seed = atoi(argv[1]);

    SelectStream(3);
    PutSeed(seed);

    unittest1(seed);
    unittest2(seed);
    unittest3(seed);
    unittest4(seed);
    smithyTest(seed);
    adventurerTest(seed);
    minionTest(seed);
    seaHagTest(seed);
    return 0;

}

