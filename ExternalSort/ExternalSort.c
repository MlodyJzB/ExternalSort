#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../ExternalSort/ExternalSort.h"

#define END INT_MAX
#define BEGINNING INT_MIN

#define TRUE 1
#define FALSE 0

void sort(FILE* sourceP, FILE* destinationP) {
	int isSorted = FALSE;

	FILE* mergeP;
	openMergeFile(&mergeP, "w");
	txtToMergeFile(sourceP, mergeP);
	fclose(mergeP);

	do {
		FILE* runs1P;
		FILE* runs2P;
		openRunsFiles(&runs1P, &runs2P,"w");
		openMergeFile(&mergeP, "r");

		mergeToRunsFiles(mergeP, runs1P, runs2P);

		closeRunsFiles(runs1P, runs2P);
		fclose(mergeP);


		openRunsFiles(&runs1P, &runs2P, "r");
		openMergeFile(&mergeP, "w");

		isSorted = runsToMergeFile(mergeP, runs1P, runs2P);

		closeRunsFiles(runs1P, runs2P);
		fclose(mergeP);
	} while (isSorted == FALSE);

	openMergeFile(&mergeP, "r");
	mergeToTxtFile(destinationP, mergeP);
	fclose(mergeP);
}

void openRunsFiles(FILE** runs1PP, FILE** runs2PP, char mode[2]) {
	if (fopen_s(runs1PP, "runs1.bin", mode) != 0) {
		printf("Missing runs1.bin");
		exit(1);
	}
	if (fopen_s(runs2PP, "runs2.bin", mode) != 0) {
		printf("Missing runs1.bin");
		exit(1);
	}
}

void closeRunsFiles(FILE* runs1P, FILE* runs2P) {
	fclose(runs1P);
	fclose(runs2P);
}

void openMergeFile(FILE** mergePP, char mode[2]) {
	if (fopen_s(mergePP, "merge.bin", mode) != 0) {
		printf("Missing merge.bin");
		exit(1);
	}
}

void txtToMergeFile(FILE* sourceP, FILE* mergeP) {
	int num;
	while (fscanf_s(sourceP, "%d", &num) != EOF) {
		fwrite(&num, sizeof(int), 1, mergeP);
	}
}

void switchCurRunFile(FILE** curFilePP, FILE* runs1P, FILE* runs2P) {
	if (*curFilePP == runs1P) {
		*curFilePP = runs2P;
	}
	else {
		*curFilePP = runs1P;
	}
}

int runsToMergeFile(FILE* mergeP, FILE* runs1P, FILE* runs2P) {
	int curNumRuns1 = BEGINNING;
	int curNumRuns2 = BEGINNING;
	int iter = 0;

	while ((curNumRuns1 != END)||(curNumRuns2 != END)) {
		if (curNumRuns1 != END) {
			curNumRuns1 = copyUntilGreater(mergeP, runs1P, curNumRuns2);
		}

		if (curNumRuns2 != END) {
			curNumRuns2 = copyUntilGreater(mergeP, runs2P, curNumRuns1);
		}
		iter++;
	}
	if (iter > 2) {
		return FALSE;
	}
	else {
		return TRUE;
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

void mergeToRunsFiles(FILE* mergeP, FILE* runs1P, FILE* runs2P) {
	int num;
	int prevNum = INT_MIN;
	FILE* curFileP = runs1P;

	while (fread(&num, sizeof(int), 1, mergeP) != 0) {
		if (num < prevNum) {
			switchCurRunFile(&curFileP, runs1P, runs2P);
		}

		fwrite(&num, sizeof(int), 1, curFileP);
		prevNum = num;
	}
}

void mergeToTxtFile(FILE* destP, FILE* mergeP) {
	int num;
	while (fread(&num, sizeof(int), 1, mergeP) != 0) {
		fprintf(destP, "%d ", num);
	}
}