Random Testing Quiz 2
anderse7@oregonstate.edu
Due Sunday by end of day.

Points possible: 20

Description: Implement a random tester for the function testme() in testme.c that is capable of printing the error message.  You should implement inputChar() and inputString() to produce random values. Write up the development of your random tester and how it finds the error message as randomstring.c. Submit testme.c and randomstring.c under your onid directory in class github. (under your onid directory and not under dominion directory).

I wrote two versions of this code.  The first version use a well known algorithm to get a random character between 32 and 126. I used  (char)((rand()%95)+32); for the inputchar() e.g. https://ideone.com/glI17.  I assert that the value of randomNum is between 32 and 126.

For the inputstring function, I wrote the function using an array (array) that will hold the letters that the testme() function is looking for before 
it prints out error.  I added the \0 terminating character to the array (otherwise it runs forever!). I Then allocate space for the randomstring.  This is used in a for loop to randomly run through and hold the values until 
the string reset is returned and then the program printed error.

A version of the same thing using the rngs library
Consistent witht he dominion game, this version is essentually the same but this version uses the random() & seed functions of the rngs library.

The tester seeds a random test and creates random char with ASCII values between 32 (space) and 126 (~). The 
test will try every combination of values between ASCII 32 to 126 for the characters and between 97 (a) 
and 126 (~) for the string. It takes a very long time for this test to run all the possible 
combinations of values. Once it finds the correct combination of values it will error and exit 
the program.

At first I tried to generate the code by only using random values between 0 and 126. The code would never exit so I thought I needed to make it more efficent. I did this by limiting the inputChar to values between 32 and 126 because this is the range of all the characters in the test function and I limited inputString to 97 to 126 because it is the range needed for the strings in the test function.