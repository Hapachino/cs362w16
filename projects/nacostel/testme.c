#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  //initialize array of alphabets and other possible chars
  char characterSet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h','i', 'j', 'k', 'l', 'm', 'n', 'o', 'p','r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '{', '(', ' ', '}', ']', ')' };
   
  int x;
  char letter;
  
  //determine a random array index
  x = rand() % 34;
  letter = characterSet[x];
  
  return letter;
}

char *inputString()
{
   //change this number to 1 for more random version
   int mode = 2;
   

   char *string = malloc(5*sizeof(char));

   //less random, faster version
   if(mode == 2){
	   //initialize array of possible chars [limited to find error in reasonable amount of time]
	   char characterSet[] = {'r', 'e', 's', 't', 'e' };
	   int x;
	   
   
	   //for each letter in string
	   for(int i = 0; i <= 5; i++){
			//determine random array index
			x = rand() % 5;
			string[i] = characterSet[x];
	    }

	   //null terminate
	   *string++ = '\0';
   }

   //more random, slower version
   else{
	 //initialize array of possible chars, modified to include all letters of alphabet 
	   char characterSet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h','i', 'j', 'k', 'l', 'm', 'n', 'o', 'p','r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	   int x;
	
   
	   //for each letter in string
	   for(int i = 0; i <= 5; i++){
			//determine random array index
			x = rand() % 27;
			string[i] = characterSet[x];
	    }

	   //null terminate
	   *string++ = '\0';
   }

   return string;
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
