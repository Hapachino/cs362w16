I fixed adventurer by un-commenting code that was commented and thus not running.
I fixed smithy by letting a loop iterate over a new variable instead of a variable that already meant something, causing it to misbehave.
I took out an unnecessary if-statement from council room causing it to branch when it shouldn't.
I also took out an unnecessary if-statement from village causing similar problems.
For Great Hall, I uncommented some code which was disrupting its behavior.

These fixes agreed with Gariepyt's analysis of my cards. The test was segfaulting on my smithy, however since my tests worked fine on smithy,
the error must be in the way the test was written. There were also a few bugs Gariepyt found which were in code I never altered from the
default, which leads me to believe that either Gariepyt's tests, or the Dominion game itself, are flawed (outside the realm of my ability to fix).

My other teammates have not posted analysis of my code.