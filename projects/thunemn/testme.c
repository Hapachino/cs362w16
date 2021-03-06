#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


char inputChar()
{
  //returns c
  char rand_char[] = {'{', '[', '(', ' ', 'a', 'x', ')', '}', ']'};
  int num = rand() % 9;

    return rand_char[num];
}


char *inputString()
{
  //returns s
  char rand_char[] = {'r', 'e', 's', 't'};
  //allocate size for string
  char *rand_string = (char*)malloc(6*sizeof(char));
  int i = 0;
  for(i = 0; i < 5; i++)
  {
    int num = rand() % 4;
    rand_string[i] = rand_char[num];
  }
  //add null terminating char at end of string
  rand_string[i+1] = '\0';
  return rand_string;
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
      free(s);
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
