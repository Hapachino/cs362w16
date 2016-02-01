*******************************************************************************
*************** CS 362 - Random Testing Quiz 2 - Spencer Winlaw ***************
*******************************************************************************

-------------------------------------------------------------------------------
Development of Random Tester
-------------------------------------------------------------------------------
When approaching the development of the random tester for testMe(), I first 
reviewed the code in order to infer a specification for the function. The 
following are my findings:

	Specification of testMe()
	-------------------------
		- testMe() constists primarily of a loop which performs checks on 3 
		  variables: c (char), state (int), and s (string)
		- testMe() gets c from the function inputChar()
		- testMe() gets s from the function inputString()
		- state is initialized to 0 and is incremented when c holds a certain 
		  character (depending on the current value of state)
		- The loop in testMe() prints the contents of these variables upon
		  each iteration and contiually executes until s = "reset" and 
		  state = 9 at which point the program prints "error" and is 
		  terminated with an exit code of 200.

Based on this knowledge, I implemented inputChar() and inputString() to produce
random values that are capable of printing the error message as described below.

	inputChar()
	---------------------------------------------------------------------------
	char inputChar()
	{
	 	//Gets a random ASCII character
	    char c = (rand() % (127 - 32)) + 32;
	    return c;
	}

	In order for the tester to acheive full coverage, the inputChar() function 
	needed to be capable of returning each character that is checked for in the 
	if statements of the loop found in testMe(), namely '[', '(', '{', ' ', 'a', 
	'x', '}, ')', and ']'. Therefore, I implemented inputChar() so that it 
    returns a randomly generated ASCII character in the range [32, 126], which 
    includes of all of the characters previously mentioned.


	inputString()
	---------------------------------------------------------------------------
	char *inputString()
	{   
	    int length = 6;
  		char* s = malloc(length);

  		int i;
 		for(i = 0; i < length - 1; i++)
 		{
    		s[i] = (rand() % (123-97)) + 97;
  		}
  		s[i] = '\0';      
  
  		return s;
	}

		In order for the tester to acheive full coverage, the inputString() 
	function needed to be capable of returning the string "reset". When going to 
	implement this function, I quickly realized that the probablility of producing 
	this string in a purely random fashion would be extremely low. This was not an 
	issue when writing inputChar(), since the function simply chose a single value 
	from a finite set of ASCII characters; however, when producing random strings 
	there are infinite possibilies given that a string can theoretically have an 
	infinite length. This means that the tester could potentially take an 
	unreasonably long amount of time to or may never reach the statement containing 
	the error message. Faced with this problem, I investigated various ways of 
	skewing the probability in favor of producing the string "reset" so that the 
	function would be capable of returning the desired string within a reasonable 
	amount of time. 
		One method that I considered was to include within the inputString() 
	function a probability of simply returning the string "reset" directly, since 
	I had the knowledge from my review of the code of the particular string I was 
	interested in testing. Using this method, inputString() could first use the 
	rand() function along with a probability factor in order to decide whether 
	"reset" should be returned directly. If not, then inputString() would generate
	a random string which by chance could be "reset". Now to be sure, I think that 
	this would have been a fine way of approaching this problem, but ultimately I 
	decided to go with a different method.
		When implementing the inputString() method, I randomly generate strings
	of size 6 and restrict the possible characters in the string to the 
	lowercase alphabet ([a, z] or ASCII code [97, 122]). This methodology greatly 
	increases the probability of producing the string "reset" in a random 
	fashion that I feel is more true to the intentions of this particular
	assignment. 


-------------------------------------------------------------------------------
Results
-------------------------------------------------------------------------------
As designed, when the random tester runs, it eventually produces the conditions
necessary to execute the statement where the error message is printed. Due to 
statistic probability (1:95), the conditions necessary for state to be 
incremented (c containing the appropriate character when state is at a given 
value) occur rather quickly. So in a fairly short number of iterations, the 
state variable reaches the value of 9, which is one of the 2 necessary 
conditions for the error message to be printed. The only remaining condition for
the statement containing the error message to be reached is for	inputString() to 
return "reset". The speed at which this occurs, measured in number of loop 
iterations, varies according to random probability. Mathmatically speaking the 
odds of "reset" being returned are 1:(26^5 - 1) or 1:11,881,375. In my testing 
of the above code, my results were as follows: 

								 Test 	 Iteration
								------------------
								Run 1:	   516,553
								Run 2: 	 8,913,037
								Run 3: 	    20,314
								Run 4: 	 2,431,339
								Run 5: 	19,153,481
								Run 6: 	 5,502,191
								Run 7:	 2,916,448
								Run 8:	 9,979,118
								Run 9:	 1,467,336
								Run 10:  4,130,911
								------------------
								AVG:	 5,451,418

-------------------------------------------------------------------------------
**Special Note on testMe()**
-------------------------------------------------------------------------------
I made two adjustments to the code for the testMe() function.
	- The first was to free s in each iteration of the loop, since I chose to 
	  malloc the memory for the	string in the inputString() function.
	- The second was a practical adjustment for testing purposes. I found that
	  when running the tests, a lot of resources were being used to print the 
	  status of each iteration. I found that by reducing the execution of the 
	  print statement to every millionth iteration, and the iteration that 
	  caused the error message to be printed, I could run tests much faster 
	  and still obtain the necessary information for my purposes.