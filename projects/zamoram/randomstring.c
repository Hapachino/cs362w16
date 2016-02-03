Test plan for testme.c

The objective of the testme program is very simple. The main function calls for a random single character and a random 
string of characters. Then, depending on the value of the character, a variable state is set to a number 1 through 9. Next, 
the error line is printed only if two conditons are met, 1) that the single character was ']', thereby setting state to 9, and
2) that the string spells 'reset' with a '\0' character at the end.

For my test, for the character input, I decided to have it randomly select a value from the list of possible characters that 
would change the state variable. This worked out just fine but I decided to include all possible printable ASCII characters.
This broadened the test suite while still keeping the amount of time the test runs short.

The input string function could not rely on pure randomness like the previous function. inputChar only need to match one
character but inputString needs to match 5. If we did 26 possible characters in each spot, the possible result is exponentially
huge. Instead, I used a string of characters from the word 'reset' and chose from that list. Even simply doubling that list with
four more possbile characters causes the test suite to run for far too long. In the end, choosing from the smaller list for inputString
and chosing from a bigger list for inputChar gives me an acceptable test to check the requirements of the function.