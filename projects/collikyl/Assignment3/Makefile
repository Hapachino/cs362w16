unittestresults.out:
gcc dominion_helpers.h dominion.h rngs.c dominion.c interface.h interface.c unittest1.c -o urun1 -Wall -fpic -fprofile-arcs -ftest-coverage -lm
gcc dominion_helpers.h dominion.h rngs.c dominion.c interface.h interface.c unittest2.c -o urun2 -Wall -fpic -fprofile-arcs -ftest-coverage -lm
gcc dominion_helpers.h dominion.h rngs.c dominion.c interface.h interface.c unittest3.c -o urun3 -Wall -fpic -fprofile-arcs -ftest-coverage -lm
gcc dominion_helpers.h dominion.h rngs.c dominion.c interface.h interface.c unittest4.c -o urun4 -Wall -fpic -fprofile-arcs -ftest-coverage -lm

gcc dominion_helpers.h dominion.h rngs.c dominion.c interface.h interface.c cardtest1.c -o run1 -Wall -fpic -fprofile-arcs -ftest-coverage -lm
gcc dominion_helpers.h dominion.h rngs.c dominion.c interface.h interface.c cardtest2.c -o run2 -Wall -fpic -fprofile-arcs -ftest-coverage -lm
gcc dominion_helpers.h dominion.h rngs.c dominion.c interface.h interface.c cardtest3.c -o run3 -Wall -fpic -fprofile-arcs -ftest-coverage -lm
gcc dominion_helpers.h dominion.h rngs.c dominion.c interface.h interface.c cardtest4.c -o run4 -Wall -fpic -fprofile-arcs -ftest-coverage -lm

./urun1>unittestresults.out
./urun2>>unittestresults.out
./urun3>>unittestresults.out
./urun4>>unittestresults.out


./run1>>unittestresults.out
./run2>>unittestresults.out
./run3>>unittestresults.out
./run4>>unittestresults.out


gcov -b unittest1.gcda >> unittestresults.out
gcov -b unittest2.gcda >> unittestresults.out
gcov -b unittest3.gcda >> unittestresults.out
gcov -b unittest4.gcda >> unittestresults.out

gcov -b cardtest1.gcda >> unittestresults.out
gcov -b cardtest2.gcda >> unittestresults.out
gcov -b cardtest3.gcda >> unittestresults.out
gcov -b cardtest4.gcda >> unittestresults.out

gcov -b unittest1.gcda > coverage1.c
gcov -b unittest2.gcda >> coverage1.c
gcov -b unittest3.gcda >> coverage1.c
gcov -b unittest4.gcda >> coverage1.c

gcov -b cardtest1.gcda >> coverage1.c
gcov -b cardtest2.gcda >> coverage1.c
gcov -b cardtest3.gcda >> coverage1.c
gcov -b cardtest4.gcda >> coverage1.c





