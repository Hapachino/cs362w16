#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char inputChar() {
	// generate random number to represent ASCII value 32 to 126 or null
	int randInt = (rand() % (128 - 32)) + 32;
	if (randInt == 127)
		return '\0';		// we use 127 to deliver null characters equally
	else
		return randInt;		// otherwise, we deliver the random value directly
}

char *inputString() {
	char *s = malloc(sizeof(char) * 6);		// string of random characters
	char resetChars[5] = {'r', 'e', 's', 't', '\0'};
	int randInt,				// produces random number for character
		i = 0,					// standard iteration value for counting
		method = 1;				// random printable ASCII if 0, random 'rest' if 1

	for (i = 0; i < 6; i++) {
		// generate random number to represent one of the four characters
		randInt = rand() % 5;

		/* determine if we use the 'reset' characters or full printable
		   ASCII characters to create random string...method 0 is extremely
		   unlikely to occur */
		if (method == 0)
			// random string populated with a printable ASCII character
			s[i] = inputChar();
		else
			// random string populated with r, e, s, t, or \0 characters
			s[i] = resetChars[randInt];
	}
	
	// return random string
	return s;
}

void testme() {
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;
	
	while (1) {
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0)
			state = 1;
		if (c == '(' && state == 1)
			state = 2;
		if (c == '{' && state == 2)
			state = 3;
		if (c == ' ' && state == 3)
			state = 4;
		if (c == 'a' && state == 4)
			state = 5;
		if (c == 'x' && state == 5)
			state = 6;
		if (c == '}' && state == 6)
			state = 7;
		if (c == ')' && state == 7)
			state = 8;
		if (c == ']' && state == 8)
			state = 9;
		if (s[0] == 'r' && s[1] == 'e'
		   && s[2] == 's' && s[3] == 'e'
		   && s[4] == 't' && s[5] == '\0'
		   && state == 9) {
			printf("error \n");
			// frees memory allocated in inputString()
			free(s);
			exit(200);
		}
	}
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	testme();
	return 0;
}
