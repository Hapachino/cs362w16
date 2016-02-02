#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    int r = rand() % 39 + 91;
    char c;
    if (r == 126) 
    {
      c = '\0';
    } else if (r == 127)
    {
      c = '(';
    } else if (r == 128)
    {
      c = ')';
    } else if (r == 129)
    {
      c = ' ';
    } else 
    {
      c = r;
    }
    return c;
}

char *inputString()
{
    // TODO: rewrite this function
    char *s = malloc(6);
    char set[] = "rest\0";
    int idx;
    idx = rand() % 5;
    s[0] = set[idx];
    idx = rand() % 5;
    s[1] = set[idx];
    idx = rand() % 5;
    s[2] = set[idx];
    idx = rand() % 5;
    s[3] = set[idx];
    idx = rand() % 5;
    s[4] = set[idx];
    idx = rand() % 5;
    s[5] = set[idx];
    printf("%s\n", s);
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
