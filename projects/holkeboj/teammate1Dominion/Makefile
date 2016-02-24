randomtest.out:
gcc dominion.h dominion.c dominion_helpers.h rngs.c interface.c randomtestadventurer.c -o run -lm -Wall -fpic -fprofile-arcs -ftest-coverage
gcc dominion.h dominion.c dominion_helpers.h rngs.c interface.c randomtestcard.c -o run2 -lm -Wall -fpic -fprofile-arcs -ftest-coverage

./run>randomtestadventurer.out
./run2>>randomtestresults.out


gcov -b randomtestadventurer.gcda > randomhistory.out
gcov -b randomtestcard.gcda >> randomhistory.out
gcov -b dominion.gcda >> randomhistory.out

gcov -b randomtestadventurer.gcda > randomcoverage.out
gcov -b randomtestcard.gcda >> randomcoverage.out
gcov -b dominion.gcda >> randomcoverage.out

rm *.gcda *.gcov *.gcno
