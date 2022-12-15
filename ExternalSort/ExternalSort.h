#ifndef EXTERNALSORT_H
#define EXTERNALSORT_H

#include <stdio.h>
#include <stdlib.h>

void sort(FILE* sourceP, FILE* destinationP);

void txtToRunsFiles(sourceP, runs1, runs2);

void openRunFiles(FILE** runs1PP, FILE** runs2PP);

#endif /* treeMethods.h */