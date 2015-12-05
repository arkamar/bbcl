#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
	char * buff = NULL;
	size_t size = 0;
	while (getline(&buff, &size, stdin) > 0) {
		if (buff[18] == 'v' || buff[18] == '!')
			printf("%s", buff);
	}
	free(buff);
	return 0;
}
