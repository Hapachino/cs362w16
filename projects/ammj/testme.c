#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int random_number(int min, int max)
{

	/**
	 * Require min to be greater than max
	 */
	if(min < max)
	{

			double randNum, randSeed, rangeVal;

			// get the range for the random number
			rangeVal = max - min + 1;
			randSeed = rand();
			randSeed = randSeed / RAND_MAX;
			randNum = floor(randSeed * rangeVal) + min;

			return (int) randNum;
	}

	return 0;
}

char inputChar()
{
		// generate a random integer from the range in the ascii table
		int rInt = random_number(32, 126);

		// convert the integer into it's correspondig ascii character
		char rChar = (char) rInt;

    return rChar;
}

char *inputString()
{
  	int i=0;
  	int randChar = 0;

		// identify the list of available characters to pull from
		char *charSet = "erst";
		// get the max index in the list
	  int charSetIdxLen = strlen(charSet) - 1;

	  // get a random number from a range (1 and 10) in this instance
	  // create a pointer to store the random String
		int ranLen = random_number(1,10);
		char *randStr = (char*) malloc((ranLen+1) * sizeof(char));

		// for each character up the length of the random string
		for(i = 0; i < ranLen; i++)
		{
			// generate a random index from 0 to last index in charSet
			// move the letter at that index into randStr
			randChar = random_number(0, charSetIdxLen);
			randStr[i] = charSet[randChar];

		}

		// add the termination character in the last index
		randStr[ranLen] = '\0';

    return randStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
