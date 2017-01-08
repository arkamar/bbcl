/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_ONLINE		"\x1b[1;32m"
#define COLOR_AWAY		"\x1b[1;33m"
#define COLOR_OFFLINE	"\x1b[1;31m"
#define COLOR_RESET		"\x1b[0m"
#define CLEAR_LINE		"\x1b[0K"
#define CLEAR_PAGE		"\x1b[0J"
#define GO_TOP				"\x1b[1H"

struct node {
	struct node * next;
	struct node * prev;
	size_t len;
	char name[];
};

static struct node * front = NULL;

static char *
endname(char * name, const char end) {
	char * ob = strchr(name, end);
	if (ob)
		ob[0] = '\0';
	return ob;
}

static char *
getname(struct node * node) {
	return node->name;
}

static struct node *
find(const char * name, struct node ** ret) {
	struct node * n = front;
	while (n) {
		int comparison = strcasecmp(name, getname(n));
		if (ret && comparison > 0)
			*ret = n;
		if (comparison < 0)
			return NULL;
		if (comparison == 0)
			break;
		n = n->next;
	}
	return n;
}

static int
add(const char * name) {
	size_t len = strlen(name) + 1;
	struct node * la = NULL;
	if (find(name, &la))
		return 1;
	struct node * new = malloc(sizeof(struct node) + len);
	if (new == NULL) {
		perror("Cannont allocate memmory");
		return -1;
	}
	memcpy(new->name, name, len);

	new->prev = la;
	if (la != NULL) { /* I am in middle */
		new->next = la->next;
		la->next = new;
	} else { /* front */
		new->next = front;
		front = new;
	}

	if (new->next)
		new->next->prev = new;

	return 0;
}

static int
away(const char * name) {
	return 0;
}

static int
delete(const char * name) {
	struct node * n = find(name, NULL);
	if (n) {
		struct node * next = n->next;
		struct node * prev = n->prev;
		if (next != NULL)
			next->prev = prev;

		if (prev == NULL)
			front = next;
		else
			prev->next = next;

		free(n);
	}
	return 0;
}

static void
print() {
	struct node * n;
	n = front;
	while (n) {
		char * name = getname(n);
		printf("%s" CLEAR_LINE "\n", name);
		n = n->next;
	}
}

static void
clear() {
	struct node * n;
	while (front) {
		n = front->next;
		free(front);
		front = n;
	}
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
		printf(GO_TOP);
		print();
		printf(CLEAR_PAGE);
		fflush(stdout);
	}
	clear();
	free(buff);
	return 0;
}
