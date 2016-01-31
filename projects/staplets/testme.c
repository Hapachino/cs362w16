#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	char myChar;
	
	//Produce ascii character between the space and closed curly bracket.
	myChar = rand() % 94 + 32 ;
	
    return myChar;
}

char *inputString()
{
    // TODO: rewrite this function
	int n = 5;
	char *myString = malloc(n*sizeof(char));
	int i;
	
	char oneChar;
//printf("test");
	char word[4] = "rest";	

		int r = 0;
		int e = 0;
		int s = 0;
		int t = 0;

		//Place while loops in to force a quicker completion
		while(r == 0){
			oneChar = rand() % 4;
			if(oneChar == 0){	
				myString[0] = word[oneChar];
				r++;	
			}
		}

		while(e == 0){
			oneChar = rand() % 4;
			if(oneChar == 1){
				myString[1] = word[oneChar];
				e++;
			}
		}

		while(s == 0){
			oneChar = rand() % 4;
			if(oneChar == 2){
				myString[2] = word[oneChar];
				s++;	
			}
		}
		
		while(e == 1){
			oneChar = rand() % 4;
			if(oneChar == 1){ 
				myString[3] = word[oneChar];
				e++;
			}
		}

		while(t == 0){
			oneChar = rand() % 4;
			if(oneChar == 3){		
				myString[4] = word[oneChar];
				t++;
			}
		} 

		

	//Give the string a null character to end
	myString[5] = '\0';
		
    return myString;
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
