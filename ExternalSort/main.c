#include <stdio.h>
#include <stdlib.h>
#include "../ExternalSort/ExternalSort.h"

int main()
{
	FILE* sourceP;

	if (fopen_s(&sourceP, "numbers.txt", "r+") != 0) {
		exit(1);
	}

	FILE* runs1P;
	FILE* runs2P;

	openRunSFiles(&runs1P, &runs2P, "w");

	txtToRunsFiles(sourceP, runs1P, runs2P);

	fclose(sourceP);
	fclose(runs1P);
	fclose(runs2P);

	openRunFiles(&runs1P, &runs2P, "r");

	FILE* mergeP;
	if (fopen_s(&mergeP, "merge.bin", "w") != 0) {
		exit(1);
	}

	runsToMergeFile(mergeP, runs1P, runs2P);

	fclose(runs1P);
	fclose(runs2P);
	fclose(mergeP);

	fopen_s(&mergeP, "merge.bin", "r");

	int num;
	while (fread(&num, sizeof(int), 1, mergeP) != 0) {
		printf("%d ", num);
	}

	fclose(mergeP);
}
