all:
	cc -I -std=gnu11 -Wall -Wextra -Werror -O2 vectors.c rays.c materials.c collisions.c bmpwriter.c main.c -o main -lmingw32