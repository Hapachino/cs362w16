I used gcov to measure the code coverage for my tests.
For my cardtest2, cardtest3, and cardtest4 I had 100% branch coverage. I did
not have good boundary coverage, and this is definitely something I could improve.
Implementing random testing would go a long way toward doing this easily, or 
I could have manually added more extreme values to test.
On cardtest1 my test does not go into the else statement. This indicates
that the first 2 cards drawn were both treasure cards, and it is not 
adding anything to the temp hand. This is a big problem. I attempted to
manually set the value of the first card but it still was not going into 
that portion of the code. With a little more time I think I could have figured
it out, but I ran out of time so I just had to leave it. It could just be a bug
that is keeping the code from getting to that branch. My test for the fullDeckCount
function had very good coverage. For the isGameOver function it does not reach
the case where supplyCount equals 0, which is somewhere I could improve my testing.
I got 100% branch coverage on the updateCoins function, reaching every part of the code.
A general weakness of my testing was my boundary coverage. I need to make sure to test
more extreme inputs. I mainly focused on trying to just create basic tests that
would have good branch and statement coverage, I will ensure next time that I get 
better boundary coverage.