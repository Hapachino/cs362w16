I first started writing the inputChar function because I knew I wanted
to use this function in order to make a random string. This started 
with me looking up the ascii table so that I could choose which 
characters that I wanted to use. I only wanted "normal" characters, 
meaning that I did not want things like "start of heading" and 
"unit separator". I also wanted to exclude "DEL". This is done by
the mod by 126 and then adding 32 so that I can jump straight to the 
"space" character. This made the random number fall between 32 and 
126, which are mapped to my wanted characters with a type cast.

The inputString function was a bit more confusing. I assumed that 
the string was to be only letters, so I made it only give letters 
a-z (97-122). If the character generated was not in between these
two numbers, then it regenerated. Once it found one, it stored 
the letter in the string (character array). Finally, it added the 
null character at the end to make it a C string. 

All together, it finds the error message by first going through
each case of characters, moving one step at a time, and then looking
for the string to say "reset". After enough iterations, each case 
will be hit and the error message will be found because there is a 
chance that each character will occur, and every possible combination
of a-z will happen by random. 

I first found the error message with a seed of 2. I wanted to make 
sure I was using the same seed in development, and then start doing
a couple more. Finally, once I saw some consistency, I used time(NULL)
and found the error a few more times. 

I tried to put a timer on there, but I realized I did not truly need 
it. I could not get clock() to return anything except 0, and it was
not worth the effort. 