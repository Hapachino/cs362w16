/*

For implementing a random test for testme.c I first made a random char on the ascii chart from 32-126 inside the inputChar() function.  Inside inputString() I allocated memory for a array with 6 total elements, the first 5 being filled by calling inputChar() and the last one having null. This was then checked with the code already inside testme.c to try and find the error. 

when i set this up orginally because of the large amount of options that inputChar() could produce the error would never pop up in a reasonable amount of time.  In order to make a more refined test i limited the options that inputChar() could pick from to a list of the 13 chars that were of interest inside testme.c.  After doign that the error would pop up in a reasonable amount of time.  My test iterations below:

Number of Iterations Until Error:
1. 176421 
2. 144543
3. 317166
4. 252862
5. 282806

*/