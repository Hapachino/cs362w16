Todd Waddell
CS 362 400 W16
Random Testing Quiz 2

inputChar()
    inputChar generates and returns a random number between 32 and 126, the
    ANSI character range for the punctuation outlined in the code.


inputString()
    inputString generates a string of 5,lowercase, random characters based
    on the ansi codes between 97  and 122.  
    An earlier version fuzzed the five letters of reset, based on a random
    character selection.  But, after re-reading the assignment, I went back
    through and made the string generation completely random.  I assume the
    intent was to give us a feeling of how long a computer takes to stumble
    on a random string.  If that was an incorrect interpretation, please
    let me know.
