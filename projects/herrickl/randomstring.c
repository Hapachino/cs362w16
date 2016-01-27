/*****************************************************************************************
* Random Testing Quiz 2
* By: Lynn Herrick
* Date: 1/26/16
* Description:  Implement a random tester for the function testme() in testme.c that is 
* 		capable of printing the error message.  You should implement inputChar() and 
*		inputString() to produce random values. Write up the development of your random 
*		tester and how it finds the error message as randomstring.c. Submit testme.c and 
*		randomstring.c under your onid directory in class github. (under your onid 
*		directory and not under dominion directory).
*****************************************************************************************/

/*THIS IS A DOCUMENTATION FILE

How it was developed: The specification for these two functions, inputChar() and 
inputString(), was that they had to produce a random char/string.  Then looking at the
prewritten random test, testme(), I can see that the test will run until the random
char produced from inputChar() is ']' and the random string that is produced from 
inputString() is 'reset'.  This gives me some direction as to what range I need to
produce random inputs from.  For a truely random string and char to match up within
the parameters that would cause testme() to exit, it would takes hours of running the
code.  To break down that time, I limited my random chars to a selection from "[({ ax})]"
and my random string to be a permutation of "reset".  Although it would not matter whether
or not I had repeted 'e' in my string, I chose to include the double e to allow for a 
higher chance of selection.


Code explanation:
char inputChar()
{
  	// TODO: rewrite this function
	char randChar;
	char selections[9] = "[({ ax})]";	//array includes chars that are potential selections

	randChar = selections[rand() % sizeof(selections)];	//takes index at random number between 0-8
    return randChar;
}


char *inputString()
{
    // TODO: rewrite this function
    int i;
    int stringSize = 5;
    char *string = malloc(stringSize);
    char selections[5] = "reset";		//array includes chars that are potential selections

    for(i = 0; i < stringSize; i++){	
    	string[i] = selections[rand() % stringSize];  //takes index at random number between 0-4
    }
    string[5] = '\0';					//attaches null char to end of array as per requirements

    return string;
}


How it finds the error message:
TestMe() continues to run until it has satisfied all conditions to quiting.  First it
checked all possible chars, further producing all possible states (all possible string
combinations were also happening for each of these conditions).  Finally, when the state
condition is met, it checks all possible string combinations while at that state.  For me,
this took 1546 times through the TestMe() while loop, but this is on the higher range of
potential runs.   

Iteration 1536: c = (, s = eteer, state = 9
Iteration 1537: c = }, s = eseer, state = 9
Iteration 1538: c = x, s = seett, state = 9
Iteration 1539: c = {, s = esrts, state = 9
Iteration 1540: c = }, s = eeter, state = 9
Iteration 1541: c = (, s = reeee, state = 9
Iteration 1542: c =  , s = stere, state = 9
Iteration 1543: c =  , s = trrtr, state = 9
Iteration 1544: c = ], s = rrere, state = 9
Iteration 1545: c = }, s = seste, state = 9
Iteration 1546: c = a, s = reset, state = 9
error

Running it a few more times, I was able to achieve a quicker time in satisfying the 
conditions, further justifying the decisions I made to limit character choices.

Iteration 182: c = ), s = etrss, state = 9
Iteration 183: c = {, s = estte, state = 9
Iteration 184: c = ), s = reese, state = 9
Iteration 185: c = ], s = strst, state = 9
Iteration 186: c = (, s = rrsre, state = 9
Iteration 187: c = }, s = eeeee, state = 9
Iteration 188: c = ], s = stsee, state = 9
Iteration 189: c = a, s = eeese, state = 9
Iteration 190: c = }, s = ertes, state = 9
Iteration 191: c = ), s = tseer, state = 9
Iteration 192: c = ], s = reset, state = 9
error 


/*
