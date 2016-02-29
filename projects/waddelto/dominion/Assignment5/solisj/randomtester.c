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
#include "rtestadventurer.c"
#include "cardtest2.c"
#include "rtestminion.c"

int main(int argc, char **argv) {

    int res;
    long seed;
    res = 0;
    seed = atoi(argv[1]);

    SelectStream(3);
    PutSeed(seed);

    rTestAdventurer(seed);
	rTestMinion(seed);


    return 0;

}

