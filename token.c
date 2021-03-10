#include <stdio.h>
#include <string.h>

int main (void) {
	char s1[512] = "/home/ubuntu/lsp_winter_backup_program/backup_program/test1.txt_210310225317";

	char *ptr = strtok(s1, "_");
	char *ptr2 = strtok(NULL, "_");

	printf("ptr : %s\n", ptr);
	printf("ptr2 : %s\n", ptr2);

	return 0;
}
