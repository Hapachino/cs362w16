/*****************************************************************************************
*  Random Testing Quiz 2
*  Regina Imhoff
*  imhoffr@oregonstate.edu
*  Date: 01/29/2016
*  Description:
*      Implement a random tester for the function testme() in testme.c that is
*      capable of printing the error message.  You should implement inputChar() and
*      inputString() to produce random values. Write up the development of your random
*      tester and how it finds the error message as randomstring.c. Submit testme.c and
*	   randomstring.c under your onid directory in class github. (under your onid
*	   directory and not under dominion directory).
*****************************************************************************************/

/***

inputChar()
    Made a simple random number generator to pick an ASCII value between 0 and 255.  The
    seed for random is in int main() so I didn't feel it was necessary to seed the 
    randomness twice.

inputString()
    Creates a character array of random length between 1 and 5, which is then referenced
    at the index from 'reset' and the last character is \0, thus 6 characters.  

***/