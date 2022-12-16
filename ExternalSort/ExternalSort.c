#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../ExternalSort/ExternalSort.h"

void sort(FILE *sourceP, FILE *destinationP) {
	FILE* runs1P;
	FILE* runs2P;

	openRunFiles(&runs1P, &runs2P, "r");
	txtToRunsFiles(sourceP, runs1P, runs2P);

	fclose(runs1P);
	fclose(runs2P);
}

void openRunFiles(FILE** runs1PP, FILE** runs2PP, char mode[2]) {
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
	int curNumRuns1 = INT_MIN;
	int curNumRuns2 = INT_MIN;
	int limit;

	while ((curNumRuns1 != INT_MAX)||(curNumRuns2 != INT_MAX)) {
		if (curNumRuns1 != INT_MAX) {
			if (curNumRuns1 != INT_MIN) {
				fwrite(&curNumRuns1, sizeof(int), 1, mergeP);
			}
			curNumRuns1 = copyUntilGreater(mergeP, runs1P, curNumRuns2);
		}

		if (curNumRuns2 != INT_MAX) {
			if (curNumRuns2 != INT_MIN) {
				fwrite(&curNumRuns2, sizeof(int), 1, mergeP);
			}
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
			num = INT_MAX;
			break;
		}
		else if (num <= limit) {
			fwrite(&num, sizeof(int), 1, destP);
		}
		else {
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
