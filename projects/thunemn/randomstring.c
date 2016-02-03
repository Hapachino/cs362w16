The testme() function obtains 2 values: c from inputChar(), and s from
inputString().  

inputChar() initializes a char array with values of c that
testme() looks for.  inputChar() then uses a random number from 0-9 to 
return a random char from the array.  

inputString() initializes a char array with values of s that testme() 
looks for.  inputString() loops 5 times to get a random char from this 
array and adds that char to the string.  Once the loop is finished, 
a null terminating char is added to then end of the string.  

testme() will continue to loop through each iteration until the random 
string contains "reset\0".  Once this occurs, it will pring the error 
message and exit.