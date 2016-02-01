
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

#define MAX_LENGTH 6
#define MAX_ASCII 127

char inputChar(){
    char inputChar = (char)floor(Random() *(MAX_ASCII-32)) +32;
	assert(inputChar > 31 && inputChar < 127); 
    return inputChar;
}

char* inputString(){

    char * inputString = (char*) malloc(sizeof(char)* MAX_LENGTH);
    int i;

    for(i=0; i<MAX_LENGTH-1; i++){
        inputString[i] = (char)floor(Random() *(MAX_ASCII-97)) + 97;
    }
    inputString[MAX_LENGTH -1] = '\0';

    return inputString;
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
            printf("error \n");
            exit(200);
        }
    }
}

int main() {
	srand(time(NULL));
    int seed = (rand() % 3) + 1;

    SelectStream(2);
    PutSeed(seed);

    testme();

	return 0;
}