run 1: 20143135
run 2: 9026119
run 3: 15578757
run 4: 30881311
run 5: 18924210
run 6: 1884263
run 7: 18792615
run 8: 5360770
run 9: 508723
run 10: 4962061
run 11: 12235252
run 12: 


To create my random tester I first identified what would cause the error message to be 
displayed. I saw that the error message would only be displayed if state equaled 9 and 
the string (char array) s was reset\0. The results of input char would not affect whether 
the error message was displayed or not. 

The first thing I did was set state equal to 9. 

Although the results from inputChar() did not influence the error message I next implemented 
inputChar(). The results from inputChar() could then be used to fill the char array in
inputString() with random characters. I decided to limit the possible values that inputChar()
would produce to lowercase letters. I choose to do this because it would limit the number of 
test that would likely occur before the error message was displayed. My back of the envelope 
calculations showed that if I just used random letters, the odds of displaying the error message 
would be about 1/(26*26*26*26*26) = 1/11,881,376 

In order to get random lower case letters I created an integer variable randNum. I then set 
randNum equal to rand() % 26, which would result in an integer between 0 and 25. I then added
97 to rand num. 97 is the ASCII character number for 'a', the next 25 character numbers are the 
rest of the lowercase alphabet. I then typecast randNum to char and assigned it to a char variable
randChar. I then had inputChar() return randChar.

To implement inputString() I created a six character char array randString, that would hold five
random chars. This would leave the last character in the array \0. I used a for loop to fill the
array. inputChar() was used to provide the random character to put in randString. The location
of each random string was determined by using the length of randString. At each iteration of the
for loop this placed the random char in the subsequent location in randString. After five random
chars were added to  randString inputString() returned rand string.

I ran testme 12 times. It ran between 508,723 and 30,881,311 tests before returning the error
message. The number of tests run on each run of testme are below.

run 1: 20143135
run 2: 9026119
run 3: 15578757
run 4: 30881311
run 5: 18924210
run 6: 1884263
run 7: 18792615
run 8: 5360770
run 9: 508723
run 10: 4962061
run 11: 12235252
run 12: 6812452