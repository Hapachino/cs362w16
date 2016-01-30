/*************************
Author: Philip Jones
Term: Winter 2016

*************************/
// In order to get the error to trigger, I need specific set of characters to trigger in
// succession-- specifically, [({ ax})] for the characters, and reset\0 for the string.
// Obviously, it would be possible to write a script to produce these exact values and characters,
// but the quiz indicated that random values were needed. Thus, I used the random() function
// with a mod 256 to get the 256 possible characters. Every time inputChar is run, a random
// character is returned. For inputString, I used a similar process, but many more times.
// Because the string checks the first 6 addresses of inputString s, I formulated my random
// string function to generate a random 6-digit character. In order to save time, I implement 
// the random characters to only be lowercase a-z (because those are what trigger the error).
// Finally, the 6th address is assigned to 0, in order to trigger the check for the newline
// character. 
// The main testme() function finds the "error" message by looping through the while loop a 
// great number of times. When the random single character function outputs a "[", the first
// condition is met and the state is increased to 1. Only after the state is 1, if the function
// returns a "(" then the state will be increased to 2. And so on and so forth, until the state
// reaches 9, which is needed the trigger the error. However, along with state = 9, every single
// one of the addresses in the random string need to be set and in the right order to spell out
// "reset". The successes don't build on each other as in the char portion-- if the string spells
// "resep", then it doesn't trigger and every address value is determined randomly again. Thus,
// though this portion of the check has fewer possible random values, you can expect it will 
// take much longer to come to the success of an "error".