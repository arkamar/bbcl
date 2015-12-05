#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *
endname(char * name, const char end) {
	char * ob = strchr(name, end);
	if (ob)
		ob[0] = '\0';
	return ob;
}

int
main(int argc, char *argv[]) {
	char * buff = NULL;
	size_t size = 0;
	char * name;
	while (getline(&buff, &size, stdin) > 0) {
		if (size < 21)
			continue;
		switch (buff[18]) {
		case '!':
			name = buff + 21;
			if (!endname(name, '('))
				continue;
			break;
		case 'v':
			name = buff + 19;
			endname(name, '\n');
			break;
		default:
			continue;
		}
		printf("%s\n", name);
	}
	free(buff);
	return 0;
}
