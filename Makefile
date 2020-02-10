# See LICENSE file for copyright and license details.
# SPDX-License-Identifier: MIT

PREFIX ?= /usr

CFLAGS ?= -O2 -pipe
CFLAGS += -Wall -pedantic
CFLAGS += -Werror=implicit-function-declaration

NAME := bbcl
all: $(NAME)

clean:
	$(RM) $(NAME)

install: all
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 $(NAME) $(DESTDIR)$(PREFIX)/bin

.PHONY: all clean install
