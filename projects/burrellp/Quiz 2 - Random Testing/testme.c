#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    char c;
    
    //c will be one of the 256 ascii characters (value between 0-255)
    c = rand() % 256;

    return c;
}

char *inputString()
{
    /*************************************************************************
     * The string will need to be 'reset' to print the error message
     * I will use this fact to increase the odds by limiting the possible
     * characters for the string to 'r', 'e', 's', 't', and '\0' (the null
     * character). The length of the string and order of the characters will
     * be random
     *************************************************************************/
    
    int i = 0;                      //For loop operation
    char chars[] = "rest";          //Pool of chars for which to fill string
    
    //String length will be random number between 1-6
    int length = (rand() % 6) + 1;
    char *cString = malloc (sizeof(char) * length);
    
    for (i = 0; i < length - 1; i++)
    {
        /*****INITIAL IMPLEMENTATION - TOOK TOO LONG**********/
        //Pick a random lowercase letter and assign it to current index of string
        //char whichChar = 'a' + (rand() % 26);
        //cString[i] = whichChar;
        
        //Pick a random char from pool and add it to return string
        int whichChar = rand() % 5;
        cString[i] = chars[whichChar];
    }
    
    return cString;
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
      printf("error \n");
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
