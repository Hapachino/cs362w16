/* Joseph Vidal Quiz 2 write up
    
    My first  step to implement the random tester was to create a random character generator
    and I chose to first try it will all standard characters from ASCII.  This is a bit overkill
    but the program consistantly hit state 9 in an almost instant fashion so I figured it could
    stay just as it was.

    char inputChar()
    {
        int n = (rand() % (126 - 32 + 1)) + 32;
        char c = (char) n;
    
         return c;
    }


    My next step was to create a random string generator.  My initial attempt proved to broad with 
    characters from the entire ASCII character list being allowed.  After a few attempts, I settled 
    on the idea that since 'e' is the lowest value and 't' is the highest, that these two characters
    would represent a good range.  I also guaranteed '\0' to end every string and ensured that each 
    string would be exactly 6 characters long.  
    
    char *inputString()
    {
        char str[6];
        int i;
        for(i = 0; i < 5; i++){
        int n = (rand() % (116 - 101 + 1)) + 101;
        char c = (char) n; 
        str[i] = c;
        }
        str[5] = '\0';
        char *final = str;
        return final;
    }

    With this level of randomization, I have been able to reliably produce the error.  The error has 
    printed as fast as in the 130,000 iteration range and as slow as in the 2.8 million iteration range.
    With the program only taking a few minutes to get into the millions I figure that this is an 
    acceptable amount of iterations to produce the error in.    
*/