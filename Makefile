all:
	gcc -c main.c -Wall -Wextra
	gcc -o main main.c -lm
	gcc main.c -o main -lm
rem:
	rm main main.o

