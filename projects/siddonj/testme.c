#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    char character = rand() % 94 + 32;        // Generate a character between ' ' and '}'.
    return character;
}

char *inputString()
{
    // TODO: rewrite this function
    static char testCharacters[] = { 'r', 'e', 's', 'e', 't' };   // limit domain for some tests.
    static char input[6];
    int randomnessFactor = rand() % 10;
    char randomChar;
    int i;
    int testIndex;

    if(randomnessFactor % 9 == 0) {           // All characters a-z
      for(i = 0; i < 5; i++) {
        randomChar = ((rand() % 26) + 97);
        input[i] = randomChar;
      }
      input[randomnessFactor] = '\0';

    } else {                                  // Only pull characters from limited domain.
      for(i = 0; i < 5; i++) {
        testIndex = rand() % 6;
        input[i] = testCharacters[testIndex];
      }
      input[5] = '\0';
    }

    return input;
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
