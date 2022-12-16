#ifndef EXTERNALSORT_H
#define EXTERNALSORT_H

#include <stdio.h>
#include <stdlib.h>

void sort(FILE* sourceP, FILE* destinationP);

void openRunsFiles(FILE** runs1PP, FILE** runs2PP, char mode[2]);

void txtToRunsFiles(FILE* sourceP, FILE* runs1P, FILE* runs2P);

void runsToMergeFile(FILE* mergeP, FILE* runs1P, FILE* runs2P);

int copyUntilGreater(FILE* destP, FILE* sourceP, int limit);

void switchCurRunFile(FILE** curFilePP, FILE* runs1P, FILE* runs2P);

#endif /* treeMethods.h */