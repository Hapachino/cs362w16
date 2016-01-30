//
//  randomstring.c
//
//  Created by Patrick Burrell on 1/24/16.
//  CS 362 - Winter 2016
//  Quiz 2 - Random Testing
//
/*
 
 inputchar()
    My input character function returns a random character from the 256 available 
 ASCII characters. I implemented this by generating a random integer with a call
 to rand() and then doing a modulo operation with a value of 256. This returns an 
 integer between 0-255 which is converted to the corresponding ASCII character when
 cast as a char. This does mean that my inputChar function will return things like 
 the Null character, carriage return, or bell with equal frequency as any letter, 
 but the function only asks for a single character to be matched, so I didn't feel
 the need to limit the pool of possible characters any further. 
 
 inputstring()
    The inputstring function needs to return 'reset' in order to get the program to
 print the error message and exit. There were several different ways I thought about
 implementing this. My first method was to randomize the length of string (the array
 size) to between 1-6, and then randomly fill this random-length string from a pool
 of 26 lowercase letters. This ran for far more iterations than I had the patience
 for, so I dramatically increased my odds of returning 'reset' on my final 
 implementation. In this case, I kept the random length generator but filled the 
 random-length string with characters limited to the pool of "helpul" letters: r, e, 
 s, and t. This implementation consistently returns the error message in under 
 100,000 iterations. 
 
 */
