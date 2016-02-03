Shaun Stapleton
CS 362
Assignment 3

Use gcov to measure code coverage for all of these tests. Report your findings by discussing your tests' 
coverages (statement, branch, boundary, etc.), and describe their implications for the tests in a file called 
coverage1.c, also checked in to your dominion directory. I want you to look at the dominion code coverage and 
find out what parts of your code are not covered so that in future you can improve your test suite. 

I ran all of my test files and then had gcov output the results below of my coverage. This is additionally included
in my unittestresults.out file at the bottom after all tests.

Lines executed: 36.14% of 581
Branches executed: 40.72% of 415
Taken at least once: 31.57% of 415
Calls executed: 26.00% of 100

From an overview perspective, I was able to cover over a third of the statement lines with my tests and over
forty percent of the branches were executed. I feel that these were promising statistics to see as I was at least
testing the functionality of a large portion of the file. However when considering that of the forty percent of
branches taken that thirty one perent were taken at least once I wonder if that means that I was not iterating
over the branches as much as I would ideally want in the future for testing each edge case and boundary. I feel
like with the time available for the assignment available I was able to accomplish a good portion of tests based
on these 8 unit tests. I know that I could accomplish a more robust test suite that would eventually put to use
several other functions.

Looking at my particular unit tests, I see that I could have more rigorously tested the boundaries of every
if statement or loop to a further extent. I did some testing on out of bounds cases in the remodel and getCost()
unit tests, however I believe I could throw more tests in general at all of the cases. The gcov file does a good
job of providing me with the ways in which I could have improved and it is encouraging to see that I was able to
test more functions in the file than I was intending as the coverage percentages and file reveal. For example,
the drawCard() function was called 710 times and this was simply as part of my testing. I would say my main
takeaway would be that I would want to stress the system a little more in the future with each kind of test
rather than going through and coming once or twice that they do what I want them to do.