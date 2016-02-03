/* -----------------------------------------------------------------------------------
 * David Vogel
 * CS362 Random Testing Quiz 2
 * Due 1/31/16
 * file: randomstring.c
 * Description:
 *    Implement a random tester for the function testme() in testme.c
 *    that is capable of printing the error message.
 *    You should implement inputChar() and inputString() to produce random values. 
 *    Write up the development of your random tester and how it finds the error 
 *    message as randomstring.c. 
 *    Submit testme.c and randomstring.c under your onid directory in class github. 
 *    (under your onid directory and not under dominion directory).
 * -----------------------------------------------------------------------------------
 * Initially, I had to figure out what would trigger the error. The conditions are that
 * the character array *s would have to be the null-terminated string "reset", and
 * the state would have to be 9. 
 * 
 * I started by figuring out what inputString() would have to return and how to get it
 * to correctly return those values. I ran into some trouble with the default call to the
 * function which was: 
 *   char *s;
 *   s = inputString();
 * The string was being overwritten each time I called it, so I changed the function
 * to accept the character pointer as a parameter instead of assigning it to the variable:
 *   inputString(s);
 * Once I was able to assign each index of the string, I wrote a loop that would randomly
 * assign a character from the set of the string "reset" to each index of the string.
 * I could have expanded the set to include many other possibilities, but after running
 * gcov on what I had, I saw that my coverage was near 100% and that there was little use
 * in doing so.
 * 
 * The inputChar() function was easier to set up. Similar to inputString(), I generated
 * a random number and used the set of characters being tested to choose from as a 
 * return value. Again, gcov revealed that coverage was adequate for the software under
 * test.
 * 
 * The following is the gcov output for both statement and branch coverage:
 * $ gcov testme.c
 * File 'testme.c'
 * Lines executed:98.18% of 55
 * testme.c:creating 'testme.c.gcov'
 * 
 * $ gcov -b testme_mySolution.c
 * File 'testme.c'
 * Lines executed:98.18% of 55
 * Branches executed:100.00% of 69
 * Taken at least once:98.55% of 69
 * No calls
 * testme.c:creating 'testme.c.gcov'
 * -------------------------------------------------------------------------------- */