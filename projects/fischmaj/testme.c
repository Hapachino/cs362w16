#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // TODO: rewrite this function
  /* returns a random character from 32 to 127, ie. all the valid*/
  /* ASCII characters that aren't control symbols */
  char randomChar = (char) ((rand()%96)+32);
  return randomChar;
}

void inputString(char * myString)
{
  for(int i = 0; i < 5; i++){
    myString[i] =(char) ((rand()%26)+97);
  } 
  myString[5]='\0';
  printf("%s", myString);
}

void testme()
{
  int tcCount = 0;
  char *s= malloc(sizeof(char)*6);
  char c;
  int state = 0;

  while (1)
  {
    tcCount++;
    c = inputChar();
    inputString(s);
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
