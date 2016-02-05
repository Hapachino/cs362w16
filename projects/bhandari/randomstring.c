//Rishi Bhandarkar
//Random Testing Quiz 2 - CS 362

inputChar() Method
The testme() method checks the randomlly generated character against 9 different characters. To randomlly generate
those characters, the inputChar() method randomlly generates a number between 33 and 126. These are the ASCII values for all
printable characters, and so it includes all 9 of the characters testme() uses.

inputString() Method
The testme() method is looking for a 5 character string with characters 'r', 'e', 's', 'e', 't', and ending with a null terminator '\0'.
To generate this string, inputString() randomlly generates 5 integers between 97 and 122 and stores them in a character array. This 
I am employing 'white box' testing by looking at the code under test and designing tests to fit it. In the case of inputString(), I chose
to limit the random number to 97 - 122 to reduce the amount of possibile strings generated. In this case, there is a 1 in 11.8 million chance
of generating the matching string. If I were to expand the possible characters to all printable characters as I did in the inputChar() method,
there would be a 1 in 7.3 billion chance of generating the proper string, which is incredibly large.

Using these implementations of inputChar() and inputString(), it took around 5 million iterations to print the error message.