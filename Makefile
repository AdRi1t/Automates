CC=gcc
EXEC=DetMin
DetMin: main.o automate.o
	gcc -o DetMin main.o automate.o
main.o: main.c automate.h 
	gcc -o main.o -c main.c -Wall -ansi -pedantic
automate.o: automate.c
	gcc -o automate.o -c automate.c -Wall -ansi -pedantic
