#include <stdio.h>
#include <stdlib.h>
#include "../ExternalSort/ExternalSort.h"

int main()
{
	FILE* sourceP;

	if (fopen_s(&sourceP, "numbers.txt", "r") != 0) {
		printf("Missing numbers.txt");
		exit(1);
	}

	FILE* destP;
	if (fopen_s(&destP, "sortedNumbers.txt", "w") != 0) {
		printf("Missing sortedNumbers.txt");
		exit(1);
	}

	sort(sourceP, destP);

	fclose(sourceP);
	fclose(destP);
}
