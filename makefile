
CC = gcc
FLAGS = -Wall

all:frequency

frequency:main.o frequency.o
	$(CC) $(FLAGS) -o $@ $^
main.o:main.c
	$(CC) $(FLAGS) -o $@ -c $^
frequency.o:frequency.c
	$(CC) $(FLAGS) -o $@ -c $^
clean:
	rm *.o frequency
