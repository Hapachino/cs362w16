For inputChar(), I created a character array that included every letter of the alphabet and the other possible special characters needed 
to produce the error message ('{', '[', etc.).  I then determined a random array index and chose the character at that index as the chosen
character for each iteration.  I felt that this was sufficient randomness. Also, the odds were still fairly good to produce the characters 
needed to cause the error message to print.

For inputString(), the problem was a little more complex.  First, I tried something similar to above. I created a character array that included
every letter of the alphabet. I then determined a random array index and chose the character at that index as the character for the first index
of the random string and repeated that until the end of the random string is reached.  I left this implemenation running for a while and wasn't 
able to produce the error. So, I redesigned my approach a bit.  I redefined the character array so that it only contains the letters in the string
that produces the error(r, e, s, t). I also included 'e' twice since it appears twice in the error producing string.  Then I determined a random index 
as before and assigned each letter of the random string in the same manner. This approach granted me the error message in 435 iterations.

In the end, I ended up including both methods in testme.c.  The default method is the faster, less random version. Changing the value of the mode variable
in inputString() activates the slower, more random version. I'm sure that the slower method will eventually (after many hours) produce the error message.  
Overall, I learned that pure random testing can sometimes be impractical. Providing some constraints to the randomness can make random 
testing more practical.

Compilation Instructions: gcc -std=gnu99 -o testme testme.c
