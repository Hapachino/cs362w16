/*

Chris Loomis

Firstly, I must apoligize on the lateness.  Yesterday I was working on the project and thought I
saw their was a quiz also.  I logged in and did not see the quiz listed on the left side of
Canvas.  After searching between classes I figured I must of been mistaken and continued working
on the project.  I read Piazza today when I clocked in at work and found that I had been right.
Thus I have hurredly put this together in hopes you will forgive my tardiness.

inputChar() generates a number between 32 and 125.  This range contains all the ascii characters
we are required to find to progress through the different states.

inputString() generates a random string that is 5 char long ending in a null char.  It reuses
function inputChar() to generate the random string.

The testme() function will enter the while loop and continue until it hits the error message as
there is no way for it to break out of the loop.  Admittedly, since I know the code it may
of been better to generate random characters for inputString() that are withing the range of
'e' - 't', or going even further, randomly assign the characters needed.  I did not feel that
was the intention, so I reused inputChar().  I believe it could take some considerable time for
this to print the error message.

*/