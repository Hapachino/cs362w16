#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int fastTest = 0;

char inputChar()
{
    int r;
    if (fastTest == 1)
    {
      r = rand() % 16 + 101;
    }
    else
    {
      r = rand() % 95 + 32; 
    }


    return r;
}

char *inputString()
{

  int i;
  char *str = malloc(sizeof (char) * 6);
  for (i=0; i<5; i++)
  {
    //printf("str: %s\n", str);
    str[i] = inputChar();
  }
  
  str[5] = '\0';

    return str;
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
    if (c == ']' && state == 8) 
      {
        state = 9;
        fastTest = 1;
      }
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
    /*
    int i;
    char *s;
    for (i=0; i<100; i++)
    {
      s = inputString();
      printf("%s\n", s);
    }*/
    return 0;
}
