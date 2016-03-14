/*
 * tarantula.h
 */

#ifndef TARANTULA_H_
#define TARANTULA_H_

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

void initLineCount(struct lineCounts *lc);
struct lineCounts* createLineCount();
void initTarantula(struct tarantula *t);
struct tarantula* createTarantula();
int resizeLineCount(struct lineCounts *lc);
int updateLineCount(struct lineCounts *lc, long index, long value);
int getLineCount(struct lineCounts *lc, long index);
int uninitLineCount(struct lineCounts *lc);
int tarantInitLines(char *fileName);
int printLines(struct lineCounts *lc);
int tarParseGcovFile(char *fileName, struct tarantula *t);
int tarWriteHtml(char *fileName, char *inFile, char *tFile, struct tarantula *t);
int tarWriteTarantula(char *fileName, char *inFile, char *tFile, struct tarantula *t);

#endif /* TARANTULA_H_ */
