So the first thing that jumps out at me is that in all of the criteria I 
never get above ~20% coverage. More coverage in any of the metrics would
be a significant improvement.

One of the difficulties I've found in writing the tests is that most of what
we need to test seems to be side effects ie when a card has an effect on the
game state it can't be tested by looking at the return value but rather by
examining the game state struct. This makes the tests challenging in a couple
of ways. First it requires that the test know all the desired side effects.
While this is a headache it's pretty much what we're testing for. The second
part that makes this hard is that the tests and the dominion code both
inspect and modify the low level model of the game state. This makes the test
code very complex.

Moving forward I would refactor some of the low level data access into an api
that could be solidly unit tested from the ground up - and then refactor the
domain functions to rely on those low level methods.
