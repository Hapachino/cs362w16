/* 	File: coverage.c
	Author: Chris Trana
	CS 362
	
In reviewing my code coverage for my suite of tests it's apparent that I did not think them
out as carefully as I could.

OVERALL
 dominion.c
	Lines executed 33.56% of 584
	Branches 32.13% of 417
	tanken at least once 28.3% of 417
	calls executed 16.84% of 95
 
	These results are not surprising since I only tested 4 cards and 4 functions. Not
	surprisingly this would indicate that I would need more tests. Given that the tests are only being shown ran as once I could also see how random testing would help increse the test calls which could also result in better code coverage with just the exsisting cards
	and funcitons that I'm currently testing.  I think that random testing could also make it
	easier to identify and then hard code tests on boundary's
 
                                UNIT TESTS
 unittest1 - getCost()
    Lines executed 75.89% of 112
	Branches 100% of 54
	tanken at least once 50% of 54
	calls executed 67.47% of 83
	
	All of my tests passed on this one so the branches not taken are for failed tests.
	This was my first test and it was a pretty simple function so I'm not sure I can get much 
	out of these results.
 
 
 unittest2 - isGameOver()
    Lines executed 100% of 63
	Branches 100% of 50
	tanken at least once 50% of 50
	calls executed 43.18% of 84
 
	This one has me a little perplexed.  This test was written with assertions and no print statements for fails so I ouwl think that all calls should have been executed on this one.
 
 
 unittest3 - shuffle()
	Lines executed 100% of 23
	Branches 100% of 8
	tanken at least once 75% of 8
	calls executed 75% of 8
    
    This test worked fairly well with a good amount of the code being executed.
 
 
 unittest4 - drawCard()
    Lines executed 93.33% of 30
	Branches 100% of 12
	tanken at least once 83.33% of 12
	calls executed 86.67% of 15
 
   This was a for loop that drew a card until the deck was empty so it got pretty good coverage.  Everything passed until we got to 0 cards in the deck.  I'm still not sure this
   is a bug yet.  Overll I feel the code covered what i intended it to.
 
 
                                CARD TESTS
 cardtest1 - smithy
    Lines executed 84% of 25
	Branches 100% of 8
	tanken at least once 50% of 8
	calls executed 66.67% of 12
 
    This test did find bugs.  Overall code coerage looks good considering I would expect
	some lines to not run due to bugs.
 
 
 cardtest2 - adventurer
    Lines executed 83.33% of 24
	Branches 100% of 8
	tanken at least once 50% of 8
	calls executed 66.67% of 12
 
    Very similar to smithy and not surprising since the same number of tests failed.
 
 
 cardtest3 - village
	Lines executed 82.14% of 28
	Branches 100% of 10
	tanken at least once 50% of 10
	calls executed 64.29% of 14
    
	Similar results to the other two prior tests.  Also had failed tests and found
	some bugs in this one.
 
 
 cardtest4 - council_room
	Lines executed 80.56% of 36
	Branches 100% of 18
	tanken at least once 61.11% of 18
	calls executed 61.11% of 18
	
    This one had a few bugs in it as well so I'm not surprised the code coverage looks low.
	*/

