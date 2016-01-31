//Megan Fanning
//write up of testme.c file
//note this is note a c file but rather a text file.


The first thing I did was impliment input char because I knew that I could use this to generate random chars which I could use to build my string.
The way I found the error message in testme.c is

I knew the goal was to generate the string 'reset\0' so I needed to be sure that my strings was at 5 characters long and null terminated.
Next I noticed that I would need the state to be set to 9. To get the state to change the characters generated would need to include [,(,{,},),], lowercase letters and whitespace.

