/* -----------------------------------------------------------------------
 * Jennifer Mendoza 
 * Quiz 2- Random Tester
 * Documentation for testme.c
 * Due 1/31/16
 * -----------------------------------------------------------------------
 */
 
 /*I first studied the code to understand what it was supposed to do. So, to explain the
 code, it simply changes state depending on c. The error will print when the program 
 reaches state 9 and the inputString() function outputs "reset". The following is my
 code.
 
 This inputChar function returns a random lowercase letter from the alphabet and the
 special symbols. Look at the pValues array.
 char inputChar()
{
    // TODO: rewrite this function
	int randomIndex;
	char randomChar;
	char pValues[34]="abcdefghijklmnopqrstuvwxyz[](){} ";
	
	randomIndex= 0+rand()%33;
	randomChar=pValues[randomIndex];
	
	return randomChar;
}

For this function, my initial thought was to create an array with sizes ranging from 1-5
and using the entire alphabet to eventually output "reset". I let this run on my computer
but it was still running after an hour. I then changed my code to output a string of 5 
letters. This also took a while to run. I decided to drastically decrease the available 
letters so that the word "reset" would be reached more quickly. This ran too quick, so 
I changed the string length back to random lengths from 1-5.
char *inputString()
{
    // TODO: rewrite this function
	int i;
	int randomIndex;
	int n=1+rand()%6;
//	char sValues[27]="abcdefghijklmnopqrstuvwxyz"; This took too long.
	char sValues[7]="restab"; //reduced the characters drastically to get the word reset quickly
	char *randomString=malloc(sizeof(char)*n);
	
	for (i=0;i<n-1;i++)
	{
	//	randomIndex= rand()%27;
		randomIndex= rand()%6;
		randomString[i]=sValues[randomIndex];
	}
	randomString[n]='\0';
    return randomString;
}