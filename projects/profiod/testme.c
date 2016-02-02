#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


char inputChar()
{
    char retValue; 
    int randNum ;

    // allow domain for random numbers to be any ascii value between a-z, helps improve test randomness 
    randNum = rand() % 33 + 97; 

    switch(randNum)
    {
      case 124:
        retValue = '('; 
        break; 
      case 126: 
        retValue = ')';
        break;
      case 127: 
        retValue = '['; 
        break;
      case 128: 
        retValue = ' '; 
        break;
      case 129: 
        retValue = ']';
        break;
      default: 
        retValue = randNum; 
        break;
    }
    
    return retValue;
}


char *inputString()
{
    char* randomString; 
    int i; 
    int randNum; 
    int randChar; 

    // allocate memory for a string
    randomString = (char*) malloc(6 * sizeof(char)); 

    for (i = 0; i < 5; i++)
    {
      // create a random number between 0 and 3
      randNum = rand() % 4; 

      // switch on that number to determine the character from the proper character list 
      switch(randNum) 
      {
        case 0: 
          randChar = 101; 
          break; 
        case 1: 
          randChar = 114;
          break; 
        case 2: 
          randChar = 115; 
          break;
        case 3: 
          randChar = 116; 
          break;
      }

      // set the value of that random char in the random string
      randomString[i] = randChar; 
    }

    // null terminate 
    randomString[5] = '\0'; 

    return strdup(randomString);
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