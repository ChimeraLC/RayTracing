all:
	cc -I -std=gnu11 -Wall -Wextra -Werror -O2 main.c collisions.c rays.c vectors.c bmpwriter.c -o main -lmingw32