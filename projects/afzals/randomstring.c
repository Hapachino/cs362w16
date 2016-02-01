In building my random tester I first looked through the code
to understand what was going on in the code and how to reach
each step of the code. This code was fairly simple to understand
as it is just a loop that cycles through your random functions, and 
first needs to get to state 9 by getting each of the random symbols
that are in the code. Then you need for inputString() to return the
string "reset\0". I tailored the tester to break the code in an efficient
manner, because that was the goal of this, so I used arrays in each of
my functions that limited the possible random values that were generated.
In inputChar() the array contained each of the symbols required to increase
a step, and a random number was generated, then the symbol at that array
location was returned. In inputString it contained "rest\0" as this contains 
all of the letters in reset. I used a for loop to run 6 times and each time
generate a random number and add a character to the char array. I tested my 
tester several times and it took between 3000 and 55000 iterations to get
the error message. I could have expanded the amount of possible random characters
in each array, which would have made my tester more random, but it seemed
inefficient. By understanding the code and controlling the amount of 
possibilities it made the tester run in a more reasonable and efficient amount of 
iterations. If I had done true random then this would have taken exponentially 
longer. I attempted just adding the letters a and b to the array in inputString(), 
and by adding those 2 extra characters when I ran it the first time it took almost
250000 iterations to get the error message. It really emphasized how inefficient
truly random testing is, and how important it is to control those variables
that you can control without affecting the effectiveness of your random tester.

