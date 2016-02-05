randomChar
First I began writing randomChar by producing totally random ASCII values. Decimal numbers between 0 and 127.
I saw that in order to print the error message 'state' needed to be set to 9. The only way to get state
to equal 9 was by having randomChar() generate one of the following characters: '[', '(', '{', ' ', 'a'
'x', '}', ')', ']' so I decided to constrain the domain of possible input to be
32 - 125. 32 being the ASCII space character (the lowest value in the range) and 125 being the ASCII right-curly brace ('}')
the highest value in the range. This created the '9' state in a sufficient number of trys.


randomString
First I began creating strings with completely random characters but the chances
of generating interesting input, potentially exposing the underlying program error was very low (millions of runs with no result).
I then placed a domain constraint on values randomString() would generate by creating a special
array to draw values from. This still made producing the 'reset' string unlikely
so I constrained the possible string length input would return so it would only produce strings
with a length of 6 (inlcuding '\0'). This seemed to overly contrain the input domain so I added a
conditional that would test if a separate random value was divisible by 9, only if it was divisible by 9
would the input come from a totally random string of characters, otherwise it would pull from the constrained
character domain. This approrach required ~3,000 iterations to produce the error which seemed to strike a
fair balance between random value testing and not requiring to much computing power.
