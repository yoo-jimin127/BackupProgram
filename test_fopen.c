#include <stdio.h>
#include <string.h>

int main (void) {
	FILE *fptr1 = NULL;
	FILE *fptr2 = NULL;
	char buf[300];

	char copy[] = "backup_directory/fopen_test.txt";
	fptr1 = fopen(copy, "r");
	if (fptr1 == NULL) {
		printf("fptr1 : fopen error\n");
		return 0;
	}
	
	char paste[] = "paste.txt";
	fptr2 = fopen(paste, "w");
	if (fptr2 == NULL) {
		printf("fptr2 : fopen error\n");
		return 0;
	}

	while (feof(fptr1) == 0) {
		int count = fread(buf, sizeof(char), 300, fptr1);
		fwrite(buf, sizeof(char), count, fptr2);
		memset(buf, 0, 300);
	}

	fclose(fptr1);
	fclose(fptr2);

	/*
	else {
		char *content = fgets(buf, 300, fptr);
		printf("fgets return : %s\n", content);
	}*/
	return 0;
}
