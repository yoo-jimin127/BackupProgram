#include <stdio.h>
#include <unistd.h>

void check (int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		printf("argv[%d] : %s \n", i, argv[i]);
	}
}

int main (int argc, char* argv[]) {
	check(argc, argv);
	
//	 for (int i = 0; i < argc; i++) {
//		printf("argv[%d] : %s \n", i, argv[i]);
//	}

//	printf("argc 개수 : %d\n", argc);

	return 0;
}
