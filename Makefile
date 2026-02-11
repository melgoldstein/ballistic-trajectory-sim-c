CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -O2
trajectory: main.c
	$(CC) $(CFLAGS) main.c -lm -o trajectory
clean:
	rm -f trajectory trajectory.exe
