random string development

Procedure
My initial actions were to find out what exactly the program wanted to do and I concluded that it was
to generate a random set of characters to meet certain conditions to set state numbers. The other function
generated a random string of the letters in 'reset' and would stop once it reached state 9 from the first
function and had the letters in 'reset' spelled out to reset. After understanding what the requirements were
I first had to decide what characters to randomize. I thought about including all characters 0-127 for ascii 
but since we were testing specific characters and not all of them I thought it would be more efficient to just
test the characters that have the ability to be called. 

Function inputChar()
So what my function inputChar() does is create an array
with the chars that activate the different states available. I then got the size of the array in bytes and length 
then simply returned a random value from that array.

Function inputString()
My strategy for input string was relatively the same. I first created an array with the available characters to be 
called ('reset'). I then created another array that would be the holder for the future string. I initialized this
array with a size of 6 so that I could set the last element to null. Once I did that I just had to assign random
parts of the first array (reset) into a new string. Afterwards I had the last element set to null. It would then 
return string. 

How it all works
The tester is pretty simple, it gets a character from my inputChar function and compares it a character and state number
if it meets that condition then the state is incremented. Once the state is 9 the string function checks each element to
see if the string says 'reset' and is also followed by null. Once it does it pritns 'error' and exits. 

Testing
I did 5 iterations and they all followed between the 350 and 800 iteration range. 
