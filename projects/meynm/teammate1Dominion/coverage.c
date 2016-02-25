/*
 
                                        coverage.c
 
 Patrick Burrell
 CS 362 - Winter 2016
 Assignment 3
 
 
 OVERALL
 dominion.c
 Lines executed:36.74% of 645
 Branches executed:42.45% of 417
 Taken at least once:29.02% of 417
 
 It's hard to judge what percentage means in this context since tests were only
 written for four functions and four cards. Arbitrarily choosing to test the
 functions or cards with more lines of code or the most function calls within
 them likely would have increased coverage by a significant percentage even
 though it's still only four functions and four cards being tested. Some of the 
 shorter functions or cards could be called more often or under a greater number 
 of possible conditions and therefore potentially be a higher priority to test 
 thoroughly even though it wouldn't result in the highest overall coverage for 
 the file.
 
                                UNIT TESTS
 unittest1 - drawCard()
    called 271
    returned 100% 
    blocks executed 75%
 
    This was my first unit test, and it looks like it has room for improvement
    on coverage, but much of the uncovered code is from DEBUG statements that 
    had been turned of. This also led to multiple branches with 0% taken, but 
    there was also a branch that was only taken 1% of the time. Ironically enough,
    the branch that was taken1% of the time led me to a bug. It was taken 1% of 
    the time because the branch ends the function when taken.
 
 
 unittest2 - buyCard()
    called 108
    returned 100%
    blocks executed 100%
 
    This function was covered thoroughly, the only missing lines were DEBUG
    statements or commented out lines. The functions within buyCard were 
    mostly covered at 100%, but numHandCards was not called and fullDeckCount
    was only executed at 70%.
 
 
 unittest3 - discardCard()
    called - 48
    returned - 100%
    blocks executed - 100%
    
    This function was called a relative few number of times but had good 
    coverage. The branch coverage was unbalanced in terms of times taken, 
    but each branch was taken at least 10% of the time.
 
 
 unittest4 - updateCoins()
    called 99
    returned 100%
    blocks executed 100%
 
    I covered this function pretty well. There were several branches in the 
    function where one branch was taken 80+% of the time, so there could be 
    some potential for more balancing there.
 
 
                                CARD TESTS
 cardtest1 - smithy
    playSmithy()
        called - 9
        returned - 100%
        block executed - 100%
 
    I was surprised at how few times this function was called even as the 
    one who wrote the tests. These tests were hardcoded situations to test
    different aspects of the function, and this is represented in the 100% 
    blocks executed. The implication on the reliability of my test suite 
    comes down to how effectively the hard coded cases were implemented.
    Each call to this function involved one or more calls to drawCard() and
    discardCard().
 
 
 cardtest2 - adventurer
    playAdventurer
        called - 5
        returned - 100%
        blockes executed - 86%
 
    This unit test also ran very few times due to the hard coded nature of
    the test cases. There are several branches that are not taken, but two 
    of these instances are due to the bug in the code, so this may be an 
    instance where looking at the coverage results could point to a bug 
    just by showing potentially important lines of code that are never 
    being executed.
 
 
 cardtest3 - great_hall
    Every line was run an equal number of times, and all lines were run. 
    This is a short portion of code that calls to drawCard() and 
    discardCard() for most of its work. Testing either of those functions
    would be a necessary part of a thorough test for great_hall.
 
 
 cardtest4 - embargo
    This case in the switch statement also had every line run. There was 
    one branch condition that was only run 10% of the time, but this    
    condition is the failure state for the card and was tested to ensure
    that it did indeed fail when run. The discardCard() function is integral
    to this card, and it is called with the rare state of trashFlag = 1. 
    Again, this function would be important to test in debugging/testing
    issues with embargo. 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 */
