/* 	File: testme.c
	Author: Chris Trana
	CS 362
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
   // return a random ascii char between 32 and 127 (space and delete)
	return (rand() % 95) + 32;
	
}

char *inputString()
{
    // TODO: rewrite this function
	//inputString needs to be "reset" in order to end.  
	//we will use a limited pool of chars in order to run in a reasonable amount of time
	
	int i, j;  //used for loop and indexing variables
	char rest[14] = "restingmyhead"; //pool of chars to populate inputString
	static char testString[6];  //must be static to keep string in memory until program ends

	for (i = 0; i < 5; i++)
	{
		j = rand() % 13;
		testString[i] = rest[j];
	}

	testString[5] = '\0';
	return testString;
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
