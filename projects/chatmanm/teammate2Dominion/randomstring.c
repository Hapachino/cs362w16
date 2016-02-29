/********************************************************************************************************************************************************
*** Filename: randomstring.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Due date: 1/31/2015
*** Random testing quiz 2
*** Description:  Implement a random tester for the function testme() in testme.c that is capable of printing the error message.
***               You should implement inputChar() and inputString() to produce random values. Write up the development of your random tester
***                and how it finds the error message as randomstring.c.
***
********************************************************************************************************************************************************/

/*
inputChar()
     This function will return a random printable ASCII character between the range of 32 and 126.

inputString()
     This function will create a character array to make a five letter string with a null terminator. 
Each of the 5 letters are randomly selected from the lower case alphabet in the ASCII table.
Only the lowercase alphabet characters were used as it would take an extreme amount of time to randomly form the string "reset". 


How the random tester finds the error message: 
     The testme() function will call inputChar() and inputString() to receive random characters and strings. It will then check them for specific characters to 
be returned in a certain order which will be state 9. Once, state 9 hs been reached, it will check for a string to be returned as "reset" with a null terminator.

I found that state 9 was reached very fast as opposed to reaching a string return of "reset".
It is clear that the benefit of random testing would be that it can cover a large amount of test cases, but that it will take a very long time. 



Sample runs of testme.c:

Iteration 15822296: c = E, s = ifnrw, state = 9
Iteration 15822297: c = P, s = tapee, state = 9
Iteration 15822298: c = r, s = eodyc, state = 9
Iteration 15822299: c = B, s = ptnny, state = 9
Iteration 15822300: c = ", s = xiyxj, state = 9
Iteration 15822301: c = K, s = ftzsl, state = 9
Iteration 15822302: c = 6, s = nexek, state = 9
Iteration 15822303: c = f, s = equio, state = 9
Iteration 15822304: c = O, s = reset, state = 9
error flip2 ~/cs362/randomQuiz 72%



Iteration 2680439: c = ], s = qceli, state = 9
Iteration 2680440: c = r, s = ewnxh, state = 9
Iteration 2680441: c = y, s = pdcuf, state = 9
Iteration 2680442: c = X, s = ykgmj, state = 9
Iteration 2680443: c = x, s = mullu, state = 9
Iteration 2680444: c = :, s = fmrka, state = 9
Iteration 2680445: c = j, s = qeygd, state = 9
Iteration 2680446: c = ", s = nslpm, state = 9
Iteration 2680447: c = P, s = hmcpz, state = 9
Iteration 2680448: c = *, s = qngda, state = 9
Iteration 2680449: c = 5, s = sgoms, state = 9
Iteration 2680450: c = ], s = liulo, state = 9
Iteration 2680451: c =  , s = reset, state = 9
error flip2 ~/cs362/randomQuiz 84%

*/