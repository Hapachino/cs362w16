  To begin testing the adventurer card and the smithy card, I began with my unit tests
and figured out how to make them operate in a loop with a specified number of tests.
The next step was to make sure the random variables generated were valid game states
which gave me a lot of trouble because I was actually choosing between 0 and a number
when the game state required 1 as a minimum. This caused seg faults only for certain
values and I was utterly convinced the dominion.c code had major bugs before I realized
this off by one error was the cause of the program failure. I spent the majority of
time only being able to run 4 adventurer tests at a time. It really made clear the importance
( and difficulty ) of creating a robust test harness.

  One way to randomly test the dominion.c would be to fill the struct with random bits and see
what the program does, but this would obviously cause a failure so there needed to be
more strict parameters about what to randomize. I needed to figure out which game states to
randomize and decided to focus on the kingdom cards, and the players cards. This made a great way to
make sure the smithy and adventurer card were doing what they were supposed to be doing.

  After the initial cardeffect call was working in a loop, I could then randomize different
branch coverages by changing game state to cause, for example, the deck to be empty. This
increased branch coverage and led to a few more failed test cases.

In order to ensure correctness, I pulled the latest code from dominion.c into my dominion.c file.
The main difference between my unit tests and these current random tests ( aside from the different
test types) is that previously I had taken out the cards in the card effect function and made them
their own functions. When we introduced bugs in the first assigment, I created a 'bad' version of
each of the tests. When we had to do the unit tests, I could well make assertions with the bad
version so I made 'good' versions ( 'original' versions is probably a better way to put it).
For the previous test coverage, this bloated my dominion.c code and decreased my coverage for the
unit tests but that did not make them any less valid, it only scoped out the parts I needed to test
in case we were'nt supposed to delete the old buggy code. In the random tests, however, there
were no separate functions for the cards under test, so the number of lines in dominion.c decreased
and my coverage as a percentage increased.

In terms of assertion statements, I decided to use my assertion statements from my unit tests and
turn them into if else statements that print out the failure cases with the expected value and the
actual value. This woudl give the developer looking at the failures an easy way to see which inputs
made which tests fail. 

 - - - COVERAGE - - -
 Random Test Card

 Lines executed:25.04% of 639
 Branches executed:24.70% of 417
 Taken at least once:17.51% of 417


 Random Adventurer Test Card

 Lines executed:21.13% of 639
 Branches executed:25.18% of 417
 Taken at least once:16.07% of 417


 Combined

 Lines executed:27.39% of 639
 Branches executed:27.58% of 417
 Taken at least once:20.14% of 417

 Unit test coverage stats

 Lines executed:22.58% of 713
 Branches executed:22.57% of 443
 Taken at least once:15.58% of 443


 Notice the different number of lines. Again, this was due to my stubbing of the 'bad' and 'original'
versions of the tests so naturally the combinde coverage is somewhat higher than for the original
unittest results coverage. However, this does not account for the total jump in increased coverage.
I think the import point to notice here is that there were only two cards tested in the random testing
coverage while there are 5 unit tests being run for the unit test coverage statistics. In short, this
means that the two random tests cover MORE than the 5 unit tests did combined. This is the power of
random testing. Another important point to take away is that even though we do have more coverage in
general, this doesn't mean that the unit tests are any less valid or that we shouldnt have written them.
There are still bugs that the unit tests could catch that our random testers did not. So while the coverage
is increased, that does not necessarily mean that the random tests are 'better' than the unit tests.

This was great for the unit tests because I could call the card function
without calling the cardeffect function. With the random tests, however, I had decided to
just call the cardeffect only. This is one reason why the test coverage increased for the
random tests. There were simply fewer lines of dominion.c.

One area I could improve upon would be to ensure the functions are not inappropriately
changing values for the other players. Most of my tests were focused on the current player
and it would be great to ensure both that the function did the correct operations for the current
player and that the other players game state did not change. A simple way to try this might be
to fill the other player's game states with random values so that if the functions try to manipulate
data in there, the function and the program will fail. A more nuanced approach may be necessary,
but that is where I would begin to improve this test suite.
