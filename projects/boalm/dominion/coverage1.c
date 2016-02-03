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

