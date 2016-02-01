#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar() {
    //returns a randomly generated ASCII printable character (ASCII values 32 through 127 inclusive)
	int asciiMin = 32;
	int asciiMax = 127;
	int range = asciiMax - asciiMin + 1;
	char randChar = (rand() % range) + asciiMin;
    return randChar;
}

char *inputString() {
    // returns a randomly generated C-string of length 1, 6, 11, 16, or 21 (inclusive of '\0') and containing only the letters a, e, r, s, t, or z)
	
	// create set of available letters (e, r, s, and t because they are the characters in 'reset' which is required to generate the error and then a and z as boundary conditions)
	char charSet[] = "aerstZ!"; 
	// randomly generate string length
	int strLen = 5 * (rand() % 5) + 1;
	// initialize empty string
	char *randStr = (char *)malloc(sizeof(char)*strLen);
	
	// create random string
	int i; // initialize counter variable
	for (i = 0; i < strLen-1; i++) {
		randStr[i] = charSet[rand() % 7]; // % 7 because there are 7 characters in the character set
	}
	randStr[strLen] = '\0'; // set final character of string to '\0'
	
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
