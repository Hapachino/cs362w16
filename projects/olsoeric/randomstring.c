/************
 * Eric Olson
 * Random Testing - Quiz 2
 * Quiz Report
 ************/

//Alterations to testme.c
In addition to implementing inputChar() and inputString() functions, a couple minor changes were
made to testme.c within the testme() function in order to faciliatate the testing.  
These include:
  -  Allocating memory (10 characters) for *s.
  -  Making inputString() a void function and passing it *s, rather then having a return value.
  -  Added two '\n' to the end of the error printf() call to clean up resulting prompt.

//Assumptions made
I made the following assumptions which informed my random tester:
  -  inputChar() could return any value from the ASCII table between 32-Space and 125-'}'.
  -  inputString() could return a string of length 0 - 10.
  -  inputString() could return any value from the ASCII table between 32 & 125.

//Input Function Design
/*****inputChar()*****/
inputChar() simply returns a randomly generated character between ASCII value 32 & 125 every
interation it is run.  While this is nearly all of the valid ASCII values this iterates the 
'status' value to 9 within a reasonable amount of time for testing.
/*****inputString()*****/
I went through a number of iterations before landing on the current design.  My intial attempts
centered around ways of favoring strings of length 5, and then favoring the letters in 'reset' when
length 5 strings were generated.  Many of the attempts felt a little contrived and I wanted to ensure
most of what was being tested was truly random, which led me to the current design which consists of:
  -  String length randomly varies from 0 - 10, favoring length 5. (approx 35%) 
  -  String lengths other then 5 are randomly assigned characters from the full ASCII table (32 - 125).
  -  Strings of length 5 have a 6 in 7 chance of also being randomly assigned characters (ASCII 32 - 125).
  -  The reamaining 1 in 7 are assigned characters from a limited set of characters including 'r', 'e',
     's', 't' and 4 more randomly chosen characters.  This increases the chances of 'reset' but with
     still quite a bit of random chance involved.

This design manages to ensure the 'error' message is hit in a reasonable amount of time (generally under
1M iterations) but still tests a farily comprehensive range of randomly selected character inputs.  There
is a slight bias toward a 'reset' response but still with sufficient random chance included.

//Test Results
I tested the final iteration 10 times, each reaching the error statement in under a minute.  The average 
# of iterations required was 433,629 which takes approx 20 seconds on the COE Flip Servers.

Attempts:
//01 -   436,817
//02 -    49,277
//03 -   487,283
//04 -   263,399
//05 -    15,814
//06 - 1,385,902
//07 -   763,240
//08 -   136,804
//09 -   341,037
//10 -   457,714
