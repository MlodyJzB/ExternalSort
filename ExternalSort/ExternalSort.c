#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../ExternalSort/ExternalSort.h"

void sort(FILE *sourceP, FILE *destinationP) {
	FILE* runs1P;
	FILE* runs2P;

	openRunFiles(&runs1P, &runs2P);

	txtToRunsFiles(sourceP, runs1P, runs2P);

	fclose(runs1P);
	fclose(runs2P);
}

void openRunFiles(FILE** runs1PP, FILE** runs2PP) {
	if (fopen_s(runs1PP, "runs1.bin", "w") != 0) {
		exit(1);
	}
	if (fopen_s(runs2PP, "runs2.bin", "w") != 0) {
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

void switchCurRunFile(FILE** curFilePP, FILE* runs1P, FILE* runs2P) {
	if (*curFilePP == runs1P) {
		*curFilePP = runs2P;
	}
	else {
		*curFilePP = runs1P;
	}
}
