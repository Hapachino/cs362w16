/*
 * tarantula.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <errno.h>

#define LC_CAPACITY 10
#define BUF_SIZE 200

struct lineCounts{
	long size;
	long capacity;
	long *lineCount;
};

struct tarantula{
	int totalTests;
	int totalPass;
	int totalFail;
	int passed;
	struct lineCounts* pass;
	struct lineCounts* fail;
	struct lineCounts* total;
};

/**
 * Function: initLineCount
 * initializes linCount structs
 * inputs: lineCounts struct
 * outputs: 0 for completion, -1 for error
 */
int initLineCount(struct lineCounts *lc){

	// check that lc is not Null
	if(lc == NULL)
		return -1;

	// initialize the values in the struct
	int i;
	lc->size = 0;
	lc->capacity = LC_CAPACITY;
	lc->lineCount = (long*)malloc(LC_CAPACITY * sizeof(long));

	// update all lines in lineCount to 0
	for(i = 0; i < LC_CAPACITY; i++){
		lc->lineCount[i] = 0;
	}

	// return 0 for completion
	return 0;
}

/**
 * Function: createLineCount
 * declares lineCounts struct
 * inputs: none
 * outputs: lineCounts struct
 */
struct lineCounts* createLineCount(){

	int r;

	// create the struct and initialize
	struct lineCounts* newLC = (struct lineCounts*)malloc(sizeof(struct lineCounts));
	r = initLineCount(newLC);

	if(r != 0)
		printf("Error initializing struct!");

	// return the struct
	return newLC;
}

/**
 * Function initTarantula
 * Initializes a tarantula struct
 * Inputs tarantula struct
 * Outputs: -1 on failure, 0 on success
 */
int initTarantula(struct tarantula *t){

	if(t == NULL)
		return -1;

	t->totalTests = 0;
	t->passed = 0;
	t->pass = createLineCount();
	t->fail = createLineCount();
	t->total = createLineCount();
	return 0;

}

/**
 * Function: createTrantula
 * defines a tarantula struct and calls initialization
 * Inputs: none
 * Outputs:  Initialized tarantula struct
 */
struct tarantula* createTarantula(){

	struct tarantula* newT = (struct tarantula*)malloc(sizeof(struct tarantula));
	assert(newT != NULL);

	initTarantula(newT);
	return newT;

}

/**
 * Function: resizeLineCount
 * Resizes the dynamic array for a lineCounts struct
 * Inputs: lineCounts struct to be resized
 * Ouptus: size of new dynamic array
 */
int resizeLineCount(struct lineCounts *lc){

	// create the ptr to a larger array
	long newSize = lc->capacity * 2;
	long *temp = (long*)malloc(newSize * sizeof(long));
	long *tp;
	long i;

	// copy the values into the new ptr location
	for(i=0; i<lc->capacity; i++){
		temp[i] = lc->lineCount[i];
	}

	// move the struct ptr to the new location
	tp = lc->lineCount;
	lc->lineCount = temp;

	// free the memory in the old location
	free(tp);

	// return the new size
	return lc->capacity * 2;

}

/**
 * Function: updateLineCount
 * Adds the value to existing total in the linecount defined by lc
 * Calls resize if required
 * Inputs: lineCounts struct, index for lineNumber, value to add to value stored in index
 * Outputs: 0 on successful completion
 */
int updateLineCount(struct lineCounts *lc, long index, long value){

	assert(lc != NULL && index >=0);

	long oldCapacity = lc->capacity;
	long newCapacity = lc->capacity;
	long i;

	// resize so index can be added if greater than lc->capacity
	while(index >= lc->capacity - 1){

		newCapacity = resizeLineCount(lc);
		lc->capacity = newCapacity;

		// zerofill the new space
		for(i = oldCapacity; i < newCapacity; i++)
			lc->lineCount[i] = 0;
	}

	// set the runs of the line number
	lc->lineCount[index] = lc->lineCount[index] + value;

	// if index is greater than size - 1, set current size to index + 1
	if(index > lc->size - 1){
		lc->size = index + 1;
	}

	return 0;

}

/**
 * Function: getLineCount
 * returns the lineCount stored at location of index
 * inputs:  struct lineCounts, index to return value from
 * Output:  returns lineCount on successful completion
 */
int getLineCount(struct lineCounts *lc, long index){

	long lineCount = 0;
	assert(lc != NULL);
	assert(lc->lineCount != NULL);
	assert(index >= 0);
	assert(lc->capacity < index + 1);

	// get lineCount and return it
	lineCount = lc->lineCount[index];
	return lineCount;

}

/**
 * Function: uninitLineCount
 * Uninitilizes a lineCount for a teardown
 * Inputs: struct lineCount
 * Output 0 on successful completion
 */
int uninitLineCount(struct lineCounts *lc){

	assert(lc != NULL);

	int i;

	// 0 out the values in the lineCounts struct
	for(i=0; i<lc->capacity; i++)
	{
		lc->lineCount[i] = 0;
	}

	lc->size = 0;
	lc->capacity = 0;

	// free the memory
	free(lc->lineCount);
	free(lc);

	// return 0 for successful completion
	return 0;

}

/**
 * Function: printLines
 * print the lines of the struct to visually see values
 * Input:  struct lineCounts
 * Output:
 */
int printLines(struct lineCounts *lc){
	assert(lc != NULL);

	long i;

	// cycle through and print each line
	for(i=0; i<lc->size; i++){
		if(lc->lineCount[i] != 0)
			printf("%lu: %lu\n", i, lc->lineCount[i]);
	}

	// return 0 on successful completion
	return 0;
}

/**
 * Function: tarantInitLines
 * reads the number of lines in file under test
 * Inputs: fileName
 * Outputs: -1 on failure, count on successful read
 */
int tarantInitLines(char *fileName)
{

	assert(strcmp(fileName, "") != 0);

	FILE *fp;
	int buf = BUF_SIZE;
	char curLine[buf];
	int count = 0;

	sprintf(fileName, "%s.c", fileName);

	// open the file in read mode and count each line read
	if((fp = fopen(fileName, "r")))
	{
		while((fgets(curLine, buf, fp)) != NULL){
			count++;
		}

		fclose(fp);

	} else {
		return -1;
	}

	return count;
}

/**
 * Function calculateColor
 * returns the color for suspiciousness
 * Input: suspiciousness as an int
 * Output:  color
 */
char* calculateColor(int suspiciousness){

	assert(suspiciousness >= 0);

	char* color = (char*)malloc(10 * sizeof(char));

	if(suspiciousness == 0)
		sprintf(color, "%s", "green");
	else if(suspiciousness > 0 && suspiciousness < 0.49)
		sprintf(color, "%s", "yellow");
	else if(suspiciousness > 0.49 && suspiciousness < 1)
		sprintf(color, "%s", "orange");
	else if(suspiciousness == 1)
		sprintf(color, "%s", "red");

	return color;
}

/**
 * Function:  calculateSusp
 * Calculates the suspiciousness of a given line
 * Inputs: line Number, struct tarantula
 * Outputs: suspiciousness as double
 */
long double calculateSusp(int i, struct tarantula *t){

	long totalPassed = t->totalPass;
	long totalFailed = t->totalFail;
	long statementPass, statementFail;
	long double passedFrac;
	long double failedFrac;
	long double suspiciousness = 0.0;

	if(i < t->pass->size)
		statementPass = t->pass->lineCount[i];
	else
		statementPass = 0;

	if(i < t->fail->size)
		statementFail = t->fail->lineCount[i];
	else
		statementFail = 0;

	if(totalPassed == 0 || statementPass == 0)
		passedFrac = 0;
	else
		passedFrac = (statementPass/totalPassed);

	if (totalFailed == 0 || statementFail == 0)
		failedFrac = 0;
	else
		failedFrac = statementFail/totalFailed;

	if(failedFrac == 0)
		suspiciousness = 0;
	else if(failedFrac >=1 && passedFrac == 0)
		suspiciousness = 1;
	else
		suspiciousness = failedFrac/(passedFrac+failedFrac);

	return suspiciousness;
}

/**
 * Function:  tarWriteTarantula
 * Calculates the color and writes the color for the line to a txt file
 * Inputs: text file to write to, struct tarantula
 * Outputs: file
 */
int tarWriteTarantula(char *fileName, char *inFile, char *tFile, struct tarantula *t){

	assert(t != NULL);
	assert(t->pass != NULL);
	assert(t->fail != NULL);
	assert(t->total != NULL);
	assert(strcmp(fileName, "") != 0);

	long i;
	long double suspiciousness = 0.0;
	char *color = (char*)malloc(10*sizeof(char));

	// declaration for command
	char* command = (char*)malloc(BUF_SIZE * sizeof(char));

	// delete old file if it is there
	sprintf(command, "rm -f %s", fileName);
	system(command);

	// open file for writing and create if not exists
	FILE *wrFile = fopen(fileName, "ab");

	// return -1 on error
	if(wrFile == NULL){
		printf("Error:  Couldn't open file for writing!\n");
		return -1;
	}

	fprintf(wrFile, "Tarantula\n");
	fprintf(wrFile, "Test: %s\n", inFile);
	fprintf(wrFile, "File Under Test: %s\n", tFile);
	fprintf(wrFile, "\n\n");

	// calculate and output suspiciousness to file
	for(i=0; i<=t->total->size; i++){

		suspiciousness = calculateSusp(i, t);
		sprintf(color, "%s", calculateColor(suspiciousness));
		fprintf(wrFile, "Line %lu: %.2Lf - %s\n", i, suspiciousness, color);

	}

	fclose(wrFile);

	return 0;
}

/**
 * Function:  tarWriteHtml
 * Calculates the color and outputs the lines in the color into an html file
 * Inputs: html file to write to, file with code, struct tarantula
 * Outputs: html file and 0 on successful completion
 */
int tarWriteHtml(char *fileName, char *inFile, char *tFile, struct tarantula *t){

	assert(t != NULL);
	assert(t->pass != NULL);
	assert(t->fail != NULL);
	assert(t->total != NULL);
	assert(strcmp(fileName, "") != 0);
	assert(strcmp(inFile, "") != 0);
	assert(strcmp(tFile, "") != 0);

	// declarations for suspiciousness
	long double suspiciousness = 0.0;
	char *color = (char*)malloc(10*sizeof(char));

	// declaration for command
	char* command = (char*)malloc(BUF_SIZE * sizeof(char));

	// declarations to read and code lines to html output
	char curLine[BUF_SIZE];
	char *curChunk = (char*)malloc(BUF_SIZE * sizeof(char));
	char *curLN = (char*)malloc(BUF_SIZE * sizeof(char));
	char *curCode = (char*)malloc(BUF_SIZE * sizeof(char));
	char *endPtr;
	long lineNumber;
	int base = 10;
	int errno;
	int count = 0;

	// delete old file if it is there
	sprintf(command, "rm -f %s", fileName);
	system(command);

	FILE *wrFile = fopen(fileName, "ab");
  FILE *rdFile;

	if(wrFile == NULL){
		printf("Error:  Couldn't open file for writing!\n");
		return -1;
	}

	curChunk = "NONE";
	curLN = "NONE";

	fprintf(wrFile, "%s\n", "<html><body>");
	fprintf(wrFile, "<h1>Tarantula</h1>\n");
	fprintf(wrFile, "<h3>Test: %s</h3>\n", inFile);
	fprintf(wrFile, "<h3>File Under Test: %s</h3>\n", tFile);
	fprintf(wrFile, "<br />\n");

	printf("Starting read\n");

	if((rdFile = fopen(tFile, "r")))
	{
		while((fgets(curLine, BUF_SIZE, rdFile)) != NULL){

			// split the line with ":" to get the first chunk
			curChunk = strtok(curLine, ":");
			if(curChunk != NULL){

				// split the line with ":" to get the line number
				curLN = strtok(NULL, ":");

				if(curLN != NULL){

						// get the lineNumber if there is a numeric value
						lineNumber = strtol(curLN, &endPtr, base);

						// calculate suspiciousness and color
						suspiciousness = calculateSusp(lineNumber, t);
						sprintf(color, "%s", calculateColor(suspiciousness));

						// split the line with ":" to get the line number
						curCode = strtok(NULL, "\n");

						// write data to the file
						if(curCode != NULL){
							fprintf(wrFile, "<p>%7.7lu: <font color='%s'><b>%7.7s</b> %s</font></p>",
									lineNumber, color, color, curCode);
						}

						count++;
				}
			}
		}
	}

	fclose(rdFile);

	fprintf(wrFile, "</body></html>");

	fclose(wrFile);

	return 0;
}

/**
 * Function: tarParseGcovFile
 * reads gcov file, calculates the deltas and processes the deltas
 * Inputs: fileName, struct Tarantula
 * Outputs: count on success -1 on failure
 */
int tarParseGcovFile(char *fileName, struct tarantula *t)
{
  //http://man7.org/linux/man-pages/man3/strtol.3.html
	// assertions
	assert(!(strcmp(fileName, "") == 0));
	assert(t != NULL);

	int status;
	char *command = (char*)malloc(50 * sizeof(char));

	// generate the updated gcov data
	sprintf(command, "gcov %s >> %s.out.gcov", fileName, fileName);
	status = system(command);
	if(status == -1){
		  printf("Error Occurred using gcov %s", fileName);
		  return 0;
	}

	// open the file in read mode
	FILE *fp;

	char curLine[BUF_SIZE];
	char *curChunk = (char*)malloc(BUF_SIZE * sizeof(char));
	char *curLN = (char*)malloc(BUF_SIZE * sizeof(char));
	char *endPtr;
	int base = 10;
	int errno;

	long iterations;
	long lineNumber;

	int count = 0;
	int diff = 0;

	char *fName = (char*)malloc(50 * sizeof(char));
	struct lineCounts *lc = t->pass;

	curChunk = "NONE";
	curLN = "NONE";

	if(t->passed == 0)
		lc = t->fail;

	// identify the full name with .gcov
	sprintf(fName, "%s.gcov", fileName);

	if((fp = fopen(fName, "r")))
	{
		// while there are lines in the file
		while((fgets(curLine, BUF_SIZE, fp)) != NULL){

			// get the iterations
			curChunk = strtok(curLine, ":");
			if(curChunk != NULL){

				// and line number
				curLN = strtok(NULL, ":");
				if(curLN != NULL){

					iterations = strtol(curChunk, &endPtr, base);

					if (!((errno == ERANGE && (iterations == LONG_MAX || iterations == LONG_MIN))
					                   || (errno != 0 && iterations == 0))){
						errno=0;
						// convert Line number to integer
						lineNumber = strtol(curLN, &endPtr, base);
						diff = iterations - t->total->lineCount[lineNumber];

						// if there is a difference add one to the store to identify line was run
						if(diff > 0){
							updateLineCount(t->total, lineNumber, 1);
							updateLineCount(lc, lineNumber, 1);
							count++;
						}
					}
				}
			}
		}

		// cleanup file
		fclose(fp);

	} else {
		return -1;
	}
	return count;
}
