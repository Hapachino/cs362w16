Tanna Richardson
CS362 - Winter 2016
Quiz 2: Random Testing

My random tester uses the rand() method from stdlib to randomly select characters and a string. 
The rand method returns a random integer that can then be used with the modulus operator to get
a random number within a specific range.

For inputChar, I limited the available values to all printable ASCII characters which have a 
decimal value between 32 and 126.

For inputString, I limited the available values to a 6 character string (including null terminator)
composed of only the letters in reset (the exit condition). This restricts the number of iterations
so the program terminates in a reasonable time. If a truly random string were generated, composed of
variable length strings with any printable characters, the program could take days to select the string
"reset" and terminate. My random inputString function skews the randomness to something that will
still produce many iterations for testing, but will terminate in an acceptable time.

In my testing, the limited inputString function typically completed in around 10,000 iterations, 
with some runs taking up to 70,000. If I add only two letters (a and b) to the possible letter
values the number of iterations increases to about 100,000 on average, with some runs taking
up to 400,000 iterations to terminate. Adding just one more letter (c) causes the iterations
to jump to around 500,000 on average. The number of iterations appears to grow exponentially
with the number of possible letters. I didn't test longer strings, but this would add more
possibile values and therefore more iterations as well.

If this were a real project, it would be important to understand the code and the business rules
to evaluate whether restricting the randomness provides the necessary data. It may be important to
test strings of different lengths or strings that include other characters (e.g. non-letters). 
There is a trade-off between true randomness and time to run tests that would need to be 
evaluated on a case-by-case basis depending on the purpose and goals of the software.


