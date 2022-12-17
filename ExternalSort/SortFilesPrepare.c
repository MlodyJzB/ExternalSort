#include <stdio.h>
#include <stdlib.h>

#include "../ExternalSort/SortFilesPrepare.h"

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

void mergeToTxtFile(FILE* destP, FILE* mergeP) {
	int num;
	while (fread(&num, sizeof(int), 1, mergeP) != 0) {
		fprintf(destP, "%d ", num);
	}
}

void clearMergeAndRuns() {
	clearFile("merge.bin");
	clearFile("runs1.bin");
	clearFile("runs2.bin");
}

void clearFile(const char* fileName) {
	FILE* fileP;
	if (fopen_s(&fileP, fileName, "w") != 0) {
		printf("Missing %s.", fileName);
		exit(1);
	}
	fclose(fileP);
}