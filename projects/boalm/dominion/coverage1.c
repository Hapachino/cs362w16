Note: if, the grader, did not already notice.  You can run my makefile by running the command
	make unittestresults.out


Regarding coverage:

According to gcov, I have 37.22% of the lines executed of 634 possible lines.  Regarding
function coverage, there are 22 functions.  7 had 0% coverage and 3 more had less than 50%
coverage.  The reset were quite high levels of coverage if not at 100%.  It is worth mentioning
that the functions with a low, but non-zero, level of coverage includes cardEffect.  cardEffect 
is far and away the largest function and it only has 14% coverage.  

The reason cardEffect is so low is because I only tested 4 out of the many possible cards, and 
there are other parts of the function that are not tested either.

I am happy to note that 100% of the statements ran in the four functions I unit tested.  
Those being, isGameOver, fullDeckCount, buyCard, and scoreFor.  That said, I did not explicetly
test some of the lines that were run.  For example, I did not test the counting of great_hall, 
which I probably should have, and I did not test gardens.  I actually made the choice to not
test gardens, becasue it is really just testing fullDeckCount, which I tested in another unit test.

The principle thing that I would need to do to increase coverage is to first, make sure I cover 
every single card, and then most, if not all, functions.  This would make a huge difference, and
it would probably illuminate other areas of the code that have bugs.  Now that I have spent quite
a bit of time thinking about how these functions work, it makes more sense to me what I need to do 
when I see an untested line.  At this point when reading through and looking at untested lines though,
it is mostly just cards, or functions that I did not test.

I had 50.62 percent of branches executed and took 32.35% of them at least once.  This along with the
fact that I only had 37.22 percent line coverage, indicates that there are large swaths of the program
that I did not cover.  The branching, indicates that there are many decision tree branches that are untested.
If I went down the path of covering all the functions, it would do quite a bit toward covering the branches.
The hard part would be catching the little pieces of the cardEffect function.  

If I had the freedom and time to look into making this program work, I would break it appart into many 
smaller functions, and probably (more) separate files as well.  The fact that a function exists that's 
200+ lines long is absurd.  It's almost impossible to test and can easily be broken into component parts.