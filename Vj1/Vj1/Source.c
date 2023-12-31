#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)

typedef struct _student {
	char name(MAX_SIZE);
	char surname(MAX_SIZE);
	double points;
}Student;

int main() {
	int noRows = 0;
	FILE*filePointer = NULL;
	char buffer(MAX_LINE) = { 0 };

	filePointer = fopen("students.txt", "r");
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(filePointer)) {
		fgets(buffer, MAX_LINE, filePointer);
		noRows++;
	}


	printf("%d", noRows);
	fclose(filePointer);

	return EXIT_SUCCESS;
}