
Below in this document you will find the coverage summaries for all tests written and the overall coverage
for the dominion.c file. I've included them as a reference to what we will talk about here.

Overall I am happy with the total coverage for my tests individually. From what I've looked at in the
coverage files themselves only the "test failed" or "test passed" branches are not running. Of course
which doesn't run depends on whether the test passes or fails. This is pretty much what I expected as I
didn't design the tests to follow both paths; only the path that was applicaple to the program being
tested. One aspect of note though is in unittest4.c where I found I do miss some coverage testing
whether a kingdom card is not in the game or if its pile is empty. In the future I'd want to make sure
this part of code ran. 

The way I went about designing the tests had a large impact on the overall coverage of dominion.c. I 
found that in instances where I used more of the built in functions to test other dominion functions
I could increase the overall coverage. I didn't think this was very sound testing in some of the tests
I left those functions out. It does demonstrate how careful you have to be when interpreting your coverage
data though. For the ammount of actual code I tested in dominion.c I believe 34.3% coverage is pretty good.
If I were testing the entire program as a whole of course I'd want this number to be higher.



File 'dominion.c'
Lines executed:34.30% of 589
Branches executed:30.77% of 429
Taken at least once:27.51% of 429
Calls executed:19.39% of 98
dominion.c:creating 'dominion.c.gcov'



File 'unittest1.c'
Lines executed:100.00% of 33
Branches executed:100.00% of 12
Taken at least once:75.00% of 12
Calls executed:86.67% of 15
unittest1.c:creating 'unittest1.c.gcov'


File 'unittest2.c'
Lines executed:97.06% of 34
Branches executed:100.00% of 16
Taken at least once:87.50% of 16
Calls executed:92.31% of 13
unittest2.c:creating 'unittest2.c.gcov'


Lines executed:100.00% of 69
Branches executed:100.00% of 58
Taken at least once:96.55% of 58
Calls executed:90.00% of 10
unittest3.c:creating 'unittest3.c.gcov'


File 'unittest4.c'
Lines executed:91.67% of 36
Branches executed:85.71% of 14
Taken at least once:71.43% of 14
Calls executed:83.33% of 18
unittest4.c:creating 'unittest4.c.gcov'
-Card not in game or empty pile code not ran


File 'cardtest1.c'
Lines executed:86.79% of 53
Branches executed:100.00% of 22
Taken at least once:68.18% of 22
Calls executed:80.56% of 36
cardtest1.c:creating 'cardtest1.c.gcov'
- Test failed code not ran


File 'cardtest2.c'
Lines executed:85.25% of 61
Branches executed:100.00% of 24
Taken at least once:62.50% of 24
Calls executed:78.57% of 42
cardtest2.c:creating 'cardtest2.c.gcov'
- Test failed code not ran


File 'cardtest3.c'
Lines executed:85.25% of 61
Branches executed:100.00% of 24
Taken at least once:62.50% of 24
Calls executed:78.57% of 42
cardtest3.c:creating 'cardtest3.c.gcov'
- Test failed code not ran


File 'cardtest4.c'
Lines executed:88.24% of 51
Branches executed:100.00% of 22
Taken at least once:72.73% of 22
Calls executed:80.00% of 30
cardtest4.c:creating 'cardtest4.c.gcov'
- Some passed test messages don't run because of failure and vice versa
