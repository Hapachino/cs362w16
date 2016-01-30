#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

const int ITERATIONS = 1000;

char inputChar()
{
    // 32 - 125
    char c_rand;
    c_rand = (rand() % 125) + 32;
    
    return c_rand;
}

char *inputString()
{
    char letter_pool[5] = {'r', 'e', 's', 't','\0'};
    char *random_word = malloc (sizeof(char) * 6);
    int random_num;
    int i = 0;

    for(i; i < 6; ++i)
    {        
        random_num = (rand() % 5);
        random_word[i] = letter_pool[random_num];
    }
//    random_word[5] = '\0';
    return random_word;
        
    
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
