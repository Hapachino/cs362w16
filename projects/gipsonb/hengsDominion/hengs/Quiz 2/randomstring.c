Stephen Heng
CS 362, Winter 16
Random Testing Quiz 2
1/30/2016

For the function inputChar(), I created a char that would generate randomly from 0 to 94. Since the ASCII table has only 128 characters,
for which the first 32 are control characters and could be eliminated from the random generator. I first divided the randomizer by
95, which will give you a range of 0-94 and added 32 to it, so that the characters will be printable. It also eliminates the 128
character for which is also a control character. Afterwards, it returns the random number, from 32 to 126 to the function to determine
the state of the test.

For the function inputString(), I first created a char of 5 characters with the letters in the "reset" to end the program, which consists
of 'r','e','s','t', and '\0' the null terminator. I then create another char array to store the possible indexed chars that contain
the "rest/0" characters. I allocated enough memory for the return string. Afterwards, I created a for loop that will copy the chars
from the set of characters into the return string and set the final index of 5 to the null terminator. This process is much quicker for testing
than if I set randomized characters for my char variable that ranged from a-z. Instead I limited it the characters that are required and it helps
make the program run faster.
