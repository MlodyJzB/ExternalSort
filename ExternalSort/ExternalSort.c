#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../ExternalSort/ExternalSort.h"

#define END INT_MAX
#define BEGINNING INT_MIN

void sort(FILE *sourceP, FILE *destinationP) {
	FILE* runs1P;
	FILE* runs2P;

	openRunsFiles(&runs1P, &runs2P, "r");
	txtToRunsFiles(sourceP, runs1P, runs2P);

	fclose(runs1P);
	fclose(runs2P);
}

void openRunsFiles(FILE** runs1PP, FILE** runs2PP, char mode[2]) {
	if (fopen_s(runs1PP, "runs1.bin", mode) != 0) {
		exit(1);
	}
	if (fopen_s(runs2PP, "runs2.bin", mode) != 0) {
		exit(1);
	}
}

void txtToRunsFiles(FILE* sourceP, FILE* runs1P, FILE* runs2P) {
	int num;
	int prevNum = INT_MIN;
	FILE* curFileP = runs1P;

	while (fscanf_s(sourceP, "%d", &num) != EOF) {
		if (num < prevNum) {
			switchCurRunFile(&curFileP, runs1P, runs2P);
		}

		fwrite(&num, sizeof(int), 1, curFileP);
		prevNum = num;
	}
}

void runsToMergeFile(FILE* mergeP, FILE* runs1P, FILE* runs2P) {
	int curNumRuns1 = BEGINNING;
	int curNumRuns2 = BEGINNING;

	while ((curNumRuns1 != END)||(curNumRuns2 != END)) {
		if (curNumRuns1 != END) {
			curNumRuns1 = copyUntilGreater(mergeP, runs1P, curNumRuns2);
		}

		if (curNumRuns2 != END) {
			curNumRuns2 = copyUntilGreater(mergeP, runs2P, curNumRuns1);
		}
	}
}

int copyUntilGreater(FILE* destP, FILE* sourceP, int limit) {
	int num;
	int isRead;
	while(1) {
		int wasRead = fread(&num, sizeof(int), 1, sourceP);
		if (wasRead == 0) { 
			num = END;
			break;
		}
		else if (num <= limit) {
			fwrite(&num, sizeof(int), 1, destP);
		}
		else {
			fseek(sourceP, -(long)sizeof(int), SEEK_CUR); // move cursor before greater number
			break;
		}
	}
	return num;
}

void switchCurRunFile(FILE** curFilePP, FILE* runs1P, FILE* runs2P) {
	if (*curFilePP == runs1P) {
		*curFilePP = runs2P;
	}
	else {
		*curFilePP = runs1P;
	}
}
