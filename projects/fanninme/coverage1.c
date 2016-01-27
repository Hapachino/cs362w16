//Coverage tests

The overall coverage of these tests was very poor, some in part due to functions segfaulting, however there was additionally poor design choices made in terms of exiting the function rather than adding to some kind of running tally of types of failures. A better test suite would rather than exit upon finding an error save a running total of errors enabling the test suite to continue running.

1)unit test 1
File 'dominion.c'
Lines executed:3.60% of 556
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94
Creating 'dominion.c.gcov'

File 'unitTest1.c'
Lines executed:53.33% of 45
Creating 'unitTest1.c.gcov'

implications:
The limited coverage within unitTest itself indicates that the test coverage is less than optimal it may require a different method of dealing with failed tests so that the entire program doesn't stop when a error is found. Additionally branch coverage is poor inplying that conditional statements maybe incorrect.

2)
File 'dominion.c'
Lines executed:3.60% of 556
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94
Creating 'dominion.c.gcov'

File 'unitTest2.c'
Lines executed:54.55% of 44
Creating 'unitTest2.c.gcov'

implications:
The limited coverage within unitTest itself indicates that the test coverage is less than optimal it may require a different method of dealing with failed tests so that the entire program doesn't stop when a error is found. Additionally branch coverage is poor inplying that conditional statements maybe incorrect.


3)
File 'dominion.c'
Lines executed:3.60% of 556
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94
Creating 'dominion.c.gcov'

unitTest3.gcda:cannot open data file, assuming not executed
File 'unitTest3.c'
No executable lines
Removing 'unitTest3.c.gcov'

implications:
The limited coverage within unitTest itself indicates that the test coverage is less than optimal it may require a different method of dealing with failed tests so that the entire program doesn't stop when a error is found. Additionally branch coverage is poor inplying that conditional statements maybe incorrect.

4)
File 'unitTest4.c'
Lines executed:80.00% of 30
Creating 'unitTest4.c.gcov'

File 'dominion.c'
Lines executed:3.60% of 556
Branches executed:5.30% of 415
Taken at least once:3.61% of 415
Calls executed:0.00% of 94
Creating 'dominion.c.gcov'

implications:
The limited coverage within unitTest itself indicates that the test coverage is less than optimal it may require a different method of dealing with failed tests so that the entire program doesn't stop when a error is found. Additionally branch coverage is poor inplying that conditional statements maybe incorrect.

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

