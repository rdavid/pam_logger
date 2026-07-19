# SPDX-FileCopyrightText: 2025-2026 David Rabkin
# SPDX-License-Identifier: 0BSD
CFLAGS = -fPIC -fno-stack-protector -Wall -Wextra -Werror -O3
LIBDIR ?= /lib/i386-linux-gnu/security
MODULE = pam_logger.so

.PHONY: all clean install main test

all: main.o

main: main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

install: main.o
	sudo ld -x --shared -o $(LIBDIR)/$(MODULE) main.o

clean:
	rm -f main.o

test:
