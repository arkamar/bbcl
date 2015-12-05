#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_ONLINE		"\x1b[1;32m"
#define COLOR_AWAY		"\x1b[1;33m"
#define COLOR_OFFLINE	"\x1b[1;31m"
#define COLOR_RESET		"\x1b[0m"

static char *
endname(char * name, const char end) {
	char * ob = strchr(name, end);
	if (ob)
		ob[0] = '\0';
	return ob;
}

static int
add(const char * name) {
	printf("+%s\n", name);
	return 0;
}

static int
away(const char * name) {
	printf("-%s\n", name);
	return 0;
}

static int
delete(const char * name) {
	printf("!%s\n", name);
	return 0;
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
			delete(name);
			break;
		case 'v':
			name = buff + 19;
			endname(name, '\n');
			if (buff[17] == '+')
				add(name);
			else
				away(name);
			break;
		default:
			continue;
		}
	}
	free(buff);
	return 0;
}
