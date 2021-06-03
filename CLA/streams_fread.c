#include <stdio.h>
#include <errno.h>

/**
 * Main.
 * Read a file using fread.
 */
int main(int argc, char *argv[]) {
	
	FILE *inp;
	unsigned char buffer[1024]; /* 1 kilobyte */
	int read;

	//check arguments
	if(argc != 2) {
		printf("usage: ./pname file_name\n");
		return 1;
	}

	//check if possible open the file
	if((inp = fopen(argv[1] ,"rb")) == NULL) {
		printf("Cannot open the file %s\n", argv[1]);
		return 2;
	}

	do {
		//read buffer size at time
		read = fread(buffer, 1, sizeof(buffer), inp);
		// print char by char
		for(int i = 0; i < read; i++) {
			printf("%c",buffer[i]);
		}

	} while (read > 0);

	fclose(inp);

	return 0;
}
