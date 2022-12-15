#include <stdio.h>
#include <stdlib.h>
#include "../ExternalSort/ExternalSort.h"

int main()
{
	FILE* sourceP;

	if (fopen_s(&sourceP, "numbers.txt", "r+") != 0) {
		exit(1);
	}

	txtToRunsFiles(sourceP, NULL, NULL);

	fclose(sourceP);
}
