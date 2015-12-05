#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_ONLINE		"\x1b[1;32m"
#define COLOR_AWAY		"\x1b[1;33m"
#define COLOR_OFFLINE	"\x1b[1;31m"
#define COLOR_RESET		"\x1b[0m"

struct node {
	struct node * next;
	struct node * prev;
	size_t len;
};

static struct node * front = NULL;
static struct node * rear = NULL;

static char *
endname(char * name, const char end) {
	char * ob = strchr(name, end);
	if (ob)
		ob[0] = '\0';
	return ob;
}

#define getname(node) \
	((char *)(node + 1))

static int
add(const char * name) {
	size_t len = strlen(name) + 1;
	printf("+%2d:%s\n", len, name);
	struct node * new = malloc(sizeof(struct node) + len);
	if (new == NULL) {
		perror("Cannont allocate memmory");
		return -1;
	}
	memcpy(new + 1, name, len);
	new->next = NULL;
	new->prev = rear;
	if (front == NULL)
		front = new;
	if (rear != NULL)
		rear->next = new;
	rear = new;
	return 0;
}

static int
away(const char * name) {
	printf("-%2d:%s\n", strlen(name), name);
	return 0;
}

static struct node *
find(const char * name) {
	struct node * n = front;
	while (n) {
		if (!strcmp(name, getname(n)))
			break;
		n = n->next;
	}
	return n;
}

static int
delete(const char * name) {
	struct node * n = find(name);
	if (n) {
		struct node * next = n->next;
		struct node * prev = n->prev;
		if (next == NULL)
			rear = prev;
		else
			next->prev = prev;

		if (prev == NULL)
			front = next;
		else
			prev->next = next;

		free(n);
	}
	printf("!%2d:%s\n", strlen(name), name);
	return 0;
}

static void
print() {
	struct node * n;
	n = front;
	while (n) {
		char * name = getname(n);
		printf("name: %s\n", name);
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
	}
	print();
	clear();
	free(buff);
	return 0;
}
