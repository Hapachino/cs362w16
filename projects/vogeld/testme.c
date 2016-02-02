/* -------------------------------------------------------------------------------
 * David Vogel
 * CS362 Random Testing Quiz 2
 * Due 1/31/16
 * Description:
 *    Implement a random tester for the function testme() in testme.c
 *    that is capable of printing the error message.
 *    You should implement inputChar() and inputString() to produce random values. 
 *    Write up the development of your random tester and how it finds the error 
 *    message as randomstring.c. 
 *    Submit testme.c and randomstring.c under your onid directory in class github. 
 *    (under your onid directory and not under dominion directory).
 * ----------------------------------------------------------------------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Generate a random number between 0 and 8 to select from a set of characters
char inputChar() {
  int randInputChar;
  randInputChar = rand() % 9; // number in the range 0 to 8
  switch (randInputChar) {
    case 0: return '[';
    case 1: return '(';
    case 2: return '{';
    case 3: return ' ';
    case 4: return 'a';
    case 5: return 'x';
    case 6: return '}';
    case 7: return ')';
    case 8: return ']';    
  }
}

// Generate a 6-character null-terminated string from a randomly chosen set of characters
char *inputString(char *s) {
  int randInputString;
  int i;
  for (i = 0; i < 6; i++) {
    randInputString = rand() % 6;
    switch (randInputString) {
      case 0: s[i] = 'r';
        break;
      case 1: s[i] = 'e';
        break;
      case 2: s[i] = 's';
        break;
      case 3: s[i] = 'e';
        break;
      case 4: s[i] = 't';
        break;
      case 5: s[i] = '\0';
        break;
    }
  }
}

void testme() {
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1) {
    tcCount++;
    c = inputChar();
    inputString(s);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if   (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9) {
      printf("error ");
      exit(200);
    }
  }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    testme();
    return 0;
}