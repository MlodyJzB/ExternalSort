#ifndef EXTERNALSORT_H
#define EXTERNALSORT_H

#include <stdio.h>
#include <stdlib.h>

void sort(FILE* sourceP, FILE* destinationP);

void openRunFiles(FILE** runs1PP, FILE** runs2PP);

void txtToRunsFiles(FILE* sourceP, FILE* runs1P, FILE* runs2P);

void switchCurRunFile(FILE** curFilePP, FILE* runs1P, FILE* runs2P);

#endif /* treeMethods.h */