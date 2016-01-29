/*****************************************************************************************
 *  Random Testing Quiz 2
 *  Regina Imhoff
 *  imhoffr@oregonstate.edu
 *  Date: 01/29/2016
 *  Description:
 *      Implement a random tester for the function testme() in testme.c that is
 *      capable of printing the error message.  You should implement inputChar() and
 *      inputString() to produce random values. Write up the development of your random
 *		tester and how it finds the error message as randomstring.c. Submit testme.c and
 *		randomstring.c under your onid directory in class github. (under your onid
 *		directory and not under dominion directory).
 *****************************************************************************************/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define ASCII_MINIMUM 0
#define ASCII_MAXIMUM 255
#define INPUT_STRING_SIZE 6

char inputChar()
/* Produces a random ASCII character */
{
    // TODO: rewrite this function
    
    int range_of_characters = ASCII_MAXIMUM - ASCII_MINIMUM + 1;
    char random_character = (rand() % range_of_characters) + ASCII_MINIMUM;
    
    return random_character;
}

char *inputString()
{
    // TODO: rewrite this function
    int i;
    char string_set[INPUT_STRING_SIZE] = "reset\0";
    char *character_string = malloc(INPUT_STRING_SIZE);
    
    
    for(i = 0; i < (INPUT_STRING_SIZE - 1); i++){
        character_string[i] = string_set[rand() % (INPUT_STRING_SIZE - 1)];
    }
    
    character_string[INPUT_STRING_SIZE - 1] = '\0'; // at spot 6, the null value
    
    return character_string;
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

