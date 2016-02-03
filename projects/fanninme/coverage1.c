//Coverage tests

The overall coverage of these tests was very poor, some in part due to functions segfaulting, however there was additionally poor design choices made in terms of exiting the function rather than adding to some kind of running tally of types of failures. A better test suite would rather than exit upon finding an error save a running total of errors enabling the test suite to continue running.

1)unit test 1: play card function
GCOV 
File 'unitTest1.c'
Lines executed:87.80% of 41
Branches executed:77.78% of 18
Taken at least once:55.56% of 18
Calls executed:95.00% of 20
Creating 'unitTest1.c.gcov'

dominion.gcno:cannot open notes file

implications: While the coverage of the unit Test is good it appears there maybe a error in the dominion file which is being caught by the developers tests.
Because the error is general we can't be sure what's causing the error without refactoring to provide a unique error code for each possible cause of failure of their tests.

2)unit test 2: game over function
test 1:
File 'unitTest2.c'
Lines executed:86.67% of 45
Branches executed:100.00% of 16
Taken at least once:75.00% of 16
Calls executed:91.30% of 23
Creating 'unitTest2.c.gcov'
test2:
Lines executed:90.48% of 42
Branches executed:100.00% of 16
Taken at least once:75.00% of 16
Calls executed:100.00% of 20
Creating 'unitTest2.c.gcov'

dominion.gcno:cannot open notes file

implications:We know from the errors print out that the supply count is some how getting decrimented below 0 (which should end the game).

3)unit test 3: end of turn function
unitTest3.gcda:cannot open data file, assuming not executed
File 'unitTest3.c'
No executable lines
Removing 'unitTest3.c.gcov'

implications: The end of turn function segfaults ending the unitTest program early and resulting in a incomplete coverage file.
The dominion code most likely has a out of bounds access error and it would be best to run through a debugger or add a series of print statements to determine where in the function the segfault is occuring.

4)unit test 4: full deck count
dominion.gcno:cannot open notes file

File 'unitTest4.c'
Lines executed:87.23% of 47
Branches executed:100.00% of 16
Taken at least once:62.50% of 16
Calls executed:92.31% of 26
Creating 'unitTest4.c.gcov'

implications:
There is good branch coverage but not all lines were executed nor were all branches taken at least once implying that we are not generating test conditions which will make the program branch (and there by test by executing that code).

5)Adventurer
File 'dominion.c'
Lines executed:3.60% of 556
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94
Creating 'dominion.c.gcov'

File 'cardTest1.c'
No executable lines
Removing 'cardTest1.c.gcov'

implications:
The segfault which occured made this test virtually unusable, this code needs be corrected to allow better testing. The limited coverage within unitTest itself indicates that the test coverage is less than optimal it may require a different method of dealing with failed tests so that the entire program doesn't stop when a error is found. Additionally branch coverage is poor inplying that conditional statements maybe incorrect.

6)Feast
cardTest2.gcda:cannot open data file, assuming not executed
File 'cardTest2.c'
No executable lines
Removing 'cardTest2.c.gcov'

File 'dominion.c'
Lines executed:3.60% of 556
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94
Creating 'dominion.c.gcov'

implications:
The segfault which occured made this test virtually unusable, this code needs be corrected to allow better testing. The limited coverage within unitTest itself indicates that the test coverage is less than optimal it may require a different method of dealing with failed tests so that the entire program doesn't stop when a error is found. Additionally branch coverage is poor inplying that conditional statements maybe incorrect.


7)Smithy
File 'dominion.c'
Lines executed:3.60% of 556
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94
Creating 'dominion.c.gcov'

cardTest3.gcda:cannot open data file, assuming not executed
File 'cardTest3.c'
No executable lines
Removing 'cardTest3.c.gcov'

implications:
The segfault which occured made this test virtually unusable, this code needs be corrected to allow better testing. The limited coverage within unitTest itself indicates that the test coverage is less than optimal it may require a different method of dealing with failed tests so that the entire program doesn't stop when a error is found. Additionally branch coverage is poor inplying that conditional statements maybe incorrect.


8)Village Card

cardTest4.gcno:cannot open notes file

File 'dominion.c'
Lines executed:3.60% of 556
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94
Creating 'dominion.c.gcov'

implications:
The segfault which occured made this test virtually unusable, this code needs be corrected to allow better testing. The limited coverage within unitTest itself indicates that the test coverage is less than optimal it may require a different method of dealing with failed tests so that the entire program doesn't stop when a error is found. Additionally branch coverage is poor inplying that conditional statements maybe incorrect.

