#include <stdio.h>
#include <stdlib.h>
#include "../ExternalSort/ExternalSort.h"

int main()
{
	FILE* sourceP;

	if (fopen_s(&sourceP, "numbers.txt", "r+") != 0) {
		exit(1);
	}

	//FILE* runs1P;
	//FILE* runs2P;

	//openRunFiles(&runs1P, &runs2P);

	//txtToRunsFiles(sourceP, runs1P, runs2P);

	//fclose(runs1P);
	//fclose(runs2P);
	//fopen_s(runs1P, "runs1.bin", "r");

	//int num;
	//while (fread(&num, sizeof(int), 1, runs1P) != 0) {
	//	printf("%d ", num);
	//}

	//fclose(runs1P);

	fclose(sourceP);
}
