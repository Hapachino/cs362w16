First of all to get the makefile to work just enter either "make randomtestcard" or "make randomtestadventurer". These
commands will compile run and output the results to either randomtestcard.out or randomtestadventurer.out. These 2 
random testers achieved much better coverage than the non random ones. Due to the fact that I know these functions
have errors I used print statements and only ran the random tester 50 times. If I were using this tester to identify 
the bugs I would use assert's with smarter print statements during fail states to help identify what caused
the failure. One good thing about the random tester is that it provides much easier boundary coverage. One thing I 
should probably do is to include tests which should fail, in order to identify that the function does what
it should do when it fails. My coverage on the 2 cards I tested was 100%, they both accessed every branch and
statement of the functions. I have found that it is a little bit hard to specifically focus on the function I 
am testing, when the card functions call other functions which have errors. It is a good lesson in testing, however,
as I realize this is probably a complication often encountered in real world testing. You can write a test for a function
but finding errors does not necessarily mean there is an error in that function in particular. It just lets you know that
there is an error that you can find by executing that function. In real world testing this would inform new tests that you
create in order to then narrow down where exactly that error is coming from. I have found testing to be quite fun, while 
learning about it this term, because of all that goes into it. Another important thing I learned from the random tester 
is that selecting which values to randomize and how to randomize them is crucial. For dominion there are some variables that 
really do not matter if you randomize them, and it would almost hurt more than it would help if you did randomize them. Also 
it is very important to make sure your range of random values is correct, otherwise it can cause issues that aren't necessarily 
related to whether the function actually does what it needs to do.