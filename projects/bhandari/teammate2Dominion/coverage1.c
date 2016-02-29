/*
Overall as a whole for the tests i think my coverage is pretty good, with 100% brance coverage in every test.  Calls executed varies alot but in looking at the .c.gov files most calls that
are not executred are calls to printf statements that only would be called if there was some sort of error my tests detected. all of my tests check though gamestate after every call to a function to 
make sure only the pieces of game state that should change changes.  However in looking at coverage on dominion and knowing how i wrote the test i avoided going into calls of shuffle.  Because of this
there are large portions of the dominion code that my tests did not run through.  I didnt want to include all things like shuffle because if there was a bug inside there it would ruin the tests for many 
of my other unit tests such as drawing cards for smithy or council room.  In the future I think it would be much stronger of a test suite to make sure basic funcitions like drawCard, shuffle, playCard 
are all tests since all the card interations are built off that foundation.  If you know everything is working in the base functions it will let you know its in one of the card interations.

An example of this is a bug found in the fullDeckCount function cause that function to perform incorrectly.  THe only time its called in dominion.c is inside the scoreFor function another which
is another unittest test that I ran.  Because of this it creates more errors inside the scoreFor unittest that are directly a result of calling the fullDeckCount function.  However my unittest found 
another error in scoreFor but i had to confirm it wasnt because of any underlying issues.

Most of my branch coverage is actually just if statements to go to the low call coveages. Because of this its hard to distinguish if I have good coverage on branches that are actually in the code that are
meaninful for part of the unit tests besides just checking in there was a failed test. 

I originally had everything coded with asserts but coverage was unable to be found when the programs were aborted so I changed everything to if statements that are the result of the poor calls executed
coveage.

I think a large area to improve based on the results as more clear messages, while I seemingly found a lot of bugs just getting a bunch of generic "x is different than y" messages withoout more meaningful
info made it harder to actually pinpoint where the bug was exactly.

File 'unittest2.c'
Lines executed:81.03% of 58
Branches executed:100.00% of 40
Taken at least once:70.00% of 40
Calls executed:60.71% of 28
unittest2.c:creating 'unittest2.c.gcov'

File 'unittest3.c'
Lines executed:93.80% of 258
Branches executed:100.00% of 148
Taken at least once:88.51% of 148
Calls executed:81.82% of 88
unittest3.c:creating 'unittest3.c.gcov'

File 'unittest4.c'
Lines executed:74.15% of 147
Branches executed:100.00% of 136
Taken at least once:71.32% of 136
Calls executed:48.65% of 74
unittest4.c:creating 'unittest4.c.gcov'

File 'cardtest1.c'
Lines executed:78.95% of 76
Branches executed:100.00% of 52
Taken at least once:65.38% of 52
Calls executed:56.76% of 37
cardtest1.c:creating 'cardtest1.c.gcov'

File 'cardtest2.c'
Lines executed:89.90% of 99
Branches executed:100.00% of 64
Taken at least once:81.25% of 64
Calls executed:69.70% of 33
cardtest2.c:creating 'cardtest2.c.gcov'

File 'cardtest3.c'
Lines executed:78.21% of 78
Branches executed:100.00% of 58
Taken at least once:68.97% of 58
Calls executed:52.78% of 36
cardtest3.c:creating 'cardtest3.c.gcov'

File 'cardtest4.c'
Lines executed:81.72% of 93
Branches executed:100.00% of 72
Taken at least once:72.22% of 72
Calls executed:65.38% of 52
cardtest4.c:creating 'cardtest4.c.gcov'



*/