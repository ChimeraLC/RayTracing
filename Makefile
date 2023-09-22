all:
	cc -I -std=gnu11 -Wall -Wextra -Werror -O2 main.c vectors.c bmpwriter.c -o main -lmingw32