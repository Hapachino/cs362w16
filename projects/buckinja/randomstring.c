/*
Janel Buckingham
CS 362 Winter 2016
Random Testing Quiz, week 4
*/


/*This gets to state 9 within a second or so by trying all chars 
in ascii range 32 - 127.  Since the number count is fairly low, and 
we are able to remember that a "state" character was seen previously,
finding state 9 ends up being trivial.*/
char inputChar()
{
    int asciiRange = 127 - 32;
    char ch = (rand() % asciiRange) + 32;
    return ch;
}

/* This random tester was able to find the error after about
2 billion iterations, so within a couple of hours on the school
servers.  Testing for a wider range of characters or a less-specific 
string size sends the testing time through the roof fairly quickly!
I originally tested with varying string sizes and the full range of 
characters and symbols, but realized that that many permutations would 
take years to complete at the rate the computer was running, so I 
stuck to a single string length and eventually had to scale back to 
only lowercase letters in order to see the test complete.
*/

char *inputString()
{
    static char array[6];
    int asciiRange = 26;
    char ch;
    int i;
    for (i = 0; i < 5; i++) {
        ch = ((rand() % asciiRange) + 97);
        array[i] = ch;
    }
    array[5] = '\0';
    return array;
}
