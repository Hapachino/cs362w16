/*
Nelson Samayoa
CS362 Random testing quiz

This is the current implementation of inputChar()

	char inputChar()
	{
		return "axres et{}[]()"[random () % 14];;
	}

At first I tried including all possible characters of the American keyboard,
but that caused the program to run a very long time, could cause the iteration count variable
to produce a buffer overflow if it gets large enough, and wouldn't be an valuable test
for this particular method (the return on investment would be too low). I therefore decided
to have it return just some limited lowercase letters, a space, and {}[]() characters. The 
idea is simply that there's a string defined as "axres et{}[]()" and it's the index that is 
randomly generated. The function returns just the char within that string that corresponds 
to the randomly generated index.



The inputString() function returns random length strings populated by randomly generated 
characters (within a defined domain). testMe() never checks beyond the 6th element of the
string, so in order to get more interesting results I limited the length of the string to 
5 chars plus 1 for the \0. I was seeing a lot of empty strings which was making the test run
too long, so I set the length to 5 if a length of 0 is detected. I then allocate the memory 
needed and set each index on the char string to a randomly generated char by calling inputChar().
Lastly I add the terminating \0 character and return the string.
 
	char *inputString()
	{
		int strLen = random() % 5;

		if (strLen == 0)
		    strLen = 5;

		char *fullString = malloc(sizeof(char) * (strLen +1));

		int i = 0;
		for (; i < strLen; i++)
		    fullString[i] = inputChar();

		fullString[strLen] = '\0';
		return fullString;
	}

I both functions I limited the domain of inputs to make the test produce interesting and valuable
results. The tester first looks for specific characters in the randomly generated char. As it finds 
each char, it incrememts the "stage" variable. The tester reaches stage 9, then starts looking for 
the string "reset". Once that string is found, it "errors out". Giving the limited domain, that 
string shows up usually in less than a minute and the test terminates.

*/
