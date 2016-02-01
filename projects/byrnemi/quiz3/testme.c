//Quiz 3
//CS 362
//Michael Byrne
//ONID: byrnemi
//1 - 31 - 2016



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int REALMODE = 0;


char inputChar()
{
    int i, len;
    time_t t;
    char randOut;
    srand((unsigned) time(&t));
    static char charset1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!{}[]()\0";
    static char charset2[] = "{[( )]}xa";


    //for (i=0;i<2000;i++){
        if (REALMODE){
            int index = rand() % (int)(sizeof(charset1) -1);
            randOut = charset1[index];
            //printf("%c\n",randOut);
        }
        else{
            int index = rand() % (int)(sizeof(charset2) -1);
            randOut = charset2[index];
            //printf("%c\n",randOut);
        }
    //}

    return randOut;
}

char *inputString()
{
    int i, len;
    time_t t;
    char randOut;
    srand((unsigned) time(&t));
    static char charset1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!{}[]()\0";
    static char charset2[] = "reset";
    len = 5;
    char randStringOut[len];
    char * ptrOut;


    for (i=0;i<len;i++){
        if (REALMODE){
            int index = rand() % (int)(sizeof(charset1) -1);
            randOut = charset1[index];
            randStringOut[i] = randOut;
        }
        else{
            int index = rand() % (int)(sizeof(charset2) -1);
            randOut = charset2[index];
            randStringOut[i] = randOut;
        }
    }
    //printf("%s\n",randStringOut);
    ptrOut = &randStringOut[0];
    return ptrOut;
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
//   inputString();
//    inputChar();
    testme();
    return 0;
}
