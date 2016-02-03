// File 'smithytest.c'
// Lines executed:79.63% of 108
// Branches executed:86.36% of 44
// Taken at least once:63.64% of 44
// Calls executed:73.17% of 41
// Creating 'smithytest.c.gcov'

// File 'unittest2.c'
// Lines executed:92.31% of 13
// Branches executed:100.00% of 6
// Taken at least once:66.67% of 6
// Calls executed:75.00% of 8
// Creating 'unittest2.c.gcov'

// File 'unittest1.c'
// Lines executed:90.48% of 63
// Branches executed:100.00% of 46
// Taken at least once:73.91% of 46
// Calls executed:62.50% of 32
// Creating 'unittest1.c.gcov'

// File 'unittest3.c'
// Lines executed:69.08% of 207
// Branches executed:38.24% of 68
// Taken at least once:30.88% of 68
// Calls executed:79.38% of 97
// Creating 'unittest3.c.gcov'

// File 'unittest4.c'
// Lines executed:100.00% of 20
// Branches executed:100.00% of 8
// Taken at least once:50.00% of 8
// Calls executed:55.56% of 9
// Creating 'unittest4.c.gcov'

// File 'villagetest.c'
// Lines executed:100.00% of 86
// Branches executed:100.00% of 24
// Taken at least once:62.50% of 24
// Calls executed:70.97% of 31
// Creating 'villagetest.c.gcov'

// File 'dominion.c'
// Lines executed:29.25% of 588
// Branches executed:21.58% of 417
// Taken at least once:19.42% of 417
// Calls executed:14.58% of 96
// Creating 'dominion.c.gcov'


// My unit tests were not as thorough as I expected, which leads to the low coverage in dominion.c. Unittests1 and unittsts2 seem to be okay, but unittest3, where initializeGame() was tested was missing a few things. I could not finish the test because I could not get it to compile with gcov properly and so I had to comment out some of the subtests. The reason for this I was not able to ascertain exactly but it was narrowed down to the part where I was testing the initialization of the supply count according the types of cards in the deck. 

// I left 2 tests remaining and this also gives rise to the coverage number. The smithycard seemed to be low because I some of the business cases were untested for. For example, the status of the victory card piles and the kingdom cards. The adventurer card would not compile with gcov for some reason although the tests runs fine initially. 