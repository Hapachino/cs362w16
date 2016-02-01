#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// randomly generate character from relevant set
char inputChar()
{
    const char* set = "[({ ax})]";
    int i = rand() % strlen(set);
    return set[i];
}

// randomly shuffle the error inducing string
char *inputString()
{
    char* s1 = "reset";
    char* s2 = malloc(sizeof(char) * strlen(s1));
    strcpy(s2, s1);

    int length = strlen(s2);
    for (int i = length - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp = s2[i];
        s2[i] = s2[j];
        s2[j] = temp;
    }
    return s2;
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
  free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
