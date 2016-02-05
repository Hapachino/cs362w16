Samuel Ford
CS362-400, Winter 2016
Random Testing "Quiz"

Implementation of inputChar() and inputString()
===============================================

inputChar()
-----------
inputChar() is pretty straightforward since you know that you're only dealing with one character.  Assuming we're only working with ASCII characters (and not extended ASCII), that's 128 potential characters.  We can return a random character between 0 and 127 using a simple call to rand().  This usually takes somewhere less than 2000 iterations to reach state 9 (which you can find by running testme with s set to "reset").

If you think about it some more, the first 32 ASCII characters are control codes, so we can probably avoid those.  Additionally, the last character in that range (127) is DEL, so we can probably avoid that as well.  That leaves us with a range of 32-126 (inclusive) and this is how I set up my inputChar() function.  However, considering the relatively small number of iterations required to reach state #9 using the larger set of input characters, this doesn't end up having a tremendous effect on the overall execution time.

State is persisted between loops, so the program will proceed to the next state as long as inputChar() returns the correct character *once* for each state.  inputChar() will return one of 95 potential characters, so it usually doesn't take long to cycle through all the potential characters and move to the next state.  In my testing, it wasn't unheard of for testme to reach state #9 in less than 1000 iterations (even as low as 500 iterations).


inputString()
-------------
It doesn't matter what inputChar() returns once we've reached state #9 and we now have to receive the correct string from inputString() to print the error.  We don't have a concrete restriction on how long the string that inputString() returns should be or which characters should be used, so it's completely open-ended.  As such, it's very easy to implement inputString() such that it's *technically* possible to return "reset" but it could take a very long time.  If you were doing random testing to try to find any unknown bugs, then it's quite possible that you could stop the tester before it uncovers any existing bugs.

That having been said, I initially implemented inputString() to produce quite a bit of randomness while still being technically capable of generating the correct string.  The function would populate a string containing 1-5 characters (generated using inputChar()) followed by a null terminator.  I let this version of testme run for quite a while and it never triggered the "error" message.  With this setup, you not only have to generate the correct string but you also have to generate a string of the correct length.  It's possible that inputString() would eventually generate "reset" but it would likely take quite a long time.

Testme is always looking for a string with 5 characters and a null terminator, so I further restricted inputString() to only generate strings of that length.  I ran testme with this setup for 30 minutes and it didn't generate the correct string (after trillions of iterations).  This setup had a better chance of hitting upon the correct string but it would still take a considerable amount of time to accomplish it like this.

Continuing down this path, I restricted the range of characters used to generate strings to 65 (A) to 122 (z) (which also includes a small number of special characters between Z and a).  I ran this version for a while and it didn't produce the error message either.

I then further restricted the range of characters used to generate strings to 97 (a) to 122 (z).  After letting this run for a few million iterations, the error message finally presented itself.


After having made the error message display once, I started backtracking to see how much randomness I could reintroduce while still displaying the error message.  To speed things up during testing, I temporarily disabled the trace statement and added it before the "error " message (this isn't present in the final code).  Running the test program in this way, I was able to confirm that a couple of the previous implementations of inputString() would, indeed, print the error message after many iterations.

In the end, the range of characters used to generate the string had a much greater effect on the number of iterations required to generate "reset" than whether the generated string is fixed length (5 chars + null terminator) or variable (1-5 chars + null terminator).  If you generate nothing but 5-char strings with null terminators but you use the range of characters that my inputChar() implementation produces, then it takes too many iterations for me to let it finish running

The implementation of inputString() that I settled on generates strings with a length between 1-5 chars + a null terminator, using only lowercase alphabetic characters (a-z).  This usually takes between 10-200 million iterations, so it tries to split the difference between too random and not random enough.  [If you modify the implementation to generate strings of 5 chars + a null terminator then it usually takes less time but can run to around 150 million iterations if you're unlucky.]

Overall, I feel like it may be easier to determine what's too random and what isn't random enough when working within a real program (though I'm sure I'll have the opportunity to test this idea soon enough).
