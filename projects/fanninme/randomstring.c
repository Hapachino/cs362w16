//Megan Fanning
//write up of testme.c file
//note this is note a c file but rather a text file.


The first thing I did was impliment input char, because I knew that I could use this to generate random chars which I could use to build my characters which I could in turn use to generate random strings

I knew the goal was to generate the string 'reset\0' so I needed to be sure that my strings was at 5 characters long and null terminated.
Next I noticed that I would need the state to be set to 9. To get the state to change the characters generated would need to include [,(,{,},),], lowercase letters and whitespace.

Originally I was going to call inputChar to fill my string array however with a 7/33 chance of being a non-letter it was disadventagious to use that as a method of generating the string "reset".Instead I created a seperate but similiar character generator algorithms using 26 lower case letters and a modulous to generate the string.

I was able to produce the error message after 7613954 iterations.

