//Random Testing Quiz 2

For inputChar(), I had it return a single character within the range of ASCII characters starting from ' ' (space), which is number 32, until the end of the ASCII alphabet at 127. Character values below 32 like tab or backspace would mess with the program.

For inputString(), I had it return a randomly generated null-terminated string containing five lowercase letters. In my limited testing, it seems like the program reaches state == 9 fairly quickly. There are a lot more combinations with 26 options for each of the five characters in the string, and when allowing repeated input you end up above a million iterations before generating the desired input string "reset\0".