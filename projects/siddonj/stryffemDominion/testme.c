/*	
*	Author: Martin Stryffeler
*	Filename: testme.c
*	Description: CS 362 Random Testing Quiz 2 Code
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	//Returns a random integer corresponding to a character from the ASCII table.
	return (rand() % 95) + 32;
}

char *inputString()
{
	//Builds and returns a random string.
	int i, j;
	char rest[5] = "rest";

	static char string[6];

	//Roughly half the time, uses all standard alphanumeric and symbol characters
	if((rand() % 2) == 0)
	{
		for(i = 0; i < 5; i++)
		{
			string[i] = (rand() % 95) + 32;
		}
	}
	//Otherwise, uses only the characters 'r', 'e', 's', and 't'.
	else
	{
		for(i = 0; i < 5; i++)
		{
			j = (rand() % 4);
			string[i] = rest[j];
		}
	}

	string[5] = '\0';
	return string;

}

void testme()
{
	srand(time(NULL));
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
