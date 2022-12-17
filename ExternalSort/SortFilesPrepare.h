#ifndef SORT_FILES_PREPARE_H
#define SORT_FILES_PREPARE_H

#include <stdio.h>
#include <stdlib.h>

void openRunsFiles(FILE** runs1PP, FILE** runs2PP, char mode[2]);

void closeRunsFiles(FILE* runs1P, FILE* runs2P);

void openMergeFile(FILE** mergePP, char mode[2]);

void txtToMergeFile(FILE* sourceP, FILE* mergeP);

void mergeToTxtFile(FILE* destP, FILE* mergeP);

void clearMergeAndRuns();

void clearFile(const char* fileName);

#endif /* SortFilesPrepare.h */