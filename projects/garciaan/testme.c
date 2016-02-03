#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    int num = (rand() % 126) + 32;
    return (char)num;
}

char *inputString()
{
    // TODO: rewrite this function
    int i;
    int size = 6;//(rand() % 10) + 1;
    char letter;
    char* string;
    string = malloc(size * sizeof(char));
    for (i = 0; i < size - 1; i++){
      letter = inputChar();
      while (letter >= 123 || letter <= 96){
        letter = inputChar();
      }
      string[i] = letter;
    }
    string[size - 1] = '\0';
    return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;

  while (1)//iteration < 20)
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
    int seed = time(NULL);
    srand(seed);
    testme();
    return 0;
}