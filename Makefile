CC=gcc
EXEC=DetMin

DetMin: main.o automate.o loadAutomate.o
	gcc -o DetMin main.o automate.o loadAutomate.o
main.o: main.c automate.h 
	gcc -o main.o -c main.c -Wall
automate.o: automate.c automate.h 
	gcc -o automate.o -c automate.c -Wall 
loadAutomate.o: loadAutomate.c automate.h 
	gcc -o loadAutomate.o -c loadAutomate.c -Wall 
