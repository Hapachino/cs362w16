assignment 3 coverage


File 'unittest1.c'
Lines executed:97.50% of 40
unittest1.c:creating 'unittest1.c.gcov'


File 'unittest2.c'
Lines executed:84.09% of 44
unittest2.c:creating 'unittest2.c.gcov'


File 'unittest3.c'
Lines executed:80.00% of 60
unittest3.c:creating 'unittest3.c.gcov'


File 'unittest4.c'
Lines executed:95.12% of 41
unittest4.c:creating 'unittest4.c.gcov'


File 'cardtest1.c'
Lines executed:96.67% of 30
cardtest1.c:creating 'cardtest1.c.gcov'

File 'cardtest2.c'
Lines executed:97.30% of 37
cardtest2.c:creating 'cardtest2.c.gcov'

File 'cardtest3.c'
Lines executed:100.00% of 34
cardtest3.c:creating 'cardtest3.c.gcov'

File 'cardtest4.c'
Lines executed:100.00% of 34
cardtest4.c:creating 'cardtest4.c.gcov'

Lines executed:31.63% of 588
Branches executed:24.94% of 417
Taken at least once:22.30% of 417
Calls executed:20.00% of 100



My test suite had strong cover for the unittests
They had coverage ranging from 80 to 100% this means that the test program
worked as written as it covered the test code that was written. the lower ones
(80%) had if statements that branch when the test failed so that code was
never activated.

This only means that what was written was executed. so if I had not cover something
in the the test code those bugs would not be found. examples include if I called another
producre( which would be tested in a different test) that code would read as
successfully ran even if the call function was faulty.

the program only had 30% line coverage with 25% branch coverage. This is expeceted
as I only tested 4 functions and 4 cards. I did not test the main game or the
scoring functions. This means that my suite is not large enough to call the
program sufficantly tested. More test will be needed.
