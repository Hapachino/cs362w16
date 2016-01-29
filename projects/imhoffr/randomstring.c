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

How it finds the error:
    testme() runs until it has satisfied all of its conditions for ending the program.  
    First it checks all of the characters given, which also produces all possible states
    and string combinations.  When the state condition is fulfilled, testme() then checks
    all string combinations while at the state.
 
    It took nearly 5000 iterations the first time to finally get an error and only 2354
    iterations the second time to get an error.  If we limited the number of ASCII chars
    used we could fulfill the error requirements much more quickly, but we would also
    lose some coverage.
 
***/

/***
First output (condensed):
 
Iteration 4955: c = ç, s = erett, state = 9
Iteration 4956: c = ì, s = seree, state = 9
Iteration 4957: c = ÷, s = sesss, state = 9
Iteration 4958: c = z, s = sseee, state = 9
Iteration 4959: c = m, s = ertee, state = 9
Iteration 4960: c = †, s = ttsts, state = 9
Iteration 4961: c = %, s = etrst, state = 9
Iteration 4962: c = , s = seets, state = 9
Iteration 4963: c = j, s = rstes, state = 9
Iteration 4964: c = k, s = eeese, state = 9
Iteration 4965: c = , s = seess, state = 9
Iteration 4966: c = , s = reset, state = 9
error
***/

/***
 Second output (condensed):
 
Iteration 2338: c = Ù, s = resee, state = 9
Iteration 2339: c = ”, s = eeere, state = 9
Iteration 2340: c = N, s = teett, state = 9
Iteration 2341: c = Z, s = eetre, state = 9
Iteration 2342: c = }, s = teses, state = 9
Iteration 2343: c = ‚, s = eeees, state = 9
Iteration 2344: c = , s = terss, state = 9
Iteration 2345: c = Æ, s = etete, state = 9
Iteration 2346: c = |, s = erees, state = 9
Iteration 2347: c = ¸, s = seeee, state = 9
Iteration 2348: c = , s = eeees, state = 9
Iteration 2349: c = P, s = ettse, state = 9
Iteration 2350: c = U, s = ssest, state = 9
Iteration 2351: c = H, s = eerse, state = 9
Iteration 2352: c = /, s = srers, state = 9
Iteration 2353: c = û, s = reeee, state = 9
Iteration 2354: c = I, s = reset, state = 9
error
***/