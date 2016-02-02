#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
   int n = (rand() % 95) + 32; /* Ints 32 through 127 are ASCII chars */
   if(n > 64 && n < 91)
     {                        
       n += 32;                /* Make lower case if capital letter */
     }
   /* Could optimize getting rid of a few chars not in the state machine,
      but chose to leave this domain of testing in case to cover other
      versions of the character set, like < or > instead of ( and ). */
  char c = n;                 /* Convert ascii value to char */
  return c;
}

char *inputString()
{
    char string[5];
    int i;

    for (i = 0; i < 5; i++)
      {
        string[i] = (rand() % 25) + 97;  /* Lower case letters only */
      }
    string[5] = '\0';                    /* Terminate with null */ 
    return string;
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
