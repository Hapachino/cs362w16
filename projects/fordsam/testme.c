#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define CHAR_MAX (127 - 32)
#define STRING_MAX 5

char inputChar()
{
    /* Return an ASCII char from 32 (space) to 126 (~), thusly avoiding
       control characters */
    return (char)(rand() % CHAR_MAX + 32);
}

char *inputString()
{
    /* Generate a string of up to 5 chars (and a null terminator) */
    int length = rand() % STRING_MAX + 1;
    char *s = NULL;
    int i = 0;

    /* Allocate memory for the string */
    s = (char *)malloc((length + 1) * sizeof(char));
    if (s == NULL) {
      perror("Error allocating memory for inputString");
    }

    /* Populate the string with [length] chars followed by a null terminator */
    for (i = 0; i < length; i++) {
      /* Add a random character from 97 (a) to 122 (z) to the string */
      s[i] = (char)(rand() % 26 + 97);
    }
    s[length] = '\0';

    return s;
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
    if (c == ' ' && state == 3) state = 4;
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
      free(s);    /* Free the generated string before exiting */
      exit(200);
    }

    free(s);      /* Free the generated string before the next iteration */
  }
}


int main(int argc, char *argv[])
{
  srand(time(NULL));
  testme();
  return 0;
}
