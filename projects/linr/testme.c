#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar() //Rewrite this function
{
   char randomChar;
   randomChar = rand() % 96 + 32; //generate random # between 32-127

   return randomChar;
}

char *inputString() //Rewrite this function
{
   char *randomString;
   char choices[4] = {'r','e','s','t'}; //create char array of letters in reset
   char randomChar;

   int i;
   for(i = 0; i < 5; i++) //generate string 5 characters long
   {
      randomChar = rand() % 4; //generate random # between 0-3
      randomString[i] = choices[randomChar];
   }
   randomString[5] = '\0'; //assign last character to null terminator
  
   return randomString;
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
