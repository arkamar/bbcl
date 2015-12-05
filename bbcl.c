#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[]) {
	char * buff = NULL;
	size_t size = 0;
	char * ob;
	char * name;
	while (getline(&buff, &size, stdin) > 0) {
		if (size < 21)
			continue;
		switch (buff[18]) {
		case '!':
			name = buff + 21;
			ob = strchr(name, '(');
			if (!ob)
				continue;
			ob[0] = '\0';
			break;
		case 'v':
			name = buff + 19;
			ob = strchr(name, '\n');
			if (ob)
				ob[0] = '\0';
			break;
		default:
			continue;
		}
		printf("%s\n", name);
	}
	free(buff);
	return 0;
}
