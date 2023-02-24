all: lab27.o Lab26.o
	gcc lab27.o Lab26.o -o prog
lab27.o : lab27.c lab26.h struct.h
	gcc -c lab27.c
Lab26.o : Lab26.c lab26.h struct.h
	gcc -c Lab26.c
