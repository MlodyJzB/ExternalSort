#ifndef EXTERNALSORT_H
#define EXTERNALSORT_H

#include <stdio.h>
#include <stdlib.h>

void sort(FILE* sourceP, FILE* destinationP);

void switchCurRunFile(FILE** curFilePP, FILE* runs1P, FILE* runs2P);

int runsToMergeFile(FILE* mergeP, FILE* runs1P, FILE* runs2P);

int copyUntilGreater(FILE* destP, FILE* sourceP, int limit);

void mergeToRunsFiles(FILE* mergeP, FILE* runs1P, FILE* runs2P);

#endif /* ExternalSort.h */