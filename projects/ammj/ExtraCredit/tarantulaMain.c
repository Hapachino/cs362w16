#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#include <getopt.h>
#include "tarantula.h"
#include <regex.h>

/**
 * Function: runTest
 * Runs the test in a child process to catch the return value in the parent process
 * Inputs: filename of testfile
 * Outputs: return value from file
 */
int runTest(char *filename)
{

	assert(strcmp(filename, "") != 0);

	// setup the pipe
  int fd[2], nbytes;
  pid_t childpid;

  char readbuffer[80];
  char* fileCmd = (char*)malloc(50 * sizeof(char));
  char* endPtr = (char*)malloc(50 * sizeof(char));

  int result = -1;
  int base = 10;
  int rxFlag = 0;

  // generate the command
  sprintf(fileCmd, "./%s 0; echo $?", filename);

  // crate the pipe
	pipe(fd);

  if((childpid = fork()) == -1)
  {
  	perror("Fork");
  	exit(1);
  }

  if(childpid == 0)
  {
  	// child closes up input side of pipe
  	close(fd[0]);
  	dup2(fd[1], 1); // send stdout to pipe
  	dup2(fd[1], 2); // send stderr to pipe

  	// send string through the output side
  	system(fileCmd);

  	//write(fd[1], string, (strlen(string) +1));
  	exit(0);

  } else {

  	rxFlag = 0;

  	// parent closes output side of pipe
  	close(fd[1]);

  	// read in string from the pipe
  	nbytes = read(fd[0], readbuffer, sizeof(readbuffer));

  	// if incorrect number of bytes read set flag to exit
  	if(nbytes != 2)
  	{
  	  rxFlag = 1;
  	}
  }

  // close the file descriptors
  close(fd[0]);
  close(fd[1]);

  // exit if incorrect bytes read
  if(rxFlag == 1)
  {
  		printf("Error in return value: Test should return 1 or 0 from main\n");
  		return -1;
  }

  // check seed is an integer
  result = strtol(readbuffer, &endPtr, base);
  errno = 0;

  // error number
  if ((errno == ERANGE && (result == LONG_MAX || result == LONG_MIN))
  			|| (errno != 0 && result == 0)) {
  	printf("Error converting return value to integer.\n");
  	return -1;
  }

  // return the result
  return result;

}

/**
 * Function: test
 * Runs the test specified
 * Inputs: struct tarantula, name of the test (should match a makefile rule)
 * Outputs: 0 on successful completion
 */
int test(struct tarantula *t, char* test, char* fileTest, int iterations, int seed){

	assert(t != NULL);
	assert(strcmp(test, "") != 0);

	int status = 0;
	int i;
	char* fileName = (char*)malloc(50 * sizeof(char));
	char* cmdFile = (char*)malloc(50 * sizeof(char));

	// make the test file to ensure it is the latest version
	sprintf(cmdFile, "make %s", test);

	printf("Making file to test: %s\n", cmdFile);
	status = system(cmdFile);

	if(status == -1){
	    printf("Error Occurred making %s", test);
	    return -1;
	}

	for(i=0; i<iterations; i++)
	{

		sprintf(fileName, "%s %d", test, i+seed);
		t->passed = runTest(fileName);

		// if -1 returned from the test run exit this functions
		if(t->passed == -1){
			printf("Error getting pass/fail from test... Exiting\n");
			return -1;
		} else {
			assert(t->passed == 0 || t->passed == 1);
		}

		// if the test passed add to pass otherwise add to fail
		if(t->passed == 1)
			t->totalPass++;
		else
			t->totalFail++;

		// increment the total tests
		t->totalTests++;

		if(status == -1){
				printf("Error Occurred running %s", test);
				return 0;
		}

		// parse the gcov file and put in t->pass if t->passed = 1 or t->fail otherwise
		tarParseGcovFile(fileTest, t);

	}

	return 0;

}

void printHelp(char* fileName){
	printf("Help Menu\n");
	printf("**********\n");
	printf("Usage:\n   %s -t testfile -m fileUnderTest [-i iterations] [-s seed] [-o]\n", fileName);
	printf("\n");
	printf("Required Switches: -t [makerule] -m [makerule]\n");
	printf("\n");
	printf("\t-h:  help menu\n");
	printf("\t-v:  version\n");
	printf("\t-t:  make rule for test file (make rule must match testfile name)\n");
	printf("\t-m:  make rule for file under test (make rule must match file under\n");
	printf("\t     test name\n");
	printf("\t-o:  [optional] used for html output\n");
	printf("\t-i:  [optional] followed by an integer for number of iterations of the\n");
	printf("\t     test file\n");
	printf("\t     (default: 10)\n");
	printf("\t-s:  [optional] followed by an integer for the starting seed\n");
	printf("\t     (default: 9987)\n");
}

int main(int argc, char *argv[]){


	struct tarantula *t = createTarantula();
	int r;
	int opt = 0;
	char *inFile = (char*)malloc(100 * sizeof(char));
	char *fileTest = (char*)malloc(100 * sizeof(char));
	char *gcovFile = (char*)malloc(100 * sizeof(char));
	char *writeFile = (char*)malloc(100 * sizeof(char));
	char *outType = (char*)malloc(6 * sizeof(char));
	int iterations = 1;
	int seed = 9987;


	// flags
	int hFlag = 0, vFlag = 0, tFlag = 0, mFlag = 0;

	sprintf(outType, "txt");

	while((opt = getopt(argc, argv, "hvoi:s:t:m:")) != -1){

		switch(opt){
		case 'h':
			hFlag = 1;
			break;
		case 'v':
			vFlag = 1;
			break;
		case 'i':
			iterations = atoi(optarg);
			printf("\nIterations %d\n", iterations);
			break;
		case 'o':
			sprintf(outType, "html");
			break;
		case 's':
			seed = atoi(optarg);
			break;
		case 't':
			tFlag = 1;
			inFile = optarg;
			printf("Test File %s\n", inFile);
			break;
		case 'm':
			mFlag = 1;
			fileTest = optarg;
			printf("File UnderTest %s\n", fileTest);
			break;
		case '?':
			printf("Usage: %s -t [testfile] -m [file under test] -i [iterations]", argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	if(hFlag == 1 || vFlag == 1){
		if(vFlag == 1){
			printf("Version: tarantulaMain 1.0.0\n\n");
		}
		if(hFlag == 1){
			printHelp(argv[0]);
		}
		exit(EXIT_SUCCESS);
	}

	if(tFlag == 0 || mFlag == 0){
		if(!tFlag == 1){
			printf("Test file make rule is required\n");
		}
		if(!mFlag == 1){
			printf("File UnderTest make rule is required\n");
		}
		printHelp(argv[0]);
		exit(EXIT_FAILURE);
	}

	sprintf(gcovFile, "%s.c.gcov", fileTest);

	r = tarantInitLines(fileTest);

	if(r == -1){
		printf("Couldn't make file under test\n");
		exit(EXIT_FAILURE);
	}

	r = test(t, inFile, fileTest, iterations, seed);

	// if the test ran write the data and return -1 for failure
	if(r != -1)
	{
		// output the html version
		if(strcmp(outType, "html") == 0){
			sprintf(writeFile, "%s.tarantula.html", inFile);
			tarWriteHtml(writeFile, inFile, gcovFile, t);
		}
		else
		{
			sprintf(writeFile, "%s.tarantula.txt", inFile);
			tarWriteTarantula(writeFile, inFile, gcovFile, t);
		}
	} else {
		printf("Error running test\n");
		return -1;
	}

	printf("Finished - results store in %s\n", writeFile);

	// cleanup memory
	free(t);

	return 0;
}
