/* Random Testing Quiz 2 */
/* by Richard Ratliff */

/* 
** I used a #define TRACE 0 to print only the last iteration with error and
** TRACE 1 to print all iterations which is how the quiz code is submitted.
** TRACE 0 was used for execution times on flip. 
** 
** I used a #define FUZZ progressing the implementations of inputChar
** and inputString. The following is included at the top of testme.c:
** 
// define level of FUZZ
//     where 0 = expected outputs only by inputChar(), reset only from inputString()
//           1 = expected outputs only by inputChar() and inputString() excluding \0
//           2 = expected outputs only by inputChar() and inputString() including \0 
//           3 = all ASCII keyboard chars by inputChar() and expected only by inputString() including \0 
//           4 = all ASCII keyboard chars by inputChar() and all a-z by inputString() excluding \0 
//           5 = all ASCII keyboard chars by inputChar() and all A-z by inputString() excluding \0 
//           6 = all ASCII keyboard chars by inputChar() and inputString() excluding \0 
**
** #define FUZZ 0
** inputChar() uses a switch statement to return only the expected characters
** to change state. inputString() is hard coded to return the reset string.
** Minimum 51 maximum 125 iterations observed to get to the "error".
** Execution time neglible.
**
** #define FUZZ 1
** inputChar() uses a switch statement to return only the expected characters
** to change state. inputString() uses a switch statement to return only the
** expected characters to cause reset, excluding a null, so the string length
** returned is always a 5 character string.
** Minimum 97 maximum 3208 iterations observed to get to the "error".
** Execution time neglible.
**
** #define FUZZ 2
** inputChar() uses a switch statement to return only the expected characters
** to change state. inputString() uses a switch statement to return only the
** expected characters to cause reset, now including a null, so string length
** can vary but is a maximum of 5 characters.
** Minimum 257 maximum 5624 iterations observed to get to the "error".
** Execution time neglible.
**
** #define FUZZ 3
** inputChar() now uses purely the rand() function to return visible keyboard
** characters. inputString() uses a switch statement to return only the
** expected characters to cause reset, including a null, so string length
** can vary but is a maximum of 5 characters.
** Minimum 619 maximum 19602 iterations observed to get to the "error".
** Execution time still neglible.
**
** #define FUZZ 4
** inputChar() continues using the rand() function to return visible keyboard
** characters. inputString() now uses the rand() function to return characters
** a-z. Now again the returned string consists of 5 and only 5 characters.
** Minimum 660,033 maximum 39,276,418 iterations observed to get to the "error".
** Up to about half a minute - starting to run using "% date; testme; date".
**
** #define FUZZ 5
** inputChar() continues using the rand() function to return visible keyboard
** characters. inputString() now uses the rand() function to return characters
** A-Z, a-z, and a few extras in between Z and a on the ASCII chart. 
** Returned string consists of 5 and only 5 characters.
** Execution time starts to really be a concern because I am running on flip.
** Minimum 37,621,049 maximum 702,583,044 iterations observed to get "error".
** About one minute or less required for each run.
**
** #define FUZZ 6
** inputChar() continues using the rand() function to return visible keyboard
** characters. inputString() now uses the rand() function to return visible
** keyboard characters. Returned string consists of 5 and only 5 characters.
** Execution time takes a funny turn and because of that I ran only 3 times.
** 
** Minimum   730,479,052 iterations to get "error" - about 1 minute.
** Maximum 2,079,831,867 iterations to get "error" - about 3 minutes.
** However 1,108,392,415 iterations to get "error" - took 11 minutes.
** Other factors are coming into play now for execution time.
** I am afraid other students on flip may be affected.
** Stopped quiz here.
**
** Ideas for future development:
** - Random length strings like FUZZ cases 2 and 3.
** - Increase string length size to 6 and above.
** - Include non-visible ASCII characters.
** - Expand to UTF characters.
**
*/

