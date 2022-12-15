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

void txtToRunsFiles(FILE* sourceP, FILE* runs1, FILE* runs2) {
	int num;
	int prevNum = INT_MIN;

	while (fscanf_s(sourceP, "%d", &num) != EOF) {
	
	}
}

void openRunFiles(FILE** runs1PP, FILE** runs2PP) {
	if (fopen_s(*runs1PP, "runs1.bin", "w+") != 0) {
		exit(1);
	}
	if (fopen_s(*runs2PP, "runs2.bin", "w+") != 0) {
		exit(1);
	}
}

